# Woke
<img alt="Travis CI Build" src="https://travis-ci.org/tmstieff/Woke.svg?branch=master">

A native multiplatform REST client with grand ambitions and limited scope.

<p align="center">
  <img width="900" alt="Woke client" src="https://i.imgur.com/O156Jq9.png?1">
</p>

## Building
For now there are no binaries available. You will need QT 5.9 to build from source. So far only linux is supported. The QDjango (https://github.com/jlaine/qdjango) lib is required.

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

## Features
* Supports most basic HTTP request types
* Raw header input
* Request body input
* Response body JSON parser
* Simple request history

## Ambitions
* Focus on scripting (Python or Lua?)
* Project management options
* Local and global variable declaration
* Parsing of Swagger, JSON Schema, and other applicable REST specifications
* Support for various authentication protocols
