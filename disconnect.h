#ifndef DISCONNECT_H
#define DISCONNECT_H

#include "awidget.h"

namespace Ui {
class Disconnect;
}

namespace GUI {
    class Disconnect : public AWidget
    {
        Q_OBJECT

    public:
        explicit Disconnect(QWidget *parent = 0);
        ~Disconnect();

        void        initialize();

    private:
        Ui::Disconnect *ui;
    };
}

#endif // DISCONNECT_H
