#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menu.h"
#include "mainmenu.h"
#include "musicmenu.h"
#include "statusbar.h"

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::switchScreenTo(ScreenType screenType)
{
    // New screen
    Screen *newScreen;
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
        default:
        {
            return;
        }
    }

    newScreen->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    screenBox->layout()->addWidget(newScreen);
    connect(newScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);
    newScreen->hide();

    // Old screen
    if (screenBox->layout()->count() > 1)
    {
        // Move to offscreen position
        newScreen->move(QPoint(800, 0));
        newScreen->show();

        Screen *oldScreen = static_cast<Screen*>(screenBox->children()[0]);

        // Move right widget
        QPropertyAnimation *moveAnim = new QPropertyAnimation(newScreen, "pos");
        moveAnim->setDuration(200);
        moveAnim->setStartValue(QPoint(800, 0));
        moveAnim->setEndValue(QPoint(0, 0));
        moveAnim->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);

        // Dereference
        connect(moveAnim, &QPropertyAnimation::finished, this, [=](){
            disconnect(oldScreen, &Screen::switchScreenTo, this, &MainWindow::switchScreenTo);

            screenBox->layout()->removeWidget(oldScreen);
            oldScreen->deleteLater();
        });
    }

    // Show new screen again
    newScreen->show();
}
