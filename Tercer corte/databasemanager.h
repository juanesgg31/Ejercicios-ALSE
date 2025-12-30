#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <optional>
#include "models.h"
#include <QVector> // Added this include based on the provided Code Edit, assuming it was intended to be moved/added.
#include <QDateTime> // Added this include as QDateTime is used in the header.

class DatabaseManager {
public:
    DatabaseManager(QString path);

    std::optional<User> getUserByUsername(const QString &username);
    bool createUser(const QString &username, const QString &pass);

    bool addHealthRecord(const HealthRecord &r);
    QVector<HealthRecord> getRecordsByUserAndDateRange(int userId,
                                                       QDateTime ini,
                                                       QDateTime fin);

private:
    QSqlDatabase db;
    void initTables();
};

#endif // DATABASEMANAGER_H
