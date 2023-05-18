QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
SOURCES += \
    main.cpp \
    ./windows/mainwindow.cpp \
    ./windows/enteryw.cpp \
    ./windows/analog_w.cpp \
    ./windows/signUpW.cpp \
    ./windows/sqllib.cpp \
    ./windows/managerW.cpp \
    ./windows/dataBaseWindow.cpp\
    ./windows/gamew.cpp


HEADERS += \
    ./windows/mainwindow.h \
    ./windows/enteryw.h \
    ./windows/analog_w.h \
    ./windows/signUpW.h \
    ./windows/sqllib.h \
    ./windows/managerW.h \
    ./windows/dataBaseWindow.h\
    ./windows/gamew.h


FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
