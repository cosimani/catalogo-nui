#ifndef BOTON_H
#define BOTON_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
namespace Ui {
class Boton;
}

class Boton : public QWidget
{
    Q_OBJECT

public:
    explicit Boton(QWidget *parent = 0);
    ~Boton();
    QImage *image, ico;

    void setImage(QImage im);
    void setText(QString titulo);

    bool eventFilter(QObject *obj, QEvent *event);
    void cambiarFondoBoton(QString archivo);

private:
    Ui::Boton *ui;

protected:
    void paintEvent( QPaintEvent* );
    void mousePressEvent(QMouseEvent *event);
    void hoverMove(QHoverEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


signals:
    void signalFolderName(QString name);

};

#endif // BOTON_H
