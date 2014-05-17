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
        lPotochni(new QLabel(QString::fromUtf8("Поточнi\nпоказ., кВтг"), this)),
        lPoperedni(new QLabel(QString::fromUtf8("Попереднi\nпоказ., кВтг"), this)),
        lSpozhyto(new QLabel(QString::fromUtf8("Спожито,\nкВтг"), this)),
        lSummaSpozhyto(new QLabel(this)),
        lTaryf(new QLabel(QString::fromUtf8("\nТариф, грн\n"), this)),
        lSummaDoSplaty(new QLabel(QString::fromUtf8("Сумма до\nсплати, грн"), this)),
        lDo150(new QLabel(QString::fromUtf8("до 150/250 кВтг....................."), this)),
        lPonad150(new QLabel(QString::fromUtf8("понад 150/250 кВтг..............."), this)),
        lSummaDo150(new QLabel(this)),
        lSummaPonad150(new QLabel(this)),
        lSummaDoSplatyDo150(new QLabel(this)),
        lSummaDoSplatyPonad150(new QLabel(this)),
        lVsegoDosplaty(new QLabel(QString::fromUtf8("Всього до сплати, грн"), this)),
        lVsego(new QLabel(this)),

        lePotochni(new QLineEdit(this)),
        lePoperedni(new QLineEdit(this)),
        leTaryfDo150(new QLineEdit(this)),
        leTaryfPonad150(new QLineEdit(this)),

        bRozrahunok(new QPushButton(QString::fromUtf8("Розрахунок"), this)),

        settings("Energy.ini", QSettings::IniFormat)
{
    this->setWindowTitle(QString::fromUtf8("Розрахунок електроенергії"));
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QPixmap(":/EnergyIcon.png"));
    trayIcon->setVisible(true);
    trayIcon->showMessage(QString::fromUtf8("Расчёт электроэнергии"),
                          QString::fromUtf8("Программа \"Расчёт электроэнергии\" запущена!"));
    trayIcon->show();

    setLayout(new QVBoxLayout(this));

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

    QHBoxLayout *horDown = new QHBoxLayout;
    horDown->addWidget(bRozrahunok, 0, Qt::AlignLeft);
    horDown->addItem(new QSpacerItem(110, sizeHint().height()));
    horDown->addWidget(lVsegoDosplaty, 0, Qt::AlignRight);
    horDown->addWidget(lVsego, 0, Qt::AlignRight);
    horDown->setSpacing(5);

    layout()->addItem(horUp);
    layout()->addItem(horMidUp);
    layout()->addItem(horMidDown);
    layout()->addItem(horDown);
    layout()->setSpacing(5);

    // делает окно фиксированного размера
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    // делаю так, чтобы форма появлялась в центре экрана
    this->move(qApp->desktop()->availableGeometry(this).center()-this->rect().center());

    lePotochni->setMaximumWidth(95);
    lePoperedni->setMaximumWidth(95);
    lSummaSpozhyto->setMaximumWidth(76);
    lSummaSpozhyto->setMinimumWidth(76);
    lDo150->setMinimumWidth(195);
    lDo150->setMaximumWidth(195);
    lPonad150->setMinimumWidth(195);
    lPonad150->setMaximumWidth(195);
    lSummaDo150->setMinimumWidth(76);
    lSummaPonad150->setMinimumWidth(76);
    leTaryfDo150->setMaximumWidth(85);
    leTaryfPonad150->setMaximumWidth(85);
    lSummaDoSplatyDo150->setMinimumWidth(90);
    lSummaDoSplatyPonad150->setMinimumWidth(90);
    lVsego->setMinimumWidth(90);

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
    rozrahunok.setTaryfDo150(leTaryfDo150->text().toFloat());
    rozrahunok.setTaryfPonad150(leTaryfPonad150->text().toFloat());
    rozrahunok.setPotochni(lePotochni->text().toInt());
    rozrahunok.setPoperedni(lePoperedni->text().toInt());
    lSummaSpozhyto->setText(QString::number(rozrahunok.spozhyto()));
    lSummaDo150->setText(QString::number(rozrahunok.spozhytoDo150()));
    lSummaPonad150->setText(QString::number(rozrahunok.spozhytoPonad150()));
    lSummaDoSplatyDo150->setText(QString::number(rozrahunok.summaDo150(), 'f', 2));
    lSummaDoSplatyPonad150->setText(QString::number(rozrahunok.summaPonad150(), 'f', 2));
    lVsego->setText(QString::number(rozrahunok.summaZagalna(), 'f', 2));
}

void MainWindow::writeDefaultSettings()
{
    settings.clear();
    settings.setValue("TaryfDo150", 0.2802);
    settings.setValue("TaryfPonad150", 0.3648);
}

void MainWindow::writeSettings()
{
    settings.clear();
    settings.setValue("TaryfDo150", leTaryfDo150->text());
    settings.setValue("TaryfPonad150", leTaryfPonad150->text());
}

void MainWindow::readSettings()
{
    leTaryfDo150->setText(settings.value("TaryfDo150", 0).toString());
    leTaryfPonad150->setText(settings.value("TaryfPonad150", 0).toString());
}
