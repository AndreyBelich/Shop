#include <QtWidgets>
#include "table.h"

Table::Table(QWidget *parent,int size):QTableWidget(parent)
{

    setRowCount(size);
    setColumnCount(Table::getTableWidth());
    QStringList lst;
    lst<<tr("Тип автомобиля")<<tr("Состояние автомобиля")<<tr("Марка")<<tr("Модель")
       <<tr("Тип кузова")<<tr("Регион")<<tr("Год выпуска")<<tr("Цена")<<tr("Валюта");
    setHorizontalHeaderLabels(lst);
    setWindowTitle(tr("Результаты поиска"));
    resize(800,400);
}
