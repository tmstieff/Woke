# Woke
<a href="https://travis-ci.org/tmstieff/Woke"><img alt="Travis CI Build" src="https://travis-ci.org/tmstieff/Woke.svg?branch=master"></a>
[![Build status](https://ci.appveyor.com/api/projects/status/ixwvi3wi6mfosm9j/branch/master?svg=true)](https://ci.appveyor.com/project/tmstieff/woke/branch/master)



A native multiplatform REST client with grand ambitions and limited scope.

<p align="center">
  <img width="900" alt="Woke client" src="https://i.imgur.com/qBwiKJ4.png">
</p>

## Binaries
Releases are currently provided for Linux as AppImages and for Windows as a portable ZIP or executable installer. Mac builds will come shortly.

<a href="https://woke.rest/download">Windows and Linux</a>

## Features
* Supports most basic HTTP request types
* Focus on Python scripting
* Raw header input
* Request body input
* Response body JSON parser
* Simple request history
* Simple request saving

## Scripting

The pre and post tabs can be used to retrieve and set variables for your project. For instance, you may wish to login, capture the authentication token from the response body / headers, and declare it as a project variable to be used in the headers of another request. The script tabs run a full python interpreter, so any standard Python libraries are available to be imported. The following additional functions are used to set and retrieve variables. The get is scoped from most to least specific.

```
get_var("var_name")
set_local_var("var_name", "local_value")
set_project_var("var_name", "project_value")
set_global_var("var_name", "global_value")
```

Because the additional methods are evaluated with Python, any valid Python statement can be evaluted, and the result of the evaluation will be assigned as the value of the variable. However, for now, everything needs to be evaluated as string. As an example, you can add the following to a "Post-Request Script" for a login request.

```
set_project_var('token', body['token'])
```

In another request, in the request headers you can add:

```
Authorization: Bearer {{token}}
```

## Ambitions
* NeoVim editor built in
* Project management options
* Parsing of Swagger, JSON Schema, and other applicable REST specifications
* Support for various authentication protocols

## Building From Source
You will need QT 5.9 and the QDjango (https://github.com/jlaine/qdjango) library to build from source. Instructions are provided for Ubuntu, but the steps should apply for most Linux distributions. Just substitute aptitude for your package manager of choice.

### Ubuntu

Add some PPAs required for the Qt binaries.

```
sudo add-apt-repository ppa:beineri/opt-qt-5.10.1-trusty -y
sudo add-apt-repository ppa:fkrull/deadsnakes -y
```
Activate Python3 and install Python3.6 if not already installed.
```
pyenv global $(pyenv whence 2to3) 
sudo apt-get install python3.6 --allow-unauthenticated
sudo apt-get install python3.6-dev --allow-unauthenticated
```
Install Qt binaries and headers.
```
sudo apt-get install qt510base
source /opt/qt510/bin/qt510-env.sh
```
Clone the fork of qdjango dependency without Qt keywords and build it from source.
```
git clone https://github.com/tmstieff/qdjango.git
cd qdjango
qmake
make
sudo make install
cd ../
```
Clone the pybind11 project and build it from source.
```
git clone https://github.com/pybind/pybind11.git
cd pybind11
mkdir build
cd build
python3 -m pip install pytest
cmake ..
sudo make install
sudo ldconfig
```
Build the Woke project.
```
qmake -v
qmake CONFIG+=test
make
./woke-test
qmake CONFIG+=release PREFIX=/usr
make
make install
```

### Arch

Arch users will need Python3, Qt 5.10, and possibly CMake and GCC.
```
sudo pacman -S python qt5-base cmake gcc
```
Once installed, the instructions above should be identical.

### Windows

The project can be built from source within Windows using the MSVC2017 compiler. Instructions will vary based on the project location, but you will need to install 64-bit version of Python 3, Qt 5, and CMake. Ensure that all dependencies are available through your system path.

Build the qdjango fork and the pybind11 project from source.
```
git clone https://github.com/tmstieff/qdjango.git
cd qdjango
qmake qdjango.pro
nmake release
nmake install
C:\Python36-x64\Scripts\pip install pytest
cd ..
git clone https://github.com/pybind/pybind11.git
cd pybind11
mkdir build
cd build
cmake -A x64 ..
cmake -A x64 --build .
cmake --build . --config Release --target INSTALL
```
Build woke from source.
```
mkdir build
cd build
qmake ..
nmake release
```
Copy the qdjango libaries and the pybind11 libraries into the same folder as your executable prior to running. It may also be necessary to copy the OpenSSL dynamic libaries from the `/misc/win` folder.
