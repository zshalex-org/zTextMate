#ifndef ZTEXTEDIT_H
#define ZTEXTEDIT_H

#include <QTextEdit>

class SyntaxHighlighter;

class ZTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit ZTextEdit(QWidget *parent = 0);

    void setBackground(QColor color);
private:
    SyntaxHighlighter *m_syntax;
};

#endif // ZTEXTEDIT_H
