import tensorflow as tf

tf.compat.v1.disable_eager_execution()

in_ = tf.compat.v1.placeholder(dtype=tf.float32, shape=(4, 4), name="Hole")
op_ = tf.compat.v1.reshape(in_, shape=[2, 2, 2, 2])
