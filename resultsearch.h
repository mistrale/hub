#ifndef RESULTSEARCH_H
#define RESULTSEARCH_H

#include "awidget.h"
#include "requestmanager.h"
#include "videosearch.h"

#include <list>
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

    public slots:
        void                onError(QNetworkReply::NetworkError code);
        void                searchFinished(QNetworkReply *);

    private:
        std::list<Model::VideoSearch>   _listVideo;
        Ui::ResultSearch        *ui;
        QVBoxLayout                     *_layout;

        QWidget                 *_parent;
        Tool::RequestManager    _manager;
        QNetworkReply           *_reply;

    };
}

#endif // RESULTSEARCH_H
