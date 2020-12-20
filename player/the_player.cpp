#include "the_player.h"

ThePlayer::ThePlayer(QMap<QString, QIcon> *icons, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    layout->setMargin(0);
    setLayout(layout);

    playerAndListLayout = new QHBoxLayout();
    playerAndListLayout->setMargin(0);
    playerAndListLayout->setSpacing(0);
    playerAndListWidget = new QWidget();
    playerAndListWidget->setLayout(playerAndListLayout);

    playerWidget = new PlayerWidget();
    controlBar = new ControlBar(icons);
    listWidget = new TheListArea();

    playerAndListLayout->addWidget(playerWidget);
    playerAndListLayout->addWidget(listWidget);
    layout->addWidget(playerAndListWidget);
    layout->addWidget(controlBar);

    addConnect();
}

ThePlayer::~ThePlayer()
{

}

void ThePlayer::addConnect()
{
    connect(playerWidget, SIGNAL(finished()), controlBar, SLOT(playFinishedAction()));

    connect(listWidget, SIGNAL(playVideo(int)), controlBar, SLOT(listButtonClickedSlot(int)));

    connect(controlBar, SIGNAL(backToMenu()), this, SLOT(backToMenuSlot()));
    connect(controlBar, SIGNAL(shouldPlay()), playerWidget, SLOT(play()));
    connect(controlBar, SIGNAL(shouldPause()), playerWidget, SLOT(pause()));
    connect(controlBar, SIGNAL(shouldStop()), playerWidget, SLOT(stop()));
    connect(controlBar, SIGNAL(mediaChanged(QUrl)), playerWidget, SLOT(setMedia(QUrl)));
    connect(controlBar, SIGNAL(speedChanged(double)), playerWidget, SLOT(setSpeed(double)));
    connect(controlBar, SIGNAL(volumeChanged(int)), playerWidget, SLOT(setVolume(int)));
    connect(controlBar, SIGNAL(hideList()), listWidget, SLOT(hideList()));
    connect(controlBar, SIGNAL(showList()), listWidget, SLOT(showList()));
}

void ThePlayer::setMediaList(QVector<VideoInfo*> *list)
{
    controlBar->setMediaList(list);
    listWidget->setMediaList(list);
}

void ThePlayer::backToMenuSlot()
{
    emit backToMenu();
}
