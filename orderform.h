#ifndef ORDERFORM_H
#define ORDERFORM_H

#include <QDialog>
#include <QVector>
#include "client.h"
#include "car.h"
#include "buyinformation.h"

class QLineEdit;
class QPushButton;

class OrderForm: public QDialog
{
    Q_OBJECT
private:
    QVector<Client> clientBase;
    BuyInformation information;
    QLineEdit *firstNameLine;
    QLineEdit *surnameLine;
    QLineEdit *patronymicLine;
    QLineEdit *streetLine;
    QLineEdit *houseNumberLine;
    QLineEdit *flatNumberLine;
    QLineEdit *pasportLine;
    QLineEdit *priceLine;
    QLineEdit *brandLine;
    QLineEdit *modelLine;
    QLineEdit *currencyLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
    void readToFile();
    void writeBuyInformation();
public:
    explicit OrderForm(QWidget *parent = 0);
    void setCarInfoLine(const Car &c);
private slots:
    void activateOkButton();
    void addClientToBase();
};

#endif // ORDERFORM_H
