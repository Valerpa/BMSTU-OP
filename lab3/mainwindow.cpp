#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_file_btn, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
    connect(ui->rotate_x_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_x_clicked);
    connect(ui->rotate_y_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_y_clicked);
    connect(ui->rotate_z_btn, &QPushButton::clicked, this, &MainWindow::on_rotate_z_clicked);
    connect(ui->move_btn, &QPushButton::clicked, this, &MainWindow::on_move_clicked);
    connect(ui->scale_btn, &QPushButton::clicked, this, &MainWindow::on_scale_clicked);
    context = new Context;
    QMessageBox::information(this, "Attention", "Enter normalization parameters before opening file!");
}

MainWindow::~MainWindow()
{
    do_operation(Clean_data, context);
    delete context;
    delete ui;
}

void MainWindow::on_open_file_clicked() {
    context->error.check = true;
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "*.csv");
    if (file_path.isEmpty()) {
        ui->file_path_label->setText("File was not chosen");
        return;
    }
    else {
        ui->file_path_label->setText(file_path);
        context->file_name = qstring_to_char_array(file_path);
        context->params.max = ui->max_norm_edit->text().toFloat();
        context->params.min = ui->min_norm_edit->text().toFloat();
        context->params.step = ui->norm_step_edit->text().toFloat();
        do_operation(Load_scene, context);
        if (context->error.check == false) {
            output_error();
            return;
        }
        else {
            draw();
        }
    }
}

void MainWindow::on_rotate_x_clicked() {
    context->error.check = true;
    context->axis = X;
    context->rotation = ui->rotate_x_edit->text().toFloat();
    do_operation(Rotate_scene, context);
    if (context->error.check == true) {
        draw();
    }
    else {
        output_error();
    }
}

void MainWindow::on_rotate_y_clicked() {
    context->error.check = true;
    context->axis = Y;
    context->rotation = ui->rotate_y_edit->text().toFloat();
    do_operation(Rotate_scene, context);
    if (context->error.check == true) {
        draw();
    }
    else {
        output_error();
    }
}

void MainWindow::on_rotate_z_clicked() {
    context->axis = Z;
    context->rotation = ui->rotate_z_edit->text().toFloat();
    do_operation(Rotate_scene, context);
    if (context->error.check == true) {
        draw();
    }
    else {
        output_error();
    }
}

void MainWindow::on_move_clicked() {
    context->error.check = true;
    context->move.x_move = ui->move_x_edit->text().toFloat();
    context->move.y_move = -ui->move_y_edit->text().toFloat();
    context->move.z_move = ui->move_z_edit->text().toFloat();
    do_operation(Move_scene, context);
    if (context->error.check == true) {
        draw();
    }
    else {
        output_error();
    }
}

void MainWindow::on_scale_clicked() {
    context->error.check = true;
    context->scale.x_scale = ui->scale_x_edit->text().toFloat();
    context->scale.y_scale = ui->scale_y_edit->text().toFloat();
    context->scale.z_scale = ui->scale_z_edit->text().toFloat();
    do_operation(Scale_scene, context);
    if (context->error.check == true) {
        draw();
    }
    else {
        output_error();
    }
}

void MainWindow::draw() {
    QPicture picture = QPicture();
    picture.setBoundingRect(QRect(QPoint(0, 0), QPoint(ui->model_label->width(), ui->model_label->height())));
    QPainter painter(&picture);
    painter.fillRect(0, 0, picture.width(), picture.height() , QBrush(QColor(Qt::GlobalColor::white)));
    painter.translate(picture.width() / 2, picture.height() / 2);
    painter.setPen(QColor(Qt::GlobalColor::black));
    for (size_t i = 0; i < context->columns - 1; i++) {
        painter.drawLine(context->figure[i].x, context->figure[i].y, context->figure[i + 1].x, context->figure[i + 1].y);
    }
    for (size_t i = 0; i < context->lines - 1; i++) {
        painter.drawLine(context->figure[i * context->columns].x, context->figure[i * context->columns].y, context->figure[(i + 1) * context->columns].x, context->figure[(i + 1) * context->columns].y);
    }
    for (size_t i = context->columns + 1; i < context->number_of_points; i++) {
        if (i % context->columns != 0) {
            painter.drawLine(context->figure[i].x, context->figure[i].y, context->figure[i - 1].x, context->figure[i - 1].y);
            painter.drawLine(context->figure[i].x, context->figure[i].y, context->figure[i - context->columns].x, context->figure[i - context->columns].y);
        }
    }
    ui->model_label->setPicture(picture);
}

void MainWindow::output_error() {
    QMessageBox::critical(this, "Error", context->error.err_info);
}

char* MainWindow::qstring_to_char_array(QString str) {
    char* c_str = (char*)malloc(str.size() + 1);
    if (c_str != NULL) {
        for(qsizetype i = 0; i < str.size(); i++) {
            c_str[i] = str.at(i).unicode();
        }
        c_str[str.size()] = 0;
    }
    return c_str;
}



