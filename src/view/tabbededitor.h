#ifndef WOKE_QT_TABBEDEDITOR_H
#define WOKE_QT_TABBEDEDITOR_H

#include <QAction>
#include <QDebug>
#include <QHBoxLayout>
#include <QList>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QSharedPointer>
#include <QSyntaxHighlighter>
#include <QWidget>

namespace Ui {
class TabbedEditor;

struct TabData {
    QString name;
    QSharedPointer<QString> data;
    QSharedPointer<QPushButton> button;
    QSharedPointer<QSyntaxHighlighter> syntaxHighlighter;
};
}

class TabbedEditor : public QWidget {
    Q_OBJECT

  public:
    explicit TabbedEditor(QWidget *parent);
    explicit TabbedEditor(QWidget *parent, QList<QSharedPointer<Ui::TabData>> tabs);
    ~TabbedEditor() override;

    void addTab(int index, QSharedPointer<Ui::TabData> data);
    void addTabs(const QList<QSharedPointer<Ui::TabData>> &tabs);
    void removeTab(const QString &name);
    void removeTab(int index);
    void resetTabData();
    void refreshUi();

  protected:
    Ui::TabbedEditor *ui;
    QList<QSharedPointer<Ui::TabData>> getTabsData();
    void setTabData(int index, QSharedPointer<QString> data);
    QSharedPointer<QString> getTabData(int index);
    int activeTabIndex;

  private:
    QHBoxLayout *tabsLayout;
    QPlainTextEdit *editor;

    QList<QSharedPointer<Ui::TabData>> tabs;
    void setActiveTabStyle(QPushButton &button);
    void setInactiveTabStyle(QPushButton &button);
    void setStylesheetProperty(QWidget &widget, const QString &property, const QString &value);
    void setActiveTab(int tabIndex);
    void setupFont();

  private slots:
    void tabClicked();
    void on_editor_textChanged();
};

#endif // WOKE_QT_TABBEDEDITOR_H
