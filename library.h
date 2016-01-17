#ifndef LIBRARY_H
#define LIBRARY_H

#include "awidget.h"

namespace Ui {
class Library;
}

namespace GUI {
    class Library : public AWidget
    {
        Q_OBJECT

    public:
        explicit Library(QWidget *parent = 0);
        ~Library();

        void        initialize();

    private:
        Ui::Library *ui;
    };
}

#endif // LIBRARY_H
