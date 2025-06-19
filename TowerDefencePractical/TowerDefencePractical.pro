QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    enemies.cpp \
    enemyhandler.cpp \
    gamewindow.cpp \
    gridblocks.cpp \
    just_to_test_qt_framework_inheritance.cpp \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    menubtn.cpp \
    towerbtn.cpp

HEADERS += \
    enemies.h \
    enemyhandler.h \
    gamewindow.h \
    gridblocks.h \
    just_to_test_qt_framework_inheritance.h \
    mainwindow.h \
    menu.h \
    menubtn.h \
    towerbtn.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Basedestroyed.qrc \
    Basephoto.qrc \
    BigAlien.qrc \
    Bigsound.qrc \
    Bigtower.qrc \
    Canon.qrc \
    Click.qrc \
    Dying.qrc \
    Fasttower.qrc \
    FightMusic.qrc \
    Grass.qrc \
    Lazer.qrc \
    Mexplosion.qrc \
    Regtower.qrc \
    SmallAlien.qrc \
    Spaceship.qrc \
    homerScream.qrc \
    homerSound.qrc \
    homiepic.qrc \
    homietransparentpng.qrc \
    intro.qrc \
    menuEffect.qrc \
    minePic.qrc \
    mineboom.qrc \
    musicM.qrc
