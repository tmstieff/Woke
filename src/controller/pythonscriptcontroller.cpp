#include "pythonscriptcontroller.h"

PYBIND11_EMBEDDED_MODULE(woke, m) {
    m.def("set_global_var", &setGlobalVariable, "Set a globally scoped variable");
    m.def("set_project_var", &setGlobalVariable, "Set a project scoped variable");
    m.def("set_local_var", &setLocalVariable, "Set a locally scoped variable");
    m.def("get", &getVariable, "Get a variable ordered by scope");
    m.def("get_var", &getVariable, "Get a variable ordered by scope");

    py::class_<Project>(m, "Project")
        .def(py::init<QObject *>(), py::arg("parent") = 0)
        .def_property_readonly("name", &Project::getName);

    py::class_<Request>(m, "Request")
        .def(py::init<QObject *>(), py::arg("parent") = nullptr)
        .def_property_readonly("name", &Request::getName)
        .def_property("proto", &Request::getProto, &Request::setProto)
        .def_property("host", &Request::getHost, &Request::setHost)
        .def_property("uri", &Request::getUri, &Request::setUri)
        .def_property_readonly("status_code", &Request::getStatusCode)
        .def_property_readonly("time", &Request::getTime)
        .def_property("request_headers", &Request::getRequestHeaders, &Request::setRequestHeaders)
        .def_property("request_body", &Request::getRequestBody, &Request::setRequestBody)
        .def_property("verb", &Request::getVerb, &Request::setVerb)
        .def_property("response_body", &Request::getResponseBody, &Request::setResponseBody)
        .def_property("response_headers", &Request::getResponseHeaders, &Request::setResponseHeaders);
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
    if (script.isNull()) {
        return true;
    }

    // Append the import to the top of every script so the user
    // doesn't have to import the woke module themselves
    auto scriptHeader = QString();
    scriptHeader.append(QString("import json\n"));
    scriptHeader.append(QString("from woke import set_global_var, set_project_var, set_local_var, get_var, get, Request, Project\n\n"));
    scriptHeader.append(QString("body = ''\n"));
    scriptHeader.append(QString("try:\n"));
    scriptHeader.append(QString("\tbody = json.loads(request.response_body)\n"));
    scriptHeader.append(QString("except:\n"));
    scriptHeader.append(QString("\tpass\n\n"));

    script.prepend(scriptHeader);

    qDebug() << script;

    // Need this line so the types get registered with pybind
    auto jsonModule = py::module::import("json");
    auto wokeModule = py::module::import("woke");

    py::object scope = py::module::import("__main__").attr("__dict__");
    scope["json"] = jsonModule;

    py::object locals = py::dict();
    if (!request.isNull()) {
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
