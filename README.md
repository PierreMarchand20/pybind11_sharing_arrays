# pybind11_sharing_arrays


## Presentation

This repository offers a few examples on how to share date between python and C++ using [pybind11](https://github.com/pybind/pybind11). In particular, we show how to share data with and without copy, transfering or not the ownership from one language to the other.

## Installation

First, you need to clone this repository with its submodules:

```bash
git clone --recurse-submodules https://github.com/htool-ddm/htool_python.git && cd htool_python
```

In the folder of this repository, do:

```bash
pip install .
```

You can run the example [file](example/run.py) to see the different possibilities displayed, and check the implementation in [main.cpp](src/main.cpp).

## Acknowledgements

Most of the information I used to write these examples come from the documentation of [pybind11](https://github.com/pybind/pybind11) and [pybind/pybind11#1042](https://github.com/pybind/pybind11/issues/1042).
