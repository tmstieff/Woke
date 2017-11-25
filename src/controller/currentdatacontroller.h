#ifndef CURRENTDATACONTROLLER_H
#define CURRENTDATACONTROLLER_H

class CurrentDataController {
  public:
    CurrentDataController();

    static int getCurrentProjectId();
    static int getCurrentRequestId();

    static void setCurrentProjectId(int id);
    static void setCurrentRequestId(int id);

  private:
    static int currentProjectId;
    static int currentRequestId;
};

#endif // CURRENTDATACONTROLLER_H
