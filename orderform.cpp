#include <QtWidgets>
#include "orderform.h"

OrderForm::OrderForm(QWidget *parent):QDialog(parent)
{
    readToFile();
    QRegExp fioRegex("[А-Я]{1}[а-я]{1,15}");
    QLabel *firstNameLabel = new QLabel(tr("Введите &имя"));
    firstNameLine = new QLineEdit;
    firstNameLine->setValidator(new QRegExpValidator(fioRegex,this));
    firstNameLabel->setBuddy(firstNameLine);

    QLabel *surnameLabel = new QLabel(tr("Введите &фамилию"));
    surnameLine = new QLineEdit;
    surnameLine->setValidator(new QRegExpValidator(fioRegex,this));
    surnameLabel->setBuddy(surnameLine);

    QLabel *patronymicLabel = new QLabel(tr("Введите &отчество"));
    patronymicLine = new QLineEdit;
    patronymicLine->setValidator(new QRegExpValidator(fioRegex,this));
    patronymicLabel->setBuddy(patronymicLine);

    QLabel *streetLabel = new QLabel(tr("&Улица"));
    streetLine = new QLineEdit;
    streetLine->setMaximumWidth(120);
    streetLabel->setBuddy(streetLine);

    QLabel *houseNumberLabel = new QLabel(tr("&Дом"));
    houseNumberLine = new QLineEdit;
    houseNumberLine->setMaxLength(3);
    houseNumberLine->setMaximumWidth(30);
    houseNumberLine->setValidator(new QIntValidator(houseNumberLine));
    houseNumberLabel->setBuddy(houseNumberLine);

    QLabel *flatNumberLabel = new QLabel(tr("&Квартира"));
    flatNumberLine = new QLineEdit;
    flatNumberLine->setMaxLength(3);
    flatNumberLine->setMaximumWidth(30);
    flatNumberLine->setValidator(new QIntValidator(flatNumberLine));
    flatNumberLabel->setBuddy(flatNumberLine);

    QHBoxLayout *adressLayout = new QHBoxLayout;
    adressLayout->addWidget(streetLabel);
    adressLayout->addSpacing(47);
    adressLayout->addWidget(streetLine);
    adressLayout->addWidget(houseNumberLabel);
    adressLayout->addWidget(houseNumberLine);
    adressLayout->addWidget(flatNumberLabel);
    adressLayout->addWidget(flatNumberLine);

    QRegExp pasportRegex("[А-Я]{2}[0-9]{6}");
    QLabel *pasportLabel = new QLabel(tr("&Паспортные данные"));
    pasportLine = new QLineEdit;
    pasportLine->setValidator(new QRegExpValidator(pasportRegex,this));
    pasportLabel->setBuddy(pasportLine);

    QLabel *priceLabel = new QLabel(tr("&Цена"));
    priceLine = new QLineEdit;
    priceLine->setReadOnly(true);
    priceLine->setMaximumWidth(150);

    priceLabel->setBuddy(priceLine);

    QLabel *brandLabel = new QLabel(tr("Марка автомобиля"));
    brandLine = new QLineEdit;
    brandLine->setReadOnly(true);

    QLabel *modelLabel = new QLabel(tr("Модель автомобиля"));
    modelLine = new QLineEdit;
    modelLine->setReadOnly(true);

    QLabel *currencyLabel = new QLabel(tr("Валюта"));
    currencyLine = new QLineEdit;
    currencyLine->setReadOnly(true);

    QHBoxLayout *currencyLayout = new QHBoxLayout;
    currencyLayout->addWidget(priceLabel);
    currencyLayout->addSpacing(78);
    currencyLayout->addWidget(priceLine);
    currencyLayout->addWidget(currencyLabel);
    currencyLayout->addWidget(currencyLine);

    okButton = new QPushButton(tr("&Оформить"));
    okButton->setDefault(true);
    okButton->setEnabled(false);
    cancelButton = new QPushButton(tr("&Отменить"));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addSpacing(140);
    buttonLayout->addWidget(okButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(cancelButton);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(surnameLabel,0,0);
    mainLayout->addWidget(surnameLine,0,1);
    mainLayout->addWidget(firstNameLabel,1,0);
    mainLayout->addWidget(firstNameLine,1,1);
    mainLayout->addWidget(patronymicLabel,2,0);
    mainLayout->addWidget(patronymicLine,2,1);
    mainLayout->addLayout(adressLayout,3,0,1,2);
    mainLayout->addWidget(pasportLabel,4,0);
    mainLayout->addWidget(pasportLine,4,1);
    mainLayout->addWidget(brandLabel,5,0);
    mainLayout->addWidget(brandLine,5,1);
    mainLayout->addWidget(modelLabel,6,0);
    mainLayout->addWidget(modelLine,6,1);
    mainLayout->addLayout(currencyLayout,7,0,1,2);
    mainLayout->addLayout(buttonLayout,8,1);

    setLayout(mainLayout);
    setWindowTitle(tr("Оформление заказа"));
    QPalette wpalette;
    wpalette.setColor(backgroundRole(),QColor("#D65443"));
    setPalette(wpalette);
    setAutoFillBackground(true);
    setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                  "QLabel{color:white;}");
    okButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");

    connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(firstNameLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));
    connect(surnameLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));
    connect(patronymicLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));
    connect(pasportLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));
    connect(streetLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));
    connect(houseNumberLine,SIGNAL(textChanged(QString)),this,SLOT(activateOkButton()));

    connect(okButton,SIGNAL(clicked()),this,SLOT(addClientToBase()));
    connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
}

void OrderForm::setCarInfoLine(const Car &c)
{
    information.setCarInformation(c);
    brandLine->setText(c.getBrand());
    modelLine->setText(c.getModel());
    priceLine->setText(QString::number(c.getPrice()));
    currencyLine->setText(c.getCurrency());
}

void OrderForm::activateOkButton()
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
    if(!pasportLine->hasAcceptableInput())
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

void OrderForm::readToFile()
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
        clientBase.push_back(temp);
        stream.flush();
    }
    mFile.close();
}

void OrderForm::addClientToBase()
{
    QFile mFile("infoclient.txt");
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
    add.setPasportData(pasportLine->text());
    add.setStreet(streetLine->text());
    add.setHouseNumber(houseNumberLine->text());
    if(flatNumberLine->text().isEmpty() || flatNumberLine->text().toInt() == 0)
        add.setFlatNumber(tr("NULL"));
    else
        add.setFlatNumber(flatNumberLine->text());
    if(clientBase.contains(add))
    {
        setStyleSheet("QPushButton{background-color:#4C78C5;color:black;font:14px Times New Roman;}");
        QMessageBox::information(this,tr("Сообщение"),tr("В базе данных уже содержится информация о данном клиенте"));
        setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                      "QLabel{color:white}");
        add.setID(add.getID() - 1);
    }
    else
    {
        stream<<"\n"<<add;
    }
    mFile.close();
    information.setClientInformation(add);
    writeBuyInformation();
}

void OrderForm::writeBuyInformation()
{
    QFile mFile("BuyInfo.txt");
    if(!mFile.open(QFile::WriteOnly | QFile::Append | QFile::Text))
    {
        QMessageBox::information(this,tr("Сообщение"),tr("Не удалось открыть файл"));
        return;
    }
    QTextStream stream(&mFile);
    stream<<"\n"<<information;
    mFile.close();
}
