#include "client.h"

Client::Client(const QString &n, const QString &sn, const QString &p,const QString &s,const QString &hn,const QString &fn,const QString &pd)
    :firstName(n), surname(sn), patronymic(p), street(s),houseNumber(hn),flatNumber(fn), pasportDate(pd),mySettings("CarShop","Cars")
{
    whatConstructor = true;
    readSettings();
}

Client::Client(int index)
    :idClient(index),firstName(""), surname(""), patronymic(""), street(""),houseNumber(""),flatNumber(""), pasportDate(""),mySettings("CarShop","Cars")
{
    whatConstructor = false;
}

Client::Client(const Client &c)
{
    firstName = c.getName();
    surname = c.getSurname();
    patronymic = c.getPatronymic();
    street = c.getStreet();
    houseNumber = c.getHouseNumber();
    flatNumber = c.getFlatNumber();
    pasportDate = c.getPasportData();
    idClient = c.getID();
}

Client &Client::operator=(const Client &c)
{
    if(this == &c)
        return *this;
    firstName = c.getName();
    surname = c.getSurname();
    patronymic = c.getPatronymic();
    street = c.getStreet();
    houseNumber = c.getHouseNumber();
    flatNumber = c.getFlatNumber();
    pasportDate = c.getPasportData();
    idClient = c.getID();
    return *this;
}

Client::~Client()
{
    writeSettings();
}

void Client::setName(const QString &n)
{
    firstName = n;
}

void Client::setSurname(const QString &s)
{
    surname = s;
}

void Client::setPatronymic(const QString &p)
{
    patronymic = p;
}

void Client::setStreet(const QString &s)
{
    street = s;
}

void Client::setHouseNumber(const QString &hn)
{
    houseNumber = hn;
}

void Client::setFlatNumber(const QString &fn)
{
    flatNumber = fn;
}

void Client::setPasportData(const QString &pd)
{
    pasportDate = pd;
}

void Client::setID(int id)
{
    idClient = id;
}

QString Client::getName()const
{
    return firstName;
}

QString Client::getSurname()const
{
    return surname;
}

QString Client::getPatronymic()const
{
    return patronymic;
}

QString Client::getStreet()const
{
    return street;
}

QString Client::getHouseNumber()const
{
    return houseNumber;
}

QString Client::getFlatNumber()const
{
    return flatNumber;
}

QString Client::getPasportData()const
{
    return pasportDate;
}

int Client::getID()const
{
    return idClient;
}

void Client::readSettings()
{
    mySettings.beginGroup("/Settings");
    idClient = mySettings.value("/index",1).toInt();
    idClient++;
    mySettings.endGroup();
}

void Client::writeSettings()
{
    if(whatConstructor)
    {
        mySettings.beginGroup("/Settings");
        mySettings.setValue("/index",getID());
        mySettings.endGroup();
    }
}

bool Client::operator==(const Client &c)const
{
    if(getSurname() == c.getSurname() && getName() == c.getName()&& getPatronymic() == c.getPatronymic()
            && getStreet() == c.getStreet() && getHouseNumber() == c.getHouseNumber()
            && getFlatNumber() == c.getFlatNumber() && getPasportData() == c.getPasportData())
        return true;
    else
        return false;
}

QTextStream &operator<<(QTextStream &stream, const Client &c)
{
    stream<<c.getID()<<"\n"<<c.getSurname()<<"\n"<<c.getName()<<"\n"<<c.getPatronymic()<<"\n";
    stream<<c.getStreet()<<"\n"<<c.getHouseNumber()<<"\n"<<c.getFlatNumber()<<"\n"<<c.getPasportData();
    return stream;
}

QTextStream &operator>>(QTextStream &stream, Client &c)
{
    c.idClient = stream.readLine().toInt();
    c.surname = stream.readLine();
    c.firstName = stream.readLine();
    c.patronymic = stream.readLine();
    c.street = stream.readLine();
    c.houseNumber = stream.readLine();
    c.flatNumber = stream.readLine();
    c.pasportDate = stream.readLine();
    return stream;
}
