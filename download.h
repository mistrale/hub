#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include "awidget.h"

namespace Ui {
class Download;
}

namespace GUI {
    class Download : public AWidget
    {
        Q_OBJECT

    public:
        explicit Download(QWidget *parent = 0);
        ~Download();

        void     initialize();

    private:
        Ui::Download *ui;
    };
}

#endif // DOWNLOAD_H
