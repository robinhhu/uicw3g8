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

    QVector<VideoInfo*>* getFilterList();

private:
    AlbumLayout *layout;

    QVector<VideoInfo*> *allList;
    QVector<VideoInfo*> *filterList;
    QVector<VideoInfo*> *oneVideo;

    void showResults();

public slots:
    void addFiles(QStringList files);
    void getResults(QStringList infos);

private slots:
    void videoButtonClicked(VideoInfo *video);

signals:
    void videoClicked(QVector<VideoInfo*> *video);
};

#endif // ALBUM_WIDGET_H
