#include "config.h"

Config* Config::instance = NULL;
QVector<QStringList>* Config::strings = new QVector<QStringList>();

/**
 * @brief Config::Config
 * @param parent
 * Constructor
 */
Config::Config(QObject *parent) :
    QObject(parent)
{
    init();
}

/**
 * @brief Config::init
 * This method read the config file and assign to QStringList
 * the set of (key, value) required
 * This values are always QString, but it can take other types
 * if you get this through next methods
 */
void Config::init()
{
    QFile inputFile(CONFIG_FILE);
    if(inputFile.open(QIODevice::ReadOnly) == false)
    {
        LOG_ERR("Config: file not exists");
        return;
    }
    QTextStream in(&inputFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();

        if(line.contains(CONFIG_COMMENT))
        {
            line = line.remove(line.indexOf(CONFIG_COMMENT),
                               line.length() - line.indexOf(CONFIG_COMMENT));
        }

        if(line.simplified().isEmpty()) {
            continue;
        }

        QStringList kv = line.split(CONFIG_ASSIGNMENT);

        if(kv.size() == 2)
        {
            for(int i = 0; i < 2; i++)
            {
                kv.operator [](i) = kv.at(i).simplified();
            }
        }
        strings->append(kv);
        LOG_INF("Config: key" << kv.at(0) << "was setted");
    }
    inputFile.close();

    LOG_INF("Config: successfully initialized");
}

/**
 * @brief Config::getInstance
 * @return the instance
 */
Config *Config::getInstance()
{
    if(instance == NULL)
    {
        instance = new Config();
    }
    return instance;
}

/**
 * @brief Config::~Config
 * Destructor
 */
Config::~Config()
{
    if(instance != NULL)
    {
        delete instance;
    }
}

/**
 * @brief Config::getString
 * @param key
 * @return general value
 */
QString Config::getString(QString key)
{
    for(int i = 0; i < strings->size(); i++)
    {
        if(strings->at(i).at(0) == key)
        {
            return strings->at(i).at(1);
        }
    }

    LOG_ERR("Config string not found");
    return "";
}

/**
 * @brief Config::getStdString
 * @param key
 * @return string value
 */
string Config::getStdString(QString key)
{
    return getString(key).toStdString();
}

/**
 * @brief Config::getCharString
 * @param key
 * @return const char * value
 */
const char *Config::getCharString(QString key)
{
    return getStdString(key).c_str();
}

/**
 * @brief Config::getInt
 * @param key
 * @return int value
 */
int Config::getInt(QString key)
{
    return getString(key).toInt();
}

/**
 * @brief Config::getFloat
 * @param key
 * @return float value
 */
float Config::getFloat(QString key)
{
    return getString(key).toFloat();
}

/**
 * @brief Config::getDouble
 * @param key
 * @return double value
 */
double Config::getDouble(QString key)
{
    return getString(key).toDouble();
}

/**
 * @brief Config::getBool
 * @param key
 * @return boolean value
 */
bool Config::getBool(QString key)
{
    return getString(key) == "true";
}
