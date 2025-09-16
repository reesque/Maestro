#include "reindexscreen.h"
#include "ui_reindexscreen.h"

#include <thread>

#include <QTimer>

ReindexScreen::ReindexScreen(std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent) :
    Screen(parent),
    ui(new Ui::ReindexScreen)
{
    m_mediaPlayer = mediaPlayer;

    ui->setupUi(this);

    connect(mediaPlayer.get(), &MediaPlayer::onIndexProgress, this, &ReindexScreen::onIndexProgress);

    QTimer::singleShot(0, this, &ReindexScreen::start);
}

ReindexScreen::~ReindexScreen()
{
    delete ui;
}
void ReindexScreen::start()
{
    std::thread scanThread([=](){
        m_mediaPlayer->reindex();
    });

    scanThread.detach();
}

void ReindexScreen::onIndexProgress(int progress, int total)
{
    ui->Progress->setMaximum(total);
    ui->Progress->setValue(progress);

    if (progress == total)
    {
        disconnect(m_mediaPlayer.get(), &MediaPlayer::onIndexProgress, this, &ReindexScreen::onIndexProgress);
        switchScreenTo(ScreenType::Setting);
    }
}
