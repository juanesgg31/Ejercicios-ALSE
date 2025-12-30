#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QProcess>
#include <QApplication>

MainWindow::MainWindow(const User &u, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , usuario(u)
{
    ui->setupUi(this);

    db = new DatabaseManager("data/health_tracker.db");

    // Inicializar fechas por defecto (ej. último mes)
    ui->fechaIni->setDateTime(QDateTime::currentDateTime().addMonths(-1));
    ui->fechaFin->setDateTime(QDateTime::currentDateTime());

    cargarTabla();

    // Estilo básico
    this->setStyleSheet(
        "QMainWindow { background-color: #f0f0f0; }"
        "QPushButton { background-color: #007bff; color: white; border-radius: 5px; padding: 5px; }"
        "QPushButton:hover { background-color: #0056b3; }"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QDateTimeEdit { padding: 4px; border: 1px solid #ccc; border-radius: 3px; }"
    );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_btnLogout_clicked() {
    // Crear una nueva instancia de LoginWindow y mostrarla
    // Nota: Necesitamos incluir "loginwindow.h" al principio del archivo si no está
    // Pero LoginWindow incluye MainWindow, así que cuidado con dependencias circulares.
    // Una forma simple es cerrar esta ventana y dejar que el main maneje el flujo, 
    // pero como el main ya terminó su ejecución inicial, lo más fácil es instanciar LoginWindow aquí.
    
    // Para evitar dependencia circular en headers, usamos forward declaration en .h e include en .cpp
    // Ya tenemos #include "mainwindow.h", necesitamos #include "loginwindow.h"
    
    this->close();
    // LoginWindow *login = new LoginWindow();
    // login->show();
    // Sin embargo, para hacerlo correctamente sin fugas ni problemas de diseño, 
    // lo ideal sería emitir una señal o reiniciar la app.
    // Por simplicidad en este proyecto estudiantil:
    
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    qApp->quit();
}

void MainWindow::on_btnGuardar_clicked() {
    HealthRecord r;
    r.userId = usuario.id;
    r.weight = ui->spPeso->value();
    r.systolicPressure = ui->spSis->value();
    r.diastolicPressure = ui->spDia->value();
    r.glucose = ui->spGlu->value();
    r.timestamp = QDateTime::currentDateTime();

    if (db->addHealthRecord(r)) {
        QMessageBox::information(this, "Guardado", "Registro guardado correctamente");
        cargarTabla();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el registro.\nRevise la consola.");
    }
}

void MainWindow::on_btnFiltrar_clicked() {
    cargarTabla();
}

void MainWindow::cargarTabla() {
    QDateTime ini = ui->fechaIni->dateTime();
    QDateTime fin = ui->fechaFin->dateTime();

    auto registros = db->getRecordsByUserAndDateRange(usuario.id, ini, fin);

    QStandardItemModel *model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Peso", "Sis", "Dia", "Glucosa", "Fecha"});

    for (const auto &r : registros) {
        QList<QStandardItem*> fila;
        fila << new QStandardItem(QString::number(r.weight));
        fila << new QStandardItem(QString::number(r.systolicPressure));
        fila << new QStandardItem(QString::number(r.diastolicPressure));
        fila << new QStandardItem(QString::number(r.glucose));
        fila << new QStandardItem(r.timestamp.toString());
        model->appendRow(fila);
    }

    ui->tabla->setModel(model);
}

void MainWindow::on_btnExportar_clicked() {
    auto registros = db->getRecordsByUserAndDateRange(usuario.id,
                                                      ui->fechaIni->dateTime(),
                                                      ui->fechaFin->dateTime());
    Utils::exportToCSV(registros, "export.csv");
    QMessageBox::information(this, "Exportado", "Archivo exportado como export.csv");
}

void MainWindow::on_btnCalcular_clicked() {
    auto registros = db->getRecordsByUserAndDateRange(usuario.id,
                                                      ui->fechaIni->dateTime(),
                                                      ui->fechaFin->dateTime());
    
    auto stats = Utils::calculateStats(registros);
    
    QString info = QString("Promedios - Peso: %1 kg | Sis: %2 | Dia: %3 | Glu: %4")
            .arg(stats.avgWeight, 0, 'f', 1)
            .arg(stats.avgSystolic, 0, 'f', 0)
            .arg(stats.avgDiastolic, 0, 'f', 0)
            .arg(stats.avgGlucose, 0, 'f', 1);
            
    ui->lblStats->setText(info);
}
