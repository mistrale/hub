#include "profil.h"
#include "ui_profil.h"
#include "localdata.h"

#include <QGraphicsEffect>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSettings>

#include <iostream>

GUI::Profil::Profil(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Profil)
{
    ui->setupUi(this);
    createProfil();
    QObject::connect(ui->deleteAccount, SIGNAL(clicked()), this, SLOT(deleteAccount()));
    QObject::connect(ui->updateProfil, SIGNAL(clicked()), this, SLOT(updateProfil()));
}

GUI::Profil::~Profil()
{
    delete ui;
}

bool            GUI::Profil::checkField() {
    if (ui->usernameLineEdit->text().toStdString().empty()) {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Username cannot be blank.");
        return false;
    }
    if (ui->firstnameLineEdit->text().toStdString().empty()){
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Firstname cannot be blank.");
        return false;
    }
    if (ui->lastnameLineEdit->text().toStdString().empty()){
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Lastname cannot be blank.");
        return false;
    }
    if (ui->passwordConfirmationLineEdit->text().toStdString().empty() || ui->passwordLineEdit->text().toStdString().empty()) {
       ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
       ui->warningText->setText("Password cannot be blank.");
       return false;
   }
    if (ui->passwordConfirmationLineEdit->text().toStdString() != ui->passwordLineEdit->text().toStdString()) {
        ui->warningText->setStyleSheet("color : red; 	font: 9pt \"MS Shell Dlg 2\";font-weight: bold;");
        ui->warningText->setText("Password does not match.");
        return false;
    }
    return true;
}

void            GUI::Profil::updateProfil() {
    Model::LocalData    *data = Model::LocalData::instance();

    disconnectManager();
    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(updateProfilFinished(QNetworkReply*)));

    if (!checkField()) {
        return;
    }
    ui->warningText->setText("");
    QString     emailPrivate;
    QString     firstnamePrivate;
    QString     lastnamePrivate;

    if (ui->emailPublic->isChecked())
        emailPrivate = "false";
    if (ui->firstnamePublic->isChecked())
        firstnamePrivate = "false";
    if (ui->lastnamePublic->isChecked())
        lastnamePrivate = "false";
    _reply = _manager.updateProfilRequest(ui->usernameLineEdit->text(), ui->passwordLineEdit->text(), ui->firstnameLineEdit->text(),
                                          ui->lastnameLineEdit->text(), emailPrivate, firstnamePrivate, lastnamePrivate,
                                          data->Values["token"].toString());
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

void            GUI::Profil::updateProfilFinished(QNetworkReply * reply) {
    std::cout << "request updateprofil ok" << std::endl;
    Model::LocalData    *data = Model::LocalData::instance();
    QSettings settings("C:/everywhere/settings.ini",
                       QSettings::IniFormat);

    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();

    int status = json["status"].toInt();
    std::cout << bytes.toStdString() << std::endl;

    if (settings.value("registerAccount").toBool()) {
        settings.setValue("passwordAccount", ui->passwordLineEdit->text());
    }
    data->Values["password"] = ui->passwordLineEdit->text();
}

void            GUI::Profil::disconnectManager() {
    QObject::disconnect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(deleteAccountFinished(QNetworkReply *)));
    QObject::disconnect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    QObject::disconnect(_manager.manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(updateProfilFinished(QNetworkReply*)));
}

void            GUI::Profil::deleteAccount() {
    Model::LocalData    *data = Model::LocalData::instance();

    disconnectManager();
    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(deleteAccountFinished(QNetworkReply *)));
    _reply = _manager.deleteRequest(data->Values["token"].toString());
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
     emit deleted();
}

void            GUI::Profil::deleteAccountFinished(QNetworkReply *reply) {
    std::cout << "delete request ok" << std::endl;
    QByteArray bytes = reply->readAll();
    std::cout << bytes.toStdString() << std::endl;
}

void            GUI::Profil::initialize() {
    disconnectManager();
    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
    Model::LocalData    *data = Model::LocalData::instance();

    _reply = _manager.meRequest(data->Values["token"].toString(), data->Values["email"].toString());
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
     ui->passwordLineEdit->setText(data->Values["password"].toString());
     ui->passwordConfirmationLineEdit->setText(data->Values["password"].toString());
     ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
     ui->passwordConfirmationLineEdit->setEchoMode(QLineEdit::Password);
}

void            GUI::Profil::replyFinished(QNetworkReply *reply) {

    std::cout << "me request ok" << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();
    QJsonObject body = json["body"].toObject();
    ui->emailLineEdit->setText(body.value("email").toString());
    ui->usernameLineEdit->setText(body.value("username").toString());
    ui->firstnameLineEdit->setText(body.value("firstname").toString());
    ui->lastnameLineEdit->setText(body.value("lastname").toString());

    if (body.value("emailPrivate").toBool() == true)
        ui->emailPublic->setChecked(false);
    if (body.value("firstnamePrivate").toBool() == true)
        ui->firstnamePublic->setChecked(false);
    if (body.value("lastnamePrivate").toBool() == true)
        ui->lastnamePublic->setChecked(false);
  std::cout << bytes.toStdString() << std::endl;
}

void            GUI::Profil::onError(QNetworkReply::NetworkError code) {
    std::cout << "Error on profil request" << std::endl;
}

void            GUI::Profil::createProfil() {
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setXOffset(5);
    effect->setYOffset(5);
    ui->updateProfil->setGraphicsEffect(effect);

    QGraphicsDropShadowEffect* effect2 = new QGraphicsDropShadowEffect();
    effect->setBlurRadius(10);
    effect->setXOffset(5);
    effect->setYOffset(5);
    ui->deleteAccount->setGraphicsEffect(effect);
}
