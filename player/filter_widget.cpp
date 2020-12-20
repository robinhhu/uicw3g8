#include "filter_widget.h"

#include <QDebug>

FilterWidget::FilterWidget(QMap<QString, QIcon>* icons, QWidget *parent) : QWidget(parent)
{
    this->icons = icons;

    layout = new QHBoxLayout();
    layout->setSpacing(16);
    setLayout(layout);

    setFixedHeight(64);

    filter = new QComboBox();
    filter->setFixedSize(128, 32);
    QStringList filterText;
    filterText << "All" << "hiking" << "cycling" << "skiing";
    filter->addItems(filterText);
    layout->addWidget(filter);

    input = new QLineEdit();
    input->setFixedHeight(32);
    input->setMinimumWidth(512);
    input->setMaxLength(128);
    input->setPlaceholderText("Search by name or label");
    layout->addWidget(input);

    searchButton = new QPushButton();
    searchButton->setIcon(icons->find("search").value());
    searchButton->setIconSize(QSize(32, 32));
    searchButton->setFixedSize(searchButton->iconSize());
    searchButton->setFlat(true);
    layout->addWidget(searchButton);

    connect(searchButton, SIGNAL(clicked()), this, SLOT(enterClicked()));
}

FilterWidget::~FilterWidget()
{

}

void FilterWidget::defaultSearch()
{
    filter->setCurrentIndex(0);
    input->setText("");
    enterClicked();
}

void FilterWidget::enterClicked()
{
    QStringList infos;
    if(filter->currentText() != "All")
    {
        infos.append(filter->currentText());
    }
    for(QString info : input->text().split(" "))
    {
        if(info != "")
        {
            infos.append(info);
        }
    }
    if(infos.length() == 0)
    {
        infos.append("");
    }
    emit search(infos);
}
