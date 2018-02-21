#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H


#include <QThread>
#include <QTimer>

#include <vector>

#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "camera/camera.h"

#include "common.h"

#define FRAMES_FACELESS 70
#define FRAMES_FACELESS_BACK 50

using namespace cv;
using namespace std;


/**
 * @brief The DimensionThread class Esta clase mantiene las dimensiones (columnas y filas) de ese menu a controlar
 */
class DimensionThread  {
public:
    DimensionThread( int columnas = 0, int filas = 0 ) : columnas( columnas ), filas( filas )  {  }
    int columnas, filas;
};

class CameraThread : public QThread
{
    Q_OBJECT

public:

    enum TipoCaptura { NO_DEFINIDO, SOLO_VIDEO, CONTROL_MENU };

    explicit CameraThread( QObject *parent = NULL );
    virtual ~CameraThread();



    CascadeClassifier *getFrontalFaceClassifier() const;
    void setFrontalFaceClassifier( CascadeClassifier *value);

    CascadeClassifier *getSmileClassifier() const;
    void setSmileClassifier( CascadeClassifier *value);

    int getSize() const;
    void setSize( int value );

    bool getSmiling() const;
    void setSmiling( bool value );

    void detenerCamara();

    /**
     * @brief encenderCamara Las opciones para encender camara son:
     *      indexCamara = -1  - Requiere url para el RTSP
     *      indexCamara = 0, 1, 2, ...  es el index para VideoCapture
     * @param indexCamara
     * @param milisegundos
     * @param url
     */
    void encenderCamara( int indexCamara = 0, int milisegundos = 10, QString url = "" );

    void setDimension( int columnas , int filas );

    TipoCaptura getTipoCaptura() const;
    void setTipoCaptura( const TipoCaptura & value );

private:

    VideoCapture *videoCapture;
    QTimer *sceneTimer;
    Mat *cameraTexture;

    CascadeClassifier *frontalFaceClassifier;
    CascadeClassifier *smileClassifier;

    Rect currentFace;
    Rect calibration;

    /**
     * @brief size Es la cantidad de botones que tiene horizontalmente, en este caso, la interfaz. Los lee desde los xml.
     */
    int size;

    bool smiling;

    /**
     * @brief isCalibrated Se utiliza para saber si se calibro o no. Es decir, si este bool es false, entonces no se tiene
     * control de la interfaz, requiere que se pulse el boton Calibrar o bien, sonreir. Es bool se pondra en false nuevamente
     * cuando no se detecte la cara con Haar.
     */
    bool isCalibrated;

    /**
     * @brief countFrameFaceless Para acumular la cantidad de frames que no se detectan rostros, y asi reiniciar la frase
     */
    int countFrameFaceless;

    /**
     * @brief dim Se almacenan las dimensiones del menu a controlar
     */
    DimensionThread * dim;

    // Para detectar si se detecto un nuevo index. Para no estar emitiendo constantemente posicionDetectada
    int indexColumnaActual, indexFilaActual;

    TipoCaptura tipoCaptura;


protected:
    void run();

private slots:

    void process();

public slots:

    void calibrate();

    void recibirFrame(cv::Mat *cameraTexture);

signals:

    void positionDetected( int index );

    /**
     * @brief posicionDetectada Se emite cuando se detecta una nueva posicion en el menu a controlar
     * Se emite esta senal con -1 y -1 cuando no detecta ni la cara, y sera necesario calibrar de nuevo.
     * @param indexColumna
     * @param indexFila
     */
    void posicionDetectada( int indexColumna, int indexFila );

    /**
     * @brief seleccionDetectada Se emite cuando se hace clic sobre una posicion del menu a controlar
     * @param indexColumna
     * @param indexFila
     */
    void seleccionDetectada( int indexColumna, int indexFila );

    void selectionDetected( int index );
    void signal_newCameraFrame( cv::Mat * cameraTexture );

    /**
     * @brief signal_nonFaceDetected Se dispara cuando se no se detecta una cara luego de una cantidad de FRAMES_FACELESS
     * frames.
     */
    void signal_nonFaceDetected();

    /**
     * @brief signal_nonFaceDetectedForBack Se dispara cuando se no se detecta una cara luego de una cantidad de
     * FRAMES_FACELESS_BACK frames. Es para volver atras en la frase que se esta armando.
     */
    void signal_nonFaceDetectedForBack();
};

#endif // CAMERATHREAD_H
