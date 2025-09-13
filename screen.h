#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>

enum class ScreenType
{
    Main = 0,
    Music,
    Songs
};

class Screen : public QWidget
{
    Q_OBJECT
public:
    Screen(QWidget *parent = nullptr);
    virtual ~Screen();

signals:
    void switchScreenTo(ScreenType);
};

#endif // SCREEN_H
