#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); //класс для обработки событийного цикла
    MainWindow w; //экземпляр класса MainWindow
    w.show(); //вызов метода показа окна
    return a.exec(); //запуск событийного цикла
}
