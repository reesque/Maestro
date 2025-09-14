#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QShortcut>

enum class ScreenType
{
    None = 0,
    Main,
    Music,
    Songs,
    NowPlaying
};

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);
    virtual ~Screen();
    ScreenType getPrevScreen();

signals:
    void switchScreenTo(ScreenType);
    void playTrack(int);
    void switchToPreviousScreen();

protected:
    ScreenType prevScreen;

    std::unique_ptr<QShortcut> upKey;
    std::unique_ptr<QShortcut> dnKey;
    std::unique_ptr<QShortcut> leftKey;
    std::unique_ptr<QShortcut> rightKey;

protected slots:
    virtual void upAction() = 0;
    virtual void dnAction() = 0;
    virtual void rightAction() = 0;
    virtual void leftAction();
};

#endif // SCREEN_H
