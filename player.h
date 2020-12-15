#ifndef PLAYER_H
#define PLAYER_H

#include "video_info.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QPushButton>
#include <QVideoWidget>
#include <QWidget>
#include <QDir>
#include <QDirIterator>
#include <QSlider>
#include <QImageReader>
#include <QLabel>

class Player : public QWidget
{
Q_OBJECT

public:
    Player(QWidget *parent = nullptr) : QWidget(parent)
    {
        theWindowLayout = new QVBoxLayout();
        theWindowLayout->setMargin(0);
        setLayout(theWindowLayout);

        addPlayerAndList();
        addProcessBar();
        addButtonBar();
        readList("/Users/zhangzihan/Desktop/player/videos");

        addConnects();

        setMinimumSize(640, 480);

        thePlayer->setMedia(*list->at(0).url);
        theVolumeSlider->setValue(70);
        thePlayer->play();
    }

private:
    QMap<QString, QIcon> *icons;

    QVBoxLayout *theWindowLayout;

    QWidget *theVideoAndListWidget;
    QHBoxLayout *theVideoAndListLayout;

    QWidget *theListWidget;
    QVBoxLayout *theListLayout;

    QVideoWidget *thePlayerWidget;
    QMediaPlayer *thePlayer;

    QSlider *theProcessBar;

    QWidget *theControlBarWidget;
    QHBoxLayout *theControlBarLayout;

    QPushButton *theBackwardButton;
    QPushButton *thePlayOrPauseButton;
    QPushButton *theForwardButton;
    QPushButton *theStopButon;

    double currentSpeed;
    QPushButton *theSpeedButton;

    QString currentLoop;
    QPushButton *theLoopButon;

    QPushButton *theVolumeButton;
    int lastVolume;
    QSlider *theVolumeSlider;

    QPushButton *theListButton;
    bool listHidden;
    int currentVideoId;
    QVector<VideoInfo> *list;

    void addPlayerAndList()
    {
        theVideoAndListWidget = new QWidget();
        theVideoAndListLayout = new QHBoxLayout();
        theVideoAndListLayout->setMargin(0);
        theVideoAndListWidget->setLayout(theVideoAndListLayout);

        thePlayerWidget = new QVideoWidget();
        thePlayer = new QMediaPlayer();
        thePlayer->setVideoOutput(thePlayerWidget);

        theListWidget = new QWidget();
        theListWidget->setFixedWidth(128);
        theListLayout = new QVBoxLayout();
        theListWidget->setLayout(theListLayout);

        theVideoAndListLayout->addWidget(thePlayerWidget);
        theVideoAndListLayout->addWidget(theListWidget);
        theWindowLayout->addWidget(theVideoAndListWidget);
    }

    void addProcessBar()
    {
        theProcessBar = new QSlider();
        theProcessBar->setOrientation(Qt::Horizontal);
        theProcessBar->setMinimum(0);
        theProcessBar->setSingleStep(1);
        theProcessBar->setFixedHeight(32);
        theWindowLayout->addWidget(theProcessBar);
    }

    void addButtonBar()
    {
        theControlBarWidget = new QWidget();
        theControlBarWidget->setFixedHeight(64);
        theControlBarLayout = new QHBoxLayout();
        theControlBarLayout->setContentsMargins(32, 0, 32, 0);
        theControlBarLayout->setSpacing(16);
        theControlBarWidget->setLayout(theControlBarLayout);
        theWindowLayout->addWidget(theControlBarWidget);

        addButtons();
    }

    void readIcons(QString loc)
    {
        icons = new QMap<QString, QIcon>();
        QDir dir(loc);
        QDirIterator it(dir);
        while (it.hasNext())
        {
            QFileInfo file(it.next());
            icons->insert(file.baseName(), QIcon(file.filePath()));
        }
    }

    void addButton(QPushButton *button, QIcon *icon)
    {
        button->setIcon(*icon);
        button->setIconSize(QSize(32, 32));
        button->setFixedSize(button->iconSize());
        button->setFlat(true);
        theControlBarLayout->addWidget(button);
    }

    void addButtons()
    {
        readIcons("/Users/zhangzihan/Desktop/player/icon");

        theBackwardButton = new QPushButton();
        addButton(theBackwardButton, &icons->find("backward").value());

        thePlayOrPauseButton = new QPushButton();
        addButton(thePlayOrPauseButton, &icons->find("pause").value());

        theForwardButton = new QPushButton();
        addButton(theForwardButton, &icons->find("forward").value());

        theStopButon = new QPushButton();
        addButton(theStopButon, &icons->find("stop").value());

        currentLoop = "inorder";
        theLoopButon = new QPushButton();
        addButton(theLoopButon, &icons->find("inorder").value());

        currentSpeed = 1;
        theSpeedButton = new QPushButton();
        addButton(theSpeedButton, &icons->find("1").value());

        theControlBarLayout->addStretch();

        theVolumeButton = new QPushButton();
        addButton(theVolumeButton, &icons->find("volume").value());

        theVolumeSlider = new QSlider();
        theVolumeSlider->setOrientation(Qt::Horizontal);
        theVolumeSlider->setFixedWidth(128);
        theVolumeSlider->setMinimum(0);
        theVolumeSlider->setMaximum(100);
        theVolumeSlider->setSingleStep(1);
        theControlBarLayout->addWidget(theVolumeSlider);

        theListButton = new QPushButton();
        listHidden = false;
        addButton(theListButton, &icons->find("list").value());
    }

    void readList(QString loc)
    {
        currentVideoId = 0;
        list = new QVector<VideoInfo>();
        QDir dir(loc);
        QDirIterator it(dir);
        while (it.hasNext())
        {
            QString file = it.next();
    #if defined(_WIN32)
            if (file.contains(".wmv")) // windows
    #else
            if (file.contains(".mp4")) // mac/linux
    #endif
            {
                QString thumb = file.left(file.length() - 4) +".png";
                QImageReader *imageReader = new QImageReader(thumb);
                QImage sprite = imageReader->read();
                QIcon* ico = new QIcon(QPixmap::fromImage(sprite));
                QUrl* url = new QUrl(QUrl::fromLocalFile(file));
                list->push_back(VideoInfo(url, ico));
            }
        }
    }

    void addConnects()
    {
        connect(thePlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(stateChanged(QMediaPlayer::State)));
        connect(theBackwardButton, SIGNAL(clicked()), this, SLOT(previousVideo()));
        connect(thePlayOrPauseButton, SIGNAL(clicked()), this, SLOT(playOrPause()));
        connect(theForwardButton, SIGNAL(clicked()), this, SLOT(nextVideo()));
        connect(theStopButon, SIGNAL(clicked()), this, SLOT(stop()));
        connect(theSpeedButton, SIGNAL(clicked()), this, SLOT(setSpeed()));
        connect(theLoopButon, SIGNAL(clicked()), this, SLOT(setLoop()));
        connect(theVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
        connect(theVolumeButton, SIGNAL(clicked()), this, SLOT(mute()));

        connect(thePlayer, &QMediaPlayer::durationChanged, theProcessBar, &QSlider::setMaximum);
        connect(thePlayer, &QMediaPlayer::positionChanged, theProcessBar, &QSlider::setValue);
        connect(theProcessBar, &QSlider::sliderMoved, thePlayer, &QMediaPlayer::setPosition);

        connect(theListButton, SIGNAL(clicked()), this, SLOT(hideList()));
    }

private slots:
    void stateChanged(QMediaPlayer::State ms)
    {
        switch(ms)
        {
            case QMediaPlayer::State::StoppedState:
                thePlayOrPauseButton->setIcon(icons->find("play").value());
                if(currentLoop == "loop")
                {
                    thePlayer->play();
                }
                else
                {
                    nextVideo();
                }
                break;
            case QMediaPlayer::State::PausedState:
                thePlayOrPauseButton->setIcon(icons->find("play").value());
                break;
            case QMediaPlayer::State::PlayingState:
                thePlayOrPauseButton->setIcon(icons->find("pause").value());
                break;
            default:
                break;
        }
    }

    void previousVideo()
    {
        if(currentLoop == "loop" || currentLoop == "inorder")
        {
            currentVideoId = (currentVideoId + list->size() - 1) % list->size();
        }
        else
        {
            currentVideoId = rand() % list->size();
        }
        thePlayer->setMedia(*list->at(currentVideoId).url);
        thePlayer->play();
    }

    void playOrPause()
    {
        if(thePlayer->state() == QMediaPlayer::State::PausedState || thePlayer->state() == QMediaPlayer::State::StoppedState)
        {
            thePlayer->play();
        }
        else if(thePlayer->state() == QMediaPlayer::State::PlayingState)
        {
            thePlayer->pause();
        }
    }

    void nextVideo()
    {
        if(currentLoop == "loop" || currentLoop == "inorder")
        {
            currentVideoId = (currentVideoId + 1) % list->size();
        }
        else
        {
            currentVideoId = rand() % list->size();
        }
        thePlayer->setMedia(*list->at(currentVideoId).url);
        thePlayer->play();
    }

    void stop()
    {
        thePlayer->stop();
    }

    void setSpeed()
    {
        if(currentSpeed == 1)
        {
            currentSpeed = 2;
            theSpeedButton->setIcon(icons->find("2").value());
            thePlayer->setPlaybackRate(currentSpeed);
        }
        else if(currentSpeed == 2)
        {
            currentSpeed = 4;
            theSpeedButton->setIcon(icons->find("4").value());
            thePlayer->setPlaybackRate(currentSpeed);
        }
        else if(currentSpeed == 4)
        {
            currentSpeed = 0.5;
            theSpeedButton->setIcon(icons->find("05").value());
            thePlayer->setPlaybackRate(currentSpeed);
        }
        else if(currentSpeed == 0.5)
        {
            currentSpeed = 1;
            theSpeedButton->setIcon(icons->find("1").value());
            thePlayer->setPlaybackRate(currentSpeed);
        }
    }

    void setLoop()
    {
        if(currentLoop == "inorder")
        {
            currentLoop = "loop";
        }
        else if(currentLoop == "loop")
        {
            currentLoop = "random";
        }
        else if(currentLoop == "random")
        {
            currentLoop = "inorder";
        }
        theLoopButon->setIcon(icons->find(currentLoop).value());
    }

    void setVolume(int v)
    {
        thePlayer->setVolume(v);
    }

    void mute()
    {
        if(theVolumeSlider->value() != 0)
        {
            lastVolume = theVolumeSlider->value();
            theVolumeSlider->setValue(0);
            theVolumeButton->setIcon(icons->find("mute").value());
        }
        else
        {
            theVolumeSlider->setValue(lastVolume);
            theVolumeButton->setIcon(icons->find("volume").value());
        }
    }

    void hideList()
    {
        if(listHidden == true)
        {
            listHidden = false;
            theListWidget->setVisible(true);
        }
        else
        {
            listHidden = true;
            theListWidget->setVisible(false);
        }
    }
};

#endif // PLAYER_H
