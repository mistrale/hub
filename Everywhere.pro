#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T21:35:24
#
#-------------------------------------------------

QT       += core gui \
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets \
                                        uitools \
                                        network

TARGET = Everywhere
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    connection.cpp \
    registration.cpp \
    everywherewindow.cpp \
    news.cpp \
    disconnect.cpp \
    download.cpp \
    library.cpp \
    profil.cpp \
    radio.cpp \
    research.cpp \
    stream.cpp \
    synchronization.cpp \
    requestmanager.cpp \
    localdata.cpp \
    resultsearch.cpp \
    result.cpp \
    awidget.cpp

HEADERS  += mainwindow.h \
    connection.h \
    registration.h \
    everywherewindow.h \
    news.h \
    disconnect.h \
    download.h \
    library.h \
    profil.h \
    radio.h \
    research.h \
    stream.h \
    synchronization.h \
    requestmanager.h \
    localdata.h \
    resultsearch.h \
    result.h \
    awidget.h

FORMS    += mainwindow.ui \
    connection.ui \
    registration.ui \
    everywherewindow.ui \
    news.ui \
    disconnect.ui \
    download.ui \
    library.ui \
    profil.ui \
    radio.ui \
    research.ui \
    stream.ui \
    synchronization.ui \
    resultsearch.ui \
    result.ui

RESOURCES +=

DISTFILES += \
    images/disconnectBackgroundButton.png \
    images/disconnectBackgroundButtonHover.png \
    images/downloadBackgroundButton.png \
    images/downloadBackgroundButtonHover.png \
    images/libraryBackgroundButton.png \
    images/libraryBackgroundButtonHover.png \
    images/newBackgroundButton.png \
    images/newBackgroundButtonHover.png \
    images/profilBackgroundButton.png \
    images/profilBackgroundButtonHover.png \
    images/shareBackgroundButton.png \
    images/shareBackgroundButtonHover.png \
    images/streamBackgroundButton.png \
    images/streamBackgroundButtonHover.png \
    images/subscriptionBackgroundButton.png \
    images/subscriptionBackgroundButtonHover.png \
    images/synchronizationBackgroundButton.png \
    images/synchronizationBackgroundButtonHover.png \
    images/account.png \
    images/back.png \
    images/background.png \
    images/backgroundbutton.png \
    images/backgroundbutton-pressed.png \
    images/disconnectBackground.png \
    images/downloadBackground.png \
    images/email.png \
    images/everywhere.png \
    images/everywhere-pressed.png \
    images/everywhere-signin.png \
    images/everywhere-signin-pressed.png \
    images/facebook-signin.png \
    images/facebook-signin-pressed.png \
    images/facebook-signup.png \
    images/facebook-signup-pressed.png \
    images/friendsButton.png \
    images/google-signin.png \
    images/google-signin-pressed.png \
    images/google-signup.png \
    images/google-signup-pressed.png \
    images/libraryBackground.png \
    images/lock.png \
    images/logo.png \
    images/menuButton.png \
    images/messageButton.png \
    images/newBackground.png \
    images/notifButton.png \
    images/optionButton.png \
    images/profilBackground.png \
    images/searchButton.png \
    images/separator.png \
    images/shareBackground.png \
    images/streamBackground.png \
    images/subscriptionBackground.png \
    images/synchronizationBackground.png
