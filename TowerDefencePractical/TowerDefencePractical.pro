QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    gridblocks.cpp \
    main.cpp \
    mainwindow.cpp \
    menubtn.cpp \
    towerbtn.cpp

HEADERS += \
    gridblocks.h \
    mainwindow.h \
    menubtn.h \
    towerbtn.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Basephoto.qrc \
    Bigtower.qrc \
    Click.qrc \
    Fasttower.qrc \
    Grass.qrc \
    Regtower.qrc \
    homerSound.qrc \
    homiepic.qrc \
    homietransparentpng.qrc
