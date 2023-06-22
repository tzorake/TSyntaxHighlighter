#include "scriptworker.h"
#include "helper.h"

ScriptWorker::ScriptWorker(QObject *parent)
    : QObject(parent)
{
    m_engine.installExtensions(QJSEngine::AllExtensions);
}

void ScriptWorker::setScript(const QString &codeOrPath)
{
    QFileInfo info(codeOrPath);

    if (info.exists()) {
        Helper::readFile(codeOrPath, m_script);
    }
    else {
        m_script = codeOrPath;
    }
}

ScriptWorker::ExecutionCode ScriptWorker::code()
{
    return m_code;
}

QJSValue ScriptWorker::result()
{
    return m_result;
}

QString ScriptWorker::script()
{
    return m_script;
}

void ScriptWorker::start()
{
    if (m_futureWatcher.isRunning()) {
        cancel();
    }

    if (m_engine.isInterrupted()) {
        m_engine.setInterrupted(false);
    }

    m_future = QtConcurrent::run([this]() {
        emit started();

        m_code = ExecutionCode::Success;

        if (m_script.isEmpty()) {
            qWarning() << "Script is empty!";
            return;
        }

        m_result = m_engine.evaluate(m_script);

        if (m_result.isError()) {
            m_code = m_engine.isInterrupted() ? ExecutionCode::Interrupted : ExecutionCode::Error;
            qWarning() << "Error evaluating script: " << m_result.toString();
        }

        emit finished(m_code);
    });
    m_futureWatcher.setFuture(m_future);
}

void ScriptWorker::cancel()
{
    m_engine.setInterrupted(true);
    m_futureWatcher.cancel();

    emit canceled();
}

QJSEngine *ScriptWorker::engine()
{
    return &m_engine;
}
