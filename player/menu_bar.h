#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <QHBoxLayout>
#include <QIcon>
#include <QMap>
#include <QPushButton>
#include <QWidget>



class MenuBar : public QWidget
{
Q_OBJECT

public:
    MenuBar(QMap<QString, QIcon> *icons, QWidget* parent=nullptr);
    ~MenuBar();

private:
    QHBoxLayout *layout;

    QMap<QString, QIcon> *icons;

    QPushButton *uploadButton;
    QPushButton *toPlayButton;

    void setButton(QPushButton *button, QString name);
    void addItems();

    void addConnect();

private slots:
    void uploadButtonClicked();
    void toPlayButtonClicked();

signals:
    void upload(QStringList files);
    void toPlay();
};

#endif // MENU_BAR_H
