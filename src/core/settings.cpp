#include "settings.h"

Settings::Settings(std::shared_ptr<Database> db, QObject *parent)
    : QObject{parent}
{
    m_db = db;
}

Settings::~Settings()
{}

int Settings::getDpadResponsiveLevel()
{
    return std::stoi(m_db->getSetting("DpadResponsiveLevel"));
}

int Settings::getFaceBtnResponsiveLevel()
{
    return std::stoi(m_db->getSetting("FaceBtnResponsiveLevel"));
}

void Settings::setDpadResponsiveLevel(int level)
{
    m_db->setSetting("DpadResponsiveLevel", std::to_string(level));
    emit onDpadResponsiveLevelChanged(level);
}

void Settings::setFaceBtnResponsiveLevel(int level)
{
    m_db->setSetting("FaceBtnResponsiveLevel", std::to_string(level));
    emit onFaceBtnResponsiveLevelChanged(level);
}
