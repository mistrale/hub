#include "registration.h"
#include "ui_registration.h"
#include "requestmanager.h"

#include <QNetworkReply>
#include <QJsonDocument>
#include <QRegExp>

#include <iostream>

GUI::Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(clicked()), parent, SLOT(showConnection()));
    connect(ui->signinButton, SIGNAL(clicked()), this, SLOT(registerEverywhere()));

    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

    ui->emailEdit->installEventFilter(this);
    ui->usernameEdit->installEventFilter(this);
    ui->passwordEdit->installEventFilter(this);
    ui->passwordConfirmationEdit->installEventFilter(this);
    ui->lastnameEdit->installEventFilter(this);
    ui->firstnameEdit->installEventFilter(this);
}

GUI::Registration::~Registration()
{
    delete ui;
}

void            GUI::Registration::registerEverywhere() {
    if (!checkField()) {
        return;
    }
    ui->warningText->setText("");
    _reply = _manager.registrationRequest(ui->emailEdit->text(), ui->usernameEdit->text(), ui->passwordEdit->text(),
                                          ui->firstnameEdit->text(), ui->lastnameEdit->text());
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
     _background = new QMovie("C:/Everywhere/images/Ring.gif");
     ui->ring->setMovie(_background);
    _background->start();
}

void            GUI::Registration::replyFinished(QNetworkReply *reply) {
    std::cout << "request registration ok" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();
    int status = json["status"].toObject().value("code").toInt();
    if (status == 200) {
        ui->warningText->setText("Account created !");
        ui->warningText->setStyleSheet("color: green; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
    } else {
        std::cout << bytes.toStdString() << std::endl;
        QString message = json["status"].toObject().value("message").toString();
        ui->warningText->setText(message);
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
    }
    if (_background != NULL) {
        _background->stop();
        delete _background;
        _background = NULL;
    }
}

void            GUI::Registration::onError(QNetworkReply::NetworkError code) {
    std::cout << "Error on registration request" << std::endl;
    qDebug() << code;
    if (_background != NULL) {
        _background->stop();
        delete _background;
        _background = NULL;
    }
}

bool            GUI::Registration::checkField() {
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(ui->emailEdit->text())) {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Invalid email.");
        return false;
    }
    if (ui->usernameEdit->text().toStdString().empty() || ui->usernameEdit->text().toStdString() == "Username") {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Username cannot be blank.");
        return false;
    }
    if (ui->emailEdit->text().toStdString().empty() || ui->emailEdit->text().toStdString() == "Email") {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Email cannot be blank.");
        return false;
    }
    if (ui->firstnameEdit->text().toStdString().empty() || ui->firstnameEdit->text().toStdString() == "Firstname"){
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Firstname cannot be blank.");
        return false;
    }
    if (ui->lastnameEdit->text().toStdString().empty() || ui->lastnameEdit->text().toStdString() == "Lastname"){
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Lastname cannot be blank.");
        return false;
    }
    if (ui->passwordConfirmationEdit->text().toStdString().empty() || ui->passwordEdit->text().toStdString().empty()) {
       ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
       ui->warningText->setText("Password cannot be blank.");
       return false;
   }
    if (ui->passwordConfirmationEdit->text().toStdString() != ui->passwordEdit->text().toStdString()) {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Password does not match.");
        return false;
    }
    return true;
}

bool            GUI::Registration::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::FocusIn) {
        if (object->objectName() == "passwordEdit") {
            ui->passwordEdit->setEchoMode(QLineEdit::Password);
        }
        else if (object->objectName() == "passwordConfirmationEdit") {
            ui->passwordConfirmationEdit->setEchoMode(QLineEdit::Password);
        }
    }
    if(event->type() == QEvent::MouseButtonPress) {
        if (object->objectName() == "emailEdit")
            ui->emailEdit->setText("");
        else if (object->objectName() == "usernameEdit")
            ui->usernameEdit->setText("");
        else if (object->objectName() == "passwordEdit") {
            ui->passwordEdit->setText("");
        }
        else if (object->objectName() == "firstnameEdit")
            ui->firstnameEdit->setText("");
        else if (object->objectName() == "lastnameEdit")
            ui->lastnameEdit->setText("");
        else if (object->objectName() == "passwordConfirmationEdit") {
            ui->passwordConfirmationEdit->setText("");
        }
    }
    return false;
}
