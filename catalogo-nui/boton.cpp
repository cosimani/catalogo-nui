#include "boton.h"
#include "ui_boton.h"

#include <QDebug>

Boton::Boton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Boton)
{
    ui->setupUi(this);
    image = new QImage("../SeguimientoNariz/Recursos/3.jpg");

    setMouseTracking(true);
}

Boton::~Boton()
{
    delete ui;
}

void Boton::setImage(QImage im)
{
    ico = im;
}

void Boton::setText(QString titulo)
{
    ui->label->setText(titulo);
}

void Boton::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.drawImage(QRect(0,0,this->width(),this->height()+10), *image);
    painter.drawImage(QRect((this->width()/2)-50,(this->height()/2) -60,100,100), ico);
}

void Boton::hoverMove(QHoverEvent *event)
{
}

void Boton::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        emit signalFolderName(ui->label->text());
        this->cambiarFondoBoton("../SeguimientoNariz/Recursos/10.jpg");
    }


//    this->close();
}
bool Boton::eventFilter(QObject *obj, QEvent *event)
{
    setMouseTracking(true);

  if (event->type() == QEvent::MouseMove)
  {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
  }
  return false;
}

void Boton::cambiarFondoBoton(QString archivo)
{
    image->load(archivo);
    this->repaint();
}
void Boton::mouseMoveEvent(QMouseEvent *event){
}
