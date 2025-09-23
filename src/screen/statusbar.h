#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "datastruct.h"

#include <QWidget>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar() override;

public slots:
    void changeTitle(QString title);
    void onPlaybackStateChanged(PlaybackStatus playbackStatus);

private:
    Ui::StatusBar *ui;
};

#endif // STATUSBAR_H
