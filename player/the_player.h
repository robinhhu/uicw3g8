#ifndef THE_PLAYER_H
#define THE_PLAYER_H

#include "control_bar.h"
#include "list_area.h"
#include "player_widget.h"

#include <QVBoxLayout>
#include <QWidget>



class ThePlayer : public QWidget
{
Q_OBJECT

public:
    ThePlayer(QMap<QString, QIcon> *icons, QWidget *parent=nullptr);
    ~ThePlayer();

private:
    QVBoxLayout *layout;

    QHBoxLayout *playerAndListLayout;
    QWidget *playerAndListWidget;

    PlayerWidget *playerWidget;
    ControlBar *controlBar;
    TheListArea *listWidget;

    void addConnect();

public slots:
    void setMediaList(QVector<VideoInfo*> *list);

private slots:
    void backToMenuSlot();

signals:
    void backToMenu();
};

#endif // THE_PLAYER_H
