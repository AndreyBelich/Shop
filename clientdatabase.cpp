#include <QtWidgets>
#include "clientdatabase.h"

ClientDataBase::ClientDataBase(QWidget *parent):QDialog(parent),click(false)
{
    readToFile();

    table = new QTableWidget;
    table->setColumnCount(4);
    table->setColumnWidth(0,100);
    table->setColumnWidth(1,200);
    table->setColumnWidth(2,375);
    table->setColumnWidth(3,155);
    QStringList lst;
    lst<<tr("ID клиента")<<tr("Фамилия, Имя, Отчество")<<tr("Адрес проживания")<<tr("Паспортные данные");
    table->setHorizontalHeaderLabels(lst);
    setTable();

    editButton = new QPushButton(tr("&Править"));
    deleteButton = new QPushButton(tr("&Удалить"));
    exitButton = new QPushButton(tr("&Выход"));
    if(clientList.size() == 0)
    {
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
    }

    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    setFixedSize(950,400);

    connect(exitButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(deleteButton,SIGNAL(clicked()),this,SLOT(deleteConnect()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(editConnect()));
}

void ClientDataBase::setRowSize(int size)
{
    table->setRowCount(size);
}

void ClientDataBase::readToFile()
{
    QFile mFile("infoclient.txt");
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(this,tr("Информация"),tr("Не удалось открыть файл"));
        return;
    }
    QString str;
    QTextStream stream(&mFile);
    str = stream.readLine();
    Client temp(0);
    while(!stream.atEnd())
    {
        stream>>temp;
        clientList.push_back(temp);
        stream.flush();
    }
    mFile.close();
}

void ClientDataBase::writeToFile()
{
    QFile mFile("infoclient.txt");
    if(!mFile.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::information(this,tr("Информация"),tr("Не удалось открыть файл"));
        return;
    }
    QTextStream stream(&mFile);
    for(int i = 0; i < clientList.size(); i++)
    {
        stream<<"\n"<<clientList.at(i);
        stream.flush();
    }
    mFile.close();
}

void ClientDataBase::deleteConnect()
{
    try
    {
        if(table->currentRow() < 0)
            throw tr("Некорректный индекс");
    }
    catch(const QString &mes)
    {
        QMessageBox::warning(this,tr("Предупреждение"),mes);
        return;
    }
    click = true;
    clientList.removeAt(table->currentRow());
    setTable();
}

void ClientDataBase::setTable()
{
    table->setRowCount(clientList.size());
    QTableWidgetItem *item = NULL;
    QString itemText;
    for(int i = 0; i < clientList.size(); i++)
    {
        int j = 0;
        itemText = QString::number(clientList.at(i).getID());
        item = new QTableWidgetItem(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
        j++;
        itemText = clientList.at(i).getSurname() + " " + clientList.at(i).getName() + " " + clientList.at(i).getPatronymic();
        item = new QTableWidgetItem(itemText);
        table->setItem(i,j,item);
        j++;
        itemText = "улица " + clientList.at(i).getStreet() + " дом " + clientList.at(i).getHouseNumber();
        if(clientList.at(i).getFlatNumber() != "NULL")
            itemText += " квартира № " + clientList.at(i).getFlatNumber();
        item = new QTableWidgetItem(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
        j++;
        itemText = clientList.at(i).getPasportData();
        item = new QTableWidgetItem(itemText);
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(i,j,item);
    }
}

void ClientDataBase::closeEvent(QCloseEvent *)
{
    if(click)
    {
        int answer = QMessageBox::information(this,tr("Сообщение"),
                                 tr("Данные базы данных были изменены. Сохранить результат?"),
                                 QMessageBox::Yes | QMessageBox::No);
        if(answer == QMessageBox::Yes)
            writeToFile();
    }
    reject();
}

void ClientDataBase::editConnect()
{
    try
    {
        if(table->currentRow() < 0)
        throw tr("Некорректный индекс");
    }
    catch(const QString &mes)
    {
        QMessageBox::warning(this,tr("Предупреждение"),mes);
        return;
    }
    click = true;
    form = new ClientForm(false);
    form->show();
    hide();
    form->setLines(getData());
    if(form->exec() == QDialog::Rejected)
    {
        clientList[table->currentRow()] = form->getOldClientData();
    }
    else
    {
        clientList[table->currentRow()] = form->getNewClientData();
    }
    close();
    delete form;
}

Client ClientDataBase::getData()const
{
    Client temp(0);
    temp = clientList.at(table->currentRow());
    return temp;
}
