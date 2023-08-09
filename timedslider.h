#ifndef TIMEDSLIDER_H
#define TIMEDSLIDER_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QDir>
#include <QDebug>
#include <QVector> //vector(dynamic)
#include <QTimer>
#include <QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class timedslider; }
QT_END_NAMESPACE

class timedslider : public QMainWindow
{
    Q_OBJECT

public:
    timedslider(QWidget *parent = nullptr);
    ~timedslider();
private:
    void paintEvent(QPaintEvent*);
    void timerEvent(QTimerEvent* event);
    //to load images into vector from path given
    void loadImages(const QString& path);
public slots:
    void on_btnStart_clicked();

private:
    Ui::timedslider *ui;
    QVector<QImage> vecImages;
    int m_index;
    int m_timerID;
    bool isStarted;

};
#endif // TIMEDSLIDER_H
