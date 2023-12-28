#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->open_button, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
    connect(ui->load_data_button, &QPushButton::clicked, this, &MainWindow::on_load_data_clicked);
    connect(ui->calc_button, &QPushButton::clicked, this, &MainWindow::on_calculate_metrics_clicked);
    connect(ui->draw_button, &QPushButton::clicked, this, &MainWindow::on_draw_button_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_file_clicked() {
    QString file_path = (QFileDialog::getOpenFileName(this, tr("Open File"), "C://", "CSV File (*.csv)"));
    if (file_path.isEmpty()) {
        ui->file_path_label->setText(QString("File was not opened."));
    }
    else {
    std::string file_path_str = file_path.toStdString();
    table.filename = file_path_str.c_str();
    entry_point(Open_file, &table, &list, NULL, NULL);
    show_data(&list);
    ui->file_path_label->setText(QString(table.filename));
    QMessageBox msg_box;
    msg_box.setText(QString::number(table.invalid_lines) + QString(" indavid lines were deleted!!!\n\n зачем вы так с инвалидами?"));
    msg_box.exec();
    if (table.errors.error_check == 1) {
        QMessageBox::critical(this, QString("ERROR"), QString("In line: ") + QString::number(table.errors.err_line) + QString("\n") + QString(table.errors.err_info));
        return;
    }
    }
}

void MainWindow::on_load_data_clicked() {
    QComboBox *combo_box = ui->region_cb;
    std::string cb_std = combo_box->currentText().toStdString();
    const char *cb_region = cb_std.c_str();
    QComboBox *min_year_cbox = ui->min_year_cb;
    int min_year = min_year_cbox->currentText().toInt();
    QComboBox *max_year_cbox = ui->max_year_cb;
    int max_year = max_year_cbox->currentText().toInt();
    Params params;
    params.chosen_region = cb_region;
    params.min_year = min_year;
    params.max_year = max_year;
    entry_point(Load_data, &table, &list, NULL, &params);
    if (table.errors.error_check == 1) {
        QMessageBox::critical(this, "ERROR", QString("In line: ") + QString::number(table.errors.err_line) + QString("\n") + QString(table.errors.err_info));
        return;
    }
    show_data(&list);
}

void MainWindow::on_calculate_metrics_clicked() {
    QComboBox *combo_box = ui->column_num_cb;
    const int column_num = combo_box->currentText().toInt();
    Params params;
    params.column_num = column_num;
    entry_point(Calculate_metrics, &table, &list, &metrics, &params);
    if (table.errors.error_check) {
        QMessageBox::critical(this, "ERROR", QString("In line: ") + QString::number(table.errors.err_line) + QString("\n") + QString(table.errors.err_info));
        return;
    }
    show_metrics(&metrics);
    //entry_point(Clean_data, &table, &list, &metrics, &params);
}

QStringList MainWindow::convert_headers_to_qt_format()
{
    QStringList qsl = {};

    qsl.append(QString::fromUtf8(table.headers.year_header));
    qsl.append(QString::fromUtf8(table.headers.region_header));
    qsl.append(QString::fromUtf8(table.headers.npg_header));
    qsl.append(QString::fromUtf8(table.headers.birth_rate_header));
    qsl.append(QString::fromUtf8(table.headers.death_rate_header));
    qsl.append(QString::fromUtf8(table.headers.gdw_header));
    qsl.append(QString::fromUtf8(table.headers.urban_header));
    return qsl;
}

void MainWindow::show_data(List* list) {
    QTableWidget *my_table = ui->table;
    my_table->setColumnCount(table.fields);
    QStringList QColumns = convert_headers_to_qt_format();
    my_table->setHorizontalHeaderLabels(QColumns);
    my_table->setRowCount(0);
    Node *current = list->head;
    int row = 0;
    while (current != NULL) {
        Dem_unit data = current->data;
        my_table->insertRow(row);
        my_table->setItem(row, 0, new QTableWidgetItem(QString::number(data.year)));
        if (ui->min_year_cb->findText(QString::number(data.year)) == -1) {
            ui->min_year_cb->addItem(QString::number(data.year));
        }
        if (ui->max_year_cb->findText(QString::number(data.year)) == -1) {
            ui->max_year_cb->addItem(QString::number(data.year));
        }
        my_table->setItem(row, 1, new QTableWidgetItem(data.region));
        if (ui->region_cb->findText(data.region) == -1) {
            ui->region_cb->addItem(data.region);
        }
        my_table->setItem(row, 2, new QTableWidgetItem(QString::number(data.npg)));
        my_table->setItem(row, 3, new QTableWidgetItem(QString::number(data.birth_rate)));
        my_table->setItem(row, 4, new QTableWidgetItem(QString::number(data.death_rate)));
        my_table->setItem(row, 5, new QTableWidgetItem(QString::number(data.gdw)));
        my_table->setItem(row, 6, new QTableWidgetItem(QString::number(data.urban)));
        current = current->next;
        row++;
    }
    my_table->resizeColumnsToContents();
    my_table->resizeRowsToContents();
}

void MainWindow::show_metrics(Metrics *metrics) {
    ui->result_label->setText(QString("Max: ") + QString::number(metrics->max_value) + QString("\n") +
                              QString("Min: ") + QString::number(metrics->min_value) + QString("\n") +
                              QString("Median: ") + QString::number(metrics->median));
}

QStringList MainWindow::convert_years_to_qt_format() {
    int rows_for_ox = ui->table->rowCount();
    QStringList qsl = {};
    for (int i = 0; i < rows_for_ox; i++) {
        QString year = ui->table->item(i, 0)->text();
        qsl.append(year);
    }
    return qsl;
}

void MainWindow::on_draw_button_clicked()
{
    QPixmap pix(601, 321);
    QPainter painter(&pix);
    pix.fill(Qt::white);
    QTableWidgetItem *item = ui->table->horizontalHeaderItem(0);
    QString header_for_ox = item->text();
    if (header_for_ox == "year") {
        painter.drawText(571, 185, header_for_ox);
    }
    else {
        QMessageBox::critical(this, "ERROR", "header /year/ was not found");
    }
    QTableWidgetItem *item_1 = ui->table->horizontalHeaderItem(ui->column_num_cb->currentText().toInt() - 1);
    QString header_for_oy = item_1->text();
    painter.drawText(50, 20, header_for_oy);
    painter.setPen(QColor(0, 0, 0, 255));
    painter.drawLine(50, 30, 50, 160); //ось Oy при y > 0
    painter.drawLine(50, 30, 45, 35); //левая часть оси Oy при y > 0
    painter.drawLine(50, 30, 55, 35); //правая часть оси Oy при y > 0
    painter.drawLine(50, 160, 50, 290); //ось Oy при y < 0
    painter.drawLine(50, 160, 571, 160); // ось Ox
    painter.drawLine(571, 160, 566, 155); //левая часть оси Ox
    painter.drawLine(571, 160, 566, 165); //правая часть оси Ox
    QStringList years = convert_years_to_qt_format();
    QFont font;
    font.setPixelSize(11);
    int rows_for_ox = ui->table->rowCount();
    int offset_for_ox = 531 / (rows_for_ox + 1);
    for (int i = 1; i <= rows_for_ox; i++) {
        painter.rotate(-90);
        painter.setFont(font);
        painter.drawText(-200, 50 + i * offset_for_ox, years[i - 1]);
        painter.rotate(90);
        painter.drawLine(45 + i * offset_for_ox, 155, 45 + i * offset_for_ox, 165);
    }

    painter.translate(50, 160);

    double k;
    if (abs(metrics.max_value) >= abs(metrics.min_value)) {
        k = -100 / metrics.max_value;
    }
    else {
        k = 100 / metrics.min_value;
    }

    QString metrics_max = QString::number(metrics.max_value);
    painter.drawText(-30, k * metrics.max_value, metrics_max);
    painter.drawLine(-5, k * metrics.max_value, 5, k * metrics.max_value);

    QString metrics_min = QString::number(metrics.min_value);
    painter.drawText(-30, k * metrics.min_value, metrics_min);
    painter.drawLine(-5, k * metrics.min_value, 5, k * metrics.min_value);

    QString metrics_median = QString::number(metrics.median);
    painter.drawText(-30, k * metrics.median, metrics_median);
    painter.drawLine(-5, k * metrics.median, 5, k * metrics.median);
    painter.setPen(QColor(104, 0, 174));
    for (int i = 1; i <= rows_for_ox; i++) {
        QString stats_item = ui->table->item((i - 1), ui->column_num_cb->currentText().toInt() - 1)->text();
        double current_metric = stats_item.toDouble();
        QRect rect(-7.5 + i * offset_for_ox, k * current_metric - 2.5, 5, 5);
        painter.fillRect(rect, QColor(104, 0, 174));
        painter.drawRect(rect);
    }
    ui->graphic_lable->setPixmap(pix);
}

