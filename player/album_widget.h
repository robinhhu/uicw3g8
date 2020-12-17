#ifndef ALBUM_WIDGET_H
#define ALBUM_WIDGET_H

#include "album_layout.h"
#include "video_info.h"

#include <QPushButton>
#include <QWidget>

class AlbumWidget : public QWidget
{
Q_OBJECT

public:
    AlbumWidget();
    ~AlbumWidget();

    QVector<VideoInfo>* getFilterList() const;

    //临时
    void readList(QString loc);

private:
    AlbumLayout *layout;

    QVector<VideoInfo> *allList;
    QVector<VideoInfo> *filterList;

    void showResults();
};

#endif // ALBUM_WIDGET_H
