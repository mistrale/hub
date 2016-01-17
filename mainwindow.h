#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <connection.h>
#include <registration.h>
#include <everywherewindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void                    showRegistration();
    void                    showConnection();
    void                    showEverywhere();

private:
    Ui::MainWindow          *ui;
    GUI::Connection         *_connectionWidget;
    GUI::Registration       *_registrationWidget;
    GUI::EverywhereWindow   *_everywhereWidget;

    QMovie          *_background;
};

#endif // MAINWINDOW_H
