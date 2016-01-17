#ifndef RESULTSEARCH_H
#define RESULTSEARCH_H

#include "awidget.h"

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

    private:
        Ui::ResultSearch *ui;

        QWidget     *_parent;
    };
}

#endif // RESULTSEARCH_H
