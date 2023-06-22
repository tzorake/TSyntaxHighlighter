#ifndef TSYNTAXHIGHLIGHTER_H
#define TSYNTAXHIGHLIGHTER_H

#include "lexerworker.h"

#include <QObject>
#include <QTextEdit>

class TSyntaxHighlighter : public QObject
{
    Q_OBJECT
public:
    explicit TSyntaxHighlighter(QTextEdit *parent = nullptr);

    QPair<int, int> linesWithinViewport();

private slots:
    void onTextChanged();
    void handleProcessingFinished(const QString &text);

private:
    LexerWorker m_lexerWorker;
    QString m_styles;
};

#endif // TSYNTAXHIGHLIGHTER_H
