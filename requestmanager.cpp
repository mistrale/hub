#include "requestmanager.h"

#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>

#include <iostream>

Tool::RequestManager::RequestManager()
{
    manager = new QNetworkAccessManager;
}

Tool::RequestManager::~RequestManager() {
    delete manager;
}

QNetworkReply   *Tool::RequestManager::randomGetRequest(const QString &url) {
    QUrl        tmp(url);
    QNetworkRequest request(tmp);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return manager->get(request);
}

QNetworkReply   *Tool::RequestManager::researchRequest(const QString &search, const QString &provider,
                                                       const QString &kind, const QString &token) {
    QUrl        url("http://62.210.237.116:8080/search?provider=" + provider + "&kind=" + kind + "&keyword=" + search);
    QNetworkRequest   request(url);

    request.setRawHeader("authentication-token", token.toStdString().c_str());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return manager->get(request);
}

QNetworkReply   *Tool::RequestManager::updateProfilRequest(const QString &username, const QString &password,
                                                           const QString &firstname, const QString &lastname, const QString &emailPrivate,
                                                           const QString &firstnamePrivate, const QString &lastnamePrivate, const QString &token) {
    QUrl        url("http://62.210.237.116:8080/me");
    QNetworkRequest request(url);
    QUrlQuery   query;

    query.addQueryItem("firstname", firstname);
    query.addQueryItem("lastname", lastname);
    query.addQueryItem("username", username);
    query.addQueryItem("emailPrivate", emailPrivate);
    query.addQueryItem("firstnamePrivate", firstnamePrivate);
    query.addQueryItem("lastnamePrivate", lastnamePrivate);
    query.addQueryItem("password", password);

    request.setRawHeader("authentication-token", token.toStdString().c_str());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return manager->put(request, query.toString(QUrl::FullyEncoded).toUtf8());
}

QNetworkReply   *Tool::RequestManager::meRequest(const QString &token, const QString &email) {
    QUrl        url("http://62.210.237.116:8080/me");
    QNetworkRequest request(url);


    request.setRawHeader("authentication-token", token.toStdString().c_str());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    return manager->get(request);
}

QNetworkReply   *Tool::RequestManager::deleteRequest(const QString &token) {
    QUrl        url("http://62.210.237.116:8080/me");
    QNetworkRequest request(url);

    std::cout << url.toString().toStdString() << std::endl;
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setRawHeader("authentication-token", token.toStdString().c_str());
    return manager->deleteResource(request);
}

QNetworkReply   *Tool::RequestManager::connectionRequest(const QString &email, const QString &password) {
    QUrl        url("http://62.210.237.116:8080/signin");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("email", email);
    params.addQueryItem("password", password);

    return manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
}

QNetworkReply   *Tool::RequestManager::registrationRequest(const QString &email, const QString &username, const QString &password,
                                                           const QString &firstname, const QString &lastname) {
    QUrl        url("http://62.210.237.116:8080/signup");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("email", email);
    params.addQueryItem("username", username);
    params.addQueryItem("firstname", firstname);
    params.addQueryItem("lastname", lastname);
    params.addQueryItem("firstnamePrivate", "true");
    params.addQueryItem("lastnamePrivate", "true");
    params.addQueryItem("emailPrivate", "true");
    params.addQueryItem("password", password);

    return manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
}
