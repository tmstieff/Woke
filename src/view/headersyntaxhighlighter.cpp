#include "headersyntaxhighlighter.h"

HeaderSyntaxHighlighter::HeaderSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    headerKeyFormat.setForeground(QBrush(QColor(216, 126, 127)));
    headerKeyFormat.setFontWeight(QFont::Bold);

    rule.pattern = QRegularExpression("^.*(?=:)");
    rule.format = headerKeyFormat;
    highlightingRules.append(rule);
}

void HeaderSyntaxHighlighter::highlightBlock(const QString &text) {
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
