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
* Focus on Python scripting
* Raw header input
* Request body input
* Response body JSON parser
* Simple request history
* Simple request saving

## Scripting

The pre and post tabs can be used to retrieve and set variables for your project. For instance, you may wish to login, capture the authentication token from the response body / headers, and declare it as a project variable to be used in the headers of another request. The script tabs run a full python interpreter, so any standard Python libraries are available to be imported. The following additional functions are used to set and retrieve variables. The get is scoped from most to least specific.

```
getVar("")
setLocalVar("", *)
setProjectVar("", *)
setGlobalVar("", *)
```

Because the additional methods are evaluated with Python, any valid Python statement can be evaluted, and the result of the evaluation will be assigned as the value of the variable. However, for now, everything needs to be evaluated as string. As an example, you can add the following to a "Post-Request Script" for a login request.

```
import json

body = json.loads(request.responseBody)
setProjectVar('token', body['token'])
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

```
sudo apt-get install libpython3.6-dev
sudo add-apt-repository ppa:beineri/opt-qt591-trusty -y
sudo apt-get update
sudo apt-get install qt59base
source /opt/qt59/bin/qt59-env.sh
git clone https://github.com/tmstieff/qdjango.git
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
