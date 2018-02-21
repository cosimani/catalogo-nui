#ifndef LOGGER_H
#define LOGGER_H

#define PREF_INF "[INF]"
#define PREF_WAR "[WAR]"
#define PREF_ERR "[ERR]"

#define LOG_INF(X) qDebug().noquote() << PREF_INF << X
#define LOG_WAR(X) qDebug().noquote() << PREF_WAR << X
#define LOG_ERR(X) qDebug().noquote() << PREF_ERR << X

#include <QDebug>

#endif // LOGGER_H
