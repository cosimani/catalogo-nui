#ifndef CONFIG_H
#define CONFIG_H

#define CONFIG_FILE "/home/ubp/Escritorio/Investigacion-2018/SeguimientoNariz/project.config"
#define CONFIG_COMMENT "*"
#define CONFIG_ASSIGNMENT "="

#include <QObject>
#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QVector>

#include "logger/logger.h"

using namespace std;

/**
 * @brief The Config class
 * This class allows you to set configuration externally to the source code
 */
class Config : public QObject
{
    Q_OBJECT

private:

    static Config *instance;
    static QVector<QStringList> *strings;

    explicit Config(QObject *parent=NULL);
    void init();

public:

    static Config *getInstance();
    ~Config();

    QString getString(QString key);
    string getStdString(QString key);
    const char *getCharString(QString key);
    int getInt(QString key);
    float getFloat(QString key);
    double getDouble(QString key);
    bool getBool(QString key);
};

#endif // CONFIG_H
