#ifndef EVERYWHEREWINDOW_H
#define EVERYWHEREWINDOW_H

#include <vector>

#include <QWidget>
#include <QMovie>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QPushButton>

#include <QGraphicsItemAnimation>

#include "awidget.h"

namespace Ui {
class EverywhereWindow;
}

namespace GUI {
    class EverywhereWindow : public QWidget
    {
         Q_OBJECT

    public:
        explicit EverywhereWindow(QWidget *parent = 0);
        ~EverywhereWindow();

        void                                closeMenu();
        void                                openMenu();
        void                                createMenu();

        void                                createCloseMenu();
        void                                createOpenMenu();

        void                                createQPropertyAnimationButton(const QRect &,
                                                                           const QRect &,
                                                                           QPushButton *,
                                                                           QParallelAnimationGroup *);


    public slots:
        void                                manageMenu();
        void                                switchView();
        void                                updateView();
        void                                getSearchResult();
        void                                showResult();

    private:
        Ui::EverywhereWindow *ui;

        QParallelAnimationGroup             *_closeAnimations;
        QParallelAnimationGroup             *_openAnimations;

        QPropertyAnimation                  *_closeLastAnimation;
        QPropertyAnimation                  *_openLastAnimation;
        bool                                _menuOpen;

        typedef std::pair<QString, AWidget *> Widget;
        std::map<QString, Widget>             _menuWidgets;
        Widget                               _current;

        QWidget                             *_parent;
    };
}

#endif // EVERYWHEREWINDOW_H
