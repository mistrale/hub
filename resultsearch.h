#ifndef RESULTSEARCH_H
#define RESULTSEARCH_H

#include "awidget.h"
#include "requestmanager.h"
#include "videosearch.h"
#include "button.h"

#include <vector>
#include <QNetworkReply>
#include <QVBoxLayout>

namespace Ui {
class ResultSearch;
}

namespace GUI {
    class ResultSearch : public AWidget
    {
        Q_OBJECT

    public:
        explicit ResultSearch(QWidget *parent = 0);
        ~ResultSearch();

        void        initialize();

    signals:
        void                goToResult();

    public slots:
        void                onError(QNetworkReply::NetworkError code);
        void                searchFinished(QNetworkReply *);
        void                goToVideo();

    private:
        std::vector<Model::VideoSearch>   _listVideo;
        std::vector<QObject *>             _buttons;
        Ui::ResultSearch        *ui;
        QVBoxLayout                     *_layout;

        QWidget                 *_parent;
        Tool::RequestManager    _manager;
        QNetworkReply           *_reply;

    };
}

#endif // RESULTSEARCH_H
