#ifndef MODELS_H
#define MODELS_H

#include <QString>
#include <QDateTime>

struct User {
    int id;
    QString username;
    QString passwordHash;
};

struct HealthRecord {
    int id;
    int userId;
    double weight;
    int systolicPressure;
    int diastolicPressure;
    double glucose;
    QDateTime timestamp;
};

#endif // MODELS_H
