#include "album_button.h"
#include "album_widget.h"

#include <QDir>
#include <QDirIterator>
#include <QInputDialog>
#include <QMessageBox>

#include <QDebug>

AlbumWidget::AlbumWidget()
{
    layout = new AlbumLayout();
    layout->setContentsMargins(64, 32, 64, 0);
    layout->setSpacing(32);
    setLayout(layout);

    allList = new QVector<VideoInfo*>();
    filterList = new QVector<VideoInfo*>();
    oneVideo = new QVector<VideoInfo*>();
}

AlbumWidget::~AlbumWidget()
{
    for(VideoInfo* v : *allList)
    {
        delete v;
    }
    delete allList;
    for(VideoInfo* v : *filterList)
    {
        delete v;
    }
    delete filterList;
    for(VideoInfo* v : *oneVideo)
    {
        delete v;
    }
    delete oneVideo;
}

QVector<VideoInfo*>* AlbumWidget::getFilterList()
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
    for(VideoInfo* i : *filterList)
    {
        AlbumButton *b = new AlbumButton(i);
        layout->addWidget(b);

        connect(b, SIGNAL(albumButtonClicked(VideoInfo*)), this, SLOT(videoButtonClicked(VideoInfo*)));
    }
}

void AlbumWidget::addFiles(QStringList files)
{
    for(QString file : files)
    {
        if(file != nullptr && file != "")
        {
            bool in = false;
            for(VideoInfo* info : *allList)
            {
                if(QUrl(file) == info->getUrl())
                {
                    in = true;
                    break;
                }
            }
            if(in == true)
            {
                QMessageBox::information(this, "打开失败", "文件已存在！");
            }
            else
            {
                VideoInfo *video = new VideoInfo(QUrl(file));
                allList->push_back(video);
            }
        }
    }
}

void AlbumWidget::getResults(QStringList infos)
{
    filterList->clear();
    for(VideoInfo *v : *allList)
    {
        if(v->matched(infos) == true)
        {
            filterList->push_back(v);
        }
    }
    showResults();
}

void AlbumWidget::videoButtonClicked(VideoInfo *video)
{
    oneVideo->clear();
    oneVideo->push_back(video);
    emit videoClicked(oneVideo);
}
