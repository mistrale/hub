#ifndef PROFIL_H
#define PROFIL_H

#include "awidget.h"

#include "requestmanager.h"

#include <QNetworkReply>

namespace Ui {
class Profil;
}

namespace GUI {
    class Profil : public AWidget
    {
        Q_OBJECT

    public:
        explicit Profil(QWidget *parent = 0);
        ~Profil();

        void        initialize();
        void        disconnectManager();
        void        createProfil();
        bool        checkField();

    public slots:
        void        replyFinished(QNetworkReply *reply);
        void        onError(QNetworkReply::NetworkError code);
        void        deleteAccount();
        void        deleteAccountFinished(QNetworkReply *reply);
        void        updateProfil();
        void        updateProfilFinished(QNetworkReply *reply);

    signals:
        void        deleted();

    private:
        Ui::Profil *ui;

        Tool::RequestManager   _manager;
        QNetworkReply           *_reply;
    };
}

#endif // PROFIL_H
