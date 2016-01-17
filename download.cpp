#include "download.h"
#include "ui_download.h"

GUI::Download::Download(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Download)
{
    ui->setupUi(this);
}

GUI::Download::~Download()
{
    delete ui;
}

void        GUI::Download::initialize() {

}
