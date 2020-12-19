#include "the_menu.h"

TheMenu::TheMenu(QMap<QString, QIcon> *icons, QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout();
    setLayout(layout);

    filter = new FilterWidget(icons);
    album = new AlbumWidget();
    menuBar = new MenuBar(icons);
    infoBar = new InfoBar(icons);

    layout->addWidget(filter);
    layout->addWidget(album);
    layout->addWidget(menuBar);
    layout->addWidget(infoBar);

    showMenuBar();

    addConnect();
}

TheMenu::~TheMenu()
{

}

void TheMenu::addConnect()
{
    connect(filter, SIGNAL(search(QStringList)), album, SLOT(getResults(QStringList)));

    connect(menuBar, SIGNAL(upload(QStringList)), album, SLOT(addFiles(QStringList)));
    connect(menuBar, SIGNAL(upload(QStringList)), filter, SLOT(defaultSearch()));
    connect(menuBar, SIGNAL(toPlay()), this, SLOT(toPlaySlot()));

    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), this, SLOT(videoClicked(QVector<VideoInfo*>*)));
    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), infoBar, SLOT(setInputPlaceHolder(QVector<VideoInfo*>*)));
    connect(album, SIGNAL(videoClicked(QVector<VideoInfo*>*)), infoBar, SLOT(clearLabels()));

    connect(infoBar, SIGNAL(back()), this, SLOT(showMenuBar()));
    connect(infoBar, SIGNAL(playVideo(QVector<VideoInfo*>*)), this, SLOT(toPlayOneSlot(QVector<VideoInfo*>*)));
}

void TheMenu::showMenuBar()
{
    menuBar->setVisible(true);
    infoBar->setHidden(true);
}
void TheMenu::showInfoBar()
{
    menuBar->setHidden(true);
    infoBar->setVisible(true);
}

void TheMenu::toPlaySlot()
{
    QVector<VideoInfo*> *list = album->getFilterList();
    if(list->size() > 0)
    {
        emit playListChanged(list);
    }
}

void TheMenu::videoClicked(QVector<VideoInfo*> *video)
{
    showInfoBar();
    infoBar->setVideo(video);
}

void TheMenu::toPlayOneSlot(QVector<VideoInfo*> *video)
{
    emit playListChanged(video);
    showMenuBar();
}
