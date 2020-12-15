#ifndef PLAYER_LAYOYT_H
#define PLAYER_LAYOYT_H

#include <iostream>
#include <QLayout>

using namespace std;

class PlayerLayout : public QLayout
{
public:
    PlayerLayout() : QLayout() {}
    ~PlayerLayout();

    void setGeometry(const QRect &rect);

    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;

private:
    QList<QLayoutItem*> list_;
};

#endif // PLAYER_LAYOYT_H
