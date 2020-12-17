#ifndef PLAYER_WIDGET_H
#define PLAYER_WIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMediaPlayer>
#include <QSlider>
#include <QVBoxLayout>
#include <QVideoWidget>
#include <QWidget>

class PlayerWidget : public QWidget
{
Q_OBJECT

public:
    PlayerWidget(QWidget* parent=nullptr);
    ~PlayerWidget();

public slots:
    void setMedia(QUrl url);
    void setSpeed(double speed);
    void setVolume(int volume);
    void play();
    void pause();
    void stop();

private:
    QVBoxLayout *layout;

    QVideoWidget* videoWidget;
    QMediaPlayer* mediaPlayer;

    QWidget *processSliderWidget;
    QHBoxLayout *processLayout;
    QSlider *processSlider;
    QLabel *processTime;

private slots:
    void setTime();
    void mediaFinished();

signals:
    void finished();
};

#endif // PLAYER_WIDGET_H
