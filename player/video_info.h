#ifndef VIDEO_INFO_H
#define VIDEO_INFO_H

#include <QIcon>
#include <QSet>
#include <QString>
#include <QUrl>

class VideoInfo
{
public:
    VideoInfo(QUrl url);
    ~VideoInfo();

    QUrl getUrl() const;
    QString getName() const;
    QIcon getIcon() const;
    QSet<QString> getLabels() const;

    void addLabel(QString label);

private:
    QUrl url;
    QString name;
    QIcon icon;
    QSet<QString> labels;
};

#endif // VIDEO_INFO_H
