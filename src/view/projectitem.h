#ifndef PROJECTITEM_H
#define PROJECTITEM_H

#include <QLabel>
#include <QWidget>

namespace Ui {
class ProjectItem;
}

class ProjectItem : public QWidget {
    Q_OBJECT

  Q_SIGNALS:
    void event_delete(QString &name);

  public:
    explicit ProjectItem(QWidget *parent = 0);
    void setInformation(QString name);
    QString getName();
    ~ProjectItem();

  private Q_SLOTS:
    void on_deleteButton_released();

  private:
    QLabel *nameLabel;
    QString name;

    Ui::ProjectItem *ui;
};

#endif // PROJECTITEM_H
