#include "database.h"

#include <QDir>
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <sstream>
#include <iostream>
#include <filesystem>

Database::Database(QObject *parent) : QObject{parent}
{
    m_appPath = QDir::homePath() + "/.config/maestro/";
    if (!std::filesystem::exists(m_appPath.toStdString()))
    {
        std::filesystem::create_directory(m_appPath.toStdString());
    }

    execute([](const QSqlDatabase& db){
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS tracks ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "filepath TEXT, "
                   "title TEXT, "
                   "artist TEXT, "
                   "album TEXT,"
                   "trackNum INTEGER)");
    });
}

Database::~Database()
{}

void Database::execute(std::function<void(const QSqlDatabase&)> func)
{
    m_mutex.lock();

    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "default");
        QString dbPath = m_appPath + "maestro.db";

        db.setDatabaseName(dbPath);

        if (!db.open()) {
            m_mutex.unlock();
            return;
        }

        func(db);

        db.close();
    }

    QSqlDatabase::removeDatabase("default");

    m_mutex.unlock();
}

void Database::insertTrack(const QString& filePath, const QString& title,
                      const QString& artist, const QString& album, int trackNum)
{
    execute([=](const QSqlDatabase& db){
        std::stringstream queryStream;

        queryStream << "INSERT INTO " << getTableName(Table::Track)
                    << " (filepath, title, artist, album, trackNum)"
                    << " VALUES (?, ?, ?, ?, ?)";

        QSqlQuery insert(db);
        insert.prepare(queryStream.str().c_str());
        insert.addBindValue(filePath);
        insert.addBindValue(title);
        insert.addBindValue(artist);
        insert.addBindValue(album);
        insert.addBindValue(trackNum);
        insert.exec();
    });
}

std::vector<Database::Track> Database::getAllTracks()
{
    std::vector<Track> trackList;

    execute([this, &trackList](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT * FROM " << getTableName(Table::Track) << ";";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next()) {
            Track track;
            track.id = query.value(0).toInt();
            track.trackNum = query.value(5).toInt();
            track.filePath = query.value(1).toString().toStdString();
            track.title = query.value(2).toString().toStdString();
            track.artist = query.value(3).toString().toStdString();
            track.album = query.value(4).toString().toStdString();
            trackList.push_back(track);
        }
    });

    return trackList;
}

std::vector<Database::Track> Database::getTracksByAlbum(const std::string& albumName)
{
    std::vector<Track> trackList;

    execute([this, &trackList, albumName](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT * FROM " << getTableName(Table::Track)
                    << " WHERE album LIKE '" << albumName
                    << "' ORDER BY trackNum ASC;";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next()) {
            Track track;
            track.id = query.value(0).toInt();
            track.trackNum = query.value(5).toInt();
            track.filePath = query.value(1).toString().toStdString();
            track.title = query.value(2).toString().toStdString();
            track.artist = query.value(3).toString().toStdString();
            track.album = query.value(4).toString().toStdString();
            trackList.push_back(track);
        }
    });

    return trackList;
}

std::vector<Database::Track> Database::getTracksByArtist(const std::string& artistName)
{
    std::vector<Track> trackList;

    execute([this, &trackList, artistName](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT * FROM " << getTableName(Table::Track)
                    << " WHERE artist LIKE '" << artistName << "';";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next()) {
            Track track;
            track.id = query.value(0).toInt();
            track.trackNum = query.value(5).toInt();
            track.filePath = query.value(1).toString().toStdString();
            track.title = query.value(2).toString().toStdString();
            track.artist = query.value(3).toString().toStdString();
            track.album = query.value(4).toString().toStdString();
            trackList.push_back(track);
        }
    });

    return trackList;
}

Database::Track Database::getTrack(int id)
{
    Track track;
    execute([this, &track, id](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT * FROM " << getTableName(Table::Track) << " WHERE id = " << id << ";";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());

        if (query.next())
        {
            track.id = query.value(0).toInt();
            track.filePath = query.value(1).toString().toStdString();
            track.title = query.value(2).toString().toStdString();
            track.artist = query.value(3).toString().toStdString();
            track.album = query.value(4).toString().toStdString();
        }
    });

    return track;
}

std::vector<std::string> Database::getAllAlbums()
{
    std::vector<std::string> albumList;

    execute([this, &albumList](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT DISTINCT album FROM " << getTableName(Table::Track) << ";";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next())
        {
            albumList.push_back(query.value(0).toString().toStdString());
        }
    });

    return albumList;
}

std::vector<std::string> Database::getAllArtists()
{
    std::vector<std::string> artistList;

    execute([this, &artistList](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT DISTINCT artist FROM " << getTableName(Table::Track) << ";";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next())
        {
            artistList.push_back(query.value(0).toString().toStdString());
        }
    });

    return artistList;
}

std::vector<std::string> Database::getAlbumByArtist(const std::string& artistName)
{
    std::vector<std::string> albumList;

    execute([this, &albumList, artistName](const QSqlDatabase& db){
        std::stringstream queryStream;
        queryStream << "SELECT DISTINCT album FROM " << getTableName(Table::Track)
                    << " WHERE artist LIKE '" << artistName << "';";

        QSqlQuery query(db);
        query.exec(queryStream.str().c_str());
        while (query.next())
        {
            albumList.push_back(query.value(0).toString().toStdString());
        }
    });

    return albumList;
}

void Database::clearTable(const Table& table)
{
    execute([this, table](const QSqlDatabase& db){
        std::stringstream queryStream;
        QSqlQuery query(db);

        queryStream << "DELETE FROM " << getTableName(table) << ";";
        query.exec(queryStream.str().c_str());

        // Reset index too
        std::stringstream querySqStream;
        QSqlQuery querySq(db);

        querySqStream << "DELETE FROM sqlite_sequence WHERE name=\'" << getTableName(table) << "\';";
        querySq.exec(querySqStream.str().c_str());
    });
}

std::string Database::getTableName(const Table& table)
{
    std::string t;
    switch (table)
    {
        case Table::Track:
        {
            t = "tracks";
            break;
        }
        default:
        {
            t = "unknown";
            break;
        }
    }

    return t;
}
