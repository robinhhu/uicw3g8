#ifndef THE_MENU_H
#define THE_MENU_H

#include "album_widget.h"
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

    AlbumWidget *album;
    MenuBar *menuBar;

    void addConnect();

private slots:
    void toPlaySlot();

signals:
    void playListChanged(QVector<VideoInfo> *list);
};

#endif // THE_MENU_H
