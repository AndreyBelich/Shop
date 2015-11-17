#ifndef CLIENTFORM_H
#define CLIENTFORM_H

#include <QDialog>
#include <QVector>
#include "client.h"

class QLineEdit;
class QPushButton;

class ClientForm: public QDialog
{
    Q_OBJECT
private:
    QVector<Client> clientContainer;
    QLineEdit *firstNameLine;
    QLineEdit *surnameLine;
    QLineEdit *patronymicLine;
    QLineEdit *streetLine;
    QLineEdit *houseNumberLine;
    QLineEdit *flatNumberLine;
    QLineEdit *passportNumberLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *resetButton;
    QPushButton *editButton;
    Client oldClient;//временный объект который будет возвращаться после изменения данных о клиенте
    Client newClient;
    bool state;//отвечает за то будет окно редактировать данные или добавлять новые
    bool luckAdd;//истина если клиента удалось добавить в базу и ложь если не удалось
    void writeToFile(const QString &path);
    void readToFile();
public:
    ClientForm(bool s = true,QWidget *parent = 0);
    void setLines(const Client &c);//заполнение строк переданной информацией
    Client getNewClientData();//возвращает информацию о клиенте, если пользователь нажал кнопку отмена
    Client getOldClientData();//возвращает информацию о клиенте, если пользователь нажал кнопку изменить на форме
signals:
    void goodReturn();//сигнал генерирующийся при нажатии на кнопку править(изменить)
    void badReturn();//сигнал генерирующийся при клике на копку отмена
private slots:
    void okButtonActive();//активирует кнопку ОК
    void resetInformation();//сбрасывает введенную информацию
    void addInfoToFile();//добавляет информаию в файл
    void editButtonActive();//активирует кнопку править(активна если таблица не пустая)
    void getCorrectValue();
};

#endif // CLIENTFORM_H
