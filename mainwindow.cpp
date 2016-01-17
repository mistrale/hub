#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_everywherewindow.h"
#include "localdata.h"

#include <QDir>
#include <QDesktopWidget>

#include <iostream>

#define WIN_WIDTH 1000
#define WIN_HEIGHT 800

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QCoreApplication::setOrganizationName("Aude Sikorav");
    QCoreApplication::setApplicationName("Everywhere");

    ui->setupUi(this);
    QDesktopWidget w;
    this->setFixedSize(WIN_WIDTH, WIN_HEIGHT);


    _background = new QMovie("C:/Everywhere/images/sound.gif");
    ui->background->setMovie(_background);
    _background->start();



    _everywhereWidget = new GUI::EverywhereWindow(this);

    _registrationWidget = new GUI::Registration(this);
    _registrationWidget->move((WIN_WIDTH - 498) / 2, (WIN_HEIGHT - 540) / 2);

    _connectionWidget = new GUI::Connection(this);
    _connectionWidget->move((WIN_WIDTH - 431)/ 2, (WIN_HEIGHT - 461) / 2);

    _everywhereWidget->hide();
    _registrationWidget->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void        MainWindow::showConnection() {
    Model::LocalData    *data = Model::LocalData::instance();

    data->Values.clear();
    ui->background->show();
   _background->start();
   _everywhereWidget->hide();
   _registrationWidget->hide();
   _connectionWidget->show();
}

void        MainWindow::showRegistration() {
    _everywhereWidget->hide();
   _connectionWidget->hide();
   _registrationWidget->show();
}

void        MainWindow::showEverywhere() {
   _background->stop();
   ui->background->hide();
   _connectionWidget->hide();
   _everywhereWidget->show();
}
