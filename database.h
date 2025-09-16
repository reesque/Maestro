#ifndef DATABASE_H
#define DATABASE_H

#include <memory>
#include <string>
#include <mutex>

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
        int trackNum;
        std::string filePath;
        std::string title;
        std::string artist;
        std::string album;
    };

    explicit Database(QObject *parent = nullptr);
    ~Database();

    void insertTrack(const QString& filePath, const QString& title,
                const QString& artist, const QString& album, int trackNum);
    std::vector<Track> getAllTracks();
    std::vector<Track> getTracksByAlbum(const std::string& albumName);
    Track getTrack(int id);
    std::vector<std::string> getAllAlbums();
    void clearTable(const Table& table);

private:
    void execute(std::function<void(const QSqlDatabase&)> func);
    std::string getTableName(const Table& table);

private:
    QString m_appPath;
    std::mutex m_mutex;
};

Q_DECLARE_METATYPE(Database::Table);

#endif // DATABASE_H
