#include "lexerworker.h"
#include "helper.h"

#include <QtConcurrent>

LexerWorker::LexerWorker(QObject *parent)
    : ScriptWorker(parent)
{
    QString script;
    Helper::readFile(":/resources/core.js", script);
    QJSValue hljs = engine()->evaluate(script);
    engine()->globalObject().setProperty("hljs", hljs);

    connect(this, &ScriptWorker::finished, this, [this]() {
        m_result = "<body><pre><code class='javascript'>" + result().toString() + "</code></pre></body>";
        emit processingFinished(m_result);
    });
}

void LexerWorker::processText(const QString &text)
{
    QString inputString = text;

    inputString = inputString.replace("\n", "\\n");
    inputString = inputString.replace("\r", "\\r");
    inputString = inputString.replace("\"", "\\\"");

    QString formattedString = "\"" + inputString + "\"";
    QString program = QLatin1String(
        "(function() { ") + QString(
            "const text = %1;").arg(formattedString) + QLatin1String(
            "const html = hljs.highlight(text, {language: 'javascript'}).value; "
            "return html;"
        "})()");

    setScript(program);
    start();
}
