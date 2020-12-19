#ifndef LIST_WIDGET_H
#define LIST_WIDGET_H

#include "video_info.h"

#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>

class TheListWidget : public QWidget
{
Q_OBJECT

public:
    TheListWidget(QWidget *parent=nullptr);
    ~TheListWidget();

    void setMediaList(QVector<VideoInfo*> *list);

public slots:
    void showList();
    void hideList();

private:
    QVBoxLayout *layout;

    QVector<VideoInfo*> *mediaList;

private slots:
    void listButtonClicked(int index);

signals:
    void playVideo(int index);
};

#endif // LIST_WIDGET_H
