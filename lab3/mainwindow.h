#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "context.h"
#include "entrypoint.h"
#include <QPicture>
#include <QMessageBox>
#include <QFileDialog>
#include <QPainter>
#include <QGraphicsScene>

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

    Context* context;
    void on_open_file_clicked();
    void draw();
    void on_rotate_x_clicked();
    void on_rotate_y_clicked();
    void on_rotate_z_clicked();
    void on_move_clicked();
    void on_scale_clicked();
    void output_error();
    char* qstring_to_char_array(QString str);
};
#endif // MAINWINDOW_H
