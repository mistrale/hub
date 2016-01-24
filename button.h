#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <qwidget.h>
#include <QPushButton>
#include <QNetworkReply>

#include "requestmanager.h"

class Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Button(const QString &path, int id, QWidget *parent = 0);

signals:

public:
    int       getId() const;

public slots:
    void      getImage(QNetworkReply *reply);

private:
    Tool::RequestManager   _manager;
    QNetworkReply           *_reply;
    int                     _id;
};

#endif // BUTTON_H
