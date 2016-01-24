#include "button.h"

#include <QPixmap>

Button::Button(const QString &path, int id, QWidget *parent) : QPushButton(parent), _id(id)
{
    connect(_manager.manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getImage(QNetworkReply*)));
    _manager.randomGetRequest(path);
}

void        Button::getImage(QNetworkReply *reply) {
    QPixmap    map;
    map.loadFromData(reply->readAll());
    this->setIcon(QIcon(map));
    this->setFixedWidth(160);
    this->setMinimumHeight(90);
    this->setIconSize(QSize(160, this->height()));
    this->setStyleSheet("background: transparent; border: none;");
}

int         Button::getId() const {
    return _id;
}
