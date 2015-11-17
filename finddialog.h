#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QVector>
#include "table.h"
#include "car.h"

class OrderForm;
class QPushButton;

class FindDialog:public QDialog
{
    Q_OBJECT
private:
    Table *tWidget;
    QPushButton *orderButton;
    OrderForm *form;
    QVector<Car> carList;
    QVector<Car> delOldCar;
    void readOldInformation();
    void deleteOldCar();
    void writeNewInformation();
public:
   FindDialog(QWidget *parent,int size,const QVector<Car> &c);
   Car getCarInfo()const;
protected:
   virtual void closeEvent(QCloseEvent *);
private slots:
   void callOrderForm();
};

#endif // FINDDIALOG_H
