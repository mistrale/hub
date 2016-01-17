#ifndef RESULT_H
#define RESULT_H

#include "awidget.h"
#include "requestmanager.h"

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QPushButton>
#include <QNetworkReply>

namespace Ui {
class Result;
}

namespace GUI {
    class Result : public AWidget
    {
        Q_OBJECT

    public:
        explicit Result(QWidget *parent = 0);
        ~Result();

        void        initialize();

    public slots:
        void        finished(QNetworkReply *reply);
        void        error(QNetworkReply::NetworkError error);
        void        seek(int);
        void        durationChanged(qint64);

    private:
        Ui::Result *ui;

        QMediaPlayer    *_player;
        QMediaPlaylist  *_playlist;

        QPushButton     *test;

        Tool::RequestManager   _manager;
        QNetworkReply           *_reply;
    };
}

#endif // RESULT_H
