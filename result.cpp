#include "result.h"
#include "ui_result.h"

#include <iostream>

GUI::Result::Result(QWidget *parent) :
    AWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);

   _reply = _manager.manager->get(QNetworkRequest(QUrl("https://www.youtube.com/watch?v=ZSKusF-4i0w")));
    connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), SLOT(error(QNetworkReply::NetworkError)));
    connect(_manager.manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(finished(QNetworkReply *)));

    _player = new QMediaPlayer(this);
    _playlist = new QMediaPlaylist(this);

    QUrl    url(QUrl::fromLocalFile("C:/Users/audes_000/Downloads/test/test.mp4"));
    QUrl    url2("http:\/\/www.dailymotion.com\/cdn\/H264-320x240\/video\/x3h2ydm.mp4?auth=1452873516-2562-i4oocjt8-0922a9657b2800d8844b2081d1ce41c0");
 //   _playlist->addMedia(url2);
    //std::cout << "C'est valide " << url.isValid() << std::endl;
    _playlist->setCurrentIndex(1);
    _player->setPlaylist(_playlist);
    _player->setVideoOutput(ui->video);
    ui->slider->setRange(0, _player->duration() / 1000);

    connect(ui->slider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(_player, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));
 //  _player->play();
   std::cout << _player->duration() << std::endl;


  //  test = new QPushButton(this);
  // test->setText("PWET");
  //  test->setGeometry(0 , 0, 200, 200);
  //  test->show();
}

GUI::Result::~Result()
{
    delete ui;
}

void    GUI::Result::initialize() {

}

void    GUI::Result::seek(int duration) {
    _player->setPosition(duration * 1000);
}

void    GUI::Result::durationChanged(qint64 duration) {
   ui->slider->setMaximum(duration / 1000);
}

void    GUI::Result::finished(QNetworkReply *reply) {
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
            std::cout << values.size() << std::endl;
           // std::cout << values.last().toStdString() << std::endl;
            _playlist->addMedia(QUrl(values.front()));
            _player->play();
        }
    }

}

void    GUI::Result::error(QNetworkReply::NetworkError error) {
    std::cout << "error result request" << std::endl;
}
