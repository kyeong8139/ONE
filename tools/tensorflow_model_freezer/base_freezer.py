# Copyright (c) 2018 Samsung Electronics Co., Ltd. All Rights Reserved
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os
import sys
import traceback
import tensorflow as tf
import model_freezer_util as util


class Tensor(object):
    def __init__(self, shape, dtype=tf.float32, const_val=None):
        '''
        Keyword arguments:
        shape -- shaps in a form of list, e.g., 3x2x4 tensor's shape => [3,2,4]. shape of a scalar is []
        dtype -- type of values in this Tensor
        const_val -- if this Tensor is const, provide this
        '''
        self._shape = shape
        self._const_val = const_val
        self._dtype = dtype

    def getShape(self):
        return self._shape

    def getConstVal(self):
        return self._const_val

    def getDType(self):
        return self._dtype


class BaseFreezer(object):
    def __init__(self, path):
        # files generated by child class will be stored under this path.
        self.root_output_path = path

    def getTestCases(self):
        ''' abstract class
            override method should return dic containing test cases '''
        raise NotImplementedError("please implement this")

    def getOutputDirectory(self):
        ''' abstract class
            override method should return directory under self.root_output_path where all pb, pbtxt, checkpoing, tensorboard log are saved '''
        raise NotImplementedError("please implement this")

    def buildModel(self, sess, test_case_tensor, tc_name):
        ''' abstract class
            override this method to define models when getTestCases() is defined.
            this method returns ( input_node_list, output_node_list ) after building a model with all variables set '''
        raise NotImplementedError("please implement this")

    def createTFInput(self, tensor, input_list):
        '''
        create TensorFlow tensor and if it is a placeholder, put it into input_list

        keyword argument:
        tensor -- base_freezer.Tensor
        input_list -- vector
        '''
        if (util.isScalar(tensor)):  # check if scalar
            if (tensor.getConstVal() == None):
                tf_tensor = tf.placeholder(shape=[], dtype=tensor.getDType())
                input_list.append(tf_tensor)
            else:
                tf_tensor = tf.constant(
                    value=tensor.getConstVal(), dtype=tensor.getDType())
        else:
            if (tensor.getConstVal() == None):
                tf_tensor = tf.placeholder(
                    shape=tensor.getShape(), dtype=tensor.getDType())
                input_list.append(tf_tensor)
            else:
                tf_tensor = tf.constant(
                    shape=tensor.getShape(),
                    value=tensor.getConstVal(),
                    dtype=tensor.getDType())

        return tf_tensor

    def saveRelatedFiles(self, sess, input_node_list, output_node_list, fn_prefix):
        # saves pb, pbtxt, chpt files and then freeze graph under top_node_name into directory
        # produce pb, pbtxt, and ckpt files
        (pb_path, pbtxt_path, checkpoint_path) = util.savePbAndCkpt(
            sess, self.getOutputDirectory(), fn_prefix)

        print("")
        print("# 1. Created Tensorflow model files :\n\t-{}\n\t-{}\n\t-{}\n".format(
            pb_path, pbtxt_path, checkpoint_path))

        # produce frozen files
        # include only nodes below softmax node. nodes for gradient descent (reduce_mean, GradientDescentOptimizer, ...) will not be included
        sess.close()

        output_node_name = fn_prefix
        (frozen_pb_path, frozen_pbtxt_path) = util.freezeGraph(pb_path, checkpoint_path,
                                                               output_node_name)

        print("")
        print("# 2. Freeze() Finished. Created :")
        print("\t-{}\n\t-{}\n".format(frozen_pb_path, frozen_pbtxt_path))

        self.generateTensorboardLog(pb_path, frozen_pb_path, fn_prefix)
        print("")

        # generate tflite file.
        # code from https://www.tensorflow.org/lite/convert/python_api
        tflite_path = os.path.join(self.getOutputDirectory(), fn_prefix + ".tflite")
        try:
            # sometime, name of node "input" contains "input:0". Let's remove ":0"
            pure_name = lambda complex_name: complex_name.name.split(":")[0]

            # returns list after mapping pure_name(element in tensor_list)
            name_list = lambda tensor_list: map(pure_name, tensor_list)

            converter = tf.contrib.lite.TFLiteConverter.from_frozen_graph(
                frozen_pb_path, name_list(input_node_list), name_list(output_node_list))
            tflite_model = converter.convert()
            open(tflite_path, "wb").write(tflite_model)
            print("# 3. TensorFlow Lite Converter : converted PB file to {}\n".format(
                tflite_path))
        except Exception:
            print("# 3. TensorFlow Lite Converter failed\n")
            print(traceback.format_exc())

        return (pb_path, frozen_pb_path, tflite_path)

    def generateTensorboardLog(self, pb_path, frozen_pb_path, fn_prefix):
        ''' generating tensorboard logs to compare original pb and frozen pb '''
        tensorboardLogDir = util.generateTensorboardLog(
            [pb_path, frozen_pb_path], ['original', 'frozen'],
            os.path.join(self.getOutputDirectory(), ".tensorboard", fn_prefix))

        print("")
        print(
            "\t# Tensorboard: You can view original graph and frozen graph with tensorboard."
        )
        print("\t  Run the following:")
        print("\t  $ tensorboard --logdir={} ".format(tensorboardLogDir))

    def createSaveFreezeModel(self):
        ''' method that actually called by main() function. '''

        test_cases = self.getTestCases()

        # when there are defined test cases
        if test_cases != None:
            for tc_name in test_cases:

                # without this, graph used previous session is reused : https://stackoverflow.com/questions/42706761/closing-session-in-tensorflow-doesnt-reset-graph
                tf.reset_default_graph()

                # TODO-nnfw session life cycle here is too tangled
                sess = tf.Session()

                print("")
                print("------------ Generating files for {} ------------".format(tc_name))
                print("# files will be saved into " + self.getOutputDirectory())

                # build model
                (input_node_list, output_node_list) = self.buildModel(
                    sess, test_cases.get(tc_name), tc_name)

                # Now, save to proto buffer format and checkpoint
                (pb_path, frozen_pb_path, tflite_path) = self.saveRelatedFiles(
                    sess, input_node_list, output_node_list, tc_name)

                sess.close()
        # when there is not test cases but the model itself
        else:
            # without this, graph used previous session is reused : https://stackoverflow.com/questions/42706761/closing-session-in-tensorflow-doesnt-reset-graph
            tf.reset_default_graph()

            # TODO-nnfw session life cycle here is too tangled
            sess = tf.Session()

            print("")
            print("------------ Generating files for {} ------------".format(tc_name))
            print("# files will be saved into " + self.getOutputDirectory())

            # build model
            (input_node_list, output_node_list) = self.buildModel(
                sess, test_cases.get(tc_name), tc_name)

            # Now, save to proto buffer format and checkpoint
            (pb_path, frozen_pb_path, tflite_path) = self.saveRelatedFiles(
                sess, input_node_list, output_node_list, tc_name)

            sess.close()
