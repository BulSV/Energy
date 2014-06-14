QT += widgets
TARGET = EnergyPro
HEADERS += payment.h \
    mainwindow.h \
    IHistoryWriter.h \
    IHistoryReader.h \
    IHistoryManager.h \
    XmlHistoryManager.h \
    FileOpenException.h \
    XmlReadException.h \
    IPayment.h \
    AbstractPartPayment.h \
    BenefitPayment.h
SOURCES += payment.cpp \
    mainwindow.cpp \
    main.cpp \
    IHistoryWriter.cpp \
    IHistoryReader.cpp \
    IHistoryManager.cpp \
    XmlHistoryManager.cpp \
    FileOpenException.cpp \
    XmlReadException.cpp \
    IPayment.cpp \
    AbstractPartPayment.cpp \
    BenefitPayment.cpp
RESOURCES += EnergyIcon.qrc
RC_FILE += EnergyIcon.rc
