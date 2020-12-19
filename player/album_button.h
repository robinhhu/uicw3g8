#ifndef ALBUM_BUTTON_H
#define ALBUM_BUTTON_H

#include "video_info.h"

#include <QPushButton>
#include <QUrl>



class AlbumButton : public QPushButton
{
Q_OBJECT

public:
    AlbumButton(VideoInfo *video);
    ~AlbumButton();

private:
    VideoInfo *video;

private slots:
    void isClicked();

signals:
    void albumButtonClicked(VideoInfo *video);
};

#endif // ALBUM_BUTTON_H
