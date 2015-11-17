#ifndef CLIENT_H
#define CLIENT_H

//Класс отображающий информацию о клиенте компании

#include <QTextStream>
#include <QSettings>

class Client
{
private:
    int idClient;//ID клиента
    bool whatConstructor;//если был вызван конструктор по умолчанию то значение - 1, если конструктор с параметром - 0
    QString firstName;
    QString surname;
    QString patronymic;
    QString street;
    QString houseNumber;
    QString flatNumber;
    QString pasportDate;
    QSettings mySettings;//объект класса отвечающий за уникальные индексы для каждого клиента, данная информация хранится в системном реестре для ОС виндоус
public:
    Client(const QString &n = "", const QString &sn = "", const QString &p = "",
           const QString &s = "",const QString &hn = "",const QString &fn = "",const QString &pd = "");
    explicit Client(int index);//конструктор для временных клиентов
    Client(const Client &c);//конструктор копии
    Client &operator=(const Client &c);//оператор присваивания
    ~Client();
    void setName(const QString &n);
    void setSurname(const QString &s);
    void setPatronymic(const QString &p);
    void setStreet(const QString &s);
    void setHouseNumber(const QString &hn);
    void setFlatNumber(const QString &fn);
    void setPasportData(const QString &pd);
    void setID(int id);
    QString getName()const;
    QString getSurname()const;
    QString getPatronymic()const;
    QString getStreet()const;
    QString getHouseNumber()const;
    QString getFlatNumber()const;
    QString getPasportData()const;
    int getID()const;
    void readSettings();
    void writeSettings();
    bool operator==(const Client &c)const;
    friend QTextStream &operator<<(QTextStream &stream, const Client &c);
    friend QTextStream &operator>>(QTextStream &stream, Client &c);
};

#endif // CLIENT_H
