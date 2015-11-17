#ifndef TABDIALOG_H
#define TABDIALOG_H

#include <QDialog>
#include <QVector>
#include "car.h"

class QTabWidget;
class Find;
class Add;
class Table;

class TabDialog:public QDialog
{
    Q_OBJECT
private:
    QTabWidget *tabWidget;
    Find *findWidget;
    Add *addWidget;
    QVector<Car> catalog;
    void writeToFile(const Car &c);
    void readToFile();
public:
    TabDialog(QWidget *parent = 0);
private slots:
    void pushData(const Car &c);
    void findResult(int size, const QVector<Car> &c);
    void importContainerInfo();
signals:
    void infoToTable(int size, const QVector<Car> &c);
};

#endif // TABDIALOG_H
