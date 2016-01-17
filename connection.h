#ifndef CONNECTION_H
#define CONNECTION_H

#include <QWidget>
#include  <QNetworkAccessManager>
#include <QNetworkReply>

#include "requestmanager.h"

namespace Ui {
class Connection;
}

namespace GUI {
    class Connection : public QWidget
    {
        Q_OBJECT

    public:
        explicit Connection(QWidget *parent = 0);
        ~Connection();

        bool                eventFilter(QObject* object, QEvent* event);


    private:
        Ui::Connection  *ui;
        QMovie          *_background;
        Tool::RequestManager   _manager;
        QNetworkReply           *_reply;

    public slots:
        void                connectEverywhere();
        void                replyFinished(QNetworkReply *);
        void                onError(QNetworkReply::NetworkError code);

    signals:
        void                showEverywhere();

    };
}

#endif // CONNECTION_H
