#include "album_layout.h"

#include <QDebug>
#include <QPushButton>

AlbumLayout::AlbumLayout() : QLayout()
{

}

AlbumLayout::~AlbumLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void AlbumLayout::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);

    QMargins margins =  contentsMargins();
    int space = spacing();

    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            QPushButton *button = static_cast<QPushButton *>(o->widget());

            int rowNum = (r.width() - margins.left() - margins.right() + space) / (button->width() + space);
            int rowSpace = (r.width() - rowNum * button->width()) / (rowNum + 1);

            if (button == NULL)
            {
                qDebug() << "warning, unknown widget class in layout" << endl;
            }
            else
            {
                int xLoc = (i % rowNum) * (button->width() + rowSpace) + rowSpace;
                int yLoc = (i / rowNum) * (button->height() + space) + margins.top();
                button->setGeometry(xLoc, yLoc, button->width(), button->height());
            }
        }
        catch (bad_cast) {
            qDebug() << "warning, unknown widget class in layout" << endl;
        }
    }
}

// following methods provide a trivial list-based implementation of the QLayout class
int AlbumLayout::count() const
{
    return list_.size();
}

QLayoutItem *AlbumLayout::itemAt(int idx) const
{
    return list_.value(idx);
}

QLayoutItem *AlbumLayout::takeAt(int idx)
{
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void AlbumLayout::addItem(QLayoutItem *item)
{
    list_.append(item);
}

QSize AlbumLayout::sizeHint() const
{
    return minimumSize();
}

QSize AlbumLayout::minimumSize() const
{
    return QSize(50, 1200);
}

