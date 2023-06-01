#include "tsyntaxhighlighter.h"

#include <QFile>
#include <QQmlEngine>

bool readFile(const QString &sourceUrl, QString &sourceCode)
{
    sourceCode = QString();

    QFile file(sourceUrl);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << QStringLiteral("Unable to find \"%1\"").arg(sourceUrl);
        return false;
    } else {
        QTextStream stream(&file);
        sourceCode = stream.readAll();
        file.close();
    }
    return true;
}

TSyntaxHighlighter::TSyntaxHighlighter(QTextEdit *parent) : QObject(parent)
{
    readFile(":/resources/core.js", m_hljs);
    readFile(":/resources/styles/googlecode.css", m_cssStyles);

    m_engine = new QJSEngine(this);
    m_engine->installExtensions(QJSEngine::Extension::AllExtensions);

    QString program = QLatin1String("(function() { return ") + m_hljs + QLatin1String("})");
    QJSValue programFunction = m_engine->evaluate(program);

    QJSValue result = programFunction.call();
    if (result.isError()) {
        qWarning() << "Error evaluating script: " << result.toString();
    }

    QQmlEngine::setObjectOwnership(parent, QQmlEngine::CppOwnership);

    m_engine->globalObject().setProperty("textEdit", m_engine->newQObject(parent));
    m_engine->globalObject().setProperty("hljs", result);
}

void TSyntaxHighlighter::highlight()
{
    QTextEdit *textEdit = static_cast<QTextEdit *>(parent());

    {
        const QSignalBlocker blocker(textEdit);

        QString code = textEdit->toPlainText();
        QString program = QLatin1String(
            "(function() { "
                "const html = hljs.highlight(textEdit.plainText, {language: 'javascript'}).value; "
                "return html;"
            "})");
        QJSValue programFunction = m_engine->evaluate(program);

        QJSValue result = programFunction.call();
        if (result.isError()) {
            qWarning() << "Error evaluating script: " << result.toString();
        }

        QTextCursor cursor = textEdit->textCursor();
        m_cursorPosition = cursor.position();

        textEdit->setHtml(
            "<head><style>" + m_cssStyles + "</style></head>"
            "<body><pre><code class='javascript'>" + result.toString() + "</code></pre></body>"
        );

        cursor.setPosition(m_cursorPosition);
        textEdit->setTextCursor(cursor);
    }
}
