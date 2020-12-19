#include "list_button.h"
#include "list_widget.h"

TheListWidget::TheListWidget(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 1200);

    layout = new QVBoxLayout();
    layout->setSpacing(32);
    setLayout(layout);
}

TheListWidget::~TheListWidget()
{

}
void TheListWidget::setMediaList(QVector<VideoInfo*> *list)
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
        ListButton *b = new ListButton(i, mediaList->at(i)->getName(), mediaList->at(i)->getIcon());
        layout->addWidget(b);

        connect(b, SIGNAL(listButtonClicked(int)), this, SLOT(listButtonClicked(int)));
    }
}

void TheListWidget::showList()
{
    setVisible(true);
}
void TheListWidget::hideList()
{
    setHidden(true);
}

void TheListWidget::listButtonClicked(int index)
{
    emit playVideo(index);
}
