#ifndef SYNCHRONIZATION_H
#define SYNCHRONIZATION_H

#include "awidget.h"

namespace Ui {
class Synchronization;
}

namespace GUI {
    class Synchronization : public AWidget
    {
        Q_OBJECT

    public:
        explicit Synchronization(QWidget *parent = 0);
        ~Synchronization();

        void        initialize();

    private:
        Ui::Synchronization *ui;
    };
}

#endif // SYNCHRONIZATION_H
