#ifndef CUSTOMTEXTEDIT_H
#define CUSTOMTEXTEDIT_H

#include "tsyntaxhighlighter.h"

#include <QTextEdit>
#include <QTimer>

class TTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TTextEdit(QWidget *parent = nullptr);

private:
    TSyntaxHighlighter *m_highlighter;
};

#endif // CUSTOMTEXTEDIT_H
