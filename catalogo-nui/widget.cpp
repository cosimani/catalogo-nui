#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QDebug>


Widget* Widget::instance = NULL;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    navegate ( false ),
    camTh( new CameraThread ( this ) )
{
    ui->setupUi(this);

    camTh->setTipoCaptura( CameraThread::CONTROL_MENU );
    camTh->setDimension( 6, 1 );
    camTh->encenderCamara( 0, 10 );

    image = new QImage("../SeguimientoNariz/Recursos/5.jpg");

    init();

    ui->horizontalSlider->setRange(-10,10);
    ui->pbUrbanismo->setText("Urbanismo");
    ui->pbUrbanismo->setImage(QImage("../SeguimientoNariz/Recursos/png/urban2.png"));
    ui->pbPaisajes->setText("Paisajes");
    ui->pbPaisajes->setImage(QImage("../SeguimientoNariz/Recursos/png/paisaje1.png"));
    ui->pbTecnologia->setText("Tecnologia");
    ui->pbTecnologia->setImage(QImage("../SeguimientoNariz/Recursos/png/tecno7.png"));
    ui->pbAnimales->setText("Animales");
    ui->pbAnimales->setImage(QImage("../SeguimientoNariz/Recursos/png/animal2.png"));

    connect(ui->pbTecnologia,SIGNAL(signalFolderName(QString)),this,SLOT(slot_changeFolder(QString)));
    connect(ui->pbUrbanismo,SIGNAL(signalFolderName(QString)),this,SLOT(slot_changeFolder(QString)));
    connect(ui->pbPaisajes,SIGNAL(signalFolderName(QString)),this,SLOT(slot_changeFolder(QString)));
    connect(ui->pbAnimales,SIGNAL(signalFolderName(QString)),this,SLOT(slot_changeFolder(QString)));

    connect(camTh,SIGNAL(posicionDetectada(int,int)),this,SLOT(slot_resaltarBoton(int,int)));
    connect(camTh,SIGNAL(seleccionDetectada(int,int)),this,SLOT(slot_seleccionActivada(int,int)));

    connect(camTh,SIGNAL(signal_newCameraFrame(cv::Mat*)),haar,SLOT(slot_process(cv::Mat*)));
    connect(camTh,SIGNAL(signal_newCameraFrame(cv::Mat*)),features,SLOT(slot_process(cv::Mat*)));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    this->setHaar(new Haar(this));
    this->setFeatures(new Features(this));
    this->setFeaturesCalibrated(false);
    this->getFirstHaarRect().setRect(0, 0, 0, 0);

    this->connect(this->getHaar(), SIGNAL(nose(QRect,cv::Mat*)), this, SLOT(haarNoseDetected(QRect,cv::Mat*)));
    this->connect(this->getFeatures(), SIGNAL(detected(QPoint)), this, SLOT(featuresDetected(QPoint)));

    ui->navigatorWidget->close();

    this->getHaar()->startTracking();

    LOG_INF("App: successfully initialized");
}

Widget *Widget::getInstance()
{
    if(instance == NULL)
    {
        instance = new Widget();
    }
    return instance;
}

Navigator *Widget::getNavigator() const
{
    return ui->navigatorWidget;

}

void Widget::setNavigator(Navigator *value)
{
    ui->navigatorWidget = value;
}

Haar *Widget::getHaar() const
{
    return haar;
}

void Widget::setHaar(Haar *value)
{
    haar = value;
}

Features *Widget::getFeatures() const
{
    return features;
}

void Widget::setFeatures(Features *value)
{
    features = value;
}

bool Widget::getFeaturesCalibrated() const
{
    return featuresCalibrated;
}

void Widget::setFeaturesCalibrated(bool value)
{
    featuresCalibrated = value;
}

QRect Widget::getFirstHaarRect() const
{
    return firstHaarRect;
}

void Widget::setFirstHaarRect(const QRect &value)
{
    firstHaarRect = value;
}

void Widget::slot_horizontalSlider(int a)
{
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.drawImage(QRect(0,0,this->width(),this->height()+10), *image);
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Escape:
            close();
            break;
    case Qt::Key_Z:
            this->slot_changeFolder("Urbanismo");
            break;
    case Qt::Key_X:
            this->slot_changeFolder("Paisajes");
            break;
    case Qt::Key_C:
            this->slot_changeFolder("Tecnologia");
            break;
    case Qt::Key_V:
            this->slot_changeFolder("Animales");
            break;
            default:;
    }
}

void Widget::slot_resaltarBoton(int c, int f)
{
    qDebug()<<c<<" -"<<f;
    if(!navegate)
    {
        if(c == 1)
        {
            ui->pbUrbanismo->cambiarFondoBoton("../SeguimientoNariz/Recursos/10.jpg");
            ui->pbPaisajes->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbAnimales->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbTecnologia->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
        }
        if(c == 2)
        {
            ui->pbUrbanismo->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbPaisajes->cambiarFondoBoton("../SeguimientoNariz/Recursos/10.jpg");
            ui->pbAnimales->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbTecnologia->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
        }
        if(c == 4)
        {
            ui->pbUrbanismo->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbPaisajes->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbAnimales->cambiarFondoBoton("../SeguimientoNariz/Recursos/10.jpg");
            ui->pbTecnologia->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
        }
        if(c == 3)
        {
            ui->pbUrbanismo->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbPaisajes->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbAnimales->cambiarFondoBoton("../SeguimientoNariz/Recursos/3.jpg");
            ui->pbTecnologia->cambiarFondoBoton("../SeguimientoNariz/Recursos/10.jpg");
        }
    }
}

void Widget::slot_seleccionActivada(int c, int f)
{
    qDebug()<<"seleccion activada"<<c<<f;
    if(!navegate){
        navegate = true;
    }
    else{
        navegate = false;
        return;
    }
    if(c == 1)
        slot_changeFolder("Urbanismo");
    if(c == 2)
        slot_changeFolder("Paisajes");
    if(c == 3)
        slot_changeFolder("Tecnologia");
    if(c == 4)
        slot_changeFolder("Animales");
}

void Widget::haarNoseDetected(QRect n,cv::Mat *currentFrame)
{
    if(!n.isEmpty() && !this->getFeaturesCalibrated())
    {
        this->getFeatures()->calibrateCamera(n,currentFrame);
        this->getFeatures()->startTracking();
        this->setFirstHaarRect(n);
        this->setFeaturesCalibrated(true);
        return;
    }

    QPoint p(n.x() + n.width() / (double)2, n.y() + n.height() / (double)2);

    QRect r = this->getFirstHaarRect();

    QPoint c(r.x() + r.width() / (float)2, r.y() + r.height() / (float)2);

    QPoint d(p.x() - c.x(), p.y() - c.y());
}

void Widget::featuresDetected(QPoint p)
{
    if(navegate)
    {
        QRect r = this->getFeatures()->getRoi();

        QPoint c(r.x() + r.width() / (float)2, r.y() + r.height() / (float)2);

        QPoint d(p.x() - c.x(), p.y() - c.y());

        ui->navigatorWidget->move(d.x());
        if(navegate==true)
            ui->horizontalSlider->setValue(-(d.x()));
    }
}

void Widget::slot_changeFolder(QString texto)
{
    navegate = true;

    ui->navigatorWidget->close();
    ui->navigatorWidget->changeFolder(texto);
    ui->navigatorWidget->show();

}
