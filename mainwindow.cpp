#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QShortcut>
#include <QDesktopWidget>
#include <QApplication>
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent, Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint),
        lPilga(new QLabel(QString::fromUtf8("Пiльга(%), лiмiт (кВтг)"), this)),
        lePilga(new QLineEdit(this)),
        leLimit(new QLineEdit(this)),
        lPotochni(new QLabel(QString::fromUtf8("Поточнi показання, кВтг"), this)),
        lPoperedni(new QLabel(QString::fromUtf8("Попереднi\nпоказання, кВтг"), this)),
        lSpozhyto(new QLabel(QString::fromUtf8("Спожито, Втг"), this)),
        lSummaSpozhyto(new QLabel(this)),
        lTaryf(new QLabel(QString::fromUtf8("\nТариф, грн\n"), this)),
        lSummaDoSplaty(new QLabel(QString::fromUtf8("Сумма до\nсплати, грн"), this)),
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
//        leTaryfPilgovi(new QLineEdit(this)),
        leTaryfDo150(new QLineEdit(this)),
        leTaryfPonad150(new QLineEdit(this)),
        leTaryfPonad800(new QLineEdit(this)),

        bRozrahunok(new QPushButton(QString::fromUtf8("Розрахунок"), this)),

        settings("Energy.ini", QSettings::IniFormat)
{
    this->setWindowTitle(QString::fromUtf8("Розрахунок електроенергії"));
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QPixmap(":/EnergyIcon.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage(QString::fromUtf8("Розрахунок електроенергії"),
                          QString::fromUtf8("Програма \"Розрахунок електроенергії\" запущена!"));
    trayIcon->show();

    lPotochni->setAlignment(Qt::AlignCenter);
    lPoperedni->setAlignment(Qt::AlignCenter);
    lSpozhyto->setAlignment(Qt::AlignCenter);
    lTaryf->setAlignment(Qt::AlignCenter);
    lSummaDoSplaty->setAlignment(Qt::AlignCenter);

    setLayout(new QVBoxLayout(this));

    QHBoxLayout *horUpUp = new QHBoxLayout;
    horUpUp->addWidget(lPilga, 0, Qt::AlignLeft);
    horUpUp->addWidget(lePilga, 0, Qt::AlignLeft);
    horUpUp->addWidget(leLimit, 0, Qt::AlignLeft);
    horUpUp->addItem(new QSpacerItem(171, sizeHint().height()));
    horUpUp->setSpacing(5);

    QVBoxLayout *vertPot = new QVBoxLayout;
    vertPot->addWidget(lPotochni, 0, Qt::AlignLeft);
    vertPot->addWidget(lePotochni, 0, Qt::AlignLeft);
    vertPot->setSpacing(5);    

    QVBoxLayout *vertPop = new QVBoxLayout;
    vertPop->addWidget(lPoperedni, 0, Qt::AlignLeft);
    vertPop->addWidget(lePoperedni, 0, Qt::AlignLeft);
    vertPop->setSpacing(5);

    QVBoxLayout *vertSpo = new QVBoxLayout;
    vertSpo->addWidget(lSpozhyto, 0, Qt::AlignLeft);
    vertSpo->addWidget(lSummaSpozhyto, 0, Qt::AlignLeft);
    vertSpo->setSpacing(5);

    QHBoxLayout *horUp = new QHBoxLayout;
    horUp->addItem(vertPot);
    horUp->addItem(vertPop);
    horUp->addItem(vertSpo);
    horUp->addWidget(lTaryf, 0, Qt::AlignLeft);
    horUp->addWidget(lSummaDoSplaty, 0, Qt::AlignLeft);
    horUp->setSpacing(5);

    QHBoxLayout *horMidUpUp = new QHBoxLayout;
    horMidUpUp->addWidget(lPilgovi, 0, Qt::AlignLeft);
    horMidUpUp->addWidget(lSummaPilgovi, 0, Qt::AlignLeft);
    horMidUpUp->addWidget(lTaryfPilgovi, 0, Qt::AlignLeft);
    horMidUpUp->addWidget(lSummaDoSplatyPilgovi, 0, Qt::AlignLeft);
    horMidUpUp->setSpacing(5);

    QHBoxLayout *horMidUp = new QHBoxLayout;    
    horMidUp->addWidget(lDo150, 0, Qt::AlignLeft);
    horMidUp->addWidget(lSummaDo150, 0, Qt::AlignLeft);
    horMidUp->addWidget(leTaryfDo150, 0, Qt::AlignLeft);
    horMidUp->addWidget(lSummaDoSplatyDo150, 0, Qt::AlignLeft);
    horMidUp->setSpacing(5);

    QHBoxLayout *horMidDown = new QHBoxLayout;
    horMidDown->addWidget(lPonad150, 0, Qt::AlignLeft);
    horMidDown->addWidget(lSummaPonad150, 0, Qt::AlignLeft);
    horMidDown->addWidget(leTaryfPonad150, 0, Qt::AlignLeft);
    horMidDown->addWidget(lSummaDoSplatyPonad150, 0, Qt::AlignLeft);
    horMidDown->setSpacing(5);

    QHBoxLayout *horMidDownDown = new QHBoxLayout;
    horMidDownDown->addWidget(lPonad800, 0, Qt::AlignLeft);
    horMidDownDown->addWidget(lSummaPonad800, 0, Qt::AlignLeft);
    horMidDownDown->addWidget(leTaryfPonad800, 0, Qt::AlignLeft);
    horMidDownDown->addWidget(lSummaDoSplatyPonad8000, 0, Qt::AlignLeft);
    horMidDownDown->setSpacing(5);

    QHBoxLayout *horDown = new QHBoxLayout;
    horDown->addWidget(bRozrahunok, 0, Qt::AlignLeft);
    horDown->addItem(new QSpacerItem(190, sizeHint().height()));
    horDown->addWidget(lVsegoDosplaty, 0, Qt::AlignRight);
    horDown->addWidget(lVsego, 0, Qt::AlignRight);
    horDown->setSpacing(5);

    layout()->addItem(horUpUp);
    layout()->addItem(horUp);
    layout()->addItem(horMidUpUp);
    layout()->addItem(horMidUp);
    layout()->addItem(horMidDown);
    layout()->addItem(horMidDownDown);
    layout()->addItem(horDown);    
    layout()->setSpacing(5);

    // делает окно фиксированного размера
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // делаю так, чтобы форма появлялась в центре экрана
    this->move(qApp->desktop()->availableGeometry(this).center()-this->rect().center());

    lPilga->setMinimumWidth(135);
    lPilga->setMaximumWidth(135);
    lePilga->setMinimumWidth(95);
    lePilga->setMaximumWidth(95);
    leLimit->setMinimumWidth(76);
    leLimit->setMaximumWidth(76);

    lePotochni->setMaximumWidth(135);
    lePotochni->setMinimumWidth(135);
    lePoperedni->setMaximumWidth(95);
    lSummaSpozhyto->setMaximumWidth(76);
    lSummaSpozhyto->setMinimumWidth(76);
    lDo150->setMinimumWidth(235);
    lDo150->setMaximumWidth(235);
    lPonad150->setMinimumWidth(235);
    lPonad150->setMaximumWidth(235);
    lSummaDo150->setMinimumWidth(76);
    lSummaPonad150->setMinimumWidth(76);
    leTaryfDo150->setMaximumWidth(85);
    leTaryfPonad150->setMaximumWidth(85);
    lSummaDoSplatyDo150->setMinimumWidth(90);
    lSummaDoSplatyPonad150->setMinimumWidth(90);
    lVsego->setMinimumWidth(90);

    lPilgovi->setMinimumWidth(235);
    lPilgovi->setMaximumWidth(235);
    lPonad800->setMinimumWidth(235);
    lPonad800->setMaximumWidth(235);
    lPotochni->setMinimumWidth(135);
    lPotochni->setMaximumWidth(135);
    lPoperedni->setMinimumWidth(95);
    lPoperedni->setMaximumWidth(95);
    lSpozhyto->setMinimumWidth(76);
    lSpozhyto->setMaximumWidth(76);
    lSummaPilgovi->setMinimumWidth(76);
    lSummaPilgovi->setMaximumWidth(76);
    lSummaPonad800->setMinimumWidth(76);
    lSummaPonad800->setMaximumWidth(76);
    lTaryf->setMinimumWidth(85);
    lTaryf->setMaximumWidth(85);
    lTaryfPilgovi->setMinimumWidth(85);
    lTaryfPilgovi->setMaximumWidth(85);
    leTaryfPonad800->setMinimumWidth(85);
    leTaryfPonad800->setMaximumWidth(85);
    lSummaDoSplaty->setMinimumWidth(90);
    lSummaDoSplaty->setMaximumWidth(90);
    lSummaDoSplatyPilgovi->setMinimumWidth(90);
    lSummaDoSplatyPilgovi->setMaximumWidth(90);
    lSummaDoSplatyPonad8000->setMinimumWidth(90);
    lSummaDoSplatyPonad8000->setMaximumWidth(90);

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

    // чтобы вызывался деструктор явно!!!
    if (!testAttribute(Qt::WA_DeleteOnClose))
        setAttribute(Qt::WA_DeleteOnClose, false);
    // false, чтобы не выдавало ошибку munmap_chunk(): invalid pointer

    // проверяю наличие файла конфигурации
    QFile fileOfSettings;
    if(!fileOfSettings.exists("Energy.ini"))
    {
        writeDefaultSettings();
    }

    // чтение данных из файла
    readSettings();    

    QShortcut *returnShortcut = new QShortcut(QKeySequence("return"), this);
    QShortcut *enterShortcut = new QShortcut(QKeySequence("enter"), this);

    connect(returnShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(enterShortcut, SIGNAL(activated()), this, SLOT(onButtonRozrahunok()));
    connect(bRozrahunok, SIGNAL(clicked()), this, SLOT(onButtonRozrahunok()));
}

MainWindow::~MainWindow()
{
    writeSettings();    
}

void MainWindow::onButtonRozrahunok()
{    
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
