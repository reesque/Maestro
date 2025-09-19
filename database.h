#ifndef DATABASE_H
#define DATABASE_H

#include "datastruct.h"

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

    explicit Database(QObject *parent = nullptr);
    ~Database() override;

    void insertTrack(const QString& filePath, const QString& title,
                const QString& artist, const QString& album, int trackNum);
    std::vector<Track> getAllTracks();
    std::vector<std::string> getAllAlbums();
    std::vector<std::string> getAllArtists();
    std::vector<Track> getTracksByAlbum(const std::string& albumName);
    std::vector<Track> getTracksByArtist(const std::string& artistName);
    std::vector<std::string> getAlbumByArtist(const std::string& artistName);
    Track getTrack(int id);
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
