#ifndef CONTROL_BAR_H
#define CONTROL_BAR_H

#include "video_info.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMap>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class ControlBar : public QWidget
{
Q_OBJECT

public:
    ControlBar(QMap<QString, QIcon> *icons, QWidget* parent=nullptr);
    ~ControlBar();

    void setMediaList(QVector<VideoInfo*> *list);

private:
    QHBoxLayout *layout;

    QMap<QString, QIcon>* icons;

    QPushButton *menuButton;

    bool isPlaying;
    QPushButton *playOrPauseButton;

    QPushButton *stopButton;

    QString loopStatus;
    QPushButton *loopButton;

    double speed;
    QPushButton *speedButton;

    bool isMute;
    int lastVolume;
    QPushButton *volumeButton;
    QSlider *volumeSlider;
    QLabel *volumeValue;

    QPushButton *backwardButton;
    QPushButton *forwardButton;

    int currentMedia;
    QVector<VideoInfo*> *mediaList;

    bool isHiddenList;
    QPushButton *listButton;

    void setButton(QPushButton *button, QString name);
    void addItems();

    void addConnect();

public slots:
    void playFinishedAction();
    void listButtonClickedSlot(int index);

private slots:
    void menuButtonClicked();
    void playOrPauseButtonClicked();
    void stopButtonClicked();
    void backwardButtonClicked();
    void forwardButtonClickede();
    void loopButtonClicked();
    void speedButtonClicked();
    void volumeButtonClicked();
    void volumeSliderChanged(int newValue);
    void listButtonClicked();

signals:
    void backToMenu();
    void shouldPlay();
    void shouldPause();
    void shouldStop();
    void mediaChanged(QUrl url);
    void speedChanged(double newSpeed);
    void volumeChanged(int newVolume);
    void hideList();
    void showList();
};

#endif // CONTROL_BAR_H
