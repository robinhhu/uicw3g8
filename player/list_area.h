#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "video_info.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class TheListArea : public QScrollArea
{
Q_OBJECT

public:
    TheListArea(QWidget *parent=nullptr);
    ~TheListArea();

    void setMediaList(QVector<VideoInfo*> *list);

public slots:
    void showList();
    void hideList();

private:
    QVBoxLayout *layout;
    QWidget *widget;

    QVector<VideoInfo*> *mediaList;

private slots:
    void listButtonClicked(int index);

signals:
    void playVideo(int index);
};

#endif // LIST_WIDGET_H
