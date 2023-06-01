#include "ttextedit.h"
#include <QDebug>

TTextEdit::TTextEdit(QWidget *parent) : QTextEdit(parent)
{
    m_highlighter = new TSyntaxHighlighter(this);

    connect(this, &TTextEdit::textChanged, m_highlighter, &TSyntaxHighlighter::highlight);
}
