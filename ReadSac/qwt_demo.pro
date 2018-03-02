include ( /usr/local/qwt-6.1.3/features/qwt.prf )
QT += core widgets
TARGET = qwt
TEMPLATE = app
CONFIG += qwt
INCLUDEPATH += /usr/local/qwt-6.1.3/lib/qwt.framework/Headers/
LIBS += -L /usr/local/qwt-6.1.3/lib/ 
SOURCES += qwt.cpp
