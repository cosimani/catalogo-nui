#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QObject>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QPainter>
#include "logger/logger.h"
#include "navigator.h"
#include "camerathread.h"
#include "haar/haar.h"
#include "features/features.h"

#include "image.h"
#include "keys.h"
#include "config/config.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QImage *image;

    void init();

    CameraThread * camTh;

    static Widget *getInstance();

    Navigator *getNavigator() const;
    void setNavigator(Navigator *value);

    Haar *getHaar() const;
    void setHaar(Haar *value);

    Features *getFeatures() const;
    void setFeatures(Features *value);

    bool getFeaturesCalibrated() const;
    void setFeaturesCalibrated(bool value);

    QRect getFirstHaarRect() const;
    void setFirstHaarRect(const QRect &value);
private:
    Ui::Widget *ui;

    static Widget *instance;

    Haar *haar;
    Features *features;

    bool navegate;

    bool featuresCalibrated;
    QRect firstHaarRect;

    void keyPressEvent(QKeyEvent * event);

private slots:
    void slot_horizontalSlider(int a);

    void haarNoseDetected(QRect n, cv::Mat *currentFrame);
    void featuresDetected(QPoint p);

    void slot_changeFolder(QString texto);

    void slot_resaltarBoton(int c, int f);

    void slot_seleccionActivada(int c, int f);

protected:
    void paintEvent( QPaintEvent* );

signals:
    void signal_navigatorOn(bool);
};

#endif // WIDGET_H
