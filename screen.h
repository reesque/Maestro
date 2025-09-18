#ifndef SCREEN_H
#define SCREEN_H

#include "datastruct.h"

#include <QWidget>
#include <QShortcut>
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

protected:
    ScreenType prevScreen;
    QVector<QVariant> prevScreenArgs;

    std::unique_ptr<QShortcut> upKey;
    std::unique_ptr<QShortcut> downKey;
    std::unique_ptr<QShortcut> leftKey;
    std::unique_ptr<QShortcut> rightKey;
    std::unique_ptr<QShortcut> backKey;
    std::unique_ptr<QShortcut> confirmKey;

protected slots:
    virtual void upAction();
    virtual void downAction();
    virtual void rightAction();
    virtual void leftAction();
    virtual void backAction();
    virtual void confirmAction();
};

#endif // SCREEN_H
