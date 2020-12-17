#include "control_bar.h"

#include <QDir>
#include <QDirIterator>
#include <QIcon>

ControlBar::ControlBar(QMap<QString, QIcon> *icons, QWidget* parent) : QWidget(parent)
{
    this->icons = icons;

    setFixedHeight(64);
    layout = new QHBoxLayout();
    layout->setContentsMargins(32, 0, 32, 0);
    layout->setSpacing(16);
    setLayout(layout);

    addItems();
    addConnect();
}

ControlBar::~ControlBar()
{

}

void ControlBar::setMediaList(QVector<VideoInfo> *list)
{
    currentMedia = 0;
    mediaList = list;
    emit mediaChanged(mediaList->at(currentMedia).getUrl());
}

void ControlBar::setButton(QPushButton *button, QString name)
{
    button->setIcon(icons->find(name).value());
    button->setIconSize(QSize(32, 32));
    button->setFixedSize(button->iconSize());
    button->setFlat(true);
    layout->addWidget(button);
}

void ControlBar::addItems()
{
    menuButton = new QPushButton();
    setButton(menuButton, "backtomenu");

    backwardButton = new QPushButton();
    setButton(backwardButton, "backward");

    isPlaying = false;
    playOrPauseButton = new QPushButton();
    setButton(playOrPauseButton, "play");

    forwardButton = new QPushButton();
    setButton(forwardButton, "forward");

    stopButton = new QPushButton();
    setButton(stopButton, "stop");

    loopStatus = "inorder";
    loopButton = new QPushButton();
    setButton(loopButton, "inorder");

    speed = 1;
    speedButton = new QPushButton();
    setButton(speedButton, "1");

    layout->addStretch();

    isMute = false;
    lastVolume = 70;
    volumeButton = new QPushButton();
    setButton(volumeButton, "volume");
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setFixedWidth(128);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setSingleStep(1);
    volumeSlider->setValue(lastVolume);
    layout->addWidget(volumeSlider);
    volumeValue = new QLabel();
    volumeValue->setFixedSize(32, 32);
    volumeValue->setNum(volumeSlider->value());
    layout->addWidget(volumeValue);

    isHiddenList = false;
    listButton = new QPushButton();
    setButton(listButton, "list");
}

void ControlBar::addConnect()
{
    connect(volumeSlider, SIGNAL(valueChanged(int)), volumeValue, SLOT(setNum(int)));

    connect(menuButton, SIGNAL(clicked()), this, SLOT(menuButtonClicked()));
    connect(playOrPauseButton, SIGNAL(clicked()), this, SLOT(playOrPauseButtonClicked()));
    connect(stopButton, SIGNAL(clicked()), this, SLOT(stopButtonClicked()));
    connect(backwardButton, SIGNAL(clicked()), this, SLOT(backwardButtonClicked()));
    connect(forwardButton, SIGNAL(clicked()), this, SLOT(forwardButtonClickede()));
    connect(loopButton, SIGNAL(clicked()), this, SLOT(loopButtonClicked()));
    connect(speedButton, SIGNAL(clicked()), this, SLOT(speedButtonClicked()));
    connect(volumeButton, SIGNAL(clicked()), this, SLOT(volumeButtonClicked()));
    connect(volumeSlider, SIGNAL(valueChanged(int)), this, SLOT(volumeSliderChanged(int)));
    connect(listButton, SIGNAL(clicked()), this, SLOT(listButtonClicked()));
}

void ControlBar::playFinishedAction()
{
    int nextMedia = currentMedia;
    if(loopStatus == "inorder")
    {
        nextMedia = (currentMedia + 1) % mediaList->size();
    }
    else if(loopStatus == "random")
    {
        nextMedia = rand() % mediaList->size();
    }
    QUrl url = mediaList->at(nextMedia).getUrl();
    emit mediaChanged(url);
    emit shouldPlay();
    isPlaying = true;
    playOrPauseButton->setIcon(icons->find("pause").value());
    currentMedia = nextMedia;
}

void ControlBar::menuButtonClicked()
{
    emit shouldStop();
    emit backToMenu();
    isPlaying = false;
    playOrPauseButton->setIcon(icons->find("play").value());
}

void ControlBar::playOrPauseButtonClicked()
{
    if(isPlaying == true)
    {
        emit shouldPause();
        isPlaying = false;
        playOrPauseButton->setIcon(icons->find("play").value());
    }
    else
    {
        emit shouldPlay();
        isPlaying = true;
        playOrPauseButton->setIcon(icons->find("pause").value());
    }
}

void ControlBar::stopButtonClicked()
{
    emit shouldStop();
    isPlaying = false;
    playOrPauseButton->setIcon(icons->find("play").value());
}

void ControlBar::backwardButtonClicked()
{
    int nextMedia = currentMedia;
    if(loopStatus == "inorder" || loopStatus == "loop")
    {
        nextMedia = (currentMedia + mediaList->size() - 1) % mediaList->size();
    }
    else if(loopStatus == "random")
    {
        nextMedia = rand() % mediaList->size();
    }
    QUrl url = mediaList->at(nextMedia).getUrl();
    emit mediaChanged(url);
    emit shouldPlay();
    isPlaying = true;
    playOrPauseButton->setIcon(icons->find("pause").value());
    currentMedia = nextMedia;
}

void ControlBar::forwardButtonClickede()
{
    int nextMedia = currentMedia;
    if(loopStatus == "inorder" || loopStatus == "loop")
    {
        nextMedia = (currentMedia + 1) % mediaList->size();
    }
    else if(loopStatus == "random")
    {
        nextMedia = rand() % mediaList->size();
    }
    QUrl url = mediaList->at(nextMedia).getUrl();
    emit mediaChanged(url);
    emit shouldPlay();
    isPlaying = true;
    playOrPauseButton->setIcon(icons->find("pause").value());
    currentMedia = nextMedia;
}

void ControlBar::loopButtonClicked()
{
    if(loopStatus == "inorder")
    {
        loopStatus = "loop";
    }
    else if(loopStatus == "loop")
    {
        loopStatus = "random";
    }
    else if(loopStatus == "random") {
        loopStatus = "inorder";
    }
    loopButton->setIcon(icons->find(loopStatus).value());
}

void ControlBar::speedButtonClicked()
{
    if(speed == 1)
    {
        speed = 2;
        emit speedChanged(speed);
        speedButton->setIcon(icons->find("2").value());
    }
    else if(speed == 2)
    {
        speed = 4;
        emit speedChanged(speed);
        speedButton->setIcon(icons->find("4").value());
    }
    else if(speed == 4)
    {
        speed = 0.5;
        emit speedChanged(speed);
        speedButton->setIcon(icons->find("05").value());
    }
    else if(speed == 0.5)
    {
        speed = 1;
        emit speedChanged(speed);
        speedButton->setIcon(icons->find("1").value());
    }
}

void ControlBar::volumeButtonClicked()
{
    if(isMute == true)
    {
        volumeSlider->setValue(lastVolume);
    }
    else
    {
        lastVolume = volumeSlider->value();
        volumeSlider->setValue(0);
    }
}

void ControlBar::volumeSliderChanged(int newValue)
{
    emit volumeChanged(newValue);
    if(newValue == 0)
    {
        isMute = true;
        volumeButton->setIcon(icons->find("mute").value());
    }
    else
    {
        isMute = false;
        volumeButton->setIcon(icons->find("volume").value());
    }
}

void ControlBar::listButtonClicked()
{
    if(isHiddenList == true)
    {
        emit displayList();
        isHiddenList = false;
    }
    else
    {
        emit hideList();
        isHiddenList = true;
    }
}
