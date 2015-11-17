#include <QtWidgets>
#include "tabdialog.h"
#include "find.h"
#include "add.h"
#include "table.h"
#include "finddialog.h"

TabDialog::TabDialog(QWidget *parent):QDialog(parent)
{
    readToFile();
    findWidget = new Find(this);
    addWidget = new Add(this);
    tabWidget = new QTabWidget;
    tabWidget->addTab(findWidget,tr("Поиск"));
    tabWidget->addTab(addWidget,tr("Добавить"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tabWidget);
    setLayout(layout);

    connect(addWidget,SIGNAL(addCar(Car)),this,SLOT(pushData(Car)));
    connect(findWidget,SIGNAL(findClick()),this,SLOT(importContainerInfo()));
    connect(this,SIGNAL(infoToTable(int,QVector<Car>)),this,SLOT(findResult(int,QVector<Car>)));
    setWindowTitle(tr("Каталог автомобилей"));
}

void TabDialog::pushData(const Car &c)
{
    catalog.push_back(c);
    writeToFile(c);
}

void TabDialog::writeToFile(const Car &c)
{
    QFile mFile("mycar.txt");
    if(!mFile.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox::information(this,tr("Предупреждение"),tr("Не удалось открыть файл"));
        return;
    }
    QTextStream stream(&mFile);
    stream<<"\n"<<c;
    mFile.close();
}

void TabDialog::readToFile()
{
    QFile mFile("mycar.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,tr("Предупреждение"),tr("Не удалось открыть файл. Если Вы запускаете программу впервый раз проигнорируйте это сообщение"));
        return;
    }
    QTextStream stream(&mFile);
    Car temp;
    QString str;
    str = stream.readLine();
    while(!stream.atEnd())
    {
        stream>>temp;
        catalog.push_back(temp);
        stream.flush();
    }
    mFile.close();
}

void TabDialog::findResult(int size,const QVector<Car> &c)
{
    if(size == 0)
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Поиск не дал результатов!"));
        return;
    }
    FindDialog *dialog = new FindDialog(this,size,c);
    hide();
    dialog->show();
    dialog->exec();
    close();
    delete dialog;
}

void TabDialog::importContainerInfo()
{
    QVector<Car> import;
    for(int i = 0; i < catalog.size();i++)
    {
        if(catalog[i].getType() != findWidget->getCurrentType())
            continue;
        if(catalog[i].getState() != findWidget->getCurrentState())
            continue;
        if(catalog[i].getBrand() != findWidget->getCurrentBrand() && findWidget->getCurrentBrand() != "Любая")
            continue;
        if(catalog[i].getModel() != findWidget->getCurrentModel() && findWidget->getCurrentModel() != "Любая")
            continue;
        if(catalog[i].getBodyType() != findWidget->getCurrentBodyType() && findWidget->getCurrentBodyType() != "Любой")
            continue;
        if(catalog[i].getRegion() != findWidget->getCurrentRegion() && findWidget->getCurrentRegion() != "Любой")
            continue;
        if(catalog[i].getCurrency() != findWidget->getCurrentCurrency())
            continue;
        if(((catalog[i].getYear() >= findWidget->getMinimumYear()) && (catalog[i].getYear() <= findWidget->getMaximumYear()))
                || ((findWidget->getMinimumYear() != 0) && (findWidget->getMaximumYear() != 0)))
            continue;
        if(catalog[i].getPrice() <= findWidget->getMinimumPrice() || catalog[i].getPrice() >= findWidget->getMaximumPrice())
            continue;
        import.push_back(catalog[i]);
    }
    emit infoToTable(import.size(),import);
}
