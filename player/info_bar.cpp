#include "info_bar.h"

#include <QDebug>

InfoBar::InfoBar(QMap<QString, QIcon>* icons, QWidget *parent) : QWidget(parent)
{
    this->icons = icons;

    setFixedHeight(128);

    layout = new QHBoxLayout();
    layout->setSpacing(16);
    layout->setContentsMargins(64, 0, 64, 0);
    setLayout(layout);

    backButton = new QPushButton();
    setButton(backButton, "backtomenu");

    layout->addStretch();

    c1 = new QCheckBox();
    setCheckBox(c1, "hiking");
    c2 = new QCheckBox();
    setCheckBox(c2, "cycling");
    c3 = new QCheckBox();
    setCheckBox(c3, "skiing");

    inputLabels = new QLineEdit();
    inputLabels->setFixedHeight(32);
    inputLabels->setMaxLength(128);
    layout->addWidget(inputLabels);

    enterButton = new QPushButton();
    setButton(enterButton, "add");

    layout->addStretch();

    playButton = new QPushButton();
    setButton(playButton, "play");

    connect(backButton, SIGNAL(clicked()), this, SLOT(backButtonClicked()));
    connect(playButton, SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(enterButton, SIGNAL(clicked()), this, SLOT(enterButtonClicked()));
}

InfoBar::~InfoBar()
{

}

void InfoBar::setVideo(QVector<VideoInfo*>* video)
{
    this->video = video;
}

void InfoBar::setCheckBox(QCheckBox *checkBox, QString name)
{
    checkBox->setText(name);
    checkBox->setFixedSize(128, 64);
    layout->addWidget(checkBox);
}

void InfoBar::setButton(QPushButton *button, QString name)
{
    button->setIcon(icons->find(name).value());
    button->setIconSize(QSize(64, 64));
    button->setFixedSize(button->iconSize());
    button->setFlat(true);
    layout->addWidget(button);
}

void InfoBar::setInputPlaceHolder(QVector<VideoInfo*>* video)
{
    QString ph = "Enter/select the label of：" + video->at(0)->getName();
    inputLabels->setPlaceholderText(ph);
}

void InfoBar::clearLabels()
{
    c1->setCheckState(Qt::CheckState::Unchecked);
    c2->setCheckState(Qt::CheckState::Unchecked);
    c3->setCheckState(Qt::CheckState::Unchecked);

    inputLabels->clear();
}

void InfoBar::backButtonClicked()
{
    emit back();
}

void InfoBar::playButtonClicked()
{
    emit playVideo(video);
}

void InfoBar::enterButtonClicked()
{
    QStringList labels;
    if(c1->isChecked() == true)
    {
        labels << c1->text();
    }
    if(c2->isChecked() == true)
    {
        labels << c2->text();
    }
    if(c3->isChecked() == true)
    {
        labels << c3->text();
    }
    for(QString l : inputLabels->text().split(" "))
    {
        if(l != "")
        {
            labels << l;
        }
    }

    if(labels.length() > 0)
    {
        video->at(0)->addLabels(labels);
    }
    emit back();
}
