#include "features/features.h"
#include <QDebug>
/**
 * @brief Features::Features
 * @param parent
 * Constructor
 */
Features::Features(QObject *parent) :
    QObject(parent)
{
    init();
}

/**
 * @brief Features::~Features
 * Destructor
 */
Features::~Features()
{
    delete this->getPreviousGrayImage();
    delete this->getGrayImage();
    delete this->getTimer();
}

/**
 * @brief Features::init
 * Auxiliar method
 */
void Features::init()
{
    this->setTimer( new QTimer(this) );

    this->setNeedCalibrate(true);
    this->setRoi(QRect(0, 0, 0, 0));

    this->setGrayImage( new Mat() );
    this->setPreviousGrayImage( new Mat() );
    this->setTermCriteria( TermCriteria( TermCriteria::COUNT | TermCriteria::EPS, 20, 0.03 ) );
    this->setSubWinPixSize( Size( 10, 10 ) );
    this->setWinSize( Size( 31, 31 ) );
    this->setMaxCount( 5000 );
    this->setInitialFrames( true );
    this->setInitialFramesCounter( 0 );
    this->setOffset( Point( 0, 0 ) );
    this->setFirstCentroid( true );

//    this->connect( this->getTimer(), SIGNAL( timeout() ), this, SLOT( slot_process() ) );
    this->getTimer()->setInterval( Config::getInstance()->getInt(TIMEOUT) );

    LOG_INF("Features extractor: successfully initialized");
}

/**
 * @brief Features::calculateFlowInLastFrames
 * Calculate the flow between the last frames
 */
void Features::calculateFlowInLastFrames()
{
    vector< uchar > status;
    vector< float > error;

    if( this->getPreviousGrayImage()->empty() )
    {
        this->getGrayImage()->copyTo( *this->getPreviousGrayImage() );
    }

    calcOpticalFlowPyrLK( *this->getPreviousGrayImage(),
                          *this->getGrayImage(),
                          points[0],
                          points[1],
                          status, error,
                          this->getWinSize(),
                          3, this->getTermCriteria(), 0, 0.001 );
    size_t i, k;
    for( i = k = 0; i < points[1].size(); i++ )
    {
        if( !status[i] )
        {
            continue;
        }

        points[1][k++] = points[1][i];
    }
    points[1].resize( k );
}

/**
 * @brief Features::pointsFilteringAccordingRoi
 * Filtering points in initial frames
 */
void Features::pointsFilteringAccordingRoi()
{
    this->setInitialFramesCounter( this->getInitialFramesCounter() + 1 );

    for( unsigned int i = 0; i < points[0].size(); i++ )
    {
        if( points[0][i].x < this->getRoi().x() ||
            points[0][i].x > this->getRoi().x() + this->getRoi().width() ||
            points[0][i].y < this->getRoi().y() ||
            points[0][i].y > this->getRoi().y() + this->getRoi().height() )
        {
            points[0].erase( points[0].begin() + i );
        }
    }
    if( this->getInitialFramesCounter() == 20 )
    {
        this->setInitialFrames( false );
    }
}

/**
 * @brief Features::essentialPointsProcessing
 * @param points
 * @return the target point
 */
QPoint Features::essentialPointsProcessing()
{
    Point centroid( 0, 0 );

    int pointsCounter = 0;
    for( unsigned int i = 0; i < points[0].size(); i++ )
    {
        centroid.x += points[0][i].x;
        centroid.y += points[0][i].y;
        pointsCounter++;
    }
    if( pointsCounter != 0 )
    {
        centroid.x /= ( double )pointsCounter;
        centroid.y /= ( double )pointsCounter;
    }

    if( this->getFirstCentroid() )
    {
        this->setOffset( Point( this->getRoi().center().x() - centroid.x,
                                this->getRoi().center().y() - centroid.y ) );
    }
    this->setFirstCentroid( false );

    Point final( centroid.x + this->getOffset().x,
                 centroid.y + this->getOffset().y );

    return QPoint(final.x, final.y);
}

/**
 * @brief Features::getTimer
 * @return the timer
 */
QTimer *Features::getTimer() const
{
    return timer;
}

/**
 * @brief Features::setTimer
 * @param value
 */
void Features::setTimer(QTimer *value)
{
    timer = value;
}

/**
 * @brief Features::getNeedCalibrate
 * @return if it's necessary to calibrate
 */
bool Features::getNeedCalibrate() const
{
    return needCalibrate;
}

/**
 * @brief Features::getRoi
 * @return the region of interest for features extracting
 */
QRect Features::getRoi() const
{
    return roi;
}

/**
 * @brief Features::setRoi
 * @param value
 */
void Features::setRoi(const QRect &value)
{
    roi = value;
}

/**
 * @brief Features::getGrayImage
 * @return the gray image
 */
Mat *Features::getGrayImage() const
{
    return grayImage;
}

/**
 * @brief Features::setGrayImage
 * @param value
 */
void Features::setGrayImage(Mat *value)
{
    grayImage = value;
}

/**
 * @brief Features::getPreviousGrayImage
 * @return the previous gray image
 */
Mat *Features::getPreviousGrayImage() const
{
    return previousGrayImage;
}

/**
 * @brief Features::setPreviousGrayImage
 * @param value
 */
void Features::setPreviousGrayImage( Mat *value )
{
    previousGrayImage = value;
}

/**
 * @brief Features::getMaxCount
 * @return the max count points
 */
int Features::getMaxCount() const
{
    return maxCount;
}

/**
 * @brief Features::setMaxCount
 * @param value
 */
void Features::setMaxCount(int value)
{
    maxCount = value;
}

/**
 * @brief Features::getSubWinPixSize
 * @return the size of sub-window
 */
Size Features::getSubWinPixSize() const
{
    return subWinPixSize;
}

/**
 * @brief Features::setSubWinPixSize
 * @param value
 */
void Features::setSubWinPixSize( const Size &value )
{
    subWinPixSize = value;
}

/**
 * @brief Features::getWinSize
 * @return the win size
 */
Size Features::getWinSize() const
{
    return winSize;
}

/**
 * @brief Features::setWinSize
 * @param value
 */
void Features::setWinSize(const Size &value)
{
    winSize = value;
}

/**
 * @brief Features::getTermCriteria
 * @return the term criteria
 */
TermCriteria Features::getTermCriteria() const
{
    return termCriteria;
}

/**
 * @brief Features::setTermCriteria
 * @param value
 */
void Features::setTermCriteria( const TermCriteria &value )
{
    termCriteria = value;
}

/**
 * @brief Features::getInitialFrames
 * @return if are the initial frames
 */
bool Features::getInitialFrames() const
{
    return initialFrames;
}

/**
 * @brief Features::setInitialFrames
 * @param value
 */
void Features::setInitialFrames(bool value)
{
    initialFrames = value;
}

/**
 * @brief Features::getInitialFramesCounter
 * @return how many frames are needed to init
 */
int Features::getInitialFramesCounter() const
{
    return initialFramesCounter;
}

/**
 * @brief Features::setInitialFramesCounter
 * @param value
 */
void Features::setInitialFramesCounter(int value)
{
    initialFramesCounter = value;
}

/**
 * @brief Features::getFirstCentroid
 * @return the first centroid
 */
bool Features::getFirstCentroid() const
{
    return firstCentroid;
}

/**
 * @brief Features::setFirstCentroid
 * @param value
 */
void Features::setFirstCentroid(bool value)
{
    firstCentroid = value;
}

/**
 * @brief Features::getOffset
 * @return the points offset
 */
Point Features::getOffset() const
{
    return offset;
}

/**
 * @brief Features::setOffset
 * @param value
 */
void Features::setOffset(const Point &value)
{
    offset = value;
}

/**
 * @brief Features::startTracking
 * Starts events tracking
 */
void Features::startTracking()
{
    this->getTimer()->start();
}

/**
 * @brief Features::stopTracking
 * Stops events tracking
 */
void Features::stopTracking()
{
    this->getTimer()->stop();
}

/**
 * @brief Features::calibrate
 * @param roi
 * Calibrate with the noise rect
 */
void Features::calibrate(QRect roi)
{
    if(roi.isEmpty())
    {
        LOG_ERR("Features extractor: cannot calibrate features extractor with an empty roi");
        return;
    }

    this->setRoi(roi);

    Mat *currentFrame = Camera::getInstance()->getCurrentFrame();

    cvtColor( *currentFrame, *this->getGrayImage(), COLOR_BGR2GRAY );

    goodFeaturesToTrack( *this->getGrayImage(),
                         points[1],
                         this->getMaxCount(),
                         0.01, 10, Mat(), 3, 0, 0.04 );

    cornerSubPix( *this->getGrayImage(),
                  points[1],
                  this->getSubWinPixSize(),
                  Size( -1, -1 ),
                  this->getTermCriteria() );

    this->setInitialFrames( true );
    this->setInitialFramesCounter( 0 );
    this->setFirstCentroid( true );

    this->setNeedCalibrate(false);
}
void Features::calibrateCamera(QRect roi,cv::Mat *currentFrame)
{
    if(roi.isEmpty())
    {
        LOG_ERR("Features extractor: cannot calibrate features extractor with an empty roi");
        return;
    }

    this->setRoi(roi);

    cvtColor( *currentFrame, *this->getGrayImage(), COLOR_BGR2GRAY );

    goodFeaturesToTrack( *this->getGrayImage(),
                         points[1],
                         this->getMaxCount(),
                         0.01, 10, Mat(), 3, 0, 0.04 );

    cornerSubPix( *this->getGrayImage(),
                  points[1],
                  this->getSubWinPixSize(),
                  Size( -1, -1 ),
                  this->getTermCriteria() );

    this->setInitialFrames( true );
    this->setInitialFramesCounter( 0 );
    this->setFirstCentroid( true );

    this->setNeedCalibrate(false);
}

/**
 * @brief Features::setNeedCalibrate
 * @param value
 */
void Features::setNeedCalibrate(bool value)
{
    needCalibrate = value;
}

/**
 * @brief Features::process
 * Process camera frame and emit detected events
 */
void Features::process()
{
    Mat *currentFrame = Camera::getInstance()->getCurrentFrame();

    if(currentFrame->empty())
    {
        LOG_WAR("Features extractor: current camera frame is empty");
        this->stopTracking();
        return;
    }

    if(this->getNeedCalibrate())
    {
        LOG_WAR("Features extractor: is not calibrated yet");
        this->stopTracking();
        return;
    }

    cvtColor( *currentFrame, *this->getGrayImage(), COLOR_BGR2GRAY );

    if( !points[0].empty() )
    {
        this->calculateFlowInLastFrames();
    }

    std::swap( points[1], points[0] );

    if( this->getInitialFrames() )
    {
        this->pointsFilteringAccordingRoi();
        LOG_INF("Features extractor: processing initial frames...");
    }
    else
    {
        QPoint final = this->essentialPointsProcessing();

        if(final.isNull())
        {
            LOG_ERR("Features extractor: cannot calculate final point");
        }
        else
        {
            emit detected( final );
        }
    }

    cv::swap( *this->getPreviousGrayImage(), *this->getGrayImage() );
}
void Features::slot_process(cv::Mat *currentFrame)
{
    if(currentFrame->empty())
    {
        LOG_WAR("Features extractor: current camera frame is empty");
        this->stopTracking();
        return;
    }

    if(this->getNeedCalibrate())
    {
        LOG_WAR("Features extractor: is not calibrated yet");
        this->stopTracking();
        return;
    }

    cvtColor( *currentFrame, *this->getGrayImage(), COLOR_BGR2GRAY );

    if( !points[0].empty() )
    {
        this->calculateFlowInLastFrames();
    }

    std::swap( points[1], points[0] );

    if( this->getInitialFrames() )
    {
        this->pointsFilteringAccordingRoi();
        LOG_INF("Features extractor: processing initial frames...");
    }
    else
    {
        QPoint final = this->essentialPointsProcessing();

        if(final.isNull())
        {
            LOG_ERR("Features extractor: cannot calculate final point");
        }
        else
        {
            emit detected( final );
        }
    }

    cv::swap( *this->getPreviousGrayImage(), *this->getGrayImage() );
}

