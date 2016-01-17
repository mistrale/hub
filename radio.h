#ifndef RADIO_H
#define RADIO_H

#include "awidget.h"

namespace Ui {
class Radio;
}

namespace GUI {
    class Radio : public AWidget
    {
        Q_OBJECT

    public:
        explicit Radio(QWidget *parent = 0);
        ~Radio();

        void        initialize();

    private:
        Ui::Radio *ui;
    };
}

#endif // RADIO_H
