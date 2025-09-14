#include "database.h"

#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

#include <sstream>

Database::Database(QObject *parent) : QObject{parent}
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("maestro.db");

    m_db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS tracks ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "filepath TEXT, "
               "title TEXT, "
               "artist TEXT, "
               "album TEXT)");
}

Database::~Database()
{
    m_db.close();
}

void Database::insertTrack(const QString& filePath, const QString& title,
                      const QString& artist, const QString& album)
{
    std::stringstream queryStream;

    queryStream << "INSERT INTO " << getTableName(Table::Track)
                << " (filepath, title, artist, album)"
                << " VALUES (?, ?, ?, ?)";

    QSqlQuery insert;
    insert.prepare(queryStream.str().c_str());
    insert.addBindValue(filePath);
    insert.addBindValue(title);
    insert.addBindValue(artist);
    insert.addBindValue(album);
    insert.exec();
}

std::vector<Database::Track> Database::getAllTracks()
{
    std::stringstream queryStream;
    queryStream << "SELECT * FROM " << getTableName(Table::Track) << ";";

    std::vector<Track> trackList;

    QSqlQuery query(queryStream.str().c_str());
    while (query.next()) {
        Track track;
        track.id = query.value(0).toInt();
        track.filePath = query.value(1).toString().toStdString();
        track.title = query.value(2).toString().toStdString();
        track.artist = query.value(3).toString().toStdString();
        track.album = query.value(4).toString().toStdString();
        trackList.push_back(track);
    }

    return trackList;
}

Database::Track Database::getTrack(int id)
{
    std::stringstream queryStream;
    queryStream << "SELECT * FROM " << getTableName(Table::Track) << " WHERE id = " << id << ";";

    QSqlQuery query(queryStream.str().c_str());

    Track track;
    if (query.next())
    {
        track.id = query.value(0).toInt();
        track.filePath = query.value(1).toString().toStdString();
        track.title = query.value(2).toString().toStdString();
        track.artist = query.value(3).toString().toStdString();
        track.album = query.value(4).toString().toStdString();
    }

    return track;
}

void Database::clearTable(const Table& table)
{
    std::stringstream queryStream;
    QSqlQuery query;

    queryStream << "DELETE FROM " << getTableName(table) << ";";
    query.exec(queryStream.str().c_str());

    // Reset index too
    std::stringstream querySqStream;
    QSqlQuery querySq;

    querySqStream << "DELETE FROM sqlite_sequence WHERE name=\'" << getTableName(table) << "\';";
    querySq.exec(querySqStream.str().c_str());
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
