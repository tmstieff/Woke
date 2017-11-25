#include "tabbededitor.h"
#include "ui_tabbededitor.h"

/**
 * Construct a new tabbed editor component.
 * @brief TabbedEditor::TabbedEditor
 * @param parent
 * @param tabs List of tab names
 */
TabbedEditor::TabbedEditor(QWidget *parent, QList<QSharedPointer<Ui::TabData>> tabs)
    : QWidget(parent), ui(new Ui::TabbedEditor) {
    this->setupEditor(tabs);

    this->setupFont();
}


TabbedEditor::TabbedEditor(QWidget *parent) : QWidget(parent), ui(new Ui::TabbedEditor) {
    this->setupEditor(QList<QSharedPointer<Ui::TabData>>());
    this->setupFont();
}

void TabbedEditor::setupEditor(const QList<QSharedPointer<Ui::TabData>> &tabs) {
    ui->setupUi(this);

    editor = ui->editor;
    tabsLayout = ui->tabsLayout;
    tabsLayout->setAlignment(Qt::AlignLeft);

    addTabs(tabs);
    activeTabIndex = 0;

    autoCompleter = new QCompleter(this);
    autoCompleter->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
}

void TabbedEditor::setupFont() {
    QFont defaultMonoFont;
    defaultMonoFont.setFamily("Courier");
    defaultMonoFont.setStyleHint(QFont::Monospace);
    defaultMonoFont.setFixedPitch(true);
    defaultMonoFont.setPointSize(10);
    this->editor->setFont(defaultMonoFont);

    const int tabSpaces = 2;
    QFontMetrics metrics(defaultMonoFont);

    // Set tab width to 2 spaces
    this->editor->setTabStopWidth(tabSpaces * metrics.width(' '));
}

TabbedEditor::~TabbedEditor() {
    delete ui;
}

void TabbedEditor::addTabs(const QList<QSharedPointer<Ui::TabData>> &tabs) {
    for (int i = 0; i < tabs.length(); i++) {
        auto name = tabs.at(i).data()->name;
        this->addTab(i, tabs.at(i));
    }

    this->tabsLayout->update();
    this->tabs = tabs;

    this->setActiveTab(0);
}

void TabbedEditor::addTab(int index, QSharedPointer<Ui::TabData> tabData) {
    auto tab = new QPushButton(this);
    tab->setText(tabData.data()->name);
    tab->updateGeometry();

    tabData.data()->button = QSharedPointer<QPushButton>(tab);
    QObject::connect(tab, &QPushButton::pressed, this, &TabbedEditor::tabClicked);

    this->tabsLayout->insertWidget(index, tab);

    if (index == 0) {
        this->setActiveTab(0);
    }
}

void TabbedEditor::setStylesheetProperty(QWidget &widget, const QString &property, const QString &value) {
    auto stylesheet = widget.styleSheet();

    QString newStylesheet;
    if (stylesheet.contains(property + ": " + value + ";")) {
        newStylesheet =
            stylesheet.replace(QRegularExpression(QString(property + ": .+;")), property + ": " + value + ";");
    } else {
        newStylesheet = stylesheet.append("\n" + property + ": " + value + ";");
    }

    widget.setStyleSheet(newStylesheet);
}

void TabbedEditor::setActiveTabStyle(QPushButton &button) {
    QString property("border-bottom");
    QString value("3px solid #6ABDDB");

    this->setStylesheetProperty(button, property, value);

    property = "background-color";
    value = "#3c3e3f";

    this->setStylesheetProperty(button, property, value);
}

void TabbedEditor::setInactiveTabStyle(QPushButton &button) {
    QString property("border-bottom");
    QString value("3px solid #2C2E2F");

    this->setStylesheetProperty(button, property, value);

    property = "background-color";
    value = "#313335";

    this->setStylesheetProperty(button, property, value);
}

void TabbedEditor::setActiveTab(int tabIndex) {
    this->activeTabIndex = tabIndex;
    for (int i = 0; i < this->tabs.length(); i++) {
        if (tabIndex == i) {
            this->setActiveTabStyle(*this->tabs.at(i).data()->button);
            this->editor->setPlainText(*this->tabs.at(i).data()->data.data());

            auto syntaxHighlighter = this->tabs.at(i).data()->syntaxHighlighter;
            if (syntaxHighlighter) {
                syntaxHighlighter.data()->setDocument(this->editor->document());
            }

            auto autoCompletions = this->tabs.at(i).data()->autoCompletions;
            if (autoCompletions) {
                this->autoCompleter->setModel(autoCompletions);
            }
        } else {
            this->setInactiveTabStyle(*this->tabs.at(i).data()->button);
        }
    }
}

void TabbedEditor::tabClicked() {
    QObject *sender = QObject::sender();
    QPushButton *button = qobject_cast<QPushButton *>(sender);
    if (button) {
        for (int i = 0; i < this->tabs.length(); i++) {
            if (this->tabs.at(i).data()->button.data() == button) {
                this->setActiveTab(i);
                break;
            }
        }
    }
}

void TabbedEditor::resetTabData() {
    for (int i = 0; i < this->tabs.length(); i++) {
        this->tabs.at(i).data()->data = QSharedPointer<QString>(new QString(""));
    }
}

QList<QSharedPointer<Ui::TabData>> TabbedEditor::getTabsData() {
    return this->tabs;
}

void TabbedEditor::setTabData(int index, QSharedPointer<QString> data) {
    this->tabs.at(index).data()->data = data;
    this->refreshUi();
}

QSharedPointer<QString> TabbedEditor::getTabData(int index) {
    return this->tabs.at(index).data()->data;
}

void TabbedEditor::refreshUi() {
    this->editor->setPlainText(*this->tabs.at(this->activeTabIndex).data()->data.data());
}

void TabbedEditor::on_editor_textChanged() {
    auto str = this->editor->toPlainText();
    this->tabs.at(this->activeTabIndex).data()->data = QSharedPointer<QString>(new QString(str.data()));
}
