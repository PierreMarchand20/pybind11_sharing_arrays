#include "utility.hpp"
#include <iostream>

namespace py = pybind11;

class VectorContainer {
  private:
    std::vector<double> cpp_vector;
    std::vector<double> python_vector;
    py::array_t<double, py::array::c_style> cpp_pyarray;

  public:
    VectorContainer(size_t dimension, double default_value) : cpp_vector(dimension, default_value) {}

    // Sharing with copy between vector and list
    std::vector<double> vector_to_list_with_copy() const { return cpp_vector; }
    void python_to_cpp_with_copy(const std::vector<double> &python_input) { python_vector = python_input; };

    // Sharing without copy from vector to numpy array, while keeping ownership in c++
    py::array_t<double, py::array::c_style> vector_to_numpy_without_copy_owned_by_cpp() {
        py::array_t<double, py::array::c_style> mat(cpp_vector.size(), cpp_vector.data(), py::capsule(cpp_vector.data()));
        return mat;
    }

    // Sharing without copy from vector to numpy array, while transfering ownership from c++ to python
    py::array_t<double, py::array::c_style> vector_to_numpy_without_copy_owned_by_python() {
        return as_pyarray(std::move(cpp_vector));
    }

    // Sharing without copy from numpy array to vector, while keeping ownership in python
    // To get the data from python, avoiding a copy into a std::vector, one can use std::span for C++20, or directly pybind11::array which is relatively similar to std::vector
    void numpy_to_cpp_without_copy_owned_by_python(py::array_t<double, py::array::c_style> python_input) { cpp_pyarray = python_input; };

    void numpy_to_cpp_without_copy_owned_by_python_const(const py::array_t<double, py::array::c_style> &python_input) { cpp_pyarray = python_input; };

    // Sharing without copy from numpy array to vector, while transfering ownership from python to c++
    // I do not know how to do it...

    // Modifying
    void change_cpp_vector() { cpp_vector.back() = 10; }
    void change_python_vector() { python_vector.back() = 10; }
    void change_cpp_pyarray() {
        cpp_pyarray.mutable_at(cpp_pyarray.size() - 1) = 10;
    }

    // Printing
    void print_cpp_vector(std::string preoutput) const {
        if (!cpp_vector.empty()) { // this may not always work, see https://stackoverflow.com/a/17735913/5913047 when cpp_vector is moved
            std::cout << preoutput << "[";
            for (size_t i = 0; i < cpp_vector.size() - 1; i++) {
                std::cout << cpp_vector[i] << ",";
            }
            std::cout << cpp_vector[cpp_vector.size() - 1] << "]\n";
        } else
            std::cout << "cpp vector is empty\n";
    }
    void print_python_vector(std::string preoutput) const {
        std::cout << preoutput << "[";
        for (size_t i = 0; i < python_vector.size() - 1; i++) {
            std::cout << python_vector[i] << ",";
        }
        std::cout << python_vector[python_vector.size() - 1] << "]\n";
    }
    void print_cpp_pyarray(std::string preoutput) const {
        std::cout << preoutput << "[";
        for (size_t i = 0; i < cpp_pyarray.size() - 1; i++) {
            std::cout << cpp_pyarray.at(i) << ",";
        }
        std::cout << cpp_pyarray.at(cpp_pyarray.size() - 1) << "]\n";
    }
};

PYBIND11_MODULE(Pybind11ExampleSharingArrays, m) {
    m.doc() = "pybind11 example plugin for sharing arrays";

    py::class_<VectorContainer>(m, "VectorContainer")
        .def(py::init<size_t, double>())
        .def("print_cpp_vector", &VectorContainer::print_cpp_vector)
        .def("print_python_vector", &VectorContainer::print_python_vector)
        .def("print_cpp_pyarray", &VectorContainer::print_cpp_pyarray)
        .def("vector_to_list_with_copy", &VectorContainer::vector_to_list_with_copy)
        .def("python_to_cpp_with_copy", &VectorContainer::python_to_cpp_with_copy)
        .def("numpy_to_cpp_without_copy_owned_by_python", &VectorContainer::numpy_to_cpp_without_copy_owned_by_python)
        .def("numpy_to_cpp_without_copy_owned_by_python_const", &VectorContainer::numpy_to_cpp_without_copy_owned_by_python_const)
        .def("vector_to_numpy_without_copy_owned_by_cpp", &VectorContainer::vector_to_numpy_without_copy_owned_by_cpp)
        .def("vector_to_numpy_without_copy_owned_by_python", &VectorContainer::vector_to_numpy_without_copy_owned_by_python)
        .def("change_cpp_vector", &VectorContainer::change_cpp_vector)
        .def("change_cpp_pyarray", &VectorContainer::change_cpp_pyarray)
        .def("change_python_vector", &VectorContainer::change_python_vector);
}
