# model
model = Model()
i1 = Input("op1", "TENSOR_INT32", "{8}")
axis = Int32Scalar("axis", 0)
num_out = Int32Scalar("num_out", 8)
i2 = Output("op2", "TENSOR_INT32", "{1}")
i3 = Output("op3", "TENSOR_INT32", "{1}")
i4 = Output("op4", "TENSOR_INT32", "{1}")
i5 = Output("op5", "TENSOR_INT32", "{1}")
i6 = Output("op6", "TENSOR_INT32", "{1}")
i7 = Output("op7", "TENSOR_INT32", "{1}")
i8 = Output("op8", "TENSOR_INT32", "{1}")
i9 = Output("op9", "TENSOR_INT32", "{1}")

model = model.Operation("SPLIT", i1, axis, num_out).To([i2, i3, i4, i5, i6, i7, i8, i9])

# Example 1. Input in operand 0,
input0 = {i1: # input 0
          [1, 2, 3, 4, 5, 6, 7, 8]}

output0 = {
    i2: # output 0
          [1],
    i3: # output 1
          [2],
    i4: # output 2
          [3],
    i5: # output 3
          [4],
    i6: # output 4
          [5],
    i7: # output 5
          [6],
    i8: # output 6
          [7],
    i9: # output 7
          [8]}

# Instantiate an example
Example((input0, output0))
