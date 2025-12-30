#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "models.h"
#include "databasemanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(const User &u, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnGuardar_clicked();
    void on_btnFiltrar_clicked();
    void on_btnCalcular_clicked();
    void on_btnExportar_clicked();
    void on_btnLogout_clicked();

private:
    Ui::MainWindow *ui;
    User usuario;
    DatabaseManager *db;

    void cargarTabla();
};

#endif // MAINWINDOW_H

