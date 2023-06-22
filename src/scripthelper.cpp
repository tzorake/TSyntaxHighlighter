#include "scripthelper.h"
#include "helper.h"

#include <iostream>

ScriptHelper::ScriptHelper(QJSEngine *engine, QObject *parent)
    : QObject(parent)
    , m_engine(engine)
{

}

void ScriptHelper::require(const QString &name)
{
    // get full name of file
    // skip on errors
    QString fullName;
    fullName = QLatin1String(":/resources/") + name;
    if (!QFile::exists(fullName)) {
        return;
    }

    // check include guard
    QJSValue require_guard = m_engine->globalObject().property(QStringLiteral("require_guard"));
    if (require_guard.property(fullName).toBool()) {
        return;
    }

    // try to read complete file
    // skip non-existing files
    QString code;
    if (!Helper::readFile(fullName, code)) {
        return;
    }

    // eval in current script engine
    const QJSValue val = m_engine->evaluate(code, fullName);
    if (val.isError()) {
        qWarning() << "Error evaluating" << fullName << val.toString() << ", at line" << val.property(QStringLiteral("lineNumber")).toInt();
    }

    // set include guard
    require_guard.setProperty(fullName, QJSValue(true));
}

void ScriptHelper::debug(const QString &message)
{
    // debug in blue to distance from other debug output if necessary
    std::cerr << "\033[31m" << qPrintable(message) << "\033[0m\n";
}
