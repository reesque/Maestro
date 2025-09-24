#include "songsmenu.h"

#include <QDir>
#include <QVector>

#include <filesystem>

SongsMenu::SongsMenu(std::shared_ptr<Database> db, QWidget *parent) :
    Menu(parent)
{
    prevScreen = ScreenType::Music;
    m_db = db;

    fillSongRecords(db->getAllTracks());
}

SongsMenu::SongsMenu(std::shared_ptr<Database> db, Filter filter, QVector<QVariant> values, QWidget *parent) :
    Menu(parent)
{
    m_db = db;

    switch (filter)
    {
        case Filter::Album:
        {
            prevScreen = ScreenType::Album;
            fillSongRecords(db->getTracksByAlbum(values.at(0).toString().toStdString()));
            break;
        }
        case Filter::Artist:
        {
            prevScreen = ScreenType::Artist;
            fillSongRecords(db->getTracksByArtist(values.at(0).toString().toStdString()));
            break;
        }
        case Filter::AlbumArtist:
        {
            prevScreen = ScreenType::AlbumByArtist;
            prevScreenArgs.push_back(QVariant(QString::fromStdString(values.at(1).toString().toStdString())));
            fillSongRecords(db->getTracksByAlbum(values.at(0).toString().toStdString()));
            break;
        }
    }
}

SongsMenu::~SongsMenu()
{}

DetailedMenuListItem* SongsMenu::createListItem(std::shared_ptr<DetailedMenuEntry> entry)
{
    DetailedMenuListItem *item = new DetailedMenuListItem(entry->header, entry->subtext, entry->artPath, ui->ListObject);
    item->setActivator(entry->activator);
    return item;
}

void SongsMenu::fillSongRecords(std::vector<Track> records)
{
    ui->ListObject->setStyleSheet(
        "QListWidget::item { background-color: white; border-top: none; border-bottom: 1px solid #cccccc; }"
        "QListWidget::item:selected { background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #0096FF, stop:1 #0066CC); border: none; }"
    );

    QString artworkPath = QDir::homePath() + "/.config/maestro/artwork/";
    for (unsigned queueNum = 0; queueNum < records.size(); ++queueNum)
    {
        // Check if artwork is available
        QString trackArtworkPath = artworkPath + records[queueNum].album.c_str();
        QString trackArtPathPng = trackArtworkPath + ".png";
        QString trackArtPathJpg = trackArtworkPath + ".jpg";
        std::string artPath = "";
        if (std::filesystem::exists(trackArtPathPng.toStdString()))
        {
            artPath = trackArtPathPng.toStdString();
        }
        else if (std::filesystem::exists(trackArtPathJpg.toStdString()))
        {
            artPath = trackArtPathJpg.toStdString();
        }

        // Create menu list
        menuList->push_back(std::make_shared<DetailedMenuEntry>(
            records[queueNum].title, records[queueNum].artist, artPath, [=](){
                emit switchScreenTo(ScreenType::NowPlaying);
                QVector<Track> vec;
		vec.reserve(records.size());
		for (const auto& track : records) {
    		    vec.append(track);
		}
		emit playTrack(vec, queueNum);
            }
        ));
    }

    populateMenu();
}

