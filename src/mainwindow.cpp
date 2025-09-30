#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "database.h"
#include "mainmenu.h"
#include "musicmenu.h"
#include "songsmenu.h"
#include "albummenu.h"
#include "artistmenu.h"
#include "artistfiltermenu.h"
#include "statusbar.h"
#include "nowplaying.h"
#include "settingmenu.h"
#include "reindexscreen.h"
#include "controllermenu.h"
#include "bluetoothmenu.h"
#include "bluetoothscanmenu.h"
#include "bluetoothpairscreen.h"

#include <memory>
#include <iomanip>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Init database
    m_database = std::make_shared<Database>();

    // Init setting
    m_setting = std::make_shared<Settings>(m_database);

    // Init media player
    m_mediaPlayer = std::make_shared<MediaPlayer>(m_database);

    // Init controller
    m_controller = std::make_shared<Controller>(m_setting, this);
    connect(m_setting.get(), &Settings::onDpadResponsiveLevelChanged, m_controller.get(), &Controller::onDpadResponsiveLevelChanged);
    connect(m_setting.get(), &Settings::onFaceBtnResponsiveLevelChanged, m_controller.get(), &Controller::onFaceBtnResponsiveLevelChanged);

    // Init UI layout
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);

    // Status bar
    StatusBar *statusBar = new StatusBar(this);
    layout->addWidget(statusBar);
    connect(this, &MainWindow::changeTitle, statusBar, &StatusBar::changeTitle);
    connect(m_mediaPlayer.get(), &MediaPlayer::onPlaybackStateChanged,
            statusBar, &StatusBar::onPlaybackStateChanged);

    // Content pane
    screenStack = new QStackedWidget(this);
    screenStack->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout->addWidget(screenStack);

    ui->centralwidget->setLayout(layout);

    switchScreenTo(ScreenType::Main, QVector<QVariant>(), ScreenAnimationType::None);
    prevScreen = ScreenType::None;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchScreenTo(ScreenType screenType,
                                QVector<QVariant> args,
                                ScreenAnimationType screenAnimationType)
{
    // New screen
    Screen *newScreen = nullptr;
    switch (screenType)
    {
        case ScreenType::Main:
        {
            newScreen = new MainMenu(this);
            emit changeTitle("Maestro");
            break;
        }
        case ScreenType::Music:
        {
            newScreen = new MusicMenu(this);
            emit changeTitle("Music");
            break;
        }
        case ScreenType::Songs:
        {
            newScreen = new SongsMenu(m_database, this);
            emit changeTitle("Songs");
            break;
        }
        case ScreenType::Album:
        {
            newScreen = new AlbumMenu(m_database, this);
            emit changeTitle("Albums");
            break;
        }
        case ScreenType::Artist:
        {
            newScreen = new ArtistMenu(m_database, this);
            emit changeTitle("Artists");
            break;
        }
        case ScreenType::ArtistFilter:
        {
            newScreen = new ArtistFilterMenu(args.at(0).toString().toStdString(), this);
            emit changeTitle(args.at(0).toString());
            break;
        }
        case ScreenType::SongsByAlbum:
        {
            newScreen = new SongsMenu(m_database, SongsMenu::Filter::Album, args, this);
            emit changeTitle(args.at(0).toString());
            break;
        }
        case ScreenType::SongsByArtist:
        {
            newScreen = new SongsMenu(m_database, SongsMenu::Filter::Artist, args, this);
            emit changeTitle(args.at(0).toString());
            break;
        }
        case ScreenType::SongsByAlbumArtist:
        {
            newScreen = new SongsMenu(m_database, SongsMenu::Filter::AlbumArtist, args, this);
            emit changeTitle(args.at(0).toString());
            break;
        }
        case ScreenType::AlbumByArtist:
        {
            newScreen = new AlbumMenu(m_database, args.at(0).toString().toStdString(), this);
            emit changeTitle(args.at(0).toString());
            break;
        }
        case ScreenType::NowPlaying:
        {
            newScreen = new NowPlaying(m_database, m_mediaPlayer, this);
            emit changeTitle("Now Playing");
            break;
        }
        case ScreenType::Setting:
        {
            newScreen = new SettingMenu(this);
            emit changeTitle("Settings");
            break;
        }
        case ScreenType::Reindex:
        {
            newScreen = new ReindexScreen(m_mediaPlayer, this);
            emit changeTitle("Sync Library");
            break;
        }
        case ScreenType::Controller:
        {
            newScreen = new ControllerMenu(m_setting, this);
            emit changeTitle("Controller Settings");
            break;
        }
        case ScreenType::Bluetooth:
        {
            newScreen = new BluetoothMenu(this);
            emit changeTitle("Bluetooth");
            break;
        }
        case ScreenType::BluetoothScan:
        {
            newScreen = new BluetoothScanMenu(this);
            emit changeTitle("Bluetooth Scan");
            break;
        }
        case ScreenType::BluetoothPair:
        {
            newScreen = new BluetoothPairScreen(args.at(0).value<QBluetoothAddress>(), this);
            emit changeTitle("Bluetooth Pair");
            break;
        }
        default:
        {
            return;
        }
    }

    screenStack->layout()->addWidget(newScreen);
    newScreen->setFocus();
    prevScreen = newScreen->getPrevScreen();
    connect(newScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);
    connect(newScreen, &Screen::switchToPreviousScreen, this, &MainWindow::switchToPreviousScreen);
    connect(newScreen, &Screen::playTrack, m_mediaPlayer.get(), &MediaPlayer::playTrack);
    connect(newScreen, &Screen::queueTrack, m_mediaPlayer.get(), &MediaPlayer::queueTrack);

    connect(m_controller.get(), &Controller::triggerLeftAction, newScreen, &Screen::leftAction);
    connect(m_controller.get(), &Controller::triggerRightAction, newScreen, &Screen::rightAction);
    connect(m_controller.get(), &Controller::triggerUpAction, newScreen, &Screen::upAction);
    connect(m_controller.get(), &Controller::triggerDownAction, newScreen, &Screen::downAction);
    connect(m_controller.get(), &Controller::triggerBackAction, newScreen, &Screen::backAction);
    connect(m_controller.get(), &Controller::triggerConfirmAction, newScreen, &Screen::confirmAction);

    connect(this, &MainWindow::resizeEvent, newScreen, &Screen::resizeEvent);

    // Delete old screen
    if (screenStack->layout()->count() > 1)
    {
        Screen *oldScreen = static_cast<Screen *>(screenStack->layout()->itemAt(0)->widget());

        // Lock input
        oldScreen->setInputLock(true);
        newScreen->setInputLock(true);

        QRect geo = screenStack->geometry();
        int width = geo.width();
        int height = geo.height();

        newScreen->setGeometry(width, 0, width, geo.height());

        QParallelAnimationGroup* group = new QParallelAnimationGroup;

        switch (screenAnimationType)
        {
            case (ScreenAnimationType::Forward):
            {
                QPropertyAnimation* animCurrent = new QPropertyAnimation(oldScreen, "geometry");
                animCurrent->setDuration(200);
                animCurrent->setStartValue(QRect(0, 0, width, geo.height()));
                animCurrent->setEndValue(QRect(-width, 0, width, geo.height()));

                QPropertyAnimation* animNext = new QPropertyAnimation(newScreen, "geometry");
                animNext->setDuration(200);
                animNext->setStartValue(QRect(width, 0, width, geo.height()));
                animNext->setEndValue(QRect(0, 0, width, geo.height()));

                group->addAnimation(animCurrent);
                group->addAnimation(animNext);
                break;
            }
            case (ScreenAnimationType::Backward):
            {
                newScreen->setGeometry(-width, 0, width, height);

                QPropertyAnimation* animCurrent = new QPropertyAnimation(oldScreen, "geometry");
                animCurrent->setDuration(200);
                animCurrent->setStartValue(QRect(0, 0, width, height));
                animCurrent->setEndValue(QRect(width, 0, width, height));

                QPropertyAnimation* animNext = new QPropertyAnimation(newScreen, "geometry");
                animNext->setDuration(200);
                animNext->setStartValue(QRect(-width, 0, width, height));
                animNext->setEndValue(QRect(0, 0, width, height));

                group->addAnimation(animCurrent);
                group->addAnimation(animNext);
                break;
            }
            default:
            {
                break;
            }
        }

        oldScreen->raise();
        oldScreen->show();
        newScreen->show();

        connect(group, &QParallelAnimationGroup::finished, [=]() {
            screenStack->setCurrentIndex(1);
            disconnect(oldScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);
            disconnect(oldScreen, &Screen::switchToPreviousScreen, this, &MainWindow::switchToPreviousScreen);

            disconnect(m_controller.get(), &Controller::triggerLeftAction, oldScreen, &Screen::leftAction);
            disconnect(m_controller.get(), &Controller::triggerRightAction, oldScreen, &Screen::rightAction);
            disconnect(m_controller.get(), &Controller::triggerUpAction, oldScreen, &Screen::upAction);
            disconnect(m_controller.get(), &Controller::triggerDownAction, oldScreen, &Screen::downAction);
            disconnect(m_controller.get(), &Controller::triggerBackAction, oldScreen, &Screen::backAction);
            disconnect(m_controller.get(), &Controller::triggerConfirmAction, oldScreen, &Screen::confirmAction);

            disconnect(this, &MainWindow::resizeEvent, oldScreen, &Screen::resizeEvent);

            QLayoutItem *item = screenStack->layout()->takeAt(0);
            if (item) {
                QWidget *widget = item->widget();
                if (widget) {
                    widget->deleteLater();
                }
                delete item;
            }

            // Release input for new screen
            newScreen->setInputLock(false);
        });

        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void MainWindow::switchToPreviousScreen(QVector<QVariant> args)
{
    if (prevScreen != ScreenType::None)
    {
        switchScreenTo(prevScreen, args, ScreenAnimationType::Backward);
    }
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
}
