#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QAction;
class Button;
class TabDialog;
class ClientForm;
class SellDialog;
class ClientDataBase;

class MainWindow: public QMainWindow
{
    Q_OBJECT
private:
    QAction *dataBaseAction;
    Button *catalogButton;
    Button *clientButton;
    Button *sellButton;
    TabDialog *catalogDialog;
    ClientForm *clientDialog;
    SellDialog *sellDialog;
    ClientDataBase *dataBaseDialog;
public:
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void callCatalog();
    void callClient();
    void callSellDialog();
    void callDataBase();
};

#endif // MAINWINDOW_H
