#ifndef CLIENTDATABASE_H
#define CLIENTDATABASE_H

#include <QDialog>
#include <QVector>
#include "client.h"
#include "clientform.h"

class QTableWidget;
class QPushButton;

class ClientDataBase : public QDialog
{
    Q_OBJECT
private:
    QVector<Client> clientList;
    QTableWidget *table;
    QPushButton *exitButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    ClientForm *form;
    bool click;
    void readToFile();//считывание информации из файла
    void writeToFile();//запись информации в файл
    void setTable();//заполнение таблицы информацией
public:
    explicit ClientDataBase(QWidget *parent = 0);
    void setRowSize(int size);//устанавливает количество строк для таблицы
    Client getData()const;//возвращает информацию о клиенте
protected:
    virtual void closeEvent(QCloseEvent *);//событие наступающее при уничтожении объекта(вызывается крестиком в верхнем правом углу) либо кнопкой связанной со слотом close()
private slots:
    void deleteConnect();//слот удаляющи клиента из базы
    void editConnect();//слот вызывающий форму для правки информации о клиенте
};

#endif // CLIENTDATABASE_H
