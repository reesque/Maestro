#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"
#include "mainmenu.h"
#include "musicmenu.h"
#include "songsmenu.h"
#include "albummenu.h"
#include "statusbar.h"
#include "nowplaying.h"

#include <memory>
#include <iomanip>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init database
    m_database = std::make_shared<Database>();

    // Init media player
    m_mediaPlayer = std::make_shared<MediaPlayer>(m_database);
    m_mediaPlayer->reindex();

    // Init UI layout
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    StatusBar *statusBar = new StatusBar(this);
    layout->addWidget(statusBar);

    screenBox = new QWidget(this);
    screenBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout *screenLayout = new QHBoxLayout(screenBox);
    screenLayout->setAlignment(Qt::AlignCenter);
    screenLayout->setSpacing(0);
    screenLayout->setMargin(0);

    layout->addWidget(screenBox);

    ui->centralwidget->setLayout(layout);

    switchScreenTo(ScreenType::Main);
    prevScreen = ScreenType::None;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchScreenTo(ScreenType screenType, QVector<QVariant> args)
{
    // Delete old screen
    if (screenBox->layout()->count() > 0)
    {
        Screen *oldScreen = static_cast<Screen *>(screenBox->layout()->itemAt(0)->widget());

        disconnect(oldScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);
        disconnect(oldScreen, &Screen::switchToPreviousScreen, this, &MainWindow::switchToPreviousScreen);

        QLayoutItem *item = screenBox->layout()->takeAt(0);
        if (item) {
            QWidget *widget = item->widget();
            if (widget) {
                widget->deleteLater(); // Safe deletion in Qt
            }
            delete item; // Also delete the layout item
        }
        screenBox->layout()->removeItem(screenBox->layout()->itemAt(0));
    }

    // New screen
    Screen *newScreen = nullptr;
    switch (screenType)
    {
        case ScreenType::Main:
        {
            newScreen = new MainMenu(this);
            break;
        }
        case ScreenType::Music:
        {
            newScreen = new MusicMenu(this);
            break;
        }
        case ScreenType::Songs:
        {
            newScreen = new SongsMenu(m_database, this);
            break;
        }
        case ScreenType::Album:
        {
            newScreen = new AlbumMenu(m_database, this);
            break;
        }
        case ScreenType::SongsByAlbum:
        {
            newScreen = new SongsMenu(m_database, SongsMenu::Filter::Album,
                                      args.at(0).toString().toStdString(), this);
            break;
        }
        case ScreenType::NowPlaying:
        {
            newScreen = new NowPlaying(m_database, m_mediaPlayer, this);
            break;
        }
        default:
        {
            return;
        }
    }

    screenBox->layout()->addWidget(newScreen);
    newScreen->setFocus();
    prevScreen = newScreen->getPrevScreen();
    connect(newScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);
    connect(newScreen, &Screen::switchToPreviousScreen, this, &MainWindow::switchToPreviousScreen);
    connect(newScreen, &Screen::playTrack, m_mediaPlayer.get(), &MediaPlayer::playTrack);
}

void MainWindow::switchToPreviousScreen()
{
    if (prevScreen != ScreenType::None)
    {
        switchScreenTo(prevScreen);
    }
}
