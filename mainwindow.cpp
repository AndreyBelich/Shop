#include <QtWidgets>
#include "button.h"
#include "tabdialog.h"
#include "clientform.h"
#include "selldialog.h"
#include "clientdatabase.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent):QMainWindow(parent)
{
    QMenu *menu_1 = menuBar()->addMenu(tr("Информация для администратора"));
    dataBaseAction = new QAction(tr("База данных клиентов"),this);
    menu_1->addAction(dataBaseAction);

    QLabel *titleLabel = new QLabel(tr("<h2 align = center>Мир автомобилей</h2>"));

    catalogButton = new Button(this);
    catalogButton->setText(tr("&Каталог машин"));

    clientButton = new Button(this);
    clientButton->setText(tr("&Добавить клиента в базу"));

    sellButton = new Button(this);
    sellButton->setText(tr("Информация о &продажах"));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(10);
    mainLayout->addWidget(catalogButton);
    mainLayout->addWidget(clientButton);
    mainLayout->addWidget(sellButton);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(titleLabel);
    vLayout->addLayout(mainLayout);

    QWidget *widget = new QWidget(this);
    widget->setLayout(vLayout);
    setCentralWidget(widget);
    setFixedSize(900,375);

    connect(catalogButton,SIGNAL(clicked()),this,SLOT(callCatalog()));
    connect(clientButton,SIGNAL(clicked()),this,SLOT(callClient()));
    connect(sellButton,SIGNAL(clicked()),this,SLOT(callSellDialog()));
    connect(dataBaseAction,SIGNAL(triggered()),this,SLOT(callDataBase()));
}

void MainWindow::callCatalog()
{
    catalogDialog = new TabDialog(this);
    catalogDialog->show();
    hide();
    catalogDialog->exec();
    delete catalogDialog;
    show();
}

void MainWindow::callClient()
{
    clientDialog = new ClientForm(this);
    clientDialog->show();
    hide();
    clientDialog->exec();
    delete clientDialog;
    show();
}

void MainWindow::callSellDialog()
{
    sellDialog = new SellDialog(this);
    sellDialog->show();
    hide();
    sellDialog->exec();
    delete sellDialog;
    show();
}

void MainWindow::callDataBase()
{
    dataBaseDialog = new ClientDataBase(this);
    dataBaseDialog->show();
    hide();
    if(dataBaseDialog->exec() == QDialog::Rejected)
    {
        delete dataBaseDialog;
        show();
    }
}
