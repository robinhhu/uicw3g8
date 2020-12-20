#ifndef THE_MENU_H
#define THE_MENU_H

#include "album_area.h"
#include "filter_widget.h"
#include "info_bar.h"
#include "menu_bar.h"
#include "video_info.h"

#include <QVBoxLayout>
#include <QWidget>

class TheMenu : public QWidget
{
Q_OBJECT

public:
    TheMenu(QMap<QString, QIcon> *icons, QWidget *parent=nullptr);
    ~TheMenu();

private:
    QVBoxLayout *layout;

    FilterWidget *filter;
    AlbumArea *album;
    MenuBar *menuBar;
    InfoBar *infoBar;

    void addConnect();

private slots:
    void showMenuBar();
    void showInfoBar();

    void toPlaySlot();
    void videoClicked(QVector<VideoInfo*> *video);
    void toPlayOneSlot(QVector<VideoInfo*> *video);

signals:
    void playListChanged(QVector<VideoInfo*> *list);
};

#endif // THE_MENU_H
