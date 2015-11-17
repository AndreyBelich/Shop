#ifndef BUYINFORMATION_H
#define BUYINFORMATION_H

//Класс отвечающи за отобажение информации о продажах

#include <QTextStream>
#include "client.h"
#include "car.h"


class BuyInformation
{
private:
    Client clientInfo;
    Car carInfo;
    int day;
    int month;
    int year;
public:
    BuyInformation();
    int getID()const;
    QString getSurname()const;
    QString getName()const;
    QString getPatronymic()const;
    QString getBrand()const;
    QString getModel()const;
    int getPrice()const;
    QString getCurrency()const;
    int getDay()const;
    int getMonth()const;
    int getYear()const;
    void setCarInformation(const Car &c);
    void setClientInformation(const Client &c);
    friend QTextStream &operator<<(QTextStream &stream, const BuyInformation &b);
    friend QTextStream &operator>>(QTextStream &stream, BuyInformation &b);
};

#endif // BUYINFORMATION_H
