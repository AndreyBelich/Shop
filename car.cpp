#include "car.h"

Car::Car(const QString &t,const QString &s,const QString &b,const QString &mod,const QString &bt,
         const QString &r,const QString &c,int y, int p)
        :type(t),state(s),brand(b),model(mod),bodyType(bt),region(r),currency(c),year(y),price(p)
{

}

void Car::setType(const QString &t)
{
    type = t;
}

void Car::setState(const QString &s)
{
    state = s;
}

void Car::setBrand(const QString &b)
{
    brand = b;
}

void Car::setModel(const QString &m)
{
    model = m;
}

void Car::setBodyType(const QString &b)
{
    bodyType = b;
}

void Car::setRegion(const QString &r)
{
    region = r;
}

void Car::setCurrency(const QString &c)
{
    currency = c;
}

void Car::setYear(int y)
{
    year = y;
}

void Car::setPrice(int p)
{
    price = p;
}

QString Car::getType()const
{
    return type;
}

QString Car::getState()const
{
    return state;
}

QString Car::getBrand()const
{
    return brand;
}

QString Car::getModel()const
{
    return model;
}

QString Car::getBodyType()const
{
    return bodyType;
}

QString Car::getRegion()const
{
    return region;
}

QString Car::getCurrency()const
{
    return currency;
}

int Car::getYear()const
{
    return year;
}

int Car::getPrice()const
{
    return price;
}

QTextStream &operator<<(QTextStream &stream, const Car &c)
{
    stream<<c.getType()<<"\n"<<c.getState()<<"\n"<<c.getBrand()<<"\n"<<c.getModel()<<"\n"<<c.getBodyType()<<"\n"
          <<c.getRegion()<<"\n"<<c.getYear()<<"\n"<<c.getPrice()<<"\n"<<c.getCurrency();
    return stream;
}

QTextStream &operator>>(QTextStream &stream, Car &c)
{
    c.type = stream.readLine();
    c.state = stream.readLine();
    c.brand = stream.readLine();
    c.model = stream.readLine();
    c.bodyType = stream.readLine();
    c.region = stream.readLine();
    c.year = stream.readLine().toInt();
    c.price = stream.readLine().toInt();
    c.currency = stream.readLine();
    return stream;
}

bool Car::operator==(const Car &c)
{
    if(c.getBodyType() == getBodyType() && c.getBrand() == getBrand() && c.getCurrency() == getCurrency()
            && c.getModel() == c.getModel() && c.getPrice() == getPrice() && c.getRegion() == getRegion()
            && c.getState() == getState() && c.getType() == getType() && c.getYear() == getYear())
        return true;
    else
        return false;
}
