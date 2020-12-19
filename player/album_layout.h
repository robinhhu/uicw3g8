#ifndef ALBUM_LAYOUT_H
#define ALBUM_LAYOUT_H

#include <QLayout>
#include <QScrollArea>

using namespace std;

class AlbumLayout : public QLayout {
public:
    AlbumLayout();
    ~AlbumLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    void addItem(QLayoutItem *item);
    QSize sizeHint() const;

private:
    QList<QLayoutItem*> list_;
};

#endif // ALBUM_LAYOUT_H
