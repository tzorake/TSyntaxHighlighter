#ifndef TTEXTEDIT_H
#define TTEXTEDIT_H

#include "tsyntaxhighlighter.h"

#include <QObject>
#include <QTextEdit>

class TTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TTextEdit(QWidget *parent = nullptr);

private:
    TSyntaxHighlighter *m_highlighter;
};
#endif // TTEXTEDIT_H
