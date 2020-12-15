#include "player.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Player *player = new Player();
    player->show();

    return a.exec();
}
