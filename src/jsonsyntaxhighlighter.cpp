#include "jsonsyntaxhighlighter.h"

JsonSyntaxHighlighter::JsonSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::white);

    QStringList keywordPatterns;
    keywordPatterns << "\"" << "\'"; //<< "\[" << "\]" << "\{" << "\}";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    jsonKeyFormat.setForeground(QBrush(QColor(216, 126, 127)));
    jsonKeyFormat.setFontWeight(QFont::Bold);

    rule.pattern = QRegularExpression("\".*\"(?=:)");
    rule.format = jsonKeyFormat;
    highlightingRules.append(rule);

    jsonValueKeywordFormat.setForeground(QBrush(QColor(217, 141, 240)));

    rule.pattern = QRegularExpression("(?= ?)true|false|null(?= +|,)");
    rule.format = jsonValueKeywordFormat;
    highlightingRules.append(rule);
}

void JsonSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
