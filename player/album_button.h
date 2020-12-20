#ifndef ALBUM_BUTTON_H
#define ALBUM_BUTTON_H

#include "video_info.h"

#include <QLabel>
#include <QPushButton>
#include <QUrl>
#include <QVBoxLayout>



class AlbumButton : public QPushButton
{
Q_OBJECT

public:
    AlbumButton(VideoInfo *video);
    ~AlbumButton();

private:
    QVBoxLayout *layout;
    VideoInfo *video;

    QLabel *pic;
    QLabel *name;

private slots:
    void isClicked();

signals:
    void albumButtonClicked(VideoInfo *video);
};

#endif // ALBUM_BUTTON_H
