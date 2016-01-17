#include "synchronization.h"
#include "ui_synchronization.h"

GUI::Synchronization::Synchronization(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Synchronization)
{
    ui->setupUi(this);
}

GUI::Synchronization::~Synchronization()
{
    delete ui;
}

void        GUI::Synchronization::initialize() {

}
