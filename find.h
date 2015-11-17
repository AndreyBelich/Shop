#ifndef FIND_H
#define FIND_H

//Виджет для поиска автомобилей
#include <QWidget>

class QComboBox;
class QRadioButton;
class QCheckBox;
class QLabel;
class QPushButton;
class QSpinBox;

class Find:public QWidget
{
    Q_OBJECT
private:
    QComboBox *carType;
    QRadioButton *oldCar;
    QRadioButton *newCar;
    QLabel *brandLabel;
    QLabel *modelLabel;
    QComboBox *brandBox;
    QComboBox *modelBox;
    QLabel *bodyTypeLabel;
    QComboBox *bodyTypeBox;
    QLabel *regionLabel;
    QComboBox *regionBox;
    QLabel *makeLabel;
    QComboBox *minYear;
    QComboBox *maxYear;
    QLabel *priceLabel;
    QSpinBox *minPrice;
    QSpinBox *maxPrice;
    QComboBox *currencyBox;
    QPushButton *findButton;
public:
    Find(QWidget *parent = 0);
    QString getCurrentType()const;
    QString getCurrentState()const;
    QString getCurrentBrand()const;
    QString getCurrentModel()const;
    QString getCurrentBodyType()const;
    QString getCurrentRegion()const;
    QString getCurrentCurrency()const;
    int getMinimumYear()const;
    int getMaximumYear()const;
    int getMinimumPrice()const;
    int getMaximumPrice()const;
private slots:
    void correctPrice();
    void correctYear();
    void setBrandBox(int index);
    void setModelBox(int index);
signals:
    void findClick();
};

#endif // FIND_H
