#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "screen.h"
#include "mediaplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchScreenTo(ScreenType screenType);

private:
    Ui::MainWindow *ui;
    QWidget *screenBox;
    Database *m_database;
    MediaPlayer *m_mediaPlayer;
};

#endif // MAINWINDOW_H
