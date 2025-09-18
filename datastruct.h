#include <string>
#include <QWidget>

#ifndef DATASTRUCT_H
#define DATASTRUCT_H

struct Track
{
    int id;
    int trackNum;
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;

    bool operator==(const Track& otherTrack)
    {
        return id==otherTrack.id;
    }

    bool operator!=(const Track& otherTrack)
    {
        return !(id==otherTrack.id);
    }
};

Q_DECLARE_METATYPE(Track);

enum class PlaybackStatus
{
    Stopped, Paused, Playing
};

Q_DECLARE_METATYPE(PlaybackStatus);

#endif // DATASTRUCT_H
