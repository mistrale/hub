#include "news.h"
#include "ui_news.h"

GUI::News::News(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::News)
{
    ui->setupUi(this);
}

GUI::News::~News()
{
    delete ui;
}

void        GUI::News::initialize() {

}
