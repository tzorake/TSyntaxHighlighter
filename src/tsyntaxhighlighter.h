#ifndef TSYNTAXHIGHLIGHTER_H
#define TSYNTAXHIGHLIGHTER_H

#include <QObject>
#include <QDebug>
#include <QTextEdit>
#include <QJSEngine>

class TSyntaxHighlighter : public QObject
{
    Q_OBJECT
public:
    explicit TSyntaxHighlighter(QTextEdit *parent);

public slots:
    void highlight();

private:
    int m_cursorPosition = 0;

    QString m_hljs;
    QString m_cssStyles;

    QJSEngine *m_engine;
};

#endif // TSYNTAXHIGHLIGHTER_H
