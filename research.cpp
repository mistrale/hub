#include "research.h"
#include "ui_research.h"

GUI::Research::Research(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Research)
{
    ui->setupUi(this);
}

GUI::Research::~Research()
{
    delete ui;
}

void        GUI::Research::initialize() {

}
