# Woke
<a href="https://travis-ci.org/tmstieff/Woke"><img alt="Travis CI Build" src="https://travis-ci.org/tmstieff/Woke.svg?branch=master"></a>
[![Build status](https://ci.appveyor.com/api/projects/status/ixwvi3wi6mfosm9j/branch/master?svg=true)](https://ci.appveyor.com/project/tmstieff/woke/branch/master)



A native multiplatform REST client with grand ambitions and limited scope.

<p align="center">
  <img width="900" alt="Woke client" src="https://i.imgur.com/qBwiKJ4.png">
</p>

## Binaries
Releases are currently provided for Linux as AppImages and for Windows as a portable ZIP or executable installer. Mac builds will come shortly.

<a href="https://github.com/tmstieff/Woke/releases">Windows and Linux</a>

## Features
* Supports most basic HTTP request types
* Raw header input
* Request body input
* Response body JSON parser
* Simple request history
* Simple request saving

## Ambitions
* Focus on scripting (Python)
* NeoVim editor built in
* Project management options
* Local and global variable declaration
* Parsing of Swagger, JSON Schema, and other applicable REST specifications
* Support for various authentication protocols

## Building From Source
You will need QT 5.9 and the QDjango (https://github.com/jlaine/qdjango) library to build from source. Instructions are provided for Ubuntu, but the steps should apply for most Linux distributions. Just substitute aptitude for your package manager of choice.

### Ubuntu

```
sudo add-apt-repository ppa:beineri/opt-qt591-trusty -y
sudo apt-get update
sudo apt-get install qt59base
source /opt/qt59/bin/qt59-env.sh
git clone https://github.com/jlaine/qdjango.git
cd qdjango
qmake
make
sudo make install
sudo ldconfig
cd ~/
git clone git@github.com:tmstieff/Woke.git
cd Woke
qmake woke-qt.pro -spec linux-g++
make
sudo make install
```
