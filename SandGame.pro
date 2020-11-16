TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        button.cpp \
        main.cpp \
        particle.cpp


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-system-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-graphics-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../SFML-2.5.1/lib/ -lsfml-window-d

INCLUDEPATH += $$PWD/../SFML-2.5.1/include
DEPENDPATH += $$PWD/../SFML-2.5.1/include

HEADERS += \
    button.h \
    particle.h

