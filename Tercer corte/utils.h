#ifndef UTILS_H
#define UTILS_H

#include "models.h"
#include <QVector>

class Utils {
public:
    struct HealthStats {
        double avgWeight = 0;
        double avgSystolic = 0;
        double avgDiastolic = 0;
        double avgGlucose = 0;
    };

    static HealthStats calculateStats(const QVector<HealthRecord> &records);
    static bool exportToCSV(const QVector<HealthRecord> &records, const QString &path);
};

#endif // UTILS_H
