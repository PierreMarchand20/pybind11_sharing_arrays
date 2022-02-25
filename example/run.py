import Pybind11ExampleSharingArrays
import numpy as np


vector_container = Pybind11ExampleSharingArrays.VectorContainer(10, 1)

# vector_to_list_with_copy
vector_container.print_cpp_vector("Initial cpp vector: ")
python_list = vector_container.vector_to_list_with_copy()
print("cpp vector to python list:", python_list, type(python_list))
python_list.append(2)
print("modification of python list:", python_list)
vector_container.print_cpp_vector("cpp vector not modified: ")

print("")

# python_to_cpp_with_copy
python_list = [2]*3
print("Initial python list: ", python_list)
vector_container.python_to_cpp_with_copy(python_list)
vector_container.print_python_vector("python list to cpp vector:")
vector_container.modify_python_vector()
vector_container.print_python_vector("modification of cpp vector:")
print("python list not modified: ", python_list)

print("")

# vector_to_numpy_without_copy_owned_by_cpp
vector_container.print_cpp_vector("Initial cpp vector: ")
numpy_array = vector_container.vector_to_numpy_without_copy_owned_by_cpp()
print("cpp vector to numpy array without copy:",
      numpy_array, type(numpy_array), numpy_array.shape)
numpy_array[0] = 10
print("modification of numpy array:", numpy_array)
vector_container.print_cpp_vector("cpp vector modified: ")
del numpy_array
print("delete numpy array")
vector_container.print_cpp_vector("cpp vector still here, owned by cpp: ")

print("")

# vector_to_numpy_without_copy_owned_by_cpp
vector_container.print_cpp_vector("Initial cpp vector: ")
numpy_array = vector_container.vector_to_numpy_without_copy_owned_by_python()
print("cpp vector to numpy array and owned by cpp:",
      numpy_array, type(numpy_array), numpy_array.shape)
numpy_array[0] = 1
print("modification of numpy array:", numpy_array)
vector_container.print_cpp_vector("cpp vector modified: ")
del vector_container
print("delete pybind11 object")
print("numpy array still here, owned by python:", numpy_array)

print("")

# numpy_to_cpp_without_copy_owned_by_python
vector_container = Pybind11ExampleSharingArrays.VectorContainer(10, 1)
print("Initial numpy array:", numpy_array)
vector_container.numpy_to_cpp_without_copy_owned_by_python(numpy_array)
vector_container.print_cpp_pyarray_vector("numpy array to cpp pyarray:")
vector_container.modify_cpp_pyarray()
vector_container.print_cpp_pyarray_vector("modification of cpp pyarray:")
print("numpy array modified: ", numpy_array)
del vector_container
print("delete pybind11 object")
print("numpy array still here, owned by python:", numpy_array)
