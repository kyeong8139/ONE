# automatically generated by the FlatBuffers compiler, do not modify

# namespace: tflite

import flatbuffers


class SquareOptions(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAsSquareOptions(cls, buf, offset):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = SquareOptions()
        x.Init(buf, n + offset)
        return x

    # SquareOptions
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)


def SquareOptionsStart(builder):
    builder.StartObject(0)


def SquareOptionsEnd(builder):
    return builder.EndObject()
