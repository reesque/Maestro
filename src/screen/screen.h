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
    Reindex,
    Controller,
    Bluetooth,
    BluetoothScan,
    BluetoothPair,
    About
};

enum class ScreenAnimationType
{
    Forward = 0,
    Backward,
    None
};

Q_DECLARE_METATYPE(ScreenAnimationType);

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);
    virtual ~Screen();
    ScreenType getPrevScreen();
    void setInputLock(bool isLocked);

signals:
    void switchScreenTo(ScreenType,
                        QVector<QVariant> = QVector<QVariant>(),
                        ScreenAnimationType = ScreenAnimationType::Forward);
    void switchToPreviousScreen(QVector<QVariant> = QVector<QVariant>());
    void playTrack(QVector<Track>, int);
    void queueTrack(int);

public slots:
    virtual void upAction();
    virtual void downAction();
    virtual void rightAction();
    virtual void leftAction();
    virtual void backAction();
    virtual void confirmAction();
    virtual void extra1Action();
    virtual void extra2Action();
    virtual void resizeEvent(QResizeEvent *event);

protected:
    ScreenType prevScreen;
    QVector<QVariant> prevScreenArgs;
    bool m_inputLock;
};

#endif // SCREEN_H
