#ifndef JSONSYNTAXHIGHLIGHTER_H
#define JSONSYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QSyntaxHighlighter>
#include <QRegularExpression>
#include <QDebug>

class JsonSyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    JsonSyntaxHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    struct HighlightingRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat jsonKeyFormat;
    QTextCharFormat jsonValueTextFormat;
    QTextCharFormat jsonValueKeywordFormat;
};

#endif // JSONSYNTAXHIGHLIGHTER_H
