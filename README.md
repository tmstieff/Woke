# Woke
<img alt="Travis CI Build" src="https://travis-ci.org/tmstieff/Woke.svg?branch=master">

A native multiplatform REST client with grand ambitions and limited scope.

<p align="center">
  <img width="900" alt="Woke client" src="http://i.imgur.com/2OC3Ubk.png">
</p>

## Building
For now there are no binaries available. You will need QT 5.9 to build from source. So far only linux is supported. The QDjango (https://github.com/jlaine/qdjango) lib is required.

```
qmake woke-qt.pro -spec linux-g++
make
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
