#include "list_button.h"

ListButton::ListButton(int index, QString name, QIcon icon) : QPushButton(name)
{
    videoIndex = index;

    setIconSize(QSize(128, 64));
    setIcon(icon);
    setFixedSize(256, 100);

    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));
}

ListButton::~ListButton()
{

}

void ListButton::isClicked()
{
    emit listButtonClicked(videoIndex);
}
