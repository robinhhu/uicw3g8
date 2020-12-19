#ifndef LIST_BUTTON_H
#define LIST_BUTTON_H

#include "video_info.h"

#include <QPushButton>

class ListButton : public QPushButton
{
Q_OBJECT

public:
    ListButton(int index, QString name, QIcon icon);
    ~ListButton();

private:
    int videoIndex;

private slots:
    void isClicked();

signals:
    void listButtonClicked(int index);
};

#endif // LIST_BUTTON_H
