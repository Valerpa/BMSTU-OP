#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr); //Конструктор - список методов, вызыввемых при создании объекта
    ~MainWindow(); //Деструктор - список, вызываемый при освбождении памяти


private:
    Ui::MainWindow *ui;
    App_context context;

    void on_digit_button_clicked();
    void on_button_plus_minus_clicked();
    void on_button_clear_clicked();
    void on_button_del_cliked();
    void on_button_dot_clicked();
    void on_button_equal_clicked();
    void on_button_plus_clicked();
    void on_button_minus_clicked();
    void on_button_multiply_clicked();
    void on_button_divide_clicked();
    void on_divide_1_by_x_clicked();
    void on_button_root_clicked();
    void on_button_sin_clicked();
    void on_button_cos_clicked();
    void on_button_tan_clicked();
    void on_button_cot_clicked();
    void on_button_M_Plus_clicked();
    void on_button_M_Minus_clicked();
    void on_button_M_R_clicked();
    void on_button_M_C_clicked();
    void update_label();
};
#endif // MAINWINDOW_H
