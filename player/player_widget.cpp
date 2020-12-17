#include "player_widget.h"

#include <QTime>

PlayerWidget::PlayerWidget(QWidget* parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);

    videoWidget = new QVideoWidget();
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setVideoOutput(videoWidget);

    processSliderWidget = new QWidget();
    processSliderWidget->setFixedHeight(64);
    processLayout = new QHBoxLayout();
    processLayout->setContentsMargins(32, 0, 32, 0);
    processLayout->setSpacing(32);
    processSliderWidget->setLayout(processLayout);

    processSlider = new QSlider(Qt::Horizontal);

    processTime = new QLabel();
    processTime->setFixedWidth(150);

    processLayout->addWidget(processSlider);
    processLayout->addWidget(processTime);

    layout->addWidget(videoWidget);
    layout->addWidget(processSliderWidget);

    connect(mediaPlayer, &QMediaPlayer::durationChanged, processSlider, &QSlider::setMaximum);
    connect(mediaPlayer, &QMediaPlayer::positionChanged, processSlider, &QSlider::setValue);
    connect(processSlider, &QSlider::sliderMoved, mediaPlayer, &QMediaPlayer::setPosition);

    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(setTime()));
    connect(mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(mediaFinished()));
}

PlayerWidget::~PlayerWidget()
{

}

void PlayerWidget::setMedia(QUrl url)
{
    mediaPlayer->setMedia(url);
}

void PlayerWidget::setSpeed(double speed)
{
    mediaPlayer->setPlaybackRate(speed);
}

void PlayerWidget::setVolume(int volume)
{
    mediaPlayer->setVolume(volume);
}

void PlayerWidget::play()
{
    mediaPlayer->play();
}

void PlayerWidget::pause()
{
    mediaPlayer->pause();
}
void PlayerWidget::stop()
{
    mediaPlayer->stop();
}

void PlayerWidget::setTime()
{
    QString currentTime = QTime(0, 0, 0).addMSecs(mediaPlayer->position()).toString();
    QString totalTime = QTime(0, 0, 0).addMSecs(mediaPlayer->duration()).toString();
    processTime->setText(currentTime + "/" + totalTime);
}
void PlayerWidget::mediaFinished()
{
    if(mediaPlayer->position() == mediaPlayer->duration() && mediaPlayer->position() > 0)
    {
        emit finished();
    }
}
