#ifndef SCREEN_H
#define SCREEN_H

#include "datastruct.h"

#include <QWidget>
#include <QVector>
#include <QVariant>

enum class ScreenType
{
    None = 0,
    Main,
    Music,
    Songs,
    Album,
    Artist,
    ArtistFilter,
    AlbumByArtist,
    SongsByAlbum,
    SongsByArtist,
    SongsByAlbumArtist,
    NowPlaying,
    Setting,
    Reindex
};

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);
    virtual ~Screen();
    ScreenType getPrevScreen();

signals:
    void switchScreenTo(ScreenType, QVector<QVariant> = QVector<QVariant>());
    void switchToPreviousScreen(QVector<QVariant>);
    void playTrack(QVector<Track>, int);
    void queueTrack(int);

public slots:
    virtual void upAction();
    virtual void downAction();
    virtual void rightAction();
    virtual void leftAction();
    virtual void backAction();
    virtual void confirmAction();

protected:
    ScreenType prevScreen;
    QVector<QVariant> prevScreenArgs;
};

#endif // SCREEN_H
