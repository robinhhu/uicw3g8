#ifndef ALBUM_WIDGET_H
#define ALBUM_WIDGET_H

#include "album_layout.h"
#include "video_info.h"

#include <QPushButton>
#include <QWidget>

class AlbumArea : public QScrollArea
{
Q_OBJECT

public:
    AlbumArea();
    ~AlbumArea();

    void resizeEvent(QResizeEvent *e);

    QVector<VideoInfo*>* getFilterList();

private:
    AlbumLayout *layout;
    QWidget *widget;

    QVector<VideoInfo*> *allList;
    QVector<VideoInfo*> *filterList;
    QVector<VideoInfo*> *oneVideo;

    void showResults();

public slots:
    void addFiles(QStringList files);
    void getResults(QStringList infos);

private slots:
    void videoButtonClicked(VideoInfo *video);
    void changeWidgetSize(QSize size);

signals:
    void videoClicked(QVector<VideoInfo*> *video);
};

#endif // ALBUM_WIDGET_H
