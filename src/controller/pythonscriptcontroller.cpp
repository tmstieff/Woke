#include "pythonscriptcontroller.h"

PYBIND11_EMBEDDED_MODULE(woke, m) {
    m.def("setGlobalVar", &setGlobalVariable, "Set a globally scoped variable");
    m.def("setProjectVar", &setGlobalVariable, "Set a project scoped variable");
    m.def("setLocalVar", &setLocalVariable, "Set a locally scoped variable");
    m.def("getVar", &getVariable, "Get a variable ordered by scope");

    py::class_<Project>(m, "Project")
        .def(py::init<QObject *>(), py::arg("parent") = 0)
        .def_property_readonly("name", &Project::getName);

    py::class_<Request>(m, "Request")
        .def(py::init<QObject *>(), py::arg("parent") = nullptr)
        .def_property_readonly("name", &Request::getName)
        .def_property("proto", &Request::getProto, &Request::setProto)
        .def_property("host", &Request::getHost, &Request::setHost)
        .def_property("uri", &Request::getUri, &Request::setUri)
        .def_property_readonly("statusCode", &Request::getStatusCode)
        .def_property_readonly("time", &Request::getTime)
        .def_property("requestHeaders", &Request::getRequestHeaders, &Request::setRequestHeaders)
        .def_property("requestBody", &Request::getRequestBody, &Request::setRequestBody)
        .def_property("verb", &Request::getVerb, &Request::setVerb)
        .def_property("responseBody", &Request::getResponseBody, &Request::setResponseBody)
        .def_property("responseHeaders", &Request::getResponseHeaders, &Request::setResponseHeaders);
}

PythonScriptController::PythonScriptController() {
}

/**
 * Executes a string as a python script
 * @brief PythonScriptController::executeScript
 * @param script: Valid python script to execute
 * @return result of execution
 */
bool PythonScriptController::executeScript(QString &script, QSharedPointer<Request> request) {
    // Append the import to the top of every script so the user
    // doesn't have to import the woke module themselves
    script.prepend(QString("from woke import setGlobalVar, setProjectVar, setLocalVar, getVar, Request, Project\n\n"));

    // Need this line so the types get registered with pybind
    auto wokeModule = py::module::import("woke");

    py::object scope = py::module::import("__main__").attr("__dict__");
    py::object locals = py::dict();
    if (request.data() != NULL) {
        py::object pythonRequest = py::cast(request.data());
        locals["request"] = pythonRequest;
    }

    try {
        py::exec(script.toUtf8().constData(), scope, locals);
        return true;
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();

        return false;
    }
}
