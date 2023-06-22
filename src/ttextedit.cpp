#include "ttextedit.h"

TTextEdit::TTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    setLineWrapMode(TTextEdit::LineWrapMode::NoWrap);
    m_highlighter = new TSyntaxHighlighter(this);
}
