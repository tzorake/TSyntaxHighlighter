#ifndef SCRIPTHELPER_H
#define SCRIPTHELPER_H

#include <QObject>
#include <QJSEngine>

class ScriptHelper : public QObject
{
    Q_OBJECT
public:
    explicit ScriptHelper(QJSEngine *engine, QObject *parent = nullptr);

    void require(const QString &name);
    void debug(const QString &message);

private:
    QJSEngine *m_engine;
};

#endif // SCRIPTHELPER_H
