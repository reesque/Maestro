#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "controller.h"
#include "screen.h"
#include "settings.h"
#include "mediaplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

signals:
    void changeTitle(QString title);

private slots:
    void switchScreenTo(ScreenType screenType, QVector<QVariant> args = QVector<QVariant>());
    void switchToPreviousScreen(QVector<QVariant> args);

private:
    Ui::MainWindow *ui;
    QWidget *screenBox;
    std::shared_ptr<Database> m_database;
    std::shared_ptr<MediaPlayer> m_mediaPlayer;
    std::shared_ptr<Controller> m_controller;
    std::shared_ptr<Settings> m_setting;
    ScreenType prevScreen;
};

#endif // MAINWINDOW_H
