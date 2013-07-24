#include <QTextCharFormat>
#include <QDebug>

#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    m_colorScheme.loadColorScheme("Amy.xml");
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat myClassFormat;
    SubScheme sub = m_colorScheme.scheme("keyword");
    myClassFormat.setFontItalic(sub.italic);
    myClassFormat.setFontUnderline(sub.underline);
    myClassFormat.setForeground(sub.foreground);
    QString pattern = "\\b(break|case|continue|default|do|else|for|goto|if|_Pragma|return|switch|while)\\b";

    QRegExp expression(pattern);
    int index = text.indexOf(expression);
    while (index >= 0) {
        int length = expression.matchedLength();
        setFormat(index, length, myClassFormat);
        index = text.indexOf(expression, index + length);
    }
}

//hangzhouwap54g
