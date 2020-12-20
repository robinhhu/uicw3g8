#ifndef LIST_BUTTON_H
#define LIST_BUTTON_H

#include "video_info.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

class ListButton : public QPushButton
{
Q_OBJECT

public:
    ListButton(int index, QString sName, QPixmap pMap);
    ~ListButton();

private:
    QHBoxLayout *layout;

    int videoIndex;

    QLabel *pic;
    QLabel *name;

private slots:
    void isClicked();

signals:
    void listButtonClicked(int index);
};

#endif // LIST_BUTTON_H
