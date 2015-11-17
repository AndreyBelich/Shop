#include <QtWidgets>
#include "selldialog.h"

SellDialog::SellDialog(QWidget *parent):QDialog(parent)
{
    readToFile();
    table = new QTableWidget;
    table->setRowCount(info.size());
    table->setColumnCount(6);
    QStringList sheetHeader;
    sheetHeader<<tr("ID клиента")<<tr("Фамилия, Имя, Отчество")<<tr("Марка автомобиля")<<tr("Модель автомобиля")
              <<tr("Цена автомобиля")<<tr("Дата продажи");
    table->setHorizontalHeaderLabels(sheetHeader);
    table->setColumnWidth(1,200);
    table->setColumnWidth(2,150);
    table->setColumnWidth(3,150);
    table->setColumnWidth(4,150);
    QTableWidgetItem *item = NULL;
    QString itemText;
    for(int i = 0; i < info.size(); i++)
    {
        int j = 0;//0 ID
        itemText = QString::number(info[i].getID());
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(!Qt::ItemIsEnabled);
        table->setItem(i,j,item);
        j++;//1 FIO
        itemText = info[i].getSurname() + " " + info[i].getName() + " " + info[i].getPatronymic();
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(!Qt::ItemIsEditable);
        table->setItem(i,j,item);
        j++;//2 Brand
        itemText = info[i].getBrand();
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        item->setFlags(!Qt::ItemIsEditable);
        table->setItem(i,j,item);
        j++;//3 Model
        itemText = info[i].getModel();
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
        j++;//4 price
        itemText = QString::number(info[i].getPrice()) + " " + info[i].getCurrency();
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
        j++;//5 date
        itemText = QString::number(info[i].getDay()) + "." + QString::number(info[i].getMonth()) + "."
                 + QString::number(info[i].getYear());
        item = new QTableWidgetItem;
        item->setText(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
    }
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(table);
    setLayout(mainLayout);
    setWindowTitle(tr("Информация о продажах"));
    resize(900,400);
}

void SellDialog::readToFile()
{
    QFile mFile("BuyInfo.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Не удалось открыть файл"));
        return;
    }
    QTextStream stream(&mFile);
    QString str;
    str = stream.readLine();
    BuyInformation temp;
    while(!stream.atEnd())
    {
        stream>>temp;
        info.push_back(temp);
        stream.flush();
    }
    mFile.close();
}
