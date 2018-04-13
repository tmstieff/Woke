#ifndef LABELUTIL_H
#define LABELUTIL_H

#include <QString>
#include <QLabel>
#include <QRegularExpression>

static const QString DEFAULT_INFO_LABEL_COLOR = "#595b5d";
static const QString BLUE_LABEL = "#445F68";
static const QString RED_LABEL = "#68444D";
static const QString YELLOW_LABEL = "#795C06";
static const QString PURPLE_LABEL = "#412F79";
static const QString GREEN_LABEL = "#3F684A";

class LabelUtil
{
public:
    LabelUtil();
    static void setStatusCodeLabel(const QString statusCode, QLabel &statusCodeLabel);
    static void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
};

#endif // LABELUTIL_H
