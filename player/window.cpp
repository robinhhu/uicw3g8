#include "window.h"

#include <QDir>
#include <QDirIterator>

Window::Window()
{
    layout = new QHBoxLayout();
    layout->setMargin(0);
    setLayout(layout);

    icons = readIcons("../icon");

    theMenu = new TheMenu(icons);
    thePlayer = new ThePlayer(icons);

    layout->addWidget(theMenu);
    layout->addWidget(thePlayer);

    addConnect();

    setMinimumSize(1080, 720);

    showMenu();
}

Window::~Window()
{
    delete icons;
}

QMap<QString, QIcon>* Window::readIcons(QString loc)
{
    QMap<QString, QIcon>* icons = new QMap<QString, QIcon>();
    QDir dir(loc);
    QDirIterator it(dir);
    while (it.hasNext())
    {
        QFileInfo file(it.next());
        icons->insert(file.baseName(), QIcon(file.filePath()));
    }
    return icons;
}

void Window::addConnect()
{
    connect(thePlayer, SIGNAL(backToMenu()), this, SLOT(showMenu()));
    connect(theMenu, SIGNAL(playListChanged(QVector<VideoInfo*>*)), this, SLOT(showPlayer()));

    connect(theMenu, SIGNAL(playListChanged(QVector<VideoInfo*>*)), thePlayer, SLOT(setMediaList(QVector<VideoInfo*>*)));
}

void Window::showMenu()
{
    theMenu->setVisible(true);
    thePlayer->setHidden(true);
}
void Window::showPlayer()
{
    theMenu->setHidden(true);
    thePlayer->setVisible(true);
}
