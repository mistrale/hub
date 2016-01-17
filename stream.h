#ifndef STREAM_H
#define STREAM_H

#include "awidget.h"

namespace Ui {
class Stream;
}

namespace GUI {
    class Stream : public AWidget
    {
        Q_OBJECT

    public:
        explicit Stream(QWidget *parent = 0);
        ~Stream();

        void        initialize();

    private:
        Ui::Stream *ui;
    };
}

#endif // STREAM_H
