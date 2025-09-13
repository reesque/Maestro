#ifndef DATABASE_H
#define DATABASE_H

#include <memory>

#include <QtSql/QSqlDatabase>

class Database
{
public:
    enum class Criteria
    {
        Title = 0,
        Artist,
        Album
    };

    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    static Database& getInstance() {
        if (!instance)
        {
            instance.reset(new Database);
        }

        return *instance;
    }

    void insert(const std::string& filePath, const std::string& title,
                const std::string& artist, const std::string& album, int duration);
    void select(const Criteria& criteria, const std::string& value);

private:
    Database();
    ~Database() = default;

    static void initDatabase() {
    }

    static std::unique_ptr<Database> instance;

private:
    QSqlDatabase m_db;
};

#endif // DATABASE_H
