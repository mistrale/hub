#include "result.h"
#include "ui_result.h"
#include "localdata.h"

#include <iostream>

GUI::Result::Result(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);

    connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(getFlow(QNetworkReply *)));

    _player = new QMediaPlayer(this);
    _playlist = new QMediaPlaylist(this);

  //  QUrl    url(QUrl::fromLocalFile("C:/Users/audes_000/Downloads/test/test.mp4"));
  //  QUrl    url2("http:\/\/www.dailymotion.com\/cdn\/H264-320x240\/video\/x3h2ydm.mp4?auth=1452873516-2562-i4oocjt8-0922a9657b2800d8844b2081d1ce41c0");
 //   _playlist->addMedia(url2);
    //std::cout << "C'est valide " << url.isValid() << std::endl;
    _playlist->setCurrentIndex(1);
    _player->setPlaylist(_playlist);
    _player->setVideoOutput(ui->video);
    ui->slider->setRange(0, _player->duration() / 1000);

    connect(ui->slider, SIGNAL(valueChanged(int)), this, SLOT(seek(int)));
    connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(_player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(managePlayPause()));
    connect(ui->volumeButton, SIGNAL(clicked()), this, SLOT(manageVolume()));
    connect(ui->volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(volumeChanged(int)));
    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(50);
    ui->video->showFullScreen();
}

GUI::Result::~Result()
{
    delete ui;
}

void    GUI::Result::initialize() {
    _play = true;
    _volumeoff = false;
    _player->stop();
    _playlist->clear();

    Model::LocalData    *data = Model::LocalData::instance();
    QVariantMap         item = data->Values["media"].toMap();
    QString             url = item["url"].toString();
    url.insert(4, 's');
    url.insert(8, "www.");
    qDebug() << url;
    _reply = _manager.manager->get(QNetworkRequest(QUrl(url)));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(error(QNetworkReply::NetworkError)));
}

void    GUI::Result::volumeChanged(int volume) {
    _player->setVolume(volume);
}

void    GUI::Result::manageVolume() {
    if (_volumeoff) {
        _volumeoff = false;
        _player->setMuted(false);
        ui->volumeButton->setStyleSheet("QPushButton#volumeButton {"
                                        "background: url(C:/everywhere/images/volume-high.png);"
                                        "width : 36 px; height : 36 px; border : none;}");
    } else {
        _volumeoff = true;
        _player->setMuted(true);
        ui->volumeButton->setStyleSheet("QPushButton#volumeButton {"
                                        "background: url(C:/everywhere/images/volume-off.png);"
                                        "width : 36 px; height : 36 px; border : none;}");
    }
}

void    GUI::Result::managePlayPause() {
    if (_play) {
        _play = false;
        _player->pause();
        ui->playButton->setStyleSheet("QPushButton#playButton {"
                                      "background: url(C:/everywhere/images/play.png);"
                                      "width : 36 px; height : 36 px; border : none;}");
    } else {
        _play = true;
        _player->play();
        ui->playButton->setStyleSheet("QPushButton#playButton {"
                                      "background: url(C:/everywhere/images/pause.png);"
                                      "width : 36 px; height : 36 px; border : none;}");
    }
}

void    GUI::Result::seek(int duration) {
    _player->setPosition(duration * 1000);
}

void    GUI::Result::durationChanged(qint64 duration) {
   ui->slider->setMaximum(duration / 1000);
}

void    GUI::Result::getFlow(QNetworkReply *reply) {
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    std::cout << "resutl search ok : " << statusCode << std::endl;
    if (statusCode >= 200 && statusCode < 300) {
        // This block is based on file youtube.lua from VideoLAN project
        QHash<int, QString> stream_map;
        QList<QString>  values;

        QRegExp re("\"url_encoded_fmt_stream_map\":\"([^\"]*)\"", Qt::CaseInsensitive, QRegExp::RegExp2);
        QRegExp urls("url=(.*)");

        int res = re.indexIn(reply->readAll());
        if (res != -1) {
            QString result = re.cap(1);
            foreach (QString line, result.split("\\u0026")) {
                //std::cout << line.toStdString() << std::endl;
                if (urls.indexIn(QUrl::fromPercentEncoding(line.toLatin1())) != -1) {
                    values.push_back(urls.cap(1));
                    //stream_map[1] = urls.cap(1);
                }
            }

            // XXX hardcoded
           // std::cout << values.last().toStdString() << std::endl;
            qDebug() << values.front();
            qDebug() << values.back();
            _playlist->addMedia(QUrl(values.front()));
            _player->play();
        }
    }

}

void    GUI::Result::error(QNetworkReply::NetworkError error) {
    std::cout << "error result request" << std::endl;
}
