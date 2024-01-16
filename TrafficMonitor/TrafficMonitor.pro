QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

DESTDIR     += $$PWD/../out_put
MOC_DIR     += $$PWD/../build
UI_DIR      += $$PWD/../build
OBJECTS_DIR += $$PWD/../build

HEADERS += \
    common/configmanagement.h \
    trafficmonitor.h

SOURCES += \
    main.cpp \
    trafficmonitor.cpp

FORMS += \
    trafficmonitor.ui

TRANSLATIONS += \
    translation/TrafficMonitor_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
