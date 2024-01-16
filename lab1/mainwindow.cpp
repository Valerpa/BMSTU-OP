#include "mainwindow.h"
#include "./ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); //генерация кода для отрисовки UI
    //connect - метод для связи сигналов и слотов с объектами
    //      sender            signal            receiver           slot                     connection_type
    connect(ui->Button_0, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_1, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_2, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_3, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_4, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_5, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_6, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_7, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_8, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);
    connect(ui->Button_9, &QPushButton::clicked, this, &MainWindow::on_digit_button_clicked);

    connect(ui->Button_Sep, &QPushButton::clicked, this, &MainWindow::on_button_dot_clicked);
    connect(ui->Button_Plus_Minus, &QPushButton::clicked, this, &MainWindow::on_button_plus_minus_clicked);
    connect(ui->Button_Clear, &QPushButton::clicked, this, &MainWindow::on_button_clear_clicked);
    connect(ui->Button_Del, &QPushButton::clicked, this, &MainWindow::on_button_del_cliked);
    connect(ui->Button_Equal, &QPushButton::clicked, this, &MainWindow::on_button_equal_clicked);

    connect(ui->Button_Plus, &QPushButton::clicked, this, &MainWindow::on_button_plus_clicked);
    connect(ui->Button_Minus, &QPushButton::clicked, this, &MainWindow::on_button_minus_clicked);
    connect(ui->Button_Multiply, &QPushButton::clicked, this, &MainWindow::on_button_multiply_clicked);
    connect(ui->Button_Divide, &QPushButton::clicked, this, &MainWindow::on_button_divide_clicked);
    connect(ui->Button_One_Divide, &QPushButton::clicked, this, &MainWindow::on_divide_1_by_x_clicked);
    connect(ui->Button_Sqrt, &QPushButton::clicked, this, &MainWindow::on_button_root_clicked);

    connect(ui->Button_Sin, &QPushButton::clicked, this, &MainWindow::on_button_sin_clicked);
    connect(ui->Button_Cos, &QPushButton::clicked, this, &MainWindow::on_button_cos_clicked);
    connect(ui->Button_Tan, &QPushButton::clicked, this, &MainWindow::on_button_tan_clicked);
    connect(ui->Button_Cot, &QPushButton::clicked, this, &MainWindow::on_button_cot_clicked);

    connect(ui->Button_M_Plus, &QPushButton::clicked, this, &MainWindow::on_button_M_Plus_clicked);
    connect(ui->Button_M_Minus, &QPushButton::clicked, this, &MainWindow::on_button_M_Minus_clicked);
    connect(ui->Button_MR, &QPushButton::clicked, this, &MainWindow::on_button_M_R_clicked);
    connect(ui->Button_MC, &QPushButton::clicked, this, &MainWindow::on_button_M_C_clicked);

    do_operation(Clear_all, &context, NULL);
    update_label();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_digit_button_clicked()
{
    QPushButton* button = (QPushButton*)sender();
    std::string button_text = button->text().toStdString(); // QString -> std::string
    const char *button_text_to_char_array = button_text.c_str(); // std::string -> const char *
    char clicked_digit = *button_text_to_char_array; //const char * -> char (первый элемент массива char[])
    do_operation(Operation::Add_Digit, &context, &clicked_digit);
    update_label();
}

void MainWindow::on_button_dot_clicked()
{
   do_operation(Operation::Separator, &context, NULL);
   update_label();
}

void MainWindow::on_button_plus_minus_clicked()
{
    do_operation(Operation::Sign, &context, NULL);
    update_label();
}

void MainWindow::on_button_clear_clicked()
{
    do_operation(Operation::Clear_all, &context, NULL);
    update_label();
}

void MainWindow::on_button_del_cliked()
{
    do_operation(Operation::Del_last_digit, &context, NULL);
    update_label();
}

void MainWindow::on_button_equal_clicked()
{
    do_operation(Operation::Equality, &context, NULL);
    update_label();
}

void MainWindow::on_button_plus_clicked()
{
    do_operation(Operation::Summ, &context, NULL);
    update_label();
}

void MainWindow::on_button_minus_clicked()
{
    do_operation(Operation::Substraction, &context, NULL);
    update_label();
}

void MainWindow::on_button_multiply_clicked()
{
    do_operation(Operation::Multiplication, &context, NULL);
    update_label();
}

void MainWindow::on_button_divide_clicked()
{
    do_operation(Operation::Division, &context, NULL);
    update_label();
}

void MainWindow::on_divide_1_by_x_clicked()
{
    do_operation(Operation::One_division, &context, NULL);
    update_label();
}

void MainWindow::on_button_root_clicked()
{
    do_operation(Operation::Root, &context, NULL);
    update_label();
}

void MainWindow::on_button_sin_clicked()
{
    do_operation(Operation::Sin, &context, NULL);
    update_label();
}

void MainWindow::on_button_cos_clicked()
{
    do_operation(Operation::Cos, &context, NULL);
    update_label();
}

void MainWindow::on_button_tan_clicked()
{
    do_operation(Operation::Tan, &context, NULL);
    update_label();
}

void MainWindow::on_button_cot_clicked()
{
    do_operation(Operation::Cot, &context, NULL);
    update_label();
}

void MainWindow::on_button_M_Plus_clicked()
{
    do_operation(Operation::M_plus, &context, NULL);
    update_label();
}

void MainWindow::on_button_M_Minus_clicked()
{
    do_operation(Operation::M_minus, &context, NULL);
    update_label();
}

void MainWindow::on_button_M_R_clicked()
{
    do_operation(Operation::M_R, &context, NULL);
    update_label();
}

void MainWindow::on_button_M_C_clicked()
{
    do_operation(Operation::M_C, &context, NULL);
    update_label();
}

void MainWindow::update_label()
{
    ui->label->setText(QString(context.digits)); //явно преобразуем char * в QString
}
