#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <string>

#include <QObject>
#include <QtSql/QSqlDatabase>

class Database : public QObject
{
    Q_OBJECT
public:
    enum class Table
    {
        Track = 0
    };

    struct Track
    {
        int id;
        std::string filePath;
        std::string title;
        std::string artist;
        std::string album;
    };

    explicit Database(QObject *parent = nullptr);
    ~Database();

    void insertTrack(const QString& filePath, const QString& title,
                const QString& artist, const QString& album);
    std::vector<Track> getAllTracks();
    Track getTrack(int id);
    std::vector<std::string> getAllAlbums();
    void clearTable(const Table& table);

private:
    std::string getTableName(const Table& table);

private:
    QSqlDatabase m_db;
    static std::unique_ptr<Database> instance;
};

Q_DECLARE_METATYPE(Database::Table);

#endif // DATABASE_H
