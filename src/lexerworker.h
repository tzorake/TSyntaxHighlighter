#ifndef LEXERWORKER_H
#define LEXERWORKER_H

#include "scriptworker.h"

#include <QObject>

class LexerWorker : public ScriptWorker
{
    Q_OBJECT
public:
    explicit LexerWorker(QObject *parent = nullptr);

public slots:
    void processText(const QString &text);

signals:
    void processingFinished(const QString &text);

private:
    QString m_result;
};

#endif // LEXERWORKER_H
