#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QMovie>
#include <QtNetwork/QNetworkAccessManager>
#include <QNetworkReply>

#include "requestmanager.h"

namespace Ui {
class Registration;
}

namespace GUI {
    class Registration : public QWidget
    {
        Q_OBJECT

    public:
         explicit Registration(QWidget *parent = 0);
         ~Registration();

        bool                eventFilter(QObject* object, QEvent* event);
        bool                checkField();

    public slots:
        void                registerEverywhere();
        void                replyFinished(QNetworkReply *);
        void                onError(QNetworkReply::NetworkError code);

    private:
        Ui::Registration        *ui;
        QMovie                  *_background;
        Tool::RequestManager   _manager;
        QNetworkReply           *_reply;
    };
}

#endif // REGISTRATION_H
