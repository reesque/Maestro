#ifndef SCREEN_H
#define SCREEN_H

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
    SongsByAlbum,
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
    void playTrack(int);
    void switchToPreviousScreen();

protected:
    ScreenType prevScreen;

    std::unique_ptr<QShortcut> upKey;
    std::unique_ptr<QShortcut> dnKey;
    std::unique_ptr<QShortcut> leftKey;
    std::unique_ptr<QShortcut> rightKey;

protected slots:
    virtual void upAction();
    virtual void dnAction();
    virtual void rightAction();
    virtual void leftAction();
};

#endif // SCREEN_H
