#include "library.h"
#include "ui_library.h"

GUI::Library::Library(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Library)
{
    ui->setupUi(this);
}

GUI::Library::~Library()
{
    delete ui;
}

void        GUI::Library::initialize() {

}
