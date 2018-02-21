#ifndef CAMERA_H
#define CAMERA_H

#include <QObject>
#include <QTimer>
#include <QPoint>

#include <opencv2/opencv.hpp>

#include "logger/logger.h"
#include "config/config.h"
#include "keys.h"

using namespace cv;
using namespace std;

/**
 * @brief The Camera class
 * This class allows you to manage the camera events and processing
 */
class Camera : public QObject
{
    Q_OBJECT

private:

    static Camera *instance;

    explicit Camera(QObject *parent = NULL);
    void init();

    VideoCapture *frameCapturer;
    Mat *currentFrame;
    QTimer *frameUpdater;

public:

    static Camera *getInstance();
    ~Camera();

    VideoCapture *getFrameCapturer() const;
    void setFrameCapturer(VideoCapture *value);

    Mat *getCurrentFrame() const;
    void setCurrentFrame(Mat *value);

    QTimer *getFrameUpdater() const;
    void setFrameUpdater(QTimer *value);

    bool getFirstFrame() const;
    void setFirstFrame(bool value);

    int getFrameCapturerBrightness();
    int getFrameCapturerContrast();
    int getFrameCapturerSaturation();
    int getFrameCapturerHue();

private slots:

    void updateCurrentFrame();

public slots:

    void setFrameCapturerBrightness( int value );
    void setFrameCapturerContrast( int value );
    void setFrameCapturerSaturation( int value );
    void setFrameCapturerHue( int value );

signals:
    void signal_newFrame(cv::Mat * currentFrame);
    void signal();
};

#endif // CAMERA_H
