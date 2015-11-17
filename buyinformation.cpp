#include <QDate>
#include "buyinformation.h"

BuyInformation::BuyInformation():clientInfo(0),carInfo()
{
    QDate date = QDate::currentDate();
    day = date.day();
    month = date.month();
    year = date.year();
}

int BuyInformation::getID()const
{
    return clientInfo.getID();
}

QString BuyInformation::getSurname()const
{
    return clientInfo.getSurname();
}

QString BuyInformation::getName()const
{
    return clientInfo.getName();
}

QString BuyInformation::getPatronymic()const
{
    return clientInfo.getPatronymic();
}

QString BuyInformation::getBrand()const
{
    return carInfo.getBrand();
}

QString BuyInformation::getModel()const
{
    return carInfo.getModel();
}

int BuyInformation::getPrice()const
{
    return carInfo.getPrice();
}

QString BuyInformation::getCurrency()const
{
    return carInfo.getCurrency();
}

int BuyInformation::getDay()const
{
    return day;
}

int BuyInformation::getMonth()const
{
    return month;
}

int BuyInformation::getYear()const
{
    return year;
}

void BuyInformation::setCarInformation(const Car &c)
{
    carInfo = c;
}

void BuyInformation::setClientInformation(const Client &c)
{
    clientInfo = c;
}

QTextStream &operator<<(QTextStream &stream, const BuyInformation &b)
{
    stream<<b.clientInfo.getID()<<"\n"<<b.clientInfo.getSurname()<<"\n"<<b.clientInfo.getName()<<"\n"<<b.clientInfo.getPatronymic()
            <<"\n"<<b.carInfo.getBrand()<<"\n"<<b.carInfo.getModel()<<"\n"<<b.carInfo.getPrice()
            <<"\n"<<b.carInfo.getCurrency()<<"\n"<<b.getDay()<<"\n"<<b.getMonth()<<"\n"<<b.getYear();
    return stream;
}

QTextStream &operator>>(QTextStream &stream, BuyInformation &b)
{
    b.clientInfo.setID(stream.readLine().toInt());
    b.clientInfo.setSurname(stream.readLine());
    b.clientInfo.setName(stream.readLine());
    b.clientInfo.setPatronymic(stream.readLine());
    b.carInfo.setBrand(stream.readLine());
    b.carInfo.setModel(stream.readLine());
    b.carInfo.setPrice(stream.readLine().toInt());
    b.carInfo.setCurrency(stream.readLine());
    b.day = stream.readLine().toInt();
    b.month = stream.readLine().toInt();
    b.year = stream.readLine().toInt();
    return stream;
}
