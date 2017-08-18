#ifndef URLSYNTAXHIGHLIGHTER_H
#define URLSYNTAXHIGHLIGHTER_H

#include <QDebug>
#include <QObject>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

class UrlSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

  public:
    UrlSyntaxHighlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat keywordFormat;
    QTextCharFormat jsonKeyFormat;
    QTextCharFormat jsonValueTextFormat;
    QTextCharFormat jsonValueKeywordFormat;
};

#endif // URLSYNTAXHIGHLIGHTER_H
