#ifndef IMAGE_H
#define IMAGE_H

#include <QWidget>
#include <QImage>
#include <QPaintEvent>
#include <QPainter>

#include "logger/logger.h"

/**
 * @brief The Image class
 * This class allows to show an image
 */
class Image : public QWidget
{
    Q_OBJECT

private:

    void init();

    QImage *image;

public:

    explicit Image(QWidget *parent = NULL);
    ~Image();

    QImage *getImage() const;
    void setImage(QImage *value);

    void load(QString imagePath);

    void imageFolder();

protected:

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
};

#endif // IMAGE_H
