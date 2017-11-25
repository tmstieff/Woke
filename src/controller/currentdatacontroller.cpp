#include "currentdatacontroller.h"

int CurrentDataController::currentProjectId;
int CurrentDataController::currentRequestId;

CurrentDataController::CurrentDataController() {
}

int CurrentDataController::getCurrentProjectId() {
    return CurrentDataController::currentProjectId;
}

int CurrentDataController::getCurrentRequestId() {
    return CurrentDataController::currentRequestId;
}

void CurrentDataController::setCurrentProjectId(int id) {
    CurrentDataController::currentProjectId = id;
}

void CurrentDataController::setCurrentRequestId(int id) {
    CurrentDataController::currentRequestId = id;
}
