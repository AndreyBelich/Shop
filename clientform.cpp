#include <QtWidgets>
#include <QVector>
#include "client.h"
#include "clientform.h"

ClientForm::ClientForm(bool s, QWidget *parent):QDialog(parent),oldClient(0),newClient(0),state(s),luckAdd(true)
{
    readToFile();
    QRegExp fioRegex("[А-Я]{1}[а-я]{1,15}");
    QLabel *firstNameLabel = new QLabel(tr("Введите &имя"));
    firstNameLine = new QLineEdit;
    firstNameLabel->setBuddy(firstNameLine);
    firstNameLine->setValidator(new QRegExpValidator(fioRegex,this));

    QLabel *surnameLabel = new QLabel(tr("Введите &фамилию"));
    surnameLine = new QLineEdit;
    surnameLabel->setBuddy(surnameLine);
    surnameLine->setValidator(new QRegExpValidator(fioRegex,this));

    QLabel *patronymicLabel = new QLabel(tr("Введите &отчество"));
    patronymicLine = new QLineEdit;
    patronymicLabel->setBuddy(patronymicLine);
    patronymicLine->setValidator(new QRegExpValidator(fioRegex,this));

    QRegExp streetRegex("[А-Я]{1}[а-я]{0,20}[ -]{0,1}[А-Я]{0,1}[а-я]{0,20}");
    QLabel *streetLabel = new QLabel(tr("&Улица"));
    streetLine = new QLineEdit;
    streetLine->setValidator(new QRegExpValidator(streetRegex,this));
    streetLabel->setBuddy(streetLine);

    QLabel *houseNumberLabel = new QLabel(tr("&Дом №"));
    houseNumberLine = new QLineEdit;
    houseNumberLine->setValidator(new QIntValidator(houseNumberLine));
    houseNumberLine->setMaxLength(3);
    houseNumberLine->setMaximumWidth(30);
    houseNumberLabel->setBuddy(houseNumberLine);

    QLabel *flatNumberLabel = new QLabel(tr("&Квартира №"));
    flatNumberLine = new QLineEdit;
    flatNumberLine->setValidator(new QIntValidator(flatNumberLine));
    flatNumberLine->setMaxLength(3);
    flatNumberLine->setMaximumWidth(30);
    flatNumberLabel->setBuddy(flatNumberLine);

    QHBoxLayout *adressLayout = new QHBoxLayout;
    adressLayout->addWidget(streetLabel);
    adressLayout->addSpacing(95);
    adressLayout->addWidget(streetLine);
    adressLayout->addWidget(houseNumberLabel);
    adressLayout->addWidget(houseNumberLine);
    adressLayout->addWidget(flatNumberLabel);
    adressLayout->addWidget(flatNumberLine);

    QRegExp paspRegex("[А-Я]{2}[0-9]{6}");
    QLabel *passportNumberLabel = new QLabel(tr("Введите &номер паспорта"));
    passportNumberLine = new QLineEdit;
    passportNumberLabel->setBuddy(passportNumberLine);
    passportNumberLine->setValidator(new QRegExpValidator(paspRegex,this));

    okButton = new QPushButton(tr("&Подтвердить"));
    okButton->setDefault(true);
    okButton->setEnabled(false);
    cancelButton = new QPushButton(tr("&Выход"));
    resetButton = new QPushButton(tr("&Сбросить"));
    editButton = new QPushButton(tr("Сохранить изменения"));
    if(state)
        editButton->hide();
    else
        okButton->hide();

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(cancelButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(surnameLabel,0,0);
    mainLayout->addWidget(surnameLine,0,1);
    mainLayout->addWidget(firstNameLabel,1,0);
    mainLayout->addWidget(firstNameLine,1,1);
    mainLayout->addWidget(patronymicLabel,2,0);
    mainLayout->addWidget(patronymicLine,2,1);
    mainLayout->addLayout(adressLayout,3,0,1,2);
    mainLayout->addWidget(passportNumberLabel,4,0);
    mainLayout->addWidget(passportNumberLine,4,1);
    mainLayout->addLayout(buttonLayout,5,1);

    setLayout(mainLayout);
    setWindowTitle(tr("Информация о клиенте"));
    QPalette wpalette;
    wpalette.setColor(backgroundRole(),QColor("#D65443"));
    setPalette(wpalette);
    setAutoFillBackground(true);
    setStyleSheet("QLabel{color:white;}");
    okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
    cancelButton->setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}");
    resetButton->setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}");
    editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");

    connect(firstNameLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));
    connect(surnameLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));
    connect(patronymicLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));
    connect(passportNumberLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));
    connect(streetLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));
    connect(houseNumberLine,SIGNAL(textChanged(QString)),this,SLOT(okButtonActive()));

    connect(firstNameLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));
    connect(surnameLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));
    connect(patronymicLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));
    connect(passportNumberLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));
    connect(streetLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));
    connect(houseNumberLine,SIGNAL(textChanged(QString)),this,SLOT(editButtonActive()));

    connect(resetButton,SIGNAL(clicked()),this,SLOT(resetInformation()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(addInfoToFile()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(getCorrectValue()));
    connect(this,SIGNAL(badReturn()),this,SLOT(reject()));
    connect(this,SIGNAL(goodReturn()),this,SLOT(accept()));
}

void ClientForm::okButtonActive()
{
    if(!firstNameLine->hasAcceptableInput())
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!surnameLine->hasAcceptableInput())
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!patronymicLine->hasAcceptableInput())
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!passportNumberLine->hasAcceptableInput())
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(streetLine->text().isEmpty())
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(houseNumberLine->text().isEmpty() || houseNumberLine->text().toInt() == 0)
    {
        okButton->setEnabled(false);
        okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    okButton->setEnabled(true);
    okButton->setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}");
}

void ClientForm::editButtonActive()
{
    if(!firstNameLine->hasAcceptableInput())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!surnameLine->hasAcceptableInput())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!patronymicLine->hasAcceptableInput())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(!passportNumberLine->hasAcceptableInput())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(streetLine->text().isEmpty())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    if(houseNumberLine->text().isEmpty())
    {
        editButton->setEnabled(false);
        editButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        return;
    }
    editButton->setEnabled(true);
    editButton->setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}");
}

void ClientForm::resetInformation()
{
    firstNameLine->clear();
    surnameLine->clear();
    patronymicLine->clear();
    passportNumberLine->clear();
    streetLine->clear();
    houseNumberLine->clear();
    flatNumberLine->clear();
}

void ClientForm::addInfoToFile()
{
    writeToFile("infoclient.txt");
    resetInformation();
    setStyleSheet("QPushButton{background-color:#4C78C5;color:black;font:14px Times New Roman;}");
    if(luckAdd)
        QMessageBox::information(this,tr("Информация"),tr("Информация о клиенте успешно добавлена в файл"));
    setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                  "QLabel{color:white}");
}

void ClientForm::readToFile()
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
        clientContainer.push_back(temp);
        stream.flush();
    }
    mFile.close();
}

void ClientForm::writeToFile(const QString &path)
{
    QFile mFile(path);
    if(!mFile.open(QFile::WriteOnly | QFile::Append | QFile::Text))
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Не удалось открыть файл!"));
        return;
    }
    QTextStream stream(&mFile);
    Client add;
    add.setName(firstNameLine->text());
    add.setSurname(surnameLine->text());
    add.setPatronymic(patronymicLine->text());
    add.setPasportData(passportNumberLine->text());
    add.setStreet(streetLine->text());
    add.setHouseNumber(houseNumberLine->text());
    if(flatNumberLine->text().isEmpty() || flatNumberLine->text().toInt() == 0)
        add.setFlatNumber(tr("NULL"));
    else
        add.setFlatNumber(flatNumberLine->text());
    if(clientContainer.contains(add))
    {
        setStyleSheet("QPushButton{background-color:#4C78C5;color:black;font:14px Times New Roman;}");
        QMessageBox::information(this,tr("Сообщение"),tr("В базе данных уже содержится информация о данном клиенте"));
        setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                      "QLabel{color:white}");
        add.setID(add.getID() - 1);
        luckAdd = false;
    }
    else
    {
        stream<<"\n"<<add;
        luckAdd = true;
    }
    mFile.close();
}

void ClientForm::setLines(const Client &c)
{
    newClient.setID(c.getID());
    oldClient.setID(c.getID());
    oldClient.setName(c.getName());
    oldClient.setSurname(c.getSurname());
    oldClient.setPatronymic(c.getPatronymic());
    oldClient.setPasportData(c.getPasportData());
    oldClient.setStreet(c.getStreet());
    oldClient.setHouseNumber(c.getHouseNumber());
    oldClient.setFlatNumber(c.getFlatNumber());

    firstNameLine->setText(c.getName());
    surnameLine->setText(c.getSurname());
    patronymicLine->setText(c.getPatronymic());
    passportNumberLine->setText(c.getPasportData());
    streetLine->setText(c.getStreet());
    houseNumberLine->setText(c.getHouseNumber());
    if(c.getFlatNumber() == "NULL")
        flatNumberLine->setText("");
    else
        flatNumberLine->setText(c.getFlatNumber());
}

Client ClientForm::getOldClientData()
{
    return oldClient;
}

Client ClientForm::getNewClientData()
{
    newClient.setName(firstNameLine->text());
    newClient.setSurname(surnameLine->text());
    newClient.setPatronymic(patronymicLine->text());
    newClient.setPasportData(passportNumberLine->text());
    newClient.setStreet(streetLine->text());
    newClient.setHouseNumber(houseNumberLine->text());
    newClient.setFlatNumber(flatNumberLine->text());
    return newClient;
}

void ClientForm::getCorrectValue()
{
    newClient.setName(firstNameLine->text());
    newClient.setSurname(surnameLine->text());
    newClient.setPatronymic(patronymicLine->text());
    newClient.setPasportData(passportNumberLine->text());
    newClient.setStreet(streetLine->text());
    newClient.setHouseNumber(houseNumberLine->text());
    if(flatNumberLine->text().isEmpty() || flatNumberLine->text().toInt() == 0)
        newClient.setFlatNumber(tr("NULL"));
    else
        newClient.setFlatNumber(flatNumberLine->text());
    setStyleSheet("QPushButton{background-color:#4C78C5;color:black;font:14px Times New Roman;}");
    if(clientContainer.contains(newClient))
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Невозможно изменить данные. Клиент с указанными данными уже присутствует в базе"));
        setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                      "QLabel{color:white}");
        emit badReturn();
    }
    else
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Информация о клиенте успешно изменена"));
        setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                      "QLabel{color:white}");
        emit goodReturn();
    }
}
