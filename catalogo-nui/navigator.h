#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include <QWidget>
#include <QVector>
#include <QPalette>
#include <QDirIterator>
#include <QStringList>
#include <QDir>
#include <QLabel>
#include <QFont>

#include "image.h"
#include "keys.h"
#include "config/config.h"
/**
 * @brief The Navigator class
 * This class allows to navigate into a folder
 */
class Navigator : public QWidget
{
    Q_OBJECT

private:

    QLabel *title;
    QVector<Image *> *images;
    bool navOn;

    void loadFolder(QString folder);
    void alignImages();

public:

    void init();

    explicit Navigator(QWidget *parent = NULL);
    ~Navigator();

    QLabel *getTitle() const;
    void setTitle(QLabel *value);

    QVector<Image *> *getImages() const;
    void setImages(QVector<Image *> *value);

    void move(float level);

    bool navigatorOn(bool on);
    void changeFolder(QString folder);

    QString texto;


protected:

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

};

#endif // NAVIGATOR_H
