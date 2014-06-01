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

enum LANGUAGES
{
    ENGLISH,
    UKRAINIAN,
    RUSSIAN
};

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint),
        languageDialog(new QDialog()),
        languageComboBox(new QComboBox(languageDialog)),
        lBenefitLimit(new QLabel(this)),
        leBenefit(new QLineEdit(this)),
        leLimit(new QLineEdit(this)),
        bBackward(new QPushButton(this)),
        lDate(new QLabel(this)),
        bForward(new QPushButton(this)),
        lCurrent(new QLabel(this)),
        lPrevious(new QLabel(this)),
        lConsumed(new QLabel(this)),
        lAmountConsumed(new QLabel(this)),
        lTariff(new QLabel(this)),
        lAmountPayment(new QLabel(this)),
        lBenefit(new QLabel(this)),
        lTo150(new QLabel(this)),
        lOver150(new QLabel(this)),
        lOver800(new QLabel(this)),
        lAmountBenefit(new QLabel(this)),
        lTariffBenefit(new QLabel(this)),
        lAmountTo150(new QLabel(this)),
        lAmountOver150(new QLabel(this)),
        lAmountOver800(new QLabel(this)),
        lAmountPaymentBenefit(new QLabel(this)),
        lAmountPaymentTo150(new QLabel(this)),
        lAmountPaymentOver150(new QLabel(this)),
        lAmountPaymentOver800(new QLabel(this)),
        lTotalPayment(new QLabel(this)),
        lTotal(new QLabel(this)),

        leCurrent(new QLineEdit(this)),
        lePrevious(new QLineEdit(this)),
        leTariffTo150(new QLineEdit(this)),
        leTariffOver150(new QLineEdit(this)),
        leTariffOver800(new QLineEdit(this)),

        bPayment(new QPushButton(this)),

        timer(new QTimer(this)),

        settings("EnergyPro.ini", QSettings::IniFormat),

        itsHistory(new QList<QMap<QString, QString> >()),

        itsListIterator(*itsHistory)
{
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);

    /// check existing config file
    QFile fileOfSettings;

    if(!fileOfSettings.exists("EnergyPro.ini"))
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

    /// reading data from config file
    readSettings();

    xmlHistoryManager = new XmlHistoryManager("history.xml", *itsHistory);

    /// reading history
    try{
        itsHistory = &xmlHistoryManager->readHistory();
    } catch (FileOpenException& e) {
        trayIcon->showMessage("FileOpenException",
                              e.message() + "\nIt will be created");
    } catch (XmlReadException& e) {
        trayIcon->showMessage("XmlReadException",
                              e.message(),
                              QSystemTrayIcon::Warning);
    }

    updateWidgetText();
    setupLanguageDialog();
    updateDialogText();

    trayIcon->setIcon(QPixmap(":/EnergyIcon.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage(QObject::trUtf8("Calculation of electricity"),
                          QObject::trUtf8("Program \"Calculation of electricity\" is running!"));
    trayIcon->show();

    bBackward->setIcon(QIcon(":/left.png"));
    bForward->setIcon(QIcon(":/right.png"));

    lCurrent->setAlignment(Qt::AlignCenter);
    lCurrent->setMargin(4);
    lPrevious->setAlignment(Qt::AlignCenter);
    lPrevious->setMargin(4);
    lConsumed->setAlignment(Qt::AlignCenter);
    lConsumed->setMargin(4);
    lTariff->setAlignment(Qt::AlignCenter);
    lTariff->setMargin(4);
    lAmountPayment->setAlignment(Qt::AlignCenter);
    lAmountPayment->setMargin(4);
    lTotalPayment->setAlignment(Qt::AlignRight);
    lTotalPayment->setMargin(4);

    lDate->setAlignment(Qt::AlignCenter);

    lBenefit->setMargin(4);
    lTo150->setMargin(4);
    lOver150->setMargin(4);
    lOver800->setMargin(4);

    leTariffTo150->setTextMargins(2, 2, 2, 2);
    leTariffOver150->setTextMargins(2, 2, 2, 2);
    leTariffOver800->setTextMargins(2, 2, 2, 2);

    updateTime();
    timer->start(DATE_UPDATE_TIME);

    setLayout(new QGridLayout(this));

    QHBoxLayout *hist = new QHBoxLayout;
    hist->addWidget(bBackward);
    hist->addWidget(lDate);
    hist->addWidget(bForward);
    hist->setSpacing(4);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(lBenefitLimit, 0, 0);
    grid->addWidget(leBenefit, 0, 1);
    grid->addWidget(leLimit, 0, 2);
    grid->addItem(hist, 0, 4, 1, 2);

    grid->addWidget(lCurrent, 1, 0);
    grid->addWidget(lPrevious, 1, 1, 1, 2);
    grid->addWidget(lConsumed, 1, 3);
    grid->addWidget(lTariff, 1, 4, 2, 1);
    grid->addWidget(lAmountPayment, 1, 5, 2, 1);

    grid->addWidget(leCurrent, 2, 0);
    grid->addWidget(lePrevious, 2, 1, 1, 2);
    grid->addWidget(lAmountConsumed, 2, 3);

    grid->addWidget(lBenefit, 3, 0, 1, 3);
    grid->addWidget(lAmountBenefit, 3, 3);
    grid->addWidget(lTariffBenefit, 3, 4);
    grid->addWidget(lAmountPaymentBenefit, 3, 5);

    grid->addWidget(lTo150, 4, 0, 1, 3);
    grid->addWidget(lAmountTo150, 4, 3);
    grid->addWidget(leTariffTo150, 4, 4);
    grid->addWidget(lAmountPaymentTo150, 4, 5);

    grid->addWidget(lOver150, 5, 0, 1, 3);
    grid->addWidget(lAmountOver150, 5, 3);
    grid->addWidget(leTariffOver150, 5, 4);
    grid->addWidget(lAmountPaymentOver150, 5, 5);

    grid->addWidget(lOver800, 6, 0, 1, 3);
    grid->addWidget(lAmountOver800, 6, 3);
    grid->addWidget(leTariffOver800, 6, 4);
    grid->addWidget(lAmountPaymentOver800, 6, 5);

    grid->addWidget(bPayment, 7, 0);
    grid->addWidget(lTotalPayment, 7, 3, 1, 2);
    grid->addWidget(lTotal, 7, 5);

    grid->setSpacing(1);

    layout()->addItem(grid);

    lBenefit->setFrameStyle(QFrame::Box);
    lOver800->setFrameStyle(QFrame::Box);
    lAmountBenefit->setFrameStyle(QFrame::Box);
    lAmountOver800->setFrameStyle(QFrame::Box);
    lAmountPaymentBenefit->setFrameStyle(QFrame::Box);
    lAmountPaymentOver800->setFrameStyle(QFrame::Box);

    lTo150->setFrameStyle(QFrame::Box);
    lOver150->setFrameStyle(QFrame::Box);

    lTariffBenefit->setFrameStyle(QFrame::Box);
    leTariffOver800->setStyleSheet("border: 1px solid black");

    lCurrent->setFrameStyle(QFrame::Box);
    lPrevious->setFrameStyle(QFrame::Box);
    lConsumed->setFrameStyle(QFrame::Box);
    lAmountConsumed->setFrameStyle(QFrame::Box);
    lTariff->setFrameStyle(QFrame::Box);
    lAmountTo150->setFrameStyle(QFrame::Box);
    lAmountOver150->setFrameStyle(QFrame::Box);
    lAmountPayment->setFrameStyle(QFrame::Box);
    lAmountPaymentTo150->setFrameStyle(QFrame::Box);
    lAmountPaymentOver150->setFrameStyle(QFrame::Box);
    lTotal->setFrameStyle(QFrame::Box);
    lePrevious->setStyleSheet("border: 1px solid black");
    leCurrent->setStyleSheet("border: 1px solid black");
    leTariffTo150->setStyleSheet("border: 1px solid black");
    leTariffOver150->setStyleSheet("border: 1px solid black");

    /// seting minimum size of the widget
//    this->setMinimumWidth(503);
//    this->setMinimumHeight(224);
    this->setMaximumSize(minimumSize());

    /// setting widget in the center of the desktop
    this->move(qApp->desktop()->availableGeometry(this).center() - this->rect().center());

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

    leCurrent->setFocus();

    QShortcut *returnShortcut = new QShortcut(QKeySequence("return"), this);
    QShortcut *enterShortcut = new QShortcut(QKeySequence("enter"), this);
    QShortcut* f1Shortcut = new QShortcut(QKeySequence("f1"), this);
    QShortcut* f2Shortcut = new QShortcut(QKeySequence("f2"), this);

    connect(returnShortcut, SIGNAL(activated()), this, SLOT(onButtonPayment()));
    connect(enterShortcut, SIGNAL(activated()), this, SLOT(onButtonPayment()));
    connect(bPayment, SIGNAL(clicked()), this, SLOT(onButtonPayment()));

    connect(f1Shortcut, SIGNAL(activated()), qApp, SLOT(aboutQt()));
    connect(f2Shortcut, SIGNAL(activated()), languageDialog, SLOT(show()));

    connect(languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectLanguage(int)));
    connect(languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setupTime(int)));
    connect(languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateWidgetText()));
    connect(languageComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDialogText()));

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
                             "FileOpenException",
                             e.message() + "\nHistory wasn't writen",
                             QMessageBox::Ok);
        exit(1);
    }

    delete xmlHistoryManager;
    delete itsHistory;
}

void MainWindow::onButtonPayment()
{
    updateTime();
    timer->start(DATE_UPDATE_TIME);
    bForward->setEnabled(false);
    bBackward->setEnabled(true);
    payment.setBenefit(leBenefit->text().toInt());
    payment.setLimit(leLimit->text().toInt());
    payment.setTariffTo150(leTariffTo150->text().toFloat());
    payment.setTariffOver150(leTariffOver150->text().toFloat());
    payment.setTariffOver800(leTariffOver800->text().toDouble());
    payment.setCurrent(leCurrent->text().toInt());
    payment.setPrevious(lePrevious->text().toInt());
    lTariffBenefit->setText(QString::number(payment.tariffBenefit(), 'f', 4));
    lAmountConsumed->setText(QString::number(payment.consumed()));
    lAmountBenefit->setText(QString::number(payment.consumedBenefit()));
    lAmountTo150->setText(QString::number(payment.consumedTo150()));
    lAmountOver150->setText(QString::number(payment.consumedOver150()));
    lAmountOver800->setText(QString::number(payment.consumedOver800()));
    lAmountPaymentBenefit->setText(QString::number(payment.amountBenefit(), 'f', 2));
    lAmountPaymentTo150->setText(QString::number(payment.amountTo150(), 'f', 2));
    lAmountPaymentOver150->setText(QString::number(payment.amountOver150(), 'f', 2));
    lAmountPaymentOver800->setText(QString::number(payment.amountOver800(), 'f', 2));
    lTotal->setText(QString::number(payment.amountTotal(), 'f', 2));

    writeHistory();
    itsListIterator.toBack();
}

void MainWindow::writeDefaultSettings()
{
    settings.clear();
    settings.setValue("Langauge", 1);
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
    settings.setValue("Language", languageComboBox->currentIndex());
    settings.setValue("Benefit", leBenefit->text());
    settings.setValue("BenefitLimit", leLimit->text());
    settings.setValue("TariffTo150", leTariffTo150->text());
    settings.setValue("TariffOver150", leTariffOver150->text());
    settings.setValue("TariffOver800", leTariffOver800->text());
    settings.setValue("HistoryLimit", HISTORY_LIMIT);
}

void MainWindow::readSettings()
{
    setupTime(settings.value("Language", 1).toInt());
    selectLanguage(settings.value("Language", 1).toInt());
    leBenefit->setText(settings.value("Benefit", BENEFIT_PERCENT).toString());
    leLimit->setText(settings.value("BenefitLimit", BENEFIT_LIMIT).toString());
    leTariffTo150->setText(settings.value("TariffTo150", TO_150_TARIFF).toString());
    leTariffOver150->setText(settings.value("TariffOver150", OVER_150_TARIFF).toString());
    leTariffOver800->setText(settings.value("TariffOver800", OVER_800_TARIFF).toString());
    itsHistoryLimit = settings.value("HistoryLimit", HISTORY_LIMIT).toInt();
}

void MainWindow::writeHistory()
{
    QMap<QString, QString> map;

    map.insert("date", lDate->text());
    map.insert("benefit", leBenefit->text());
    map.insert("limit", leLimit->text());
    map.insert("current", leCurrent->text());
    map.insert("previous", lePrevious->text());
    map.insert("consumed", lAmountConsumed->text());
    map.insert("benefit_consumed", lAmountBenefit->text());
    map.insert("to_150_consumed", lAmountTo150->text());
    map.insert("over_150_consumed", lAmountOver150->text());
    map.insert("over_800_consumed", lAmountOver800->text());
    map.insert("benefit_tariff", lTariffBenefit->text());
    map.insert("to_150_tariff", leTariffTo150->text());
    map.insert("over_150_tariff", leTariffOver150->text());
    map.insert("over_800_tariff", leTariffOver800->text());
    map.insert("benefit_invoicing", lAmountPaymentBenefit->text());
    map.insert("to_150_invoicing", lAmountPaymentTo150->text());
    map.insert("over_150_invoicing", lAmountPaymentOver150->text());
    map.insert("over_800_invoicing", lAmountPaymentOver800->text());
    map.insert("invoicing", lTotal->text());

    while(itsHistory->size() >= itsHistoryLimit)
    {
        itsHistory->removeFirst();
    }
    itsHistory->append(map);
}

void MainWindow::setFromHistory(QMap<QString, QString> map)
{
    lDate->setText(map.value("date"));
    leBenefit->setText(map.value("benefit"));
    leLimit->setText(map.value("limit"));
    leCurrent->setText(map.value("current"));
    lePrevious->setText(map.value("previous"));
    lAmountConsumed->setText(map.value("consumed"));
    lAmountBenefit->setText(map.value("benefit_consumed"));
    lAmountTo150->setText(map.value("to_150_consumed"));
    lAmountOver150->setText(map.value("over_150_consumed"));
    lAmountOver800->setText(map.value("over_800_consumed"));
    lTariffBenefit->setText(map.value("benefit_tariff"));
    leTariffTo150->setText(map.value("to_150_tariff"));
    leTariffOver150->setText(map.value("over_150_tariff"));
    leTariffOver800->setText(map.value("over_800_tariff"));
    lAmountPaymentBenefit->setText(map.value("benefit_invoicing"));
    lAmountPaymentTo150->setText(map.value("to_150_invoicing"));
    lAmountPaymentOver150->setText(map.value("over_150_invoicing"));
    lAmountPaymentOver800->setText(map.value("over_800_invoicing"));
    lTotal->setText(map.value("invoicing"));
}

void MainWindow::setupTime(int language)
{
    /// set the locale you want here
    switch(language) {
    case ENGLISH: locale = QLocale(QLocale::English, QLocale::UnitedStates);
        break;
    case UKRAINIAN: locale = QLocale(QLocale::Ukrainian, QLocale::Ukraine);
        break;
    case RUSSIAN: locale = QLocale(QLocale::Russian, QLocale::RussianFederation);
        break;
    default: locale = QLocale(QLocale::Ukrainian, QLocale::Ukraine);
        break;
    }

    updateTime();
}

void MainWindow::updateTime()
{
    lDate->setText(locale.toString(QDateTime::currentDateTime(), "ddd hh:mm:ss\ndd MMM yyyy"));
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

void MainWindow::selectLanguage(int language)
{
    switch (language) {
    /// text in English
    case ENGLISH: translator.load("");
        break;
    /// text in Ukrainian
    case UKRAINIAN: translator.load("mainwindow_ua.qm", ".");
        break;
    /// text in Russian
    case RUSSIAN: translator.load("mainwindow_ru.qm", ".");
        break;
    default:
    /// text in Ukrainian
        translator.load("mainwindow_ua.qm", ".");
        break;
    }

    qApp->installTranslator(&translator);
}

void MainWindow::updateWidgetText()
{
    lBenefitLimit->setText(QObject::trUtf8("Benefit(%), limit (kWh)"));
    lCurrent->setText(QObject::trUtf8("Current readings, kWh"));
    lPrevious->setText(QObject::trUtf8("Previous\nreadings, kWh"));
    lConsumed->setText(QObject::trUtf8("Consumed, kWh"));
    lTariff->setText(QObject::trUtf8("\nTariff, UAH\n"));
    lAmountPayment->setText(QObject::trUtf8("Payment\namount, UAH"));
    lBenefit->setText(QObject::trUtf8("Benefits, kWh"));
    lTo150->setText(QObject::trUtf8("to 150/250 kWh"));
    lOver150->setText(QObject::trUtf8("from 150/250 to 800 kWh"));
    lOver800->setText(QObject::trUtf8("over 800 kWh"));
    lTotalPayment->setText(QObject::trUtf8("Total to pay, UAH"));
    bPayment->setText(QObject::trUtf8("Calculation"));
    this->setWindowTitle(QObject::trUtf8("Calculation of electricity"));
}

void MainWindow::updateDialogText()
{
    languageDialog->setWindowTitle(QObject::trUtf8("Language Selection"));
}

void MainWindow::setupLanguageDialog()
{
    languageDialog->setModal(true);
    /// set only close button
    languageDialog->setWindowFlags(Qt::WindowCloseButtonHint);

    QHBoxLayout* HLayout = new QHBoxLayout;
    HLayout->addWidget(languageComboBox);
    languageDialog->setLayout(HLayout);

    QStringList list;
    list << QString::fromUtf8("English") << QString::fromUtf8("Українська") << QString::fromUtf8("Русский");
    languageComboBox->addItems(list);

    /// seting minimum size of the dialog
    languageDialog->setMinimumWidth(250);
    languageDialog->setMinimumHeight(50);
    languageDialog->setMaximumSize(minimumSize());

    switch (locale.language()) {
    case QLocale::English: languageComboBox->setCurrentIndex(ENGLISH);
        break;
    case QLocale::Ukrainian: languageComboBox->setCurrentIndex(UKRAINIAN);
        break;
    case QLocale::Russian: languageComboBox->setCurrentIndex(RUSSIAN);
        break;
    default: languageComboBox->setCurrentIndex(UKRAINIAN);
        break;
    }

    /// setting languageDialog in the center of the widget
    languageDialog->move(qApp->desktop()->availableGeometry(this).center());
}
