#include "album_widget.h"

#include <QDir>
#include <QDirIterator>

AlbumWidget::AlbumWidget()
{
    layout = new AlbumLayout();
    setLayout(layout);

    allList = new QVector<VideoInfo>();
    filterList = new QVector<VideoInfo>();

    readList("/Users/zhangzihan/Desktop/player/videos");

    showResults();
}

AlbumWidget::~AlbumWidget()
{
    delete allList;
    delete filterList;
}

QVector<VideoInfo>* AlbumWidget::getFilterList() const
{
    return filterList;
}

void AlbumWidget::showResults()
{
    QLayoutItem *child;
    while((child = layout->takeAt(0)) != nullptr)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    for(VideoInfo i : *filterList)
    {
        QPushButton *b = new QPushButton(i.getName());
        b->setIconSize(QSize(128, 64));
        b->setIcon(i.getIcon());
        b->setFixedSize(256, 100);
        layout->addWidget(b);
    }
}




void AlbumWidget::readList(QString loc)
{
    QDir dir(loc);
    QDirIterator it(dir);
    while (it.hasNext())
    {
        QString file = it.next();
        if(file.contains(".wmv")){
            allList->push_back(VideoInfo(QUrl(file)));
        }
    }
    filterList = allList;
}
