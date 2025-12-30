#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

DatabaseManager::DatabaseManager(QString path) {
    // Evitar problemas si ya existe la conexión por defecto
    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        db = QSqlDatabase::database(QSqlDatabase::defaultConnection);
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(path);

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        qDebug() << db.lastError().text();
    } else {
        qDebug() << "Database: connection ok";
        initTables();
    }
}

void DatabaseManager::initTables() {
    QSqlQuery q(db);
    if (!q.exec("CREATE TABLE IF NOT EXISTS users ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "username TEXT UNIQUE, "
                "password_hash TEXT)")) {
        qDebug() << "Error creating users table:" << q.lastError().text();
    }

    if (!q.exec("CREATE TABLE IF NOT EXISTS health_records ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "user_id INTEGER, "
                "weight REAL, "
                "systolic INTEGER, "
                "diastolic INTEGER, "
                "glucose REAL, "
                "timestamp TEXT)")) {
        qDebug() << "Error creating health_records table:" << q.lastError().text();
    }
}

std::optional<User> DatabaseManager::getUserByUsername(const QString &username) {
    QSqlQuery q(db);
    q.prepare("SELECT id, username, password_hash FROM users WHERE username=?");
    q.addBindValue(username);

    if (!q.exec()) {
        qDebug() << "Error getting user:" << q.lastError().text();
        return std::nullopt;
    }

    if (q.next()) {
        User u;
        u.id = q.value(0).toInt();
        u.username = q.value(1).toString();
        u.passwordHash = q.value(2).toString();
        return u;
    }
    return std::nullopt;
}

bool DatabaseManager::createUser(const QString &username, const QString &pass) {
    QSqlQuery q(db);
    q.prepare("INSERT INTO users (username, password_hash) VALUES (?,?)");
    q.addBindValue(username);
    q.addBindValue(pass);      // OJO: aquí podrías guardar un hash real
    if (!q.exec()) {
        qDebug() << "Error creating user:" << q.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::addHealthRecord(const HealthRecord &r) {
    QSqlQuery q(db);
    q.prepare("INSERT INTO health_records "
              "(user_id, weight, systolic, diastolic, glucose, timestamp) "
              "VALUES (?,?,?,?,?,?)");
    q.addBindValue(r.userId);
    q.addBindValue(r.weight);
    q.addBindValue(r.systolicPressure);
    q.addBindValue(r.diastolicPressure);
    q.addBindValue(r.glucose);
    q.addBindValue(r.timestamp.toString(Qt::ISODate));

    if (!q.exec()) {
        qDebug() << "Error adding record:" << q.lastError().text();
        return false;
    }
    return true;
}

QVector<HealthRecord> DatabaseManager::getRecordsByUserAndDateRange(
        int userId, QDateTime ini, QDateTime fin)
{
    QVector<HealthRecord> lista;

    QSqlQuery q(db);
    q.prepare("SELECT id, weight, systolic, diastolic, glucose, timestamp "
              "FROM health_records "
              "WHERE user_id=? "
              "AND date(timestamp) BETWEEN date(?) AND date(?) "
              "ORDER BY timestamp DESC");
    q.addBindValue(userId);
    q.addBindValue(ini.toString(Qt::ISODate));
    q.addBindValue(fin.toString(Qt::ISODate));

    if (!q.exec()) {
        qDebug() << "Error getting records:" << q.lastError().text();
        return lista;
    }

    while (q.next()) {
        HealthRecord r;
        r.id = q.value(0).toInt();
        r.weight = q.value(1).toDouble();
        r.systolicPressure = q.value(2).toInt();
        r.diastolicPressure = q.value(3).toInt();
        r.glucose = q.value(4).toDouble();
        r.timestamp = QDateTime::fromString(q.value(5).toString(), Qt::ISODate);
        lista.append(r);
    }

    return lista;
}
