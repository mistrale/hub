#include "library.h"
#include "ui_library.h"

#include <QDir>
#include <QFileInfoList>

#include <iostream>

#include <iostream>
#include <iomanip>
#include <stdio.h>

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
//    QDir dir("C:/document");
//    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//    dir.setSorting(QDir::Size | QDir::Reversed);

//    QFileInfoList list = dir.entryInfoList();
//    std::cout << "     Bytes Filename" << std::endl;
//    for (int i = 0; i < list.size(); ++i) {
//        QFileInfo fileInfo = list.at(i);
//        std::cout << qPrintable(QString("%1 %2 %3").arg(fileInfo.size(), 10)
//                                                .arg(fileInfo.fileName()).arg(fileInfo.owner()));
//        std::cout << std::endl;
//    }
}
