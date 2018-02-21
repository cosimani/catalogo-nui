#include "camera/camera.h"

Camera* Camera::instance = NULL;

/**
 * @brief Camera::Camera
 * @param parent
 * Constructor
 */
Camera::Camera(QObject *parent):
    QObject(parent)
{
    init();
}

/**
 * @brief Camera::init
 * Auxiliar method
 */
void Camera::init()
{
    this->setFrameCapturer( new VideoCapture( Config::getInstance()->getInt(CAMERA) ) );
    this->setFrameUpdater( new QTimer( this ) );
    this->setCurrentFrame( new Mat() );

    this->connect( this->getFrameUpdater(), SIGNAL( timeout() ), this, SLOT( updateCurrentFrame() ) );
    this->getFrameUpdater()->setInterval( Config::getInstance()->getInt(TIMEOUT) );
    this->getFrameUpdater()->start();

    emit signal();

    LOG_INF("Camera: successfully initialized");
}

/**
 * @brief Camera::getInstance
 * @return the instance
 */
Camera *Camera::getInstance()
{
    if(instance == NULL)
    {
        instance = new Camera();
    }
    return instance;
}

/**
 * @brief Camera::~Camera
 * Destructor
 */
Camera::~Camera()
{
    delete this->getFrameCapturer();
    delete this->getCurrentFrame();
    delete this->getFrameUpdater();
    delete this->getInstance();

    if(instance != NULL)
    {
        delete instance;
    }
}

/**
 * @brief Camera::getFrameCapturer
 * @return the frame capturer
 */
VideoCapture *Camera::getFrameCapturer() const
{
    return frameCapturer;
}

/**
 * @brief Camera::setFrameCapturer
 * @param value
 */
void Camera::setFrameCapturer(VideoCapture *value)
{
    frameCapturer = value;
}

/**
 * @brief Camera::getCurrentFrame
 * @return the current frame
 * User have to validate this Mat is not empty
 * Because it's never null, but it can return empty
 */
Mat *Camera::getCurrentFrame() const
{
    return currentFrame;
}

/**
 * @brief Camera::setCurrentFrame
 * @param value
 */
void Camera::setCurrentFrame(Mat *value)
{
    currentFrame = value;
}

/**
 * @brief Camera::getFrameUpdater
 * @return the frame updater
 */
QTimer *Camera::getFrameUpdater() const
{
    return frameUpdater;
}

/**
 * @brief Camera::setFrameUpdater
 * @param value
 */
void Camera::setFrameUpdater(QTimer *value)
{
    frameUpdater = value;
}

/**
 * @brief Camera::getFrameCapturerBrightness
 * @return the camera brightness
 */
int Camera::getFrameCapturerBrightness()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_BRIGHTNESS ) * 100;
}

/**
 * @brief Camera::getFrameCapturerContrast
 * @return the camera constrast
 */
int Camera::getFrameCapturerContrast()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_CONTRAST ) * 100;
}

/**
 * @brief Camera::getFrameCapturerSaturation
 * @return the camera saturation
 */
int Camera::getFrameCapturerSaturation()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_SATURATION ) * 100;
}

/**
 * @brief Camera::getFrameCapturerHue
 * @return the camera hue
 */
int Camera::getFrameCapturerHue()
{
    return this->getFrameCapturer()->get( CV_CAP_PROP_HUE ) * 100;
}

/**
 * @brief Camera::updateCurrentFrame
 * Update current camera frame
 */
void Camera::updateCurrentFrame()
{
    this->getFrameCapturer()->operator >>( *this->getCurrentFrame() );
}

/**
 * @brief Camera::setFrameCapturerBrightness
 * @param value
 */
void Camera::setFrameCapturerBrightness( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_BRIGHTNESS, value / ( double )100 );
}

/**
 * @brief Camera::setFrameCapturerContrast
 * @param value
 */
void Camera::setFrameCapturerContrast( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_CONTRAST, value / ( double )100 );
}

/**
 * @brief Camera::setFrameCapturerSaturation
 * @param value
 */
void Camera::setFrameCapturerSaturation( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_SATURATION, value / ( double )100 );
}

/**
 * @brief Camera::setFrameCapturerHue
 * @param value
 */
void Camera::setFrameCapturerHue( int value )
{
    this->getFrameCapturer()->set( CV_CAP_PROP_HUE, value / ( double )100 );
}
