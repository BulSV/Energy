QT += widgets
TARGET = EnergyPro
HEADERS += Payment.h \
    MainWindow.h \
    IHistoryWriter.h \
    IHistoryReader.h \
    IHistoryManager.h \
    XmlHistoryManager.h \
    FileOpenException.h \
    XmlReadException.h \
    IPayment.h \
    AbstractPartPayment.h \
    BenefitPayment.h
SOURCES += Payment.cpp \
    MainWindow.cpp \
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
