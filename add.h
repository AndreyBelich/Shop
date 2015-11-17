#ifndef ADD_H
#define ADD_H

#include <QWidget>
#include "car.h"

class QComboBox;
class QPushButton;
class QSpinBox;

class Add:public QWidget
{
    Q_OBJECT
private:
    QComboBox *carType;//
    QComboBox *bodyType;
    QComboBox *stateBox;//
    QComboBox *brandBox;//
    QComboBox *modelBox;//
    QComboBox *regionBox;
    QComboBox *makeYear;
    QComboBox *currencyBox;
    QSpinBox *priceBox;
    QPushButton *addButton;
    QPushButton *resetButton;
    Car carInfo;
public:
    explicit Add(QWidget *parent = 0);
private slots:
    void activateAddButton();//слот активирующий кнопку добавить,если не все поля заполнены то кнопка неактивна
    void resetSlot();//слот устанавливающий все индексы комбобоксов равным 0
    void importData();//слот передающий информацию
    void setBrandBox(int index);//установить соответствующие марки автомобилей
    void setModelBox(int index);//установить соответствующие модели автомобилей
signals:
    void addCar(const Car &c);
};

#endif // ADD_H
