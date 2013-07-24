#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include "colorscheme.h"

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit SyntaxHighlighter(QTextDocument *parent = 0);
    
protected:
    void highlightBlock(const QString &text);
private:
    ColorScheme m_colorScheme;
};

#endif // SYNTAXHIGHLIGHTER_H
