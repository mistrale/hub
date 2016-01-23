#include "resultsearch.h"
#include "ui_resultsearch.h"
#include "localdata.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>

GUI::ResultSearch::ResultSearch(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::ResultSearch),
    _parent(parent)
{
    ui->setupUi(this);
    QObject::connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(searchFinished(QNetworkReply*)));

    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    ui->scrollArea->setWidgetResizable(true);
    _layout = new QVBoxLayout;
    ui->scrollAreaWidgetContents->setLayout(_layout);

    //ui->scrollArea->setWidget(ui->list->widget());
}

GUI::ResultSearch::~ResultSearch()
{
    delete ui;
}

void        GUI::ResultSearch::initialize() {
    Model::LocalData    *data = Model::LocalData::instance();

    _reply = _manager.researchRequest(data->Values["keyword"].toString(), data->Values["provider"].toString(),
            data->Values["kind"].toString(), data->Values["token"].toString());
     connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onError(QNetworkReply::NetworkError)));
}

#include <QDebug>

void        GUI::ResultSearch::searchFinished(QNetworkReply *reply) {
    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();

    QJsonArray entries = json["body"].toObject().value("entries").toArray();

    _listVideo.clear();
    int number = 0;
    foreach (const QJsonValue &value, entries) {
        QJsonObject obj = value.toObject();
        Model::VideoSearch  item;
        item.setValue("duration", obj.value("duration").toInt());
        item.setValue("provider", obj.value("provider").toString());
        item.setValue("thumbnail", obj.value("thumbnail").toString());
        item.setValue("title", obj.value("title").toString());
        item.setValue("url", obj.value("url").toString());
        QGridLayout *grid = new QGridLayout;

        QPushButton *image = new QPushButton;
        if (number % 2 == 0)
            image->setStyleSheet("background: black;");
        else
            image->setStyleSheet("background: white;");
        image->setFixedSize(100, 100);
        grid->addWidget(image, 0, 0, Qt::AlignCenter);
        _layout->addLayout(grid);
        number++;
    }
    qDebug() << number;
}

void        GUI::ResultSearch::onError(QNetworkReply::NetworkError code) {

}
