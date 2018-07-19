#include "pythonsyntaxhighlighter.h"

PythonSyntaxHighlighter::PythonSyntaxHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent) {
    HighlightingRule rule;

    keywordFormat.setForeground(Qt::white);

    QStringList keywordPatterns;
    keywordPatterns << "and"
                    << "assert"
                    << "break"
                    << "class"
                    << "continue"
                    << "def"
                    << "del"
                    << "elif"
                    << "else"
                    << "except"
                    << "exec"
                    << "finally"
                    << "for"
                    << "from"
                    << "global"
                    << "if"
                    << "import"
                    << "in"
                    << "is"
                    << "lambda"
                    << "not"
                    << "or"
                    << "pass"
                    << "print"
                    << "raise"
                    << "return"
                    << "try"
                    << "while"
                    << "yield"
                    << "True"
                    << "False"
                    << "None";

    Q_FOREACH (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    quotedStringsFormat.setForeground(QBrush(QColor(216, 126, 127)));
    quotedStringsFormat.setFontWeight(QFont::Bold);

    rule.pattern = QRegularExpression("[\"|\'].*[\"|\']");
    rule.format = quotedStringsFormat;
    highlightingRules.append(rule);
}

void PythonSyntaxHighlighter::highlightBlock(const QString &text) {
    Q_FOREACH (const HighlightingRule &rule, highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);

        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
