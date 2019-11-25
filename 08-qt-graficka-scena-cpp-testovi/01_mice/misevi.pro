HEADERS += \
    mouse.h
SOURCES += \
    main.cpp \
    mouse.cpp

QT += widgets

RESOURCES += \
    mice.qrc

QMAKE_CXXFLAGS += -std=c++17

# install
target.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/collidingmice
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS collidingmice.pro images
sources.path = $$[QT_INSTALL_EXAMPLES]/graphicsview/collidingmice
INSTALLS += target sources
