#include "player_layoyt.h"

void PlayerLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
//    for (int i = 0; i < list_.size(); i++) {
//        QLayoutItem *o = list_.at(i);
//        try {
//            ResponsiveLabel *label = static_cast<ResponsiveLabel *>(o->widget());
//            if (label == NULL) // null: cast failed on pointer
//                cout << "warning, unknown widget class in layout" << endl;
//            else if(label -> text() == kSearchResult)
//                label -> setGeometry((i%num)*150+r.x(), (i/num)*200+r.y(), 130, 180);
//            else
//                label -> setGeometry (-1,-1,0,0);
//        }
//        catch (bad_cast) {
//            cout << "warning, unknown widget class in layout" << endl;
//        }
//    }
}

int PlayerLayout::count() const
{
    return list_.size();
}

QLayoutItem *PlayerLayout::itemAt(int idx) const
{
    return list_.value(idx);
}

QLayoutItem *PlayerLayout::takeAt(int idx)
{
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void PlayerLayout::addItem(QLayoutItem *item)
{
    list_.append(item);
}

QSize PlayerLayout::sizeHint() const
{
    return minimumSize();
}

QSize PlayerLayout::minimumSize() const
{
    return QSize(50,1200);
}

PlayerLayout::~PlayerLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
