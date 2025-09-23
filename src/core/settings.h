#ifndef SETTINGS_H
#define SETTINGS_H

#include "database.h"

#include <memory>
#include <map>

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT
public:
    Settings(std::shared_ptr<Database> db, QObject *parent = nullptr);
    ~Settings() override;

    int getDpadResponsiveLevel();
    int getFaceBtnResponsiveLevel();

    void setDpadResponsiveLevel(int level);
    void setFaceBtnResponsiveLevel(int level);

signals:
    void onDpadResponsiveLevelChanged(int level);
    void onFaceBtnResponsiveLevelChanged(int level);

private:
    std::shared_ptr<Database> m_db;
};

#endif // SETTINGS_H
