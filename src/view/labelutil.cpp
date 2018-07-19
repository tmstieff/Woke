#include "labelutil.h"

LabelUtil::LabelUtil()
{

}

/**
 * @brief LabelUtil::setStatusCodeLabel
 *
 * Set the color and text for the HTTP status code label
 *
 * @param statusCode
 * @param statusCodeLabel
 */
void LabelUtil::setStatusCodeLabel(const QString statusCode, QLabel &statusCodeLabel)
{
    statusCodeLabel.setText(statusCode);

    int statusCodeInt = statusCode.toInt();

    if (statusCodeInt >= 200 && statusCodeInt <= 299) {
        QString property("background-color");
        QString value(GREEN_LABEL);
        LabelUtil::setStylesheetProperty(statusCodeLabel, property, value);
    } else if (statusCodeInt >= 300 && statusCodeInt <= 399) {
        QString property("background-color");
        QString value(DEFAULT_INFO_LABEL_COLOR);
        LabelUtil::setStylesheetProperty(statusCodeLabel, property, value);
    } else if (statusCodeInt >= 400 && statusCodeInt <= 499) {
        QString property("background-color");
        QString value(YELLOW_LABEL);
        LabelUtil::setStylesheetProperty(statusCodeLabel, property, value);
    } else if (statusCodeInt >= 500 && statusCodeInt <= 599) {
        QString property("background-color");
        QString value(RED_LABEL);
        LabelUtil::setStylesheetProperty(statusCodeLabel, property, value);
    } else {
        QString property("background-color");
        QString value(DEFAULT_INFO_LABEL_COLOR);
        LabelUtil::setStylesheetProperty(statusCodeLabel, property, value);
    }
}

/**
 * @brief MainWindow::setStylesheetProperty
 *
 * Set or replace a specific stylesheet property on a widget
 *
 * @param widget
 * @param property
 * @param value
 */
void LabelUtil::setStylesheetProperty(QWidget &widget, const QString &property, const QString &value)
{
    auto stylesheet = widget.styleSheet();

    const QString &newStylesheet =
        stylesheet.replace(QRegularExpression(QString(property + ": .+;")), property + ": " + value + ";");

    widget.setStyleSheet(newStylesheet);
}
