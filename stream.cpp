#include "stream.h"
#include "ui_stream.h"

GUI::Stream::Stream(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Stream)
{
    ui->setupUi(this);
}

GUI::Stream::~Stream()
{
    delete ui;
}

void        GUI::Stream::initialize() {

}
