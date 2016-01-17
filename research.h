#ifndef RESEARCH_H
#define RESEARCH_H

#include "awidget.h"

namespace Ui {
class Research;
}

namespace GUI {
    class Research : public AWidget
    {
        Q_OBJECT

    public:
        explicit Research(QWidget *parent = 0);
        ~Research();

        void        initialize();

    private:
        Ui::Research *ui;
    };
}

#endif // RESEARCH_H
