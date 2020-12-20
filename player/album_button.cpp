#include "album_button.h"

AlbumButton::AlbumButton(VideoInfo *video)
{
    setFixedSize(256, 200);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignHCenter);
    layout->setMargin(0);
    layout->setSpacing(16);
    setLayout(layout);

    QPixmap pMap = video->getPic();
    if(pMap.isNull() == false)
    {
        pic = new QLabel();
        pic->setPixmap(pMap.scaled(QSize(252, 252), Qt::KeepAspectRatio));
        layout->addWidget(pic);
    }


    name = new QLabel(video->getName());
    name->setAlignment(Qt::AlignCenter);
    layout->addWidget(name);

    this->video = video;

    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));
}

AlbumButton::~AlbumButton()
{

}

void AlbumButton::isClicked()
{
    emit albumButtonClicked(video);
}
