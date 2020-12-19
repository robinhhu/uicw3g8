#ifndef INFO_BAR_H
#define INFO_BAR_H

#include "video_info.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QWidget>



class InfoBar : public QWidget
{
Q_OBJECT

public:
    InfoBar(QMap<QString, QIcon>* icons, QWidget *parent=nullptr);
    ~InfoBar();

    void setVideo(QVector<VideoInfo*>* video);

private:
    QMap<QString, QIcon>* icons;

    QVector<VideoInfo*>* video;

    QHBoxLayout *layout;

    QCheckBox *c1;
    QCheckBox *c2;
    QCheckBox *c3;

    QLineEdit *inputLabels;

    QPushButton *backButton;
    QPushButton *playButton;
    QPushButton *enterButton;

    void setCheckBox(QCheckBox *checkBox, QString name);
    void setButton(QPushButton *button, QString name);

public slots:
    void setInputPlaceHolder(QVector<VideoInfo*>* video);
    void clearLabels();

private slots:
    void backButtonClicked();
    void playButtonClicked();
    void enterButtonClicked();

signals:
    void back();
    void playVideo(QVector<VideoInfo*>* video);
};

#endif // INFO_BAR_H
