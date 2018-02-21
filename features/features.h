#ifndef FEATURES_H
#define FEATURES_H

#include <QObject>
#include <QTimer>
#include <QPoint>
#include <QRect>

#include "config/config.h"
#include "logger/logger.h"
#include "keys.h"
#include "camera/camera.h"

/**
 * @brief The Features class
 * This class allows to extract features and send events
 */
class Features : public QObject
{
    Q_OBJECT

private:

    void init();
    void calculateFlowInLastFrames();
    void pointsFilteringAccordingRoi();
    QPoint essentialPointsProcessing();

    QTimer *timer;

    bool needCalibrate;
    QRect roi;

    bool drawProcessing;
    Mat *grayImage;
    Mat *previousGrayImage;

    vector< Point2f > points[2];
    int maxCount;
    Size subWinPixSize;
    Size winSize;
    TermCriteria termCriteria;

    bool initialFrames;
    int initialFramesCounter;
    bool firstCentroid;
    Point offset;

public:

    explicit Features(QObject *parent = NULL);
    ~Features();

    QTimer *getTimer() const;
    void setTimer(QTimer *value);

    bool getNeedCalibrate() const;
    void setNeedCalibrate(bool value);

    QRect getRoi() const;
    void setRoi(const QRect &value);

    Mat *getGrayImage() const;
    void setGrayImage( Mat *value );

    Mat *getPreviousGrayImage() const;
    void setPreviousGrayImage( Mat *value );

    int getMaxCount() const;
    void setMaxCount( int value );

    Size getSubWinPixSize() const;
    void setSubWinPixSize( const Size &value );

    Size getWinSize() const;
    void setWinSize( const Size &value );

    TermCriteria getTermCriteria() const;
    void setTermCriteria( const TermCriteria &value );

    bool getInitialFrames() const;
    void setInitialFrames( bool value );

    int getInitialFramesCounter() const;
    void setInitialFramesCounter( int value );

    bool getFirstCentroid() const;
    void setFirstCentroid( bool value );

    Point getOffset() const;
    void setOffset( const Point &value );

    void startTracking();
    void stopTracking();
    void calibrate(QRect roi);

    void calibrateCamera(QRect roi,cv::Mat *currentFrame);

private slots:

    void process();
    void slot_process(cv::Mat *currentFrame);

signals:

    void detected(QPoint pos);
};

#endif // FEATURES_H
