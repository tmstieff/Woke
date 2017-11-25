#ifndef PYTHONSCRIPTCONTROLLER_H
#define PYTHONSCRIPTCONTROLLER_H

#include "../extension/pybind/qstring_typecaster.h"
#include "../model/project.h"
#include "../model/request.h"
#include "currentdatacontroller.h"
#include "variablecontroller.h"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

class PythonScriptController {
  public:
    PythonScriptController();
    bool executeScript(QString &script, QSharedPointer<Request> request);

  private:
    py::scoped_interpreter guard{};
};

class PythonScriptControllerFactory {
  public:
    PythonScriptControllerFactory(PythonScriptControllerFactory const &) = delete;
    void operator=(PythonScriptControllerFactory const &) = delete;

    static PythonScriptController &getInstance() {
        static PythonScriptController instance;

        return instance;
    }

  private:
    PythonScriptControllerFactory() {
    }

    static PythonScriptController &instance;
};

#endif // PYTHONSCRIPTCONTROLLER_H
