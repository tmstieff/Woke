#ifndef PYTHONSYNTAXHIGHLIGHTER_H
#define PYTHONSYNTAXHIGHLIGHTER_H

#include <QDebug>
#include <QObject>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

class PythonSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

  public:
    PythonSyntaxHighlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat quotedStringsFormat;
};

#endif // PYTHONSYNTAXHIGHLIGHTER_H
