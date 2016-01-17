#include "disconnect.h"
#include "ui_disconnect.h"

GUI::Disconnect::Disconnect(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Disconnect)
{
    ui->setupUi(this);
}

GUI::Disconnect::~Disconnect()
{
    delete ui;
}

void        GUI::Disconnect::initialize() {

}
