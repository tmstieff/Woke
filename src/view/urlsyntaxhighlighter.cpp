#include "urlsyntaxhighlighter.h"

UrlSyntaxHighlighter::UrlSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::white);

    QStringList keywordPatterns;
    keywordPatterns << "http"
                    << "https"
                    << "/";

    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    jsonKeyFormat.setForeground(QBrush(QColor(216, 126, 127)));
    jsonKeyFormat.setFontWeight(QFont::Bold);

    rule.pattern = QRegularExpression("[\?|&][A-z0-9_]+=");
    rule.format = jsonKeyFormat;
    highlightingRules.append(rule);
}

void UrlSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
