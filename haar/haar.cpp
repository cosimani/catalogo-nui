#include "haar/haar.h"
#include <QDebug>
/**
 * @brief Haar::Haar
 * @param parent
 * Constructor
 */
Haar::Haar(QObject *parent) :
    QObject(parent)
{
    init();
}

/**
 * @brief Haar::~Haar
 * Destructor
 */
Haar::~Haar()
{
    delete this->getClassifier();
    delete this->getTimer();
}

/**
 * @brief Haar::init
 * Auxiliar method
 */
void Haar::init()
{
    this->setClassifier( new CascadeClassifier(Config::getInstance()->getStdString(CLASSIFIER) ) );
    if(this->getClassifier()->empty())
    {
        LOG_ERR("Haar detector: cannot load classifier" << Config::getInstance()->getString(CLASSIFIER));
    }
    else qDebug()<<"init haar succefully";



//    this->setTimer( new QTimer(this) );

//    this->connect( this->getTimer(), SIGNAL( timeout() ), this, SLOT( process() ) );
//    this->getTimer()->setInterval( Config::getInstance()->getInt(TIMEOUT) );

    LOG_INF("Haar detector: successfully initialized");
}

/**
 * @brief Haar::getClassifier
 * @return the classifier
 */
CascadeClassifier *Haar::getClassifier() const
{
    return classifier;
}

/**
 * @brief Haar::setClassifier
 * @param value
 */
void Haar::setClassifier(CascadeClassifier *value)
{
    classifier = value;
}

/**
 * @brief Haar::getTimer
 * @return the timer
 */
QTimer *Haar::getTimer() const
{
    return timer;
}

/**
 * @brief Haar::setTimer
 * @param value
 */
void Haar::setTimer(QTimer *value)
{
    timer = value;
}

/**
 * @brief Haar::startTracking
 * Starts events tracking
 */
void Haar::startTracking()
{
//    this->getTimer()->start();
}

/**
 * @brief Haar::stopTracking
 * Stops events tracking
 */
void Haar::stopTracking()
{
    this->getTimer()->stop();
}

void Haar::slot_process( cv::Mat * cameraTexture )
{
    QRect roi = QRect(0, 0, 0, 0);

    if(this->getClassifier()->empty())
    {
        LOG_ERR("Haar detector: classifier is empty");
        return;
    }

    if(cameraTexture->empty())
    {
        LOG_WAR("Haar detector: current camera frame is empty");
        return;
    }

    vector< Rect > detectedObjects;
    detectedObjects.clear();
    classifier->detectMultiScale( *cameraTexture, detectedObjects,
                                  1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );
    if(detectedObjects.size() == 0)
    {
        return;
    }
    roi.setX(detectedObjects[0].x);
    roi.setY(detectedObjects[0].y);
    roi.setWidth(detectedObjects[0].width);
    roi.setHeight(detectedObjects[0].height);


    if(roi.isEmpty())
    {
        return;
    }

    emit face(roi);

    QRect n;
    n.setX(roi.x() + roi.width() / ( double )3);
    n.setY(roi.y() + roi.height() / ( double )2);
    n.setWidth(roi.width() / ( double )3);
    n.setHeight(roi.height() / ( double )3);
    if(n.isEmpty())
    {
        return;
    }
    emit nose(n,cameraTexture);

    QPoint p;
    p.setX(n.x() + n.width() / (float)2);
    p.setY(n.y() + n.height() / (float)2);
    if(p.isNull())
    {
        return;
    }
    emit point(p);
}

/**
 * @brief Haar::getFaceRoi
 * @return the face roi
 */
QRect Haar::getFaceRoi()
{
//    QRect roi = QRect(0, 0, 0, 0);

//    if(this->getClassifier()->empty())
//    {
//        LOG_ERR("Haar detector: classifier is empty");
//        return roi;
//    }

//    Mat *currentFrame = Camera::getInstance()->getCurrentFrame();

//    if(currentFrame->empty())
//    {
//        LOG_WAR("Haar detector: current camera frame is empty");
//        return roi;
//    }

//    vector< Rect > detectedObjects;
//    detectedObjects.clear();
//    classifier->detectMultiScale( *currentFrame, detectedObjects,
//                                  1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size( 150, 150 ) );
//    if(detectedObjects.size() == 0)
//    {
//        return roi;
//    }

//    roi.setX(detectedObjects[0].x);
//    roi.setY(detectedObjects[0].y);
//    roi.setWidth(detectedObjects[0].width);
//    roi.setHeight(detectedObjects[0].height);

//    return roi;
}

/**
 * @brief Haar::process
 * Process camera frame and emit detected events
 */
void Haar::process()
{
//    QRect f = this->getFaceRoi();
//    if(f.isEmpty())
//    {
//        return;
//    }
//    emit face(f);

//    QRect n;
//    n.setX(f.x() + f.width() / ( double )3);
//    n.setY(f.y() + f.height() / ( double )2);
//    n.setWidth(f.width() / ( double )3);
//    n.setHeight(f.height() / ( double )3);
//    if(n.isEmpty())
//    {
//        return;
//    }
//    emit nose(n);

//    QPoint p;
//    p.setX(n.x() + n.width() / (float)2);
//    p.setY(n.y() + n.height() / (float)2);
//    if(p.isNull())
//    {
//        return;
//    }
//    emit point(p);
}
