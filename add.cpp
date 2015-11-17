#include <QtWidgets>
#include "add.h"

Add::Add(QWidget *parent):QWidget(parent)
{
    QLabel *typeCarLabel = new QLabel(tr("Выберите тип автомобиля"));
    carType = new QComboBox;
    QStringList typeList;
    typeList<<tr("Легковые")<<tr("Грузовые")<<tr("Автобус")<<tr("Мотоцикл");
    carType->addItems(typeList);

    QLabel *stateLabel = new QLabel(tr("Выберите состояние автомобиля"));
    stateBox = new QComboBox;
    stateBox->addItem(tr("Не выбрано"));
    stateBox->addItem(tr("Новый"));
    stateBox->addItem(tr("б/у"));

    QLabel *brandLabel = new QLabel(tr("Выберите марку автомобиля"));
    brandBox = new QComboBox;
    QStringList brandList;
    brandList<<tr("Любая")<<tr("BMW")<<tr("Mazda")<<tr("ВАЗ");
    brandBox->addItems(brandList);

    QLabel *modelLabel = new QLabel(tr("Выберите модель автомобиля"));
    modelBox = new QComboBox;
    QStringList modelList;
    modelList<<tr("Не выбрано");
    modelBox->addItems(modelList);

    QLabel *bodyTypeLabel = new QLabel(tr("Выберите тип кузова"));
    bodyType = new QComboBox;
    QStringList bodyTypeList;
    bodyTypeList<<tr("Не выбрано")<<tr("Кабриолет")<<tr("Микроавтобус")<<tr("Седан")<<tr("Пикап")
                <<tr("Фургон")<<tr("Купе");
    bodyType->addItems(bodyTypeList);

    QLabel *regionLabel = new QLabel(tr("Выберите регион"));
    regionBox = new QComboBox;
    QStringList regionList;
    regionList<<tr("Не выбрано")<<tr("Запорожье")<<tr("Киев")<<tr("Одесса")<<tr("Харьков")<<tr("Николаев")<<tr("Ровно");
    regionBox->addItems(regionList);

    QLabel *createYearLabel = new QLabel(tr("Выберите год выпуска"));
    makeYear = new QComboBox;
    makeYear->addItem(tr("Не выбрано"));
    QDate *date = new QDate(QDate::currentDate());
    for(int i = 1950; i <= date->year(); i++)
        makeYear->addItem(QString::number(i));

    QLabel *priceLabel = new QLabel(tr("Введите стоимость автомобиля"));
    priceBox = new QSpinBox;
    priceBox->setRange(0,1000000);
    priceBox->setValue(0);
    currencyBox = new QComboBox;
    currencyBox->addItem(tr("Не выбрано"));
    currencyBox->addItem(tr("долларов"));
    currencyBox->addItem(tr("гривен"));
    currencyBox->addItem(tr("евро"));

    addButton = new QPushButton(tr("&Добавить"));
    resetButton = new QPushButton(tr("&Сброс"));
    addButton->setEnabled(false);
    addButton->setDefault(true);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(priceBox);
    hLayout->addWidget(currencyBox);

    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(typeCarLabel,0,0);
    gridLayout->addWidget(carType,0,1);
    gridLayout->addWidget(bodyTypeLabel,0,2);
    gridLayout->addWidget(bodyType,0,3);
    gridLayout->addWidget(stateLabel,1,0);
    gridLayout->addWidget(stateBox,1,1);
    gridLayout->addWidget(regionLabel,1,2);
    gridLayout->addWidget(regionBox,1,3);
    gridLayout->addWidget(brandLabel,2,0);
    gridLayout->addWidget(brandBox,2,1);
    gridLayout->addWidget(createYearLabel,2,2);
    gridLayout->addWidget(makeYear,2,3);
    gridLayout->addWidget(modelLabel,3,0);
    gridLayout->addWidget(modelBox,3,1);
    gridLayout->addWidget(priceLabel,3,2);
    gridLayout->addLayout(hLayout,3,3);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(resetButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    QPalette pal;
    pal.setColor(backgroundRole(),QColor("#D65443"));
    setPalette(pal);
    setAutoFillBackground(true);
    setStyleSheet(
                  "QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                  "QLabel{color:white;}"
                  "QRadioButton{color:white;}"
                  "QCheckBox{color:white;}");
    addButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");

    connect(carType,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(stateBox,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(brandBox,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(modelBox,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(bodyType,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(regionBox,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(makeYear,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(currencyBox,SIGNAL(activated(int)),SLOT(activateAddButton()));
    connect(priceBox,SIGNAL(valueChanged(int)),SLOT(activateAddButton()));

    connect(resetButton,SIGNAL(clicked()),this,SLOT(resetSlot()));
    connect(addButton,SIGNAL(clicked()),this,SLOT(importData()));
    connect(carType,SIGNAL(activated(int)),this,SLOT(setBrandBox(int)));
    connect(brandBox,SIGNAL(activated(int)),this,SLOT(setModelBox(int)));
}

void Add::activateAddButton()
{
    if(stateBox->currentIndex() == 0 || brandBox->currentIndex() == 0 || modelBox->currentIndex() == 0 ||
            bodyType->currentIndex() == 0 || regionBox->currentIndex() == 0
       || makeYear->currentIndex() == 0 || currencyBox->currentIndex() == 0 || priceBox->value() == 0)
    {
        addButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
        addButton->setEnabled(false);
        return;
    }
    addButton->setStyleSheet("QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}");
    addButton->setEnabled(true);
}

void Add::resetSlot()
{
    carType->setCurrentIndex(0);
    stateBox->setCurrentIndex(0);
    brandBox->clear();
    QStringList brandList;
    brandList<<tr("Любая")<<tr("BMW")<<tr("Mazda")<<tr("ВАЗ");
    brandBox->addItems(brandList);
    modelBox->clear();
    modelBox->addItem(tr("Любая"));
    bodyType->setCurrentIndex(0);
    regionBox->setCurrentIndex(0);
    makeYear->setCurrentIndex(0);
    currencyBox->setCurrentIndex(0);
    priceBox->setValue(0);
}

void Add::importData()
{
    carInfo.setType(carType->currentText());
    carInfo.setState(stateBox->currentText());
    carInfo.setBrand(brandBox->currentText());
    carInfo.setModel(modelBox->currentText());
    carInfo.setBodyType(bodyType->currentText());
    carInfo.setRegion(regionBox->currentText());
    carInfo.setCurrency(currencyBox->currentText());
    carInfo.setYear(makeYear->currentText().toInt());
    carInfo.setPrice(priceBox->value());
    emit addCar(carInfo);
    resetSlot();
}

void Add::setBrandBox(int index)
{
    addButton->setEnabled(false);
    addButton->setStyleSheet("QPushButton{background-color:#C1C5C2;color:white;font:14px Times New Roman;}");
    QStringList brandList;
    switch(index)
    {
    case 0:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Не указано"));
        brandList<<tr("Не указано")<<tr("BMW")<<tr("Mazda")<<tr("ВАЗ");
        brandBox->addItems(brandList);
        break;
    case 1:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Не указано"));
        brandList<<tr("Не указано")<<tr("Citroen")<<tr("Opel")<<tr("Ford");
        brandBox->addItems(brandList);
        break;
    case 2:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Не указано"));
        brandList<<tr("Не указано")<<tr("Volkswagen")<<tr("ЛАЗ");
        brandBox->addItems(brandList);
        break;
    case 3:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Не указано"));
        brandList<<tr("Не указано")<<tr("Honda")<<tr("Suzuki");
        brandBox->addItems(brandList);
        break;
    }
}

void Add::setModelBox(int index)
{
    QStringList modelList;
    switch(index)
    {
    case 0:
        modelBox->clear();
        modelList<<tr("Не указано");
        modelBox->addItems(modelList);
        break;
    case 1:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Не указано")<<tr("BMW X3")<<tr("BMW X6")<<tr("BMW Z4")<<tr("BMW I8")
                    <<tr("BMW X1")<<tr("BMW 4 series")<<tr("BMW M4")<<tr("BMW M5")<<tr("BMW 6 series");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Не указано")<<tr("Citroen C3")<<tr("Citroen Berlingo")<<tr("Citroen C4")<<tr("Citroen C-Crosser")
                     <<tr("Citroen Jumpy")<<tr("Citroen Nemo")<<tr("Citroen C4 Picasso")<<tr("Citroen C4 Aircross");
        }
        else if(carType->currentIndex() == 2)
            modelList<<tr("Не указано")<<tr("ЛАЗ 695")<<tr("ЛАЗ 699")<<tr("ЛАЗ 4207");
        else if(carType->currentIndex() == 3)
        {
            modelList<<tr("Не указано")<<tr("Honda CBR600RR")<<tr("Honda CB600F")<<tr("Honda CBF1000")<<tr("Honda CB500F")
                    <<tr("Honda CB500X")<<tr("Honda CTX700N")<<tr("Honda XL700V Transalp")<<tr("Honda NT700V Deauville");
        }
        modelBox->addItems(modelList);
        break;
    case 2:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Не указано")<<tr("Mazda 5")<<tr("Mazda CX-5")<<tr("Mazda Demio")
                     <<tr("Mazda 3")<<tr("Mazda 6")<<tr("Mazda RX-8")<<tr("Mazda Xedos 9")<<tr("Mazda CX-7");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Не указано")<<tr("Opel Astra")<<tr("Opel Omega")<<tr("Opel Movano")
                     <<tr("Opel Vectra")<<tr("Opel Vivaro")<<tr("Opel Corsa")<<tr("Opel Combo")<<tr("Opel Frontera");
        }
        else if(carType->currentIndex() == 2)
            modelList<<tr("Не указано")<<tr("Volkswagen Passat")<<tr("Volkswagen Tiguan")<<tr("Volkswagen Multivan");
        else if(carType->currentIndex() == 3)
        {
            modelList<<tr("Не указано")<<tr("Suzuki B-King 1300")<<tr("Suzuki DR 125S")<<tr("Suzuki GN250")
                       <<tr("Suzuki GSX 400 Impulse")<<tr("Suzuki GSX750E")<<tr("Suzuki GSX 750SD")<<tr("Suzuki GSX-R 600")<<tr("Suzuki GSX-R 750F");
        }
        modelBox->addItems(modelList);
        break;
    case 3:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Не указано")<<tr("Lada 2109")<<tr("Lada 2111")<<tr("Lada Largus")
                     <<tr("Lada Kalina")<<tr("Lada Granta")<<tr("Lada 4x4")<<tr("Lada Priora")<<tr("Lada 2102");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Не указано")<<tr("Ford Focus")<<tr("Ford Mondeo")<<tr("Ford Fusion")
                     <<tr("Ford Scorpio")<<tr("Ford C-Max")<<tr("Ford Explorer")<<tr("Ford Orion")<<tr("Ford B-Max");
        }
        modelBox->addItems(modelList);
        break;
    default:
        break;
    }
}
