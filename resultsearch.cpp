#include "resultsearch.h"
#include "ui_resultsearch.h"
#include "localdata.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPushButton>
#include <QLabel>

#include "button.h"

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
    _layout->setSpacing(15);
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

void        GUI::ResultSearch::searchFinished(QNetworkReply *reply) {
    QByteArray bytes = reply->readAll();
    QJsonDocument doc(QJsonDocument::fromJson(bytes));
    QJsonObject json = doc.object();

    QJsonArray entries = json["body"].toObject().value("entries").toArray();

    _listVideo.erase(_listVideo.begin(), _listVideo.end());
    _listVideo.clear();
    for (auto it = _buttons.begin(); it !=  _buttons.end(); ++it)
        delete *it;
    _buttons.erase(_buttons.begin(), _buttons.end());
    _buttons.clear();
    delete _layout;
    _layout = new QVBoxLayout;
    _layout->setSpacing(15);
    ui->scrollAreaWidgetContents->setLayout(_layout);


    int number = 0;

    foreach (const QJsonValue &value, entries) {
        QJsonObject obj = value.toObject();
        Model::VideoSearch  item;
        item.setValue("duration", obj.value("duration").toInt());
        item.setValue("provider", obj.value("provider").toString());
        item.setValue("thumbnail", obj.value("thumbnail").toString());
        item.setValue("title", obj.value("title").toString());
        item.setValue("url", obj.value("url").toString());

        _listVideo.push_back(item);

        QGridLayout *grid = new QGridLayout;

        Button *image = new Button(obj.value("thumbnail").toString(), number);
        image->setObjectName(QString(std::to_string(number).c_str()));
        connect(image, SIGNAL(clicked()), this, SLOT(goToVideo()));

        QLabel      *title = new QLabel;
        title->setText(item.getValue("title").toString());
        title->setAlignment(Qt::AlignLeft);
        title->setFixedWidth(200);
        title->setWordWrap(true);

        QPushButton *goTitle = new QPushButton("Play");
        connect(goTitle, SIGNAL(clicked()), this, SLOT(goToVideo()));
        goTitle->setObjectName(QString(std::to_string(number).c_str()));
        goTitle->setFixedWidth(100);

        QLabel      *duration = new QLabel;
        duration->setText(item.getValue("duration").toString());
        duration->setAlignment(Qt::AlignLeft);

        _buttons.push_back(image);
        _buttons.push_back(title);
        _buttons.push_back(goTitle);
        _buttons.push_back(duration);
        _buttons.push_back(grid);

        grid->addWidget(image, 0, 0, 2, 1);
        grid->addWidget(title, 0, 1, 1, 1);
        grid->addWidget(goTitle, 0, 2, 1, 1);
        grid->addWidget(duration, 1, 1, 1, 1);

        QWidget     *widget = new QWidget;
        widget->setStyleSheet("background: rgba(230, 230, 230, 0.7);");
        widget->setLayout(grid);
        _layout->addWidget(widget);
        number++;
    }
}

void                    GUI::ResultSearch::goToVideo() {
    QObject              *send = (sender());
    Model::LocalData    *data = Model::LocalData::instance();
    Model::VideoSearch  item = _listVideo[send->objectName().toInt()];

    data->Values["media"] = item.getValues();
    qDebug() << "pwet";
    emit goToResult();
}

void        GUI::ResultSearch::onError(QNetworkReply::NetworkError code) {
    qDebug() << code;
}
