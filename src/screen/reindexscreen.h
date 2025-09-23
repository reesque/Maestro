#ifndef REINDEXSCREEN_H
#define REINDEXSCREEN_H

#include "screen.h"
#include "mediaplayer.h"

namespace Ui {
class ReindexScreen;
}

class ReindexScreen : public Screen
{
    Q_OBJECT

public:
    explicit ReindexScreen(std::shared_ptr<MediaPlayer> mediaPlayer, QWidget *parent = nullptr);
    ~ReindexScreen() override;

private slots:
    void onIndexProgress(int progress, int total);

private:
    void start();

private:
    Ui::ReindexScreen *ui;
    std::shared_ptr<MediaPlayer> m_mediaPlayer;
};

#endif // REINDEXSCREEN_H
