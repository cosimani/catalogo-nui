#include "image.h"

/**
 * @brief Image::Image
 * @param parent
 * Constructor
 */
Image::Image(QWidget *parent) :
    QWidget(parent)
{
    this->init();
}

/**
 * @brief Image::init
 * Auxiliar method
 */
void Image::init()
{
    this->setImage(new QImage());

    LOG_INF("Image: successfully initialized");
}

/**
 * @brief Image::~Image
 * Destructor
 */
Image::~Image()
{
    delete image;
}

/**
 * @brief Image::getImage
 * @return the image
 */
QImage *Image::getImage() const
{
    return image;
}

/**
 * @brief Image::setImage
 * @param value
 */
void Image::setImage(QImage *value)
{
    image = value;
}

/**
 * @brief Image::load
 * @param imagePath
 * Method for load an image
 */
void Image::load(QString imagePath)
{
    this->getImage()->load(imagePath);

    this->setFixedSize(this->getImage()->size());

    this->repaint();
}

void Image::imageFolder()
{
    delete image;

    this->setImage(new QImage());
}

/**
 * @brief Image::paintEvent
 * @param event
 * Redefinition of paintEvent method
 */
void Image::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(QRect(0,30,this->width(),this->height()), *this->getImage());
    QWidget::paintEvent(event);
}
