#include "database.h"

#include <QVariant>
#include <QtSql/QSqlQuery>

#include <sstream>

Database::Database()
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
               "album TEXT, "
               "duration INTEGER)");
}

Database::~Database()
{
    m_db.close();
}

void Database::insert(const std::string& filePath, const std::string& title,
                      const std::string& artist, const std::string& album, int duration)
{
    QSqlQuery insert;
    insert.prepare("INSERT INTO tracks (filepath, title, artist, album, duration) "
                   "VALUES (?, ?, ?, ?, ?)");
    insert.addBindValue(QVariant::fromValue(filePath));
    insert.addBindValue(QVariant::fromValue(title));
    insert.addBindValue(QVariant::fromValue(artist));
    insert.addBindValue(QVariant::fromValue(album));
    insert.addBindValue(QVariant::fromValue(duration));
    insert.exec();
}

void Database::select(const Criteria& criteria, const std::string& value)
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

    queryStream << "SELECT * FROM tracks" << " WHERE " << c << " LIKE " << value;

    query.exec(queryStream.str().c_str());
}
