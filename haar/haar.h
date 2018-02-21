#ifndef HAAR_H
#define HAAR_H

#include <QObject>
#include <QTimer>
#include <QPoint>
#include <QRect>

#include <opencv2/opencv.hpp>

#include "config/config.h"
#include "logger/logger.h"
#include "keys.h"
#include "camera/camera.h"

using namespace cv;
using namespace std;

/**
 * @brief The Haar class
 * This class allows to identify classifiers and send events
 */
class Haar : public QObject
{
    Q_OBJECT

private:

    CascadeClassifier *classifier;
    QTimer *timer;

public:

    explicit Haar(QObject *parent = NULL);
    ~Haar();

    void init();


    CascadeClassifier *getClassifier() const;
    void setClassifier(CascadeClassifier *value);

    QTimer *getTimer() const;
    void setTimer(QTimer *value);

    void startTracking();
    void stopTracking();

    QRect getFaceRoi();

private slots:

    void process();
    void slot_process( cv::Mat * cameraTexture );

signals:

    void face(QRect f);
    void nose(QRect n, cv::Mat * cameraTexture);
    void point(QPoint p);
};

#endif // HAAR_H
