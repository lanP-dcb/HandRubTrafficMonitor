QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR     += $$PWD/../out_put
MOC_DIR     += $$PWD/../build
UI_DIR      += $$PWD/../build
OBJECTS_DIR += $$PWD/../build

win32 {
    message("win32");
    DEFINES += UNIX=0
}
unix {
    DEFINES += UNIX=1
    CONFIG += link_pkgconfig
    INCLUDEPATH += /usr/include/libappindicator3-0.1
    PKGCONFIG += gtk+-3.0
    LIBS += -lappindicator3
}

HEADERS += \
    common/configmanagement.h \
    common/default.h \
    trafficmonitor.h \
    include/traymanagement.h \
    include/mainmonitorwin.h

SOURCES += \
    main.cpp \
    trafficmonitor.cpp \
    include/traymanagement.cpp \
    include/mainmonitorwin.cpp

#FORMS += \
#    trafficmonitor.ui

TRANSLATIONS += \
    translation/TrafficMonitor_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
