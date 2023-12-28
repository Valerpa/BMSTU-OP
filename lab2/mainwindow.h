#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMessageBox>
#include <QFile>
#include "appcontext.h"
#include "entrypoint.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Operations operation;
    Table table;
    List list;
    Metrics metrics;

    void on_open_file_clicked();
    void on_load_data_clicked();
    void on_calculate_metrics_clicked();
    QStringList convert_headers_to_qt_format();
    void show_data(List *list);
    void show_metrics(Metrics *metrics);
    QStringList convert_years_to_qt_format();
    void on_draw_button_clicked();

};
#endif // MAINWINDOW_H
