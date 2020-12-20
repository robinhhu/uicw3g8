#include "list_button.h"

ListButton::ListButton(int index, QString sName, QPixmap pMap)
{
    int h = 64;
    setFixedSize(256, h);

    layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignLeft);
    layout->setMargin(0);
    layout->setSpacing(16);
    setLayout(layout);

    if(pMap.isNull() == false)
    {
        pic = new QLabel();
        if(pMap.width() > pMap.height())
        {
            h = h * pMap.width() / pMap.height();
        }
        h -= 4;
        pic->setPixmap(pMap.scaled(QSize(h, h), Qt::KeepAspectRatio));
        layout->addWidget(pic);
    }

    name = new QLabel(sName);
    layout->addWidget(name);
    if(pMap.isNull() == true)
    {
        name->setText("  " + sName);
    }

    videoIndex = index;

    connect(this, SIGNAL(clicked()), this, SLOT(isClicked()));
}

ListButton::~ListButton()
{

}

void ListButton::isClicked()
{
    emit listButtonClicked(videoIndex);
}
