#ifndef RESULT_H
#define RESULT_H

#include "awidget.h"
#include "requestmanager.h"

#include <QtMultimediaWidgets/QVideoWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QPushButton>
#include <QNetworkReply>

#include "aprovider.h"

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
        void        error(QNetworkReply::NetworkError error);
        void        getFlow(QNetworkReply *reply);
        void        seek(int);
        void        durationChanged(qint64);
        void        volumeChanged(int);
        void        managePlayPause();
        void        manageVolume();

    private:
        Ui::Result *ui;

        QMediaPlayer    *_player;
        QMediaPlaylist  *_playlist;

        QPushButton     *test;

        Tool::RequestManager   _manager;
        QNetworkReply           *_reply;

        bool            _play;
        bool            _volumeoff;

        std::map<std::string, Tool::AProvider *>    _providers;
    };
}

#endif // RESULT_H
