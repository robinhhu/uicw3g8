#include "list_button.h"
#include "list_area.h"

#include <QDebug>

TheListArea::TheListArea(QWidget *parent) : QScrollArea(parent)
{
    setFixedWidth(300);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame);

    layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignHCenter);
    layout->setSpacing(0);

    widget = new QWidget();
    widget->setLayout(layout);
}

TheListArea::~TheListArea()
{

}
void TheListArea::setMediaList(QVector<VideoInfo*> *list)
{
    mediaList = list;

    QLayoutItem *child;
    while((child = layout->takeAt(0)) != nullptr)
    {
        if(child->widget())
        {
            child->widget()->setParent(NULL);
        }
        delete child;
    }
    for(int i=0; i<mediaList->size(); i++)
    {
        ListButton *b = new ListButton(i, mediaList->at(i)->getName(), mediaList->at(i)->getPic());
        layout->addWidget(b);

        connect(b, SIGNAL(listButtonClicked(int)), this, SLOT(listButtonClicked(int)));
    }
    int h = layout->count() * 64 + layout->contentsMargins().top() + layout->contentsMargins().bottom();
    widget->setFixedHeight(h);
    setWidget(widget);
}

void TheListArea::showList()
{
    setVisible(true);
}
void TheListArea::hideList()
{
    setHidden(true);
}

void TheListArea::listButtonClicked(int index)
{
    emit playVideo(index);
}
