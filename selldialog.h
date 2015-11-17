#ifndef SELLDIALOG_H
#define SELLDIALOG_H

#include <QDialog>
#include <QVector>
#include "buyinformation.h"

class QTableWidget;

class SellDialog: public QDialog
{
    Q_OBJECT
private:
    QVector<BuyInformation> info;
    QTableWidget *table;
    void readToFile();
public:
    explicit SellDialog(QWidget *parent = 0);
};

#endif // SELLDIALOG_H
