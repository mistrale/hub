#include "connection.h"
#include "ui_connection.h"
#include "requestmanager.h"
#include "localdata.h"

#include <QMovie>
#include <QJsonDocument>
#include <QSettings>

#include <iostream>

GUI::Connection::Connection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Connection)
{
    ui->setupUi(this);

    connect(ui->signinButton, SIGNAL(clicked()), parent, SLOT(showRegistration()));
    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(connectEverywhere()));
    connect(this, SIGNAL(showEverywhere()), parent, SLOT(showEverywhere()));

    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

    ui->emailEdit->installEventFilter(this);
    ui->passwordEdit->installEventFilter(this);

    QSettings settings("C:/everywhere/settings.ini",
                       QSettings::IniFormat);
    if (settings.value("registerAccount").toBool() == true) {
        ui->emailEdit->setText(settings.value("emailAccount").toString());
        ui->passwordEdit->setText(settings.value("passwordAccount").toString());
        ui->connectedBox->setChecked(true);
        ui->passwordEdit->setEchoMode(QLineEdit::Password);

    }
}

GUI::Connection::~Connection()
{
    delete ui;
}

void            GUI::Connection::connectEverywhere() {
    ui->warningText->setText("");
    _reply = _manager.connectionRequest(ui->emailEdit->text(), ui->passwordEdit->text());
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
     _background = new QMovie("C:/Everywhere/images/Ring.gif");
     ui->ring->setMovie(_background);
    _background->start();
}

void            GUI::Connection::replyFinished(QNetworkReply *reply) {
    std::cout << "request connection ok " << std::endl;
    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();
    int status = json["status"].toObject().value("code").toInt();

    std::cout<< bytes.toStdString() << std::endl;
    if (_background != NULL) {
        _background->stop();
        delete _background;
        _background = NULL;
    }
    if (status == 200) {
        emit showEverywhere();
        QJsonObject body = json["body"].toObject();

        Model::LocalData    *data = Model::LocalData::instance();
        QSettings settings("C:/everywhere/settings.ini",
                           QSettings::IniFormat);

        if (ui->connectedBox->isChecked())
            settings.setValue("registerAccount", true);
        else
            settings.setValue("registerAccount", false);

        if (settings.value("registerAccount").toBool()) {
            ui->passwordEdit->setText(ui->passwordEdit->text());
            ui->emailEdit->setText(ui->emailEdit->text());
            settings.setValue("emailAccount", ui->emailEdit->text());
            settings.setValue("passwordAccount", ui->passwordEdit->text());

        } else {
            ui->passwordEdit->setText("password");
            ui->emailEdit->setText("Email");
            settings.setValue("emailAccount", "");
            settings.setValue("passwordAccount", "");
        }
        data->Values["token"] = body.value("token").toString();
        data->Values["email"] = body.value("email").toString();
        data->Values["password"] = ui->passwordEdit->text();
    } else {
        QString message = json["status"].toObject().value("message").toString();
        ui->warningText->setText(message);
        ui->warningText->setStyleSheet("background: transparent;"
                                       "font: 12pt \"MS Shell Dlg 2\";"
                                       "font-weight: bold;"
                                       "color :red;");
    }
}

void            GUI::Connection::onError(QNetworkReply::NetworkError code) {
    std::cout << "Error on connection request" << std::endl;
    if (_background != NULL) {
        _background->stop();
        delete _background;
        _background = NULL;
    }
}

bool            GUI::Connection::eventFilter(QObject *object, QEvent *event) {
    if(event->type() == QEvent::FocusIn) {
        if (object->objectName() == "passwordEdit") {
            ui->passwordEdit->setEchoMode(QLineEdit::Password);
        }
    }
    if(event->type() == QEvent::MouseButtonPress) {
        if (object->objectName() == "emailEdit")
            ui->emailEdit->setText("");
        else if (object->objectName() == "passwordEdit") {
            ui->passwordEdit->setText("");
        }
    }
    return false;
}
