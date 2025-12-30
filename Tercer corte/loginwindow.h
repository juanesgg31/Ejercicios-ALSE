#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "databasemanager.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_btnLogin_clicked();
    void on_btnRegister_clicked();

private:
    Ui::LoginWindow *ui;
    DatabaseManager *db;
};

#endif // LOGINWINDOW_H
