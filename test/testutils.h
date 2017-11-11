#ifndef TESTUTILS_H
#define TESTUTILS_H

#include "../src/model/project.h"
#include "../src/model/request.h"
#include <QDebug>
#include <qdjango/db/QDjango.h>

void initDatabase();

class TestUtils {
  public:
    TestUtils();
};

#endif // TESTUTILS_H
