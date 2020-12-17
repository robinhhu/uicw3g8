#include "video_info.h"

#include <QFileInfo>
#include <QDebug>

VideoInfo::VideoInfo(QUrl url)
{
    this->url = url;
    QFileInfo fileInfo(url.toString());
    name = fileInfo.fileName();
    icon = QIcon(fileInfo.path() + "/" + fileInfo.baseName() + ".png");
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

QIcon VideoInfo::getIcon() const
{
    return icon;
}

QSet<QString> VideoInfo::getLabels() const
{
    return labels;
}

void VideoInfo::addLabel(QString label)
{
    labels.insert(label);
}
