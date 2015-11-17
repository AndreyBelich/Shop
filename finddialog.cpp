#include <QtWidgets>
#include "orderform.h"
#include "finddialog.h"

FindDialog::FindDialog(QWidget *parent,int size,const QVector<Car> &c):QDialog(parent)
{
    carList = c;
    orderButton = new QPushButton(tr("&Оформить заказ"));
    tWidget = new Table(this,size);
    tWidget->setColumnWidth(1,175);
    QTableWidgetItem *item = NULL;
    for(int i = 0; i < size; i++)
    {
        int j = 0;
        item = new QTableWidgetItem(carList[i].getType());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getState());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getBrand());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getModel());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getBodyType());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getRegion());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(QString::number(carList[i].getYear()));
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(QString::number(carList[i].getPrice()));
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
        j++;
        item = new QTableWidgetItem(carList[i].getCurrency());
        item->setTextAlignment(Qt::AlignCenter);
        tWidget->setItem(i,j,item);
    }
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(orderButton);
    buttonLayout->addStretch();
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(tWidget);
    hLayout->addLayout(buttonLayout);
    setLayout(hLayout);
    resize(1111,400);
    setWindowTitle(tr("Результаты поиска"));

    connect(orderButton,SIGNAL(clicked()),this,SLOT(callOrderForm()));
}

void FindDialog::callOrderForm()
{
    form = new OrderForm(this);
    form->show();
    form->setCarInfoLine(getCarInfo());
    hide();
    if(form->exec() == QDialog::Accepted)
    {
        if(carList.at(tWidget->currentRow()).getState() == "б/у")
        {
            readOldInformation();
            deleteOldCar();
            writeNewInformation();
            QMessageBox::information(0,tr("Сообщение"),tr("Машина %1 удалена из коллекции").arg(carList[tWidget->currentRow()].getBrand()));
        }
    }
    close();
    delete form;
}

void FindDialog::closeEvent(QCloseEvent *)
{
    reject();
}

Car FindDialog::getCarInfo()const
{
    return carList.at(tWidget->currentRow());
}

void FindDialog::readOldInformation()
{
    QFile mFile("mycar.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    Car temp;
    QTextStream stream(&mFile);
    QString str;
    str = stream.readLine();
    while(!stream.atEnd())
    {
        stream >> temp;
        delOldCar.push_back(temp);
        stream.flush();
    }
    QMessageBox::information(0,tr("mes"),tr("Container size = %1").arg(delOldCar.size()));
    mFile.close();
}

void FindDialog::deleteOldCar()
{
    int index = -1;
    int i;
    for(i = 0; i < delOldCar.size(); i++)
    {
        if(delOldCar[i] == carList[tWidget->currentRow()])
        {
            index = i;
            break;
            QMessageBox::information(0,tr("mes"),tr("Remove index %1").arg(i));
        }
    }
    if(index >= 0)
        delOldCar.removeAt(index);
}

void FindDialog::writeNewInformation()
{
    QFile mFile("mycar.txt");
    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream stream(&mFile);
    for(int i = 0; i < delOldCar.size(); i++)
    {
        stream<<"\n"<<delOldCar[i];
        stream.flush();
    }
    mFile.close();
}
