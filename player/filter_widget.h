#ifndef FILTER_WIDGET_H
#define FILTER_WIDGET_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>



class FilterWidget : public QWidget
{
Q_OBJECT

public:
    FilterWidget(QMap<QString, QIcon>* icons, QWidget *parent=nullptr);
    ~FilterWidget();

private:
    QMap<QString, QIcon>* icons;

    QHBoxLayout *layout;

    QComboBox *filter;
    QLineEdit *input;
    QPushButton *searchButton;

public slots:
    void defaultSearch();

private slots:
    void enterClicked();

signals:
    void search(QStringList infos);
};

#endif // FILTER_WIDGET_H
