#include "video_info.h"

#include <QFileInfo>
#include <QDebug>

VideoInfo::VideoInfo(QUrl url)
{
    QFileInfo fileInfo(url.toString());
    this->url = url;
    name = fileInfo.fileName();
    pic = QPixmap(fileInfo.path() + "/" + fileInfo.baseName() + ".png");
    labels = QSet<QString>();
    labels.insert(name);
}

VideoInfo::~VideoInfo()
{}

QUrl VideoInfo::getUrl() const
{
    return url;
}

QString VideoInfo::getName() const
{
    return name;
}

QPixmap VideoInfo::getPic() const
{
    return pic;
}

QSet<QString> VideoInfo::getLabels() const
{
    return labels;
}

bool VideoInfo::matched(QStringList infos)
{
    for(QString info : infos)
    {
        for(QString label : labels)
        {
            if(label.contains(info))
            {
                return true;
            }
        }
    }
    return false;
}

void VideoInfo::addLabels(QStringList newLabels)
{
    for(QString l : newLabels)
    {
        this->labels.insert(l);
    }
}
