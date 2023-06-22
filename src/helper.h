#ifndef HELPER_H
#define HELPER_H

#include <QDebug>
#include <QFile>

class Helper {
public:
    static bool readFile(const QString &sourceUrl, QString &sourceCode)
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
};

#endif // HELPER_H
