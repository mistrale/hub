#ifndef NEWS_H
#define NEWS_H

#include "awidget.h"

namespace Ui {
class News;
}

namespace GUI {
    class News : public AWidget
    {
        Q_OBJECT

    public:
        explicit News(QWidget *parent = 0);
        ~News();

        void        initialize();

    private:
        Ui::News *ui;
    };
}

#endif // NEWS_H
