#include "utils.h"
#include <QFile>
#include <QTextStream>

Utils::HealthStats Utils::calculateStats(const QVector<HealthRecord> &records) {
    HealthStats s;
    if (records.isEmpty()) return s;

    for (const auto &r : records) {
        s.avgWeight += r.weight;
        s.avgSystolic += r.systolicPressure;
        s.avgDiastolic += r.diastolicPressure;
        s.avgGlucose += r.glucose;
    }

    int n = records.size();
    s.avgWeight /= n;
    s.avgSystolic /= n;
    s.avgDiastolic /= n;
    s.avgGlucose /= n;

    return s;
}

bool Utils::exportToCSV(const QVector<HealthRecord> &records, const QString &path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&file);
    out << "Peso,Sis,Dia,Glucosa,Fecha\n";

    for (const auto &r : records) {
        out << r.weight << ","
            << r.systolicPressure << ","
            << r.diastolicPressure << ","
            << r.glucose << ","
            << r.timestamp.toString(Qt::ISODate) << "\n";
    }

    file.close();
    return true;
}
