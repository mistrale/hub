#include "everywherewindow.h"
#include "ui_everywherewindow.h"
#include "ui_news.h"
#include "news.h"
#include "library.h"
#include "radio.h"
#include "disconnect.h"
#include "profil.h"
#include "download.h"
#include "research.h"
#include "synchronization.h"
#include "stream.h"
#include "resultsearch.h"
#include "result.h"

#include <QDebug>
#include <QPropertyAnimation>
#include <QStateMachine>
#include <QSignalTransition>
#include <QTimeLine>
#include <QTimer>

#include <typeinfo>
#include <iostream>

GUI::EverywhereWindow::EverywhereWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EverywhereWindow),
    _menuOpen(true),
    _parent(parent)
{
    ui->setupUi(this);

    QObject::connect(ui->menuButton, SIGNAL(clicked()), this, SLOT(manageMenu()));
    QObject::connect(ui->logoutButton, SIGNAL(clicked()), parent, SLOT(showConnection()));
    createCloseMenu();
    createOpenMenu();
    createMenu();

    _current = _menuWidgets["newButton"];
}

GUI::EverywhereWindow::~EverywhereWindow()
{
    delete ui;
}

void            GUI::EverywhereWindow::createMenu() {
    AWidget     *widget = new GUI::Library(this);
    _menuWidgets["libraryButton"] = std::make_pair("library", widget);
    connect(ui->libraryButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget->hide();
    ui->gridLayout->addWidget(widget, 3, 0, 1, 2);

    AWidget     *widget2 = new GUI::News(this);
    _menuWidgets["newButton"] = std::make_pair("new", widget2);
    connect(ui->newButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget2->hide();
    ui->gridLayout->addWidget(widget2, 4, 0, 1, 2);

    AWidget     *widget3 = new GUI::Radio(this);
    _menuWidgets["radioButton"] = std::make_pair("radio", widget3);
    connect(ui->radioButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget3->hide();
    ui->gridLayout->addWidget(widget3, 5, 0, 1, 2);

    AWidget     *widget4 = new GUI::Download(this);
    _menuWidgets["downloadButton"] = std::make_pair("download", widget4);
    connect(ui->downloadButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget4->hide();
    ui->gridLayout->addWidget(widget4, 6, 0, 1, 2);

    AWidget     *widget5 = new GUI::Research(this);
    _menuWidgets["researchButton"] = std::make_pair("research", widget5);
    connect(ui->researchButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget5->hide();
    ui->gridLayout->addWidget(widget5, 6, 0, 1, 2);

    AWidget     *widget6 = new GUI::Stream(this);
    _menuWidgets["streamButton"] = std::make_pair("stream", widget6);
    connect(ui->streamButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget6->hide();
    ui->gridLayout->addWidget(widget6, 7, 0, 1, 2);

    AWidget     *widget7 = new GUI::Synchronization(this);
    _menuWidgets["synchronizationButton"] = std::make_pair("synchronization", widget7);
    connect(ui->synchronizationButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget7->hide();
    ui->gridLayout->addWidget(widget7, 8, 0, 1, 2);

    AWidget     *widget8 = new GUI::Profil(this);
    _menuWidgets["profilButton"] = std::make_pair("profil", widget8);
    connect(dynamic_cast<GUI::Profil *>(widget8), SIGNAL(deleted()), _parent, SLOT(showConnection()));
    connect(ui->profilButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget8->hide();
    ui->gridLayout->addWidget(widget8, 9, 0, 1, 2);

    AWidget     *widget9 = new GUI::Disconnect(this);
    _menuWidgets["disconnectButton"] = std::make_pair("disconnect", widget9);
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SLOT(switchView()));
    widget9->hide();
    ui->gridLayout->addWidget(widget9, 10, 0, 1, 2);

    AWidget     *widget10 = new GUI::ResultSearch(this);
    _menuWidgets["searchButton"] = std::make_pair("resultSearch", widget10);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(getSearchResult()));
    widget10->hide();
    ui->gridLayout->addWidget(widget10, 11, 0, 1, 2);

    AWidget     *widget11 = new GUI::Result(this);
    _menuWidgets["ResultView"] = std::make_pair("Result", widget11);
    widget11->hide();
    ui->gridLayout->addWidget(widget11, 12, 0, 1, 2);
}

void            GUI::EverywhereWindow::showResult() {
    _current.second->hide();
    _current = _menuWidgets["ResultView"];
    _current.second->show();
}

void            GUI::EverywhereWindow::getSearchResult() {
    QObject* senderObj = sender();
    _current.second->hide();

    ui->globalWidget->setStyleSheet("QWidget#globalWidget { background : url(C:/everywhere/images/"
                                    + _menuWidgets[senderObj->objectName()].first + "Background.png); }");
    ui->globalWidget->style()->unpolish(ui->globalWidget);
    ui->globalWidget->style()->polish(ui->globalWidget);
    ui->globalWidget->update();

    _current = _menuWidgets[senderObj->objectName()];

    if (_menuOpen) {
        manageMenu();
        QTimer::singleShot(400, this, SLOT(updateView()));
    } else {
        _current.second->show();
    }
}

void            GUI::EverywhereWindow::switchView() {
    QObject* senderObj = sender();
    ui->globalWidget->setStyleSheet("QWidget#globalWidget { background : url(C:/everywhere/images/"
                                    + _menuWidgets[senderObj->objectName()].first + "Background.png); }");
    ui->globalWidget->style()->unpolish(ui->globalWidget);
    ui->globalWidget->style()->polish(ui->globalWidget);
    ui->globalWidget->update();

    _current = _menuWidgets[senderObj->objectName()];
    manageMenu();
    _current.second->initialize();
    QTimer::singleShot(400, this, SLOT(updateView()));
}

void            GUI::EverywhereWindow::updateView() {
    ui->globalWidget->hide();
    _current.second->show();
}

void            GUI::EverywhereWindow::createQPropertyAnimationButton(const QRect &startGeo,
                                                                      const QRect &endGeo,
                                                                      QPushButton *button,
                                                                      QParallelAnimationGroup *group) {
    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(200);
    animation->setStartValue(startGeo);
    animation->setEndValue(endGeo);
    group->addAnimation(animation);
}

void            GUI::EverywhereWindow::manageMenu() {
    if (_menuOpen)
        closeMenu();
    else
        openMenu();
}

void            GUI::EverywhereWindow::openMenu() {
    _current.second->hide();
    ui->globalWidget->show();
    _menuOpen = true;
    _openLastAnimation->start();
}

void            GUI::EverywhereWindow::closeMenu() {
    _menuOpen = false;
    _closeAnimations->start();
}

void            GUI::EverywhereWindow::createCloseMenu() {
    _closeAnimations = new QParallelAnimationGroup;
    createQPropertyAnimationButton(QRect(ui->newButton->x(), ui->newButton->y(),
                                         ui->newButton->width(), ui->newButton->height()),
                                   QRect(ui->newButton->x(), ui->newButton->height(),
                                         ui->newButton->width(), 0),ui->newButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->libraryButton->x(), ui->libraryButton->y(),
                                         ui->libraryButton->width(), ui->libraryButton->height()),
                                   QRect(ui->libraryButton->width(), ui->libraryButton->height(),
                                         0, 0),
                                   ui->libraryButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->radioButton->x(), ui->radioButton->y(),
                                         ui->radioButton->width(), ui->radioButton->height()),
                                   QRect(ui->radioButton->y()  - ui->radioButton->width(),
                                         ui->radioButton->height(), 0, 0),
                                   ui->radioButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->streamButton->x(), ui->streamButton->y(),
                                         ui->streamButton->width(), ui->streamButton->height()),
                                   QRect(ui->streamButton->x(), ui->streamButton->y(),
                                         0, ui->streamButton->height()),
                                   ui->streamButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->synchronizationButton->x(), ui->synchronizationButton->y(),
                                         ui->synchronizationButton->width(), ui->synchronizationButton->height()),
                                   QRect(ui->synchronizationButton->width(), ui->synchronizationButton->y(),
                                         0, ui->synchronizationButton->height()),
                                   ui->synchronizationButton,  _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->profilButton->x(), ui->profilButton->y(),
                                         ui->profilButton->width(), ui->profilButton->height()),
                                   QRect(ui->profilButton->width(), ui->profilButton->y(),0, 0),
                                   ui->profilButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->disconnectButton->x(), ui->disconnectButton->y(),
                                         ui->disconnectButton->width(), ui->disconnectButton->height()),
                                   QRect(ui->disconnectButton->x() - ui->disconnectButton->width(),
                                         ui->disconnectButton->y() - ui->disconnectButton->height(), 0, 0),
                                   ui->disconnectButton, _closeAnimations);
    createQPropertyAnimationButton(QRect(ui->downloadButton->x(), ui->downloadButton->y(),
                                         ui->downloadButton->width(), ui->downloadButton->height()),
                                   QRect(ui->downloadButton->x(), ui->downloadButton->y(),
                                         ui->downloadButton->width(), 0),
                                   ui->downloadButton, _closeAnimations);

    _closeLastAnimation = new QPropertyAnimation(ui->researchButton, "geometry");
    _closeLastAnimation->setDuration(200);
    _closeLastAnimation->setStartValue(QRect(ui->researchButton->x(), ui->researchButton->y(),
                                   ui->researchButton->width(), ui->researchButton->height()));
    _closeLastAnimation->setEndValue(QRect(ui->researchButton->width() / 2,
                                           ui->researchButton->height() / 2, 0, 0));
       connect(_closeAnimations, SIGNAL(finished()), _closeLastAnimation, SLOT(start()));
}

void            GUI::EverywhereWindow::createOpenMenu() {
    _openAnimations = new QParallelAnimationGroup;
    createQPropertyAnimationButton(QRect(ui->newButton->x(), ui->newButton->height(),
                                         ui->newButton->width(), 0),
                                   QRect(ui->newButton->x(), ui->newButton->y(),
                                   ui->newButton->width(), ui->newButton->height()),
                                   ui->newButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->libraryButton->width(), ui->libraryButton->height(),
                                         0, 0),
                                   QRect(ui->libraryButton->x(), ui->libraryButton->y(),
                                         ui->libraryButton->width(), ui->libraryButton->height()),
                                   ui->libraryButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->radioButton->x()  - ui->radioButton->width(),
                                         ui->radioButton->height(), 0, 0),
                                   QRect(ui->radioButton->x(), ui->radioButton->y(),
                                         ui->radioButton->width(), ui->radioButton->height()),
                                   ui->radioButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->streamButton->x(), ui->streamButton->y(),
                                         0, ui->streamButton->height()),
                                   QRect(ui->streamButton->x(), ui->streamButton->y(),
                                         ui->streamButton->width(), ui->streamButton->height()),
                                   ui->streamButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->synchronizationButton->width(), ui->synchronizationButton->y(),
                                         0, ui->synchronizationButton->height()),
                                   QRect(ui->synchronizationButton->x(), ui->synchronizationButton->y(),
                                         ui->synchronizationButton->width(), ui->synchronizationButton->height()),
                                   ui->synchronizationButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->profilButton->width(), ui->profilButton->y(),0, 0),
                                   QRect(ui->profilButton->x(), ui->profilButton->y(),
                                         ui->profilButton->width(), ui->profilButton->height()),
                                   ui->profilButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->disconnectButton->x() - ui->disconnectButton->width(),
                                         ui->disconnectButton->y() - ui->disconnectButton->height(), 0, 0),
                                   QRect(ui->disconnectButton->x(), ui->disconnectButton->y(),
                                         ui->disconnectButton->width(), ui->disconnectButton->height()),
                                   ui->disconnectButton, _openAnimations);
    createQPropertyAnimationButton(QRect(ui->downloadButton->x(), ui->downloadButton->y(),
                                         ui->downloadButton->width(), 0),
                                   QRect(ui->downloadButton->x(), ui->downloadButton->y(),
                                         ui->downloadButton->width(), ui->downloadButton->height()),
                                   ui->downloadButton, _openAnimations);

    _openLastAnimation = new QPropertyAnimation(ui->researchButton, "geometry");
    _openLastAnimation->setDuration(200);
    _openLastAnimation->setEndValue(QRect(ui->researchButton->x(), ui->researchButton->y(),
                                   ui->researchButton->width(), ui->researchButton->height()));
    _openLastAnimation->setStartValue(QRect(ui->researchButton->width() / 2,
                                           ui->researchButton->height() / 2, 0, 0));

    connect(_openLastAnimation, SIGNAL(finished()), _openAnimations, SLOT(start()));
}

