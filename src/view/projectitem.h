#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QLabel>
#include <QWidget>

namespace Ui {
class ProjectItem;
}

class ProjectItem : public QWidget {
    Q_OBJECT

  public:
    explicit ProjectItem(QWidget *parent = 0);
    void setInformation(QString name);
    QString getName();
    ~ProjectItem();

  private:
    QLabel *nameLabel;

    Ui::ProjectItem *ui;
};

#endif // PROJECTITEM_H
