#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>


class Table:public QTableWidget
{
    Q_OBJECT
private:
    static const int width = 9;
public:
    Table(QWidget *parent = 0,int size = 0);
    static int getTableWidth()
    {
        return width;
    }
};

#endif // TABLE_H
