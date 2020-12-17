#include "menu_bar.h"

MenuBar::MenuBar(QMap<QString, QIcon> *icons, QWidget* parent) : QWidget(parent)
{
    this->icons = icons;

    setFixedHeight(150);

    layout = new QHBoxLayout();
    layout->setContentsMargins(128, 0, 128, 0);
    setLayout(layout);

    addItems();

    addConnect();
}

MenuBar::~MenuBar()
{

}

void MenuBar::setButton(QPushButton *button, QString name)
{
    button->setIcon(icons->find(name).value());
    button->setIconSize(QSize(100, 100));
    button->setFixedSize(button->iconSize());
    button->setFlat(true);
    layout->addWidget(button);
}

void MenuBar::addItems()
{
    upload = new QPushButton();
    setButton(upload, "upload");

    layout->addStretch();

    toPlayButton = new QPushButton();
    setButton(toPlayButton, "toplay");
}

void MenuBar::addConnect()
{
    connect(toPlayButton, SIGNAL(clicked()), this, SLOT(toPlayButtonClicked()));
}

void MenuBar::toPlayButtonClicked()
{
    emit toPlay();
}
