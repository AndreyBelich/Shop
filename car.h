#ifndef CAR_H
#define CAR_H

//Класс описывающий автомобиль

#include <QString>
#include <QTextStream>

class Car
{
private:
    QString type;
    QString state;
    QString brand;
    QString model;
    QString bodyType;
    QString region;
    QString currency;
    int year;
    int price;
public:
    Car(const QString &t = "",const QString &s = "",const QString &b = "",const QString &mod = "",const QString &bt = "",
        const QString &r = "",const QString &c = "",int y = 0, int p = 0);
    void setType(const QString &t);
    void setState(const QString &s);
    void setBrand(const QString &b);
    void setModel(const QString &m);
    void setBodyType(const QString &b);
    void setRegion(const QString &r);
    void setCurrency(const QString &c);
    void setYear(int y);
    void setPrice(int p);
    QString getType()const;
    QString getState()const;
    QString getBrand()const;
    QString getModel()const;
    QString getBodyType()const;
    QString getRegion()const;
    QString getCurrency()const;
    int getYear()const;
    int getPrice()const;
    friend QTextStream &operator<<(QTextStream &stream, const Car &c);
    friend QTextStream &operator>>(QTextStream &stream, Car &c);
    bool operator==(const Car &c);
};

#endif // CAR_H
