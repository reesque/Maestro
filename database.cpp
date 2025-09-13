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

void Database::selectTracks(const Criteria& criteria, const QString& value)
{
    std::stringstream queryStream;
    QSqlQuery query;

    std::string c;
    switch (criteria)
    {
        case Criteria::Title:
        {
            c = "title";
            break;
        }
        case Criteria::Artist:
        {
            c = "artist";
            break;
        }
        case Criteria::Album:
        {
            c = "album";
            break;
        }
    }

    queryStream << "SELECT * FROM " << getTableName(Table::Track)
                << " WHERE " << c << " LIKE " << "%"  << value.toStdString() << "%;";

    query.exec(queryStream.str().c_str());
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
