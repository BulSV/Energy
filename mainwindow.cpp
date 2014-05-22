#include <QGridLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QShortcut>
#include <QDesktopWidget>
#include <QApplication>
#include <QSystemTrayIcon>
#include <QDateTime>
#include <QTimer>
#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint),
        lPilga(new QLabel(QString::fromUtf8("Пiльга(%), лiмiт (кВтг)"), this)),
        lePilga(new QLineEdit(this)),
        leLimit(new QLineEdit(this)),
        bBackward(new QPushButton(this)),
        lDate(new QLabel(this)),
        bForward(new QPushButton(this)),
        lPotochni(new QLabel(QString::fromUtf8("Поточнi показання, кВтг"), this)),
        lPoperedni(new QLabel(QString::fromUtf8("Попереднi\nпоказання, кВтг"), this)),
        lSpozhyto(new QLabel(QString::fromUtf8("Спожито, кВтг"), this)),
        lSummaSpozhyto(new QLabel(this)),
        lTaryf(new QLabel(QString::fromUtf8("\nТариф, грн\n"), this)),
        lSummaDoSplaty(new QLabel(QString::fromUtf8("Сума до\nсплати, грн"), this)),
        lPilgovi(new QLabel(QString::fromUtf8("пiльговi, кВтг"), this)),
        lDo150(new QLabel(QString::fromUtf8("до 150/250 кВтг"), this)),
        lPonad150(new QLabel(QString::fromUtf8("вiд 150/250 кВтг до 800 кВтг"), this)),
        lPonad800(new QLabel(QString::fromUtf8("понад 800 кВтг"), this)),
        lSummaPilgovi(new QLabel(this)),
        lTaryfPilgovi(new QLabel(this)),
        lSummaDo150(new QLabel(this)),
        lSummaPonad150(new QLabel(this)),
        lSummaPonad800(new QLabel(this)),
        lSummaDoSplatyPilgovi(new QLabel(this)),
        lSummaDoSplatyDo150(new QLabel(this)),
        lSummaDoSplatyPonad150(new QLabel(this)),
        lSummaDoSplatyPonad8000(new QLabel(this)),
        lVsegoDosplaty(new QLabel(QString::fromUtf8("Усього до сплати, грн"), this)),
        lVsego(new QLabel(this)),

        lePotochni(new QLineEdit(this)),
        lePoperedni(new QLineEdit(this)),
        leTaryfDo150(new QLineEdit(this)),
        leTaryfPonad150(new QLineEdit(this)),
        leTaryfPonad800(new QLineEdit(this)),

        bRozrahunok(new QPushButton(QString::fromUtf8("Розрахунок"), this)),

//        xmlHistoryManager(new XmlHistoryManager("history.xml", itsHistory)),

        timer(new QTimer(this)),

        settings("Energy.ini", QSettings::IniFormat),

        itsHistory(QList<QMap<QString, QString> >()),

        itsListIterator(itsHistory)
{
    qDebug() << "Constructor";
    xmlHistoryManager = new XmlHistoryManager("history.xml", itsHistory);
    this->setWindowTitle(QString::fromUtf8("Розрахунок електроенергії"));

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QPixmap(":/EnergyIcon.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage(QString::fromUtf8("Розрахунок електроенергії"),
                          QString::fromUtf8("Програма \"Розрахунок електроенергії\" запущена!"));
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

    timer->start(1000);

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
    }

    // reading data from config file
    readSettings();

    qDebug() << "reading history...";
    // reading history
    try{
        qDebug() << "in try-catch";
        itsHistory = xmlHistoryManager->readHistory();
    } catch (FileOpenException &e) {
        qDebug() << "!!!" << e.message();
    } catch (XmlReadException &e) {
        qDebug() << "!!!" << e.message();
    } catch (...) {
        qDebug() << "read history faild";
        exit(-1);
    }

    qDebug() << "read history succsess";

    for(int i = 0; i < itsHistory.size(); ++i)
    {
        qDebug() << itsHistory.at(i);
    }

    // settin up list iterator
//    itsListIterator = itsHistory;

    lePotochni->setFocus();

    QShortcut *returnShortcut = new QShortcut(QKeySequence("return"), this);
    QShortcut *enterShortcut = new QShortcut(QKeySequence("enter"), this);

    connect(returnShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(enterShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(bRozrahunok, SIGNAL(clicked()), this, SLOT(onButtonRozrahunok()));

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    connect(bBackward, SIGNAL(clicked()), this, SLOT(backwardHistory()));
    connect(bForward, SIGNAL(clicked()), this, SLOT(forwardHistory()));
}

MainWindow::~MainWindow()
{
    writeSettings();
    xmlHistoryManager->writeHistory();
}

void MainWindow::onButtonRozrahunok()
{
    updateTime();
    timer->start(1000);
    itsListIterator.toBack();
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
}

void MainWindow::writeDefaultSettings()
{
    settings.clear();
    settings.setValue("Pilga", 0);
    settings.setValue("Limit", 0);
    settings.setValue("TaryfDo150", 0.2802);
    settings.setValue("TaryfPonad150", 0.3648);
    settings.setValue("TaryfPonad800", 0.9576);
}

void MainWindow::writeSettings()
{
    settings.clear();
    settings.setValue("Pilga", lePilga->text());
    settings.setValue("Limit", leLimit->text());
    settings.setValue("TaryfDo150", leTaryfDo150->text());
    settings.setValue("TaryfPonad150", leTaryfPonad150->text());
    settings.setValue("TaryfPonad800", leTaryfPonad800->text());
}

void MainWindow::readSettings()
{
    lePilga->setText(settings.value("Pilga", 0).toString());
    leLimit->setText(settings.value("Limit", 0).toString());
    leTaryfDo150->setText(settings.value("TaryfDo150", 0).toString());
    leTaryfPonad150->setText(settings.value("TaryfPonad150", 0).toString());
    leTaryfPonad800->setText(settings.value("TaryfPonad800", 0).toString());
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

    itsHistory.append(map);
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
    lDate->setText(QDateTime::currentDateTime().toString());
}

void MainWindow::backwardHistory()
{
    timer->stop();
    setFromHistory(itsListIterator.previous());
}

void MainWindow::forwardHistory()
{
    timer->stop();
    setFromHistory(itsListIterator.next());
}
