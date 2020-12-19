#include "album_button.h"

AlbumButton::AlbumButton(VideoInfo *video) : QPushButton(video->getName())
{
    this->video = video;
    setIconSize(QSize(128, 64));
    setIcon(video->getIcon());
    setFixedSize(256, 100);

    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));
}

AlbumButton::~AlbumButton()
{

}

void AlbumButton::isClicked()
{
    emit albumButtonClicked(video);
}
