QT += widgets
TARGET = EnergyPro
HEADERS += rastchet.h \
    mainwindow.h \
    IHistoryWriter.h \
    IHistoryReader.h \
    IHistoryManager.h \
    XmlHistoryManager.h \
    FileOpenException.h \
    XmlReadException.h
SOURCES += rastchet.cpp \
    mainwindow.cpp \
    main.cpp \
    IHistoryWriter.cpp \
    IHistoryReader.cpp \
    IHistoryManager.cpp \
    XmlHistoryManager.cpp \
    FileOpenException.cpp \
    XmlReadException.cpp
RESOURCES += EnergyIcon.qrc
