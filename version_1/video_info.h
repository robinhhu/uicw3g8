#ifndef VIDEO_INFO_H
#define VIDEO_INFO_H

#include <QIcon>
#include <QUrl>

class VideoInfo
{
public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    VideoInfo (QUrl* url, QIcon* icon) : url (url), icon (icon) {}
};

#endif // VIDEO_INFO_H
