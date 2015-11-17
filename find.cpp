#include <QtWidgets>
#include "find.h"

Find::Find(QWidget *parent):QWidget(parent)
{
    QLabel *type = new QLabel(tr("Типы автомобилей"));
    carType = new QComboBox;
    QStringList types;
    types<<tr("Легковые")<<tr("Грузовые")<<tr("Автобус")<<tr("Мотоцикл");
    carType->addItems(types);

    oldCar = new QRadioButton(tr("авто б/у"));
    newCar = new QRadioButton(tr("Новое авто"));
    oldCar->setChecked(true);

    brandLabel = new QLabel(tr("Марка"));
    modelLabel = new QLabel(tr("Модель"));

    brandBox = new QComboBox;
    modelBox = new QComboBox;

    QStringList brand;
    QStringList model;
    brand<<tr("Любая")<<tr("BMW")<<tr("Mazda")<<tr("ВАЗ");
    model<<tr("Любая");
    brandBox->addItems(brand);
    modelBox->addItems(model);

    QGroupBox *firstGroup = new QGroupBox;

    QGridLayout *firstGrid = new QGridLayout;
    firstGrid->addWidget(type,0,0);
    firstGrid->addWidget(carType,0,1);
    firstGrid->addWidget(oldCar,1,0);
    firstGrid->addWidget(newCar,1,1);
    firstGrid->addWidget(brandLabel,2,0);
    firstGrid->addWidget(brandBox,2,1);
    firstGrid->addWidget(modelLabel,3,0);
    firstGrid->addWidget(modelBox,3,1);

    firstGroup->setLayout(firstGrid);

    bodyTypeLabel = new QLabel(tr("Тип кузова"));
    bodyTypeBox = new QComboBox;
    QStringList bodyType;
    bodyType<<tr("Любой")<<tr("Кабриолет")<<tr("Микроавтобус")<<tr("Седан")<<tr("Пикап")<<tr("Фургон")<<tr("Купе");
    bodyTypeBox->addItems(bodyType);

    regionLabel = new QLabel(tr("Регион"));
    regionBox = new QComboBox;
    QStringList region;
    region<<tr("Любой")<<tr("Запорожье")<<tr("Киев")<<tr("Одесса")<<tr("Харьков")<<tr("Николаев")<<tr("Ровно");
    regionBox->addItems(region);
    makeLabel = new QLabel(tr("Год выпуска"));

    minYear = new QComboBox;
    maxYear = new QComboBox;

    minYear->addItem(tr("Любой"));
    maxYear->addItem(tr("Любой"));

    QDate *date = new QDate(QDate::currentDate());
    for(int i = 1950; i <= date->year(); i++)
    {
        minYear->addItem(QString::number(i));
    }
    for(int i = 1950; i <= date->year(); i++)
    {
        maxYear->addItem(QString::number(i));
    }

    priceLabel = new QLabel(tr("Цена"));
    minPrice = new QSpinBox;
    minPrice->setPrefix(tr("от "));
    minPrice->setRange(0,1000000);
    maxPrice = new QSpinBox;
    maxPrice->setPrefix(tr("до "));
    maxPrice->setRange(0,1000000);

    currencyBox = new QComboBox;
    currencyBox->addItem(tr("долларов"));
    currencyBox->addItem(tr("гривен"));
    currencyBox->addItem(tr("евро"));

    findButton = new QPushButton(tr("&Поиск"));

    QHBoxLayout *typeLayout = new QHBoxLayout;
    typeLayout->addWidget(bodyTypeLabel);
    typeLayout->addWidget(bodyTypeBox);

    QHBoxLayout *regionLayout = new QHBoxLayout;
    regionLayout->addWidget(regionLabel);
    regionLayout->addWidget(regionBox);

    QHBoxLayout *yearLayout = new QHBoxLayout;
    yearLayout->addWidget(makeLabel);
    yearLayout->addWidget(minYear);
    yearLayout->addWidget(maxYear);

    QHBoxLayout *priceLayout = new QHBoxLayout;
    priceLayout->addWidget(priceLabel);
    priceLayout->addWidget(minPrice);
    priceLayout->addWidget(maxPrice);
    priceLayout->addWidget(currencyBox);

    QSpacerItem *spacer = new QSpacerItem(150,5);
    QHBoxLayout *findLayout = new QHBoxLayout;
    findLayout->addItem(spacer);
    findLayout->addWidget(findButton);

    QVBoxLayout *secondLayout = new QVBoxLayout;
    secondLayout->addLayout(typeLayout);
    secondLayout->addLayout(regionLayout);
    secondLayout->addLayout(yearLayout);
    secondLayout->addLayout(priceLayout);
    secondLayout->addLayout(findLayout);

    QGroupBox *secondGroup = new QGroupBox;
    secondGroup->setLayout(secondLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(firstGroup);
    mainLayout->addWidget(secondGroup);

    setLayout(mainLayout);

    QPalette wpalette;
    wpalette.setColor(backgroundRole(),QColor("#D65443"));
    setPalette(wpalette);
    setAutoFillBackground(true);
    setStyleSheet("QGroupBox{border:1px solid #D65443;}"
                  "QPushButton{background-color:#4C78C5;color:white;font:14px Times New Roman;}"
                  "QLabel{color:white;}"
                  "QRadioButton{color:white;}"
                  "QCheckBox{color:white;}");
    connect(minPrice,SIGNAL(valueChanged(int)),this,SLOT(correctPrice()));
    connect(minYear,SIGNAL(currentIndexChanged(int)),this,SLOT(correctYear()));
    connect(findButton,SIGNAL(clicked()),SIGNAL(findClick()));
    connect(carType,SIGNAL(activated(int)),this,SLOT(setBrandBox(int)));
    connect(brandBox,SIGNAL(activated(int)),this,SLOT(setModelBox(int)));
}

void Find::correctPrice()
{
    maxPrice->setMinimum(minPrice->value());
}

void Find::correctYear()
{
    maxYear->clear();
    maxYear->addItem(tr("Любой"));
    QDate *date = new QDate(QDate::currentDate());
    for(int i = minYear->currentText().toInt(); i <= date->year();i++)
    {
        maxYear->addItem(QString::number(i));
    }
}

QString Find::getCurrentType()const
{
    return carType->currentText();
}

QString Find::getCurrentState()const
{
    QString str;
    if(oldCar->isChecked())
        str = "б/у";
    else
        str = "Новый";
    return str;
}

QString Find::getCurrentBrand()const
{
    return brandBox->currentText();
}

QString Find::getCurrentModel()const
{
    return modelBox->currentText();
}

QString Find::getCurrentBodyType()const
{
    return bodyTypeBox->currentText();
}

QString Find::getCurrentRegion()const
{
    return regionBox->currentText();
}

QString Find::getCurrentCurrency()const
{
    return currencyBox->currentText();
}

int Find::getMinimumYear()const
{
    if(minYear->currentIndex() == 0)
        return 0;
    return minYear->currentText().toInt();
}

int Find::getMaximumYear()const
{
    if(maxYear->currentIndex() == 0)
        return 0;
    return maxYear->currentText().toInt();
}

int Find::getMinimumPrice()const
{
    return minPrice->value();
}

int Find::getMaximumPrice()const
{
    return maxPrice->value();
}

void Find::setBrandBox(int index)
{
    QStringList brandList;
    switch(index)
    {
    case 0:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Любая"));
        brandList<<tr("Любая")<<tr("BMW")<<tr("Mazda")<<tr("ВАЗ");
        brandBox->addItems(brandList);
        break;
    case 1:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Любая"));
        brandList<<tr("Любая")<<tr("Citroen")<<tr("Opel")<<tr("Ford");
        brandBox->addItems(brandList);
        break;
    case 2:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Любая"));
        brandList<<tr("Любая")<<tr("Volkswagen")<<tr("ЛАЗ");
        brandBox->addItems(brandList);
        break;
    case 3:
        brandBox->clear();
        modelBox->clear();
        modelBox->addItem(tr("Любая"));
        brandList<<tr("Любая")<<tr("Honda")<<tr("Suzuki");
        brandBox->addItems(brandList);
        break;
    }
}

void Find::setModelBox(int index)
{
    QStringList modelList;
    switch(index)
    {
    case 0:
        modelBox->clear();
        modelList<<tr("Любая");
        modelBox->addItems(modelList);
        break;
    case 1:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Любая")<<tr("BMW X3")<<tr("BMW X6")<<tr("BMW Z4")<<tr("BMW I8")
                    <<tr("BMW X1")<<tr("BMW 4 series")<<tr("BMW M4")<<tr("BMW M5")<<tr("BMW 6 series");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Любая")<<tr("Citroen C3")<<tr("Citroen Berlingo")<<tr("Citroen C4")<<tr("Citroen C-Crosser")
                     <<tr("Citroen Jumpy")<<tr("Citroen Nemo")<<tr("Citroen C4 Picasso")<<tr("Citroen C4 Aircross");
        }
        else if(carType->currentIndex() == 2)
            modelList<<tr("Любая")<<tr("ЛАЗ 695")<<tr("ЛАЗ 699")<<tr("ЛАЗ 4207");
        else if(carType->currentIndex() == 3)
        {
            modelList<<tr("Любая")<<tr("Honda CBR600RR")<<tr("Honda CB600F")<<tr("Honda CBF1000")<<tr("Honda CB500F")
                    <<tr("Honda CB500X")<<tr("Honda CTX700N")<<tr("Honda XL700V Transalp")<<tr("Honda NT700V Deauville");
        }
        modelBox->addItems(modelList);
        break;
    case 2:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Любая")<<tr("Mazda 5")<<tr("Mazda CX-5")<<tr("Mazda Demio")
                     <<tr("Mazda 3")<<tr("Mazda 6")<<tr("Mazda RX-8")<<tr("Mazda Xedos 9")<<tr("Mazda CX-7");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Любая")<<tr("Opel Astra")<<tr("Opel Omega")<<tr("Opel Movano")
                     <<tr("Opel Vectra")<<tr("Opel Vivaro")<<tr("Opel Corsa")<<tr("Opel Combo")<<tr("Opel Frontera");
        }
        else if(carType->currentIndex() == 2)
            modelList<<tr("Любая")<<tr("Volkswagen Passat")<<tr("Volkswagen Tiguan")<<tr("Volkswagen Multivan");
        else if(carType->currentIndex() == 3)
        {
            modelList<<tr("Любая")<<tr("Suzuki B-King 1300")<<tr("Suzuki DR 125S")<<tr("Suzuki GN250")
                       <<tr("Suzuki GSX 400 Impulse")<<tr("Suzuki GSX750E")<<tr("Suzuki GSX 750SD")<<tr("Suzuki GSX-R 600")<<tr("Suzuki GSX-R 750F");
        }
        modelBox->addItems(modelList);
        break;
    case 3:
        modelBox->clear();
        if(carType->currentIndex() == 0)
        {
            modelList<<tr("Любая")<<tr("Lada 2109")<<tr("Lada 2111")<<tr("Lada Largus")
                     <<tr("Lada Kalina")<<tr("Lada Granta")<<tr("Lada 4x4")<<tr("Lada Priora")<<tr("Lada 2102");
        }
        else if(carType->currentIndex() == 1)
        {
            modelList<<tr("Любая")<<tr("Ford Focus")<<tr("Ford Mondeo")<<tr("Ford Fusion")
                     <<tr("Ford Scorpio")<<tr("Ford C-Max")<<tr("Ford Explorer")<<tr("Ford Orion")<<tr("Ford B-Max");
        }
        modelBox->addItems(modelList);
        break;
    default:
        break;
    }
}
