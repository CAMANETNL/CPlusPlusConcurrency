
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp

HEADERS += \
    threadguard.h

macx: LIBS += -L$$PWD/../../../Libraries/build/test_library/ -lDLL.1.0.0

INCLUDEPATH += $$PWD/../../../Libraries/project/test_library
DEPENDPATH += $$PWD/../../../Libraries/project/test_library


