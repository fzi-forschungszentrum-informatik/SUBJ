# SUBJ - Subjective Logic Library

The **SUBJ** library provides types and functions for using subjective logic in your projects. The library is written in C++, and also includes Python bindings. The corresponding Python module is called **pySUBJ**

The concepts used here are mainly based on the book "Subjective Logic" from Audun Jøsang.[^1]

SUBJ is currently under development. While basic types and functionality exists, there are still some operators, advanced concepts and improvements to be released in the next updates.


## Installation of SUBJ

Currently the installation is only tested on Ubuntu (20.04, 22.04 and 24.04). SUBJ can possibly be built on other platforms, it just hasn't been tried.


### Requirements and Dependencies

SUBJ has the following requirements:
* SUBJ uses C++11 language constructs
* [CMake](https://cmake.org) is used for building SUBJ

SUBJ uses Eigen to represent and compute opinions internally. Currently, the only dependency of SUBJ is: 
* [Eigen 3.3](https://eigen.tuxfamily.org) 

Installation of the requirements and dependencies can be done via:
```bash
sudo apt update
sudo apt install cmake g++ python3-dev libeigen3-dev pybind11-dev
```


### Building SUBJ

SUBJ follows the standard cmake building procedure. Make sure the dependencies are met and you are using a C++11-compatible compiler. If you want to install the library to a local folder you can pass `-DCMAKE_INSTALL_PREFIX=../export` to `cmake` with `../export` being the local folder. For building a shared library just use `-DBUILD_SHARED_LIBS=On` as additional option for `cmake`. Then, issue the following commands: 

```bash
git clone https://github.com/fzi-forschungszentrum-informatik/SUBJ.git
cd subj
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../export -DBUILD_SHARED_LIBS=On
make
make install
```


## Installation of pySUBJ

As well as for SUBJ, the installation of pySUBJ is currently only tested on Ubuntu 20.04, 22.04 and 24.04. But pySUBJ can very well be built on other platforms, it is just not tested.


### Requirements and Dependencies

If you want to build and install pySUBJ you will need: 
* [Python3](https://www.python.org) is needed for building the Python bindings.
* [Scikit-build](https://github.com/scikit-build/scikit-build) for packaging and installing the Python bindings.
* [venv](https://docs.python.org/3/library/venv.html) is optionally used for creating a virtual environment. You may use other alternatives or even no virtual environments (which is not recommended).

Python bindings are realized with the help of pybind11. Also beliefs and base rates can be passed as either plain Python lists or numpy arguments. Thus, pySUBJ has these additional dependencies:
* [pybind11](https://github.com/pybind/pybind11)
* [numpy](https://numpy.org/)

For installation of the requirements and dependencies it is highly recommended to use some kind of virtual environment. We use venv in the following, but you may use whatever suits you best. `%VENV_PATH` must be set to the folder, where your environment should be stored. Then the installation of requirements and dependencies of pySUBJ can be done with:

```bash
sudo apt update
sudo apt install cmake g++ python3-dev libeigen3-dev pybind11-dev python3-venv 
python3 -m venv %VENV_PATH%
source %VENV_PATH%/bin/activate
pip install scikit-build numpy
```


### Building pySUBJ

pySUBJ can be built with the following commands. Make sure the requirements and dependencies are met. Also, you need to activate your environment if you installed `scikit-build` in a virtual environment ([see above commands](#requirements-and-dependencies-1)). Again, the `%VENV_PATH` in the commands below should be set to the folder of the environment.

```bash
git clone https://github.com/fzi-forschungszentrum-informatik/SUBJ.git
source %VENV_PATH%/bin/activate
pip install subj/.
```


## Examples

You can find C++, as well as Python examples in the `examples` folder.


### SUBJ

After building SUBJ ([see above](#installation-of-subj)) the examples can be run with: 

```bash
cd subj/build/examples
./subj_example
```


### pySUBJ

When pySUBJ has been built and installed ([see here](#installation-of-pysubj)) run the examples by executing:

```bash
cd subj/examples
python3 pysubj_example.py
```


## License
SUBJ is provided under the MIT license. The license can be found in the LICENSE file. By usage, distribution or contribution, you agree to the terms and conditions of this license.


[^1]: [Jøsang, Audun. Subjective logic. Vol. 3. Cham: Springer, 2016.](https://doi.org/10.1007/978-3-319-42337-1)
