#ifndef DATABASE_H
#define DATABASE_H

#include <memory>

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

    enum class Criteria
    {
        Title = 0,
        Artist,
        Album
    };

    explicit Database(QObject *parent = nullptr);
    ~Database();

public slots:
    void insertTrack(const QString& filePath, const QString& title,
                const QString& artist, const QString& album);
    void selectTracks(const Criteria& criteria, const QString& value);
    void clearTable(const Table& table);

private:
    std::string getTableName(const Table& table);

private:
    QSqlDatabase m_db;
    static std::unique_ptr<Database> instance;
};

Q_DECLARE_METATYPE(Database::Table);

#endif // DATABASE_H
