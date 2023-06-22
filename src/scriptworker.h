#ifndef SCRIPTWORKER_H
#define SCRIPTWORKER_H

#include <QObject>
#include <QJSEngine>
#include <QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

class ScriptWorker : public QObject
{
    Q_OBJECT
public:
    enum ExecutionCode {
        Success,
        Interrupted,
        Error
    };

    explicit ScriptWorker(QObject *parent = nullptr);

    void setScript(const QString &codeOrPath);

    ScriptWorker::ExecutionCode code();
    QJSValue result();
    QString script();

public slots:
    void start();
    void cancel();

protected:
    QJSEngine *engine();

signals:
    void started();
    void canceled();
    void finished(ScriptWorker::ExecutionCode code);

private:
    QJSEngine m_engine;

    QFuture<void> m_future;
    QFutureWatcher<void> m_futureWatcher;

    ExecutionCode m_code;
    QJSValue m_result;
    QString m_script;
};

#endif // SCRIPTWORKER_H
