#include "resultsearch.h"
#include "ui_resultsearch.h"

GUI::ResultSearch::ResultSearch(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::ResultSearch),
    _parent(parent)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), parent, SLOT(showResult()));
}

GUI::ResultSearch::~ResultSearch()
{
    delete ui;
}

void        GUI::ResultSearch::initialize() {

}
