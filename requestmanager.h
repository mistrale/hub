#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QNetworkAccessManager>

namespace Tool {
    class RequestManager
    {
    public:
        RequestManager();
        ~RequestManager();

        QNetworkReply   *connectionRequest(const QString &, const QString &);
        QNetworkReply   *registrationRequest(const QString &email, const QString &username,
                                        const QString &password, const QString &firstname, const QString &lastname);
        QNetworkReply   *meRequest(const QString &token, const QString &email);
        QNetworkReply   *deleteRequest(const QString &token);
        QNetworkReply   *updateProfilRequest(const QString &username, const QString &password,
                                             const QString &firstname, const QString &lastname, const QString &emailPrivate,
                                             const QString &firstnamePrivate, const QString &lastnamePrivate, const QString &token);

        QNetworkAccessManager       *manager;
    };
}

#endif // REQUESTMANAGER_H
