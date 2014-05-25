#include <QGridLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QShortcut>
#include <QDesktopWidget>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QTimer>
#include <QMessageBox>
#include "mainwindow.h"

const int BENEFIT_PERCENT = 0;
const int BENEFIT_LIMIT = 0;
const float TO_150_TARIFF = 0.2802;
const float OVER_150_TARIFF = 0.3648;
const float OVER_800_TARIFF = 0.9576;
const int HISTORY_LIMIT = 100;
const int DATE_UPDATE_TIME = 1000;

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint),
        itsLanguage(1),
        lPilga(new QLabel(QObject::trUtf8("Benefit(%), limit (kWh)"), this)),
        lePilga(new QLineEdit(this)),
        leLimit(new QLineEdit(this)),
        bBackward(new QPushButton(this)),
        lDate(new QLabel(this)),
        bForward(new QPushButton(this)),
        lPotochni(new QLabel(QObject::trUtf8("Current readings, kWh"), this)),
        lPoperedni(new QLabel(QObject::trUtf8("Previous\nreadings, kWh"), this)),
        lSpozhyto(new QLabel(QObject::trUtf8("Consumed, kWh"), this)),
        lSummaSpozhyto(new QLabel(this)),
        lTaryf(new QLabel(QObject::trUtf8("\nTariff, UAH\n"), this)),
        lSummaDoSplaty(new QLabel(QObject::trUtf8("Payment\namount, UAH"), this)),
        lPilgovi(new QLabel(QObject::trUtf8("Benefits, kWh"), this)),
        lDo150(new QLabel(QObject::trUtf8("to 150/250 kWh"), this)),
        lPonad150(new QLabel(QObject::trUtf8("from 150/250 to 800 kWh"), this)),
        lPonad800(new QLabel(QObject::trUtf8("over 800 kWh"), this)),
        lSummaPilgovi(new QLabel(this)),
        lTaryfPilgovi(new QLabel(this)),
        lSummaDo150(new QLabel(this)),
        lSummaPonad150(new QLabel(this)),
        lSummaPonad800(new QLabel(this)),
        lSummaDoSplatyPilgovi(new QLabel(this)),
        lSummaDoSplatyDo150(new QLabel(this)),
        lSummaDoSplatyPonad150(new QLabel(this)),
        lSummaDoSplatyPonad8000(new QLabel(this)),
        lVsegoDosplaty(new QLabel(QObject::trUtf8("Total to pay, UAH"), this)),
        lVsego(new QLabel(this)),

        lePotochni(new QLineEdit(this)),
        lePoperedni(new QLineEdit(this)),
        leTaryfDo150(new QLineEdit(this)),
        leTaryfPonad150(new QLineEdit(this)),
        leTaryfPonad800(new QLineEdit(this)),

        bRozrahunok(new QPushButton(QObject::trUtf8("Calculation"), this)),

        timer(new QTimer(this)),

        settings("Energy.ini", QSettings::IniFormat),

        itsHistory(new QList<QMap<QString, QString> >()),

        itsListIterator(*itsHistory)
{    
    QTranslator translator;
    translator.load("mainwindow_ua.qm", ".");
    qApp->installTranslator(&translator);

    xmlHistoryManager = new XmlHistoryManager("history.xml", *itsHistory);
    this->setWindowTitle(QObject::trUtf8("Calculation of electricity"));

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QPixmap(":/EnergyIcon.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage(QObject::trUtf8("Calculation of electricity"),
                          QObject::trUtf8("Program \"Calculation of electricity\" is running!"));
    trayIcon->show();

    bBackward->setIcon(QIcon(":/left.png"));
    bForward->setIcon(QIcon(":/right.png"));

    lPotochni->setAlignment(Qt::AlignCenter);
    lPotochni->setMargin(4);
    lPoperedni->setAlignment(Qt::AlignCenter);
    lPoperedni->setMargin(4);
    lSpozhyto->setAlignment(Qt::AlignCenter);
    lSpozhyto->setMargin(4);
    lTaryf->setAlignment(Qt::AlignCenter);
    lTaryf->setMargin(4);
    lSummaDoSplaty->setAlignment(Qt::AlignCenter);
    lSummaDoSplaty->setMargin(4);
    lVsegoDosplaty->setAlignment(Qt::AlignRight);
    lVsegoDosplaty->setMargin(4);

    lPilgovi->setMargin(4);
    lDo150->setMargin(4);
    lPonad150->setMargin(4);
    lPonad800->setMargin(4);

    leTaryfDo150->setTextMargins(2, 2, 2, 2);
    leTaryfPonad150->setTextMargins(2, 2, 2, 2);
    leTaryfPonad800->setTextMargins(2, 2, 2, 2);

    updateTime();
    timer->start(DATE_UPDATE_TIME);

    setLayout(new QGridLayout(this));

    QHBoxLayout *hist = new QHBoxLayout;
    hist->addWidget(bBackward);
    hist->addWidget(lDate);
    hist->addWidget(bForward);
    hist->setSpacing(4);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(lPilga, 0, 0);
    grid->addWidget(lePilga, 0, 1);
    grid->addWidget(leLimit, 0, 2);
    grid->addItem(hist, 0, 4, 1, 2);

    grid->addWidget(lPotochni, 1, 0);
    grid->addWidget(lPoperedni, 1, 1, 1, 2);
    grid->addWidget(lSpozhyto, 1, 3);
    grid->addWidget(lTaryf, 1, 4, 2, 1);
    grid->addWidget(lSummaDoSplaty, 1, 5, 2, 1);

    grid->addWidget(lePotochni, 2, 0);
    grid->addWidget(lePoperedni, 2, 1, 1, 2);
    grid->addWidget(lSummaSpozhyto, 2, 3);

    grid->addWidget(lPilgovi, 3, 0, 1, 3);
    grid->addWidget(lSummaPilgovi, 3, 3);
    grid->addWidget(lTaryfPilgovi, 3, 4);
    grid->addWidget(lSummaDoSplatyPilgovi, 3, 5);

    grid->addWidget(lDo150, 4, 0, 1, 3);
    grid->addWidget(lSummaDo150, 4, 3);
    grid->addWidget(leTaryfDo150, 4, 4);
    grid->addWidget(lSummaDoSplatyDo150, 4, 5);

    grid->addWidget(lPonad150, 5, 0, 1, 3);
    grid->addWidget(lSummaPonad150, 5, 3);
    grid->addWidget(leTaryfPonad150, 5, 4);
    grid->addWidget(lSummaDoSplatyPonad150, 5, 5);

    grid->addWidget(lPonad800, 6, 0, 1, 3);
    grid->addWidget(lSummaPonad800, 6, 3);
    grid->addWidget(leTaryfPonad800, 6, 4);
    grid->addWidget(lSummaDoSplatyPonad8000, 6, 5);

    grid->addWidget(bRozrahunok, 7, 0);
    grid->addWidget(lVsegoDosplaty, 7, 3, 1, 2);
    grid->addWidget(lVsego, 7, 5);

    grid->setSpacing(1);

    layout()->addItem(grid);

    // seting minimum size of the widget
    this->setMaximumSize(minimumSize());

    // setting fixed size of the widget
//    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // setting widget in the center of the window
    this->move(qApp->desktop()->availableGeometry(this).center()-this->rect().center());

    lPilgovi->setFrameStyle(QFrame::Box);
    lPonad800->setFrameStyle(QFrame::Box);
    lSummaPilgovi->setFrameStyle(QFrame::Box);
    lSummaPonad800->setFrameStyle(QFrame::Box);
    lSummaDoSplatyPilgovi->setFrameStyle(QFrame::Box);
    lSummaDoSplatyPonad8000->setFrameStyle(QFrame::Box);

    lDo150->setFrameStyle(QFrame::Box);
    lPonad150->setFrameStyle(QFrame::Box);

    lTaryfPilgovi->setFrameStyle(QFrame::Box);
    leTaryfPonad800->setStyleSheet("border: 1px solid black");

    lPotochni->setFrameStyle(QFrame::Box);
    lPoperedni->setFrameStyle(QFrame::Box);
    lSpozhyto->setFrameStyle(QFrame::Box);
    lSummaSpozhyto->setFrameStyle(QFrame::Box);
    lTaryf->setFrameStyle(QFrame::Box);
    lSummaDo150->setFrameStyle(QFrame::Box);
    lSummaPonad150->setFrameStyle(QFrame::Box);
    lSummaDoSplaty->setFrameStyle(QFrame::Box);
    lSummaDoSplatyDo150->setFrameStyle(QFrame::Box);
    lSummaDoSplatyPonad150->setFrameStyle(QFrame::Box);
    lVsego->setFrameStyle(QFrame::Box);
    lePoperedni->setStyleSheet("border: 1px solid black");
    lePotochni->setStyleSheet("border: 1px solid black");
    leTaryfDo150->setStyleSheet("border: 1px solid black");
    leTaryfPonad150->setStyleSheet("border: 1px solid black");

    // to explicitly call the destructor!!!
//    if (!testAttribute(Qt::WA_DeleteOnClose))
//        setAttribute(Qt::WA_DeleteOnClose, false);
    // false, not to give an error: "munmap_chunk(): invalid pointer"

    // check existing config file
    QFile fileOfSettings;

    if(!fileOfSettings.exists("Energy.ini"))
    {
        writeDefaultSettings();
        trayIcon->showMessage(QObject::trUtf8("FileOpenWarning"),
                              QObject::trUtf8("The config file Energy.ini does not exist\nIt was created with default settings"));
    }

    if(!settings.isWritable())
    {
        trayIcon->showMessage(QObject::trUtf8("FileOpenWarning"),
                              QObject::trUtf8("The config file Energy.ini is in read only mode\nIt can't be changed"),
                              QSystemTrayIcon::Warning);
    }

//    fileOfSettings.close();

    // reading data from config file
    readSettings();

    // reading history
    try{
        itsHistory = &xmlHistoryManager->readHistory();
    } catch (FileOpenException& e) {
        trayIcon->showMessage(QObject::trUtf8("FileOpenException"),
                              QObject::trUtf8(QString(e.message() + "\nIt will be created").toLatin1().data()));
    } catch (XmlReadException& e) {
        trayIcon->showMessage(QObject::trUtf8("XmlReadException"),
                              QObject::trUtf8(e.message().toLatin1().data()),
                              QSystemTrayIcon::Warning);
    }

    itsListIterator.toBack();

    bForward->setEnabled(false);
    if(itsHistory->size())
    {
        bBackward->setEnabled(true);
    }
    else
    {
        bBackward->setEnabled(false);
    }

    lePotochni->setFocus();

    QShortcut *returnShortcut = new QShortcut(QKeySequence("return"), this);
    QShortcut *enterShortcut = new QShortcut(QKeySequence("enter"), this);
    QShortcut* f1Shortcut = new QShortcut(QKeySequence("f1"), this);
    QShortcut* f2Shortcut = new QShortcut(QKeySequence("f2"), this);

    connect(returnShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(enterShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(f1Shortcut, SIGNAL(activated()), qApp, SLOT(aboutQt()));
    connect(f2Shortcut, SIGNAL(activated()), this, SLOT(selectLanguageDialog()));
    connect(languagePushButton, SIGNAL(clicked()), this, SLOT(selectLanguage()));

    connect(bRozrahunok, SIGNAL(clicked()), this, SLOT(onButtonRozrahunok()));

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    connect(bBackward, SIGNAL(clicked()), this, SLOT(backwardHistory()));
    connect(bForward, SIGNAL(clicked()), this, SLOT(forwardHistory()));
}

MainWindow::~MainWindow()
{
    writeSettings();
    try {
        xmlHistoryManager->writeHistory();
    } catch (FileOpenException& e) {
        QMessageBox::warning(this,
                             QObject::trUtf8("FileOpenException"),
                             QObject::trUtf8(QString(e.message() + "\nHistory wasn't writen").toLatin1().data()),
                             QMessageBox::Ok);
        exit(1);
    }

    delete xmlHistoryManager;
    delete itsHistory;
}

void MainWindow::onButtonRozrahunok()
{
    updateTime();
    timer->start(DATE_UPDATE_TIME);
    bForward->setEnabled(false);
    bBackward->setEnabled(true);
    rozrahunok.setPilga(lePilga->text().toInt());
    rozrahunok.setLimit(leLimit->text().toInt());
    rozrahunok.setTaryfDo150(leTaryfDo150->text().toFloat());
    rozrahunok.setTaryfPonad150(leTaryfPonad150->text().toFloat());
    rozrahunok.setTaryfPonad800(leTaryfPonad800->text().toDouble());
    rozrahunok.setPotochni(lePotochni->text().toInt());
    rozrahunok.setPoperedni(lePoperedni->text().toInt());
    lTaryfPilgovi->setText(QString::number(rozrahunok.taryfPilgovi(), 'f', 4));
    lSummaSpozhyto->setText(QString::number(rozrahunok.spozhyto()));
    lSummaPilgovi->setText(QString::number(rozrahunok.spozhytoPilgovi()));
    lSummaDo150->setText(QString::number(rozrahunok.spozhytoDo150()));
    lSummaPonad150->setText(QString::number(rozrahunok.spozhytoPonad150()));
    lSummaPonad800->setText(QString::number(rozrahunok.spozhytoPonad800()));
    lSummaDoSplatyPilgovi->setText(QString::number(rozrahunok.summaPilgovi(), 'f', 2));
    lSummaDoSplatyDo150->setText(QString::number(rozrahunok.summaDo150(), 'f', 2));
    lSummaDoSplatyPonad150->setText(QString::number(rozrahunok.summaPonad150(), 'f', 2));
    lSummaDoSplatyPonad8000->setText(QString::number(rozrahunok.summaPonad800(), 'f', 2));
    lVsego->setText(QString::number(rozrahunok.summaZagalna(), 'f', 2));

    writeHistory();
    itsListIterator.toBack();
}

void MainWindow::writeDefaultSettings()
{
    settings.clear();
    settings.setValue("Benefit", BENEFIT_PERCENT);
    settings.setValue("BenefitLimit", BENEFIT_LIMIT);
    /// That wasn't gibberish convering float to Qstring
    /* For int this don't needed */
    settings.setValue("TariffTo150", QString::number(TO_150_TARIFF));
    settings.setValue("TariffOver150", QString::number(OVER_150_TARIFF));
    settings.setValue("TariffOver800", QString::number(OVER_800_TARIFF));
    settings.setValue("HistoryLimit", HISTORY_LIMIT);
}

void MainWindow::writeSettings()
{
    settings.clear();
    settings.setValue("Benefit", lePilga->text());
    settings.setValue("BenefitLimit", leLimit->text());
    settings.setValue("TariffTo150", leTaryfDo150->text());
    settings.setValue("TariffOver150", leTaryfPonad150->text());
    settings.setValue("TariffOver800", leTaryfPonad800->text());
    settings.setValue("HistoryLimit", HISTORY_LIMIT);
}

void MainWindow::readSettings()
{
    lePilga->setText(settings.value("Benefit", BENEFIT_PERCENT).toString());
    leLimit->setText(settings.value("BenefitLimit", BENEFIT_LIMIT).toString());
    leTaryfDo150->setText(settings.value("TariffTo150", TO_150_TARIFF).toString());
    leTaryfPonad150->setText(settings.value("TariffOver150", OVER_150_TARIFF).toString());
    leTaryfPonad800->setText(settings.value("TariffOver800", OVER_800_TARIFF).toString());
    itsHistoryLimit = settings.value("HistoryLimit", HISTORY_LIMIT).toInt();
}

void MainWindow::writeHistory()
{
    QMap<QString, QString> map;

    map.insert("date", lDate->text());
    map.insert("benefit", lePilga->text());
    map.insert("limit", leLimit->text());
    map.insert("current", lePotochni->text());
    map.insert("previous", lePoperedni->text());
    map.insert("consumed", lSummaSpozhyto->text());
    map.insert("benefit_consumed", lSummaPilgovi->text());
    map.insert("to_150_consumed", lSummaDo150->text());
    map.insert("over_150_consumed", lSummaPonad150->text());
    map.insert("over_800_consumed", lSummaPonad800->text());
    map.insert("benefit_tariff", lTaryfPilgovi->text());
    map.insert("to_150_tariff", leTaryfDo150->text());
    map.insert("over_150_tariff", leTaryfPonad150->text());
    map.insert("over_800_tariff", leTaryfPonad800->text());
    map.insert("benefit_invoicing", lSummaDoSplatyPilgovi->text());
    map.insert("to_150_invoicing", lSummaDoSplatyDo150->text());
    map.insert("over_150_invoicing", lSummaDoSplatyPonad150->text());
    map.insert("over_800_invoicing", lSummaDoSplatyPonad8000->text());
    map.insert("invoicing", lVsego->text());

    while(itsHistory->size() >= itsHistoryLimit)
    {
        itsHistory->removeFirst();
    }
    itsHistory->append(map);
}

void MainWindow::setFromHistory(QMap<QString, QString> map)
{
    lDate->setText(map.value("date"));
    lePilga->setText(map.value("benefit"));
    leLimit->setText(map.value("limit"));
    lePotochni->setText(map.value("current"));
    lePoperedni->setText(map.value("previous"));
    lSummaSpozhyto->setText(map.value("consumed"));
    lSummaPilgovi->setText(map.value("benefit_consumed"));
    lSummaDo150->setText(map.value("to_150_consumed"));
    lSummaPonad150->setText(map.value("over_150_consumed"));
    lSummaPonad800->setText(map.value("over_800_consumed"));
    lTaryfPilgovi->setText(map.value("benefit_tariff"));
    leTaryfDo150->setText(map.value("to_150_tariff"));
    leTaryfPonad150->setText(map.value("over_150_tariff"));
    leTaryfPonad800->setText(map.value("over_800_tariff"));
    lSummaDoSplatyPilgovi->setText(map.value("benefit_invoicing"));
    lSummaDoSplatyDo150->setText(map.value("to_150_invoicing"));
    lSummaDoSplatyPonad150->setText(map.value("over_150_invoicing"));
    lSummaDoSplatyPonad8000->setText(map.value("over_800_invoicing"));
    lVsego->setText(map.value("invoicing"));
}

void MainWindow::updateTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QLocale locale;
    /// set the locale you want here
    switch(itsLanguage) {
    case 0: locale = QLocale(QLocale::English, QLocale::UnitedStates);
        break;
    case 1: locale = QLocale(QLocale::Ukrainian, QLocale::Ukraine);
        break;
    case 2: locale = QLocale(QLocale::Russian, QLocale::Russia);
        break;
    default: locale = QLocale(QLocale::Ukrainian, QLocale::Ukraine);
        break;
    }

    QString dateTimeString = locale.toString(dateTime, "ddd hh:mm:ss\ndd MMM yyyy");
//    lDate->setText(QDateTime::currentDateTime().toString("ddd hh:mm:ss\ndd MMM yyyy"));
    lDate->setText(dateTimeString);
}

void MainWindow::backwardHistory()
{
    timer->stop();
    bForward->setEnabled(true);
    setFromHistory(itsListIterator.previous());
    if(!itsListIterator.hasPrevious())
    {
        bBackward->setEnabled(false);
    }
}

void MainWindow::forwardHistory()
{
    timer->stop();
    bBackward->setEnabled(true);
    setFromHistory(itsListIterator.next());
    if(!itsListIterator.hasNext())
    {
        bForward->setEnabled(false);
    }
}

void MainWindow::selectLanguage()
{
    QTranslator translator;

    switch (languageComboBox->currentIndex()) {
    case 0: itsLanguage = 0;
        break;
    case 1: itsLanguage = 1;
        translator.load("mainwindow_ua.qm", ".");
        break;
    case 2: itsLanguage = 2;
        translator.load("mainwindow_ru.qm", ".");
        break;
    default: itsLanguage = 1;
        break;
    }

    languageDialog->close();

    qApp->installTranslator(&translator);
}

void MainWindow::selectLanguageDialog()
{
    languageDialog = new QDialog(this);
    languageComboBox = new QComboBox(languageDialog);
    languagePushButton = new QPushButton(QString::fromUtf8("OK"));

    QHBoxLayout* HLayout = new QHBoxLayout;
    HLayout->addWidget(languageComboBox);
    HLayout->addWidget(languagePushButton);
    languageDialog->setLayout(HLayout);

    QStringList list;
    list << QString::fromUtf8("English") << QString::fromUtf8("Українська") << QString::fromUtf8("Русский");
    languageComboBox->addItems(list);
    languageDialog->show();
}
