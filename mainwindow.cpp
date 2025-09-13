#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "menu.h"
#include "statusbar.h"

#include <QVBoxLayout>

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

    Menu *menu = new Menu(this);
    layout->addWidget(menu);

    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}
