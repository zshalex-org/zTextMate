#include "ztextedit.h"

ZTextEdit::ZTextEdit(QWidget *parent) :
    QTextEdit(parent)
{
}

void ZTextEdit::setBackground(QColor color)
{
    QPalette p = palette();
    p.setColor(QPalette::Base,color);
    p.setColor(QPalette::Text,QColor("#A080FF"));
    p.setColor(QPalette::HighlightedText,QColor("#A080FF"));
    color = QColor("#800000");
    color.setAlpha(80);
    p.setColor(QPalette::Highlight,color);
//    color.setAlpha(80);

    setPalette(p);
}
