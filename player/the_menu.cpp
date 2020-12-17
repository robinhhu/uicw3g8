#include "the_menu.h"

TheMenu::TheMenu(QMap<QString, QIcon> *icons, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    setLayout(layout);

    album = new AlbumWidget();
    menuBar = new MenuBar(icons);

    layout->addWidget(album);
    layout->addWidget(menuBar);

    addConnect();
}

TheMenu::~TheMenu()
{

}

void TheMenu::addConnect()
{
    connect(menuBar, SIGNAL(toPlay()), this, SLOT(toPlaySlot()));
}

void TheMenu::toPlaySlot()
{
    QVector<VideoInfo> *list = album->getFilterList();
    if(list->size() > 0)
    {
        emit playListChanged(list);
    }
}

