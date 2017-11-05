#ifndef HEADERSYNTAXHIGHLIGHTER_H
#define HEADERSYNTAXHIGHLIGHTER_H

#include <QDebug>
#include <QObject>
#include <QRegularExpression>
#include <QSyntaxHighlighter>

class HeaderSyntaxHighlighter : public QSyntaxHighlighter {
    Q_OBJECT

  public:
    HeaderSyntaxHighlighter(QTextDocument *parent = 0);

  protected:
    void highlightBlock(const QString &text) override;

  private:
    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QTextCharFormat headerKeyFormat;
};

#endif // HEADERSYNTAXHIGHLIGHTER_H
