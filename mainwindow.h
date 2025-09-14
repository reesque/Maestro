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
    void switchScreenTo(ScreenType screenType, QVector<QVariant> args = QVector<QVariant>());
    void switchToPreviousScreen();

private:
    Ui::MainWindow *ui;
    QWidget *screenBox;
    std::shared_ptr<Database> m_database;
    std::shared_ptr<MediaPlayer> m_mediaPlayer;
    ScreenType prevScreen;
};

#endif // MAINWINDOW_H
