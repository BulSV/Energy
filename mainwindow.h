#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include "rastchet.h"

class MainWindow : public QWidget
{
Q_OBJECT
    QLabel *lPilga;
    QLineEdit *lePilga;
    QLineEdit *leLimit;

    QPushButton *bBackward;
    QLabel *lDate;
    QPushButton *bForward;

    QLabel *lPotochni;
    QLabel *lPoperedni;
    QLabel *lSpozhyto;
    QLabel *lSummaSpozhyto;
    QLabel *lTaryf;
    QLabel *lSummaDoSplaty;
    QLabel *lPilgovi;
    QLabel *lDo150;
    QLabel *lPonad150;
    QLabel *lPonad800;
    QLabel *lSummaPilgovi;
    QLabel *lTaryfPilgovi;
    QLabel *lSummaDo150;
    QLabel *lSummaPonad150;
    QLabel *lSummaPonad800;
    QLabel *lSummaDoSplatyPilgovi;
    QLabel *lSummaDoSplatyDo150;
    QLabel *lSummaDoSplatyPonad150;
    QLabel *lSummaDoSplatyPonad8000;
    QLabel *lVsegoDosplaty;
    QLabel *lVsego;

    QLineEdit *lePotochni;
    QLineEdit *lePoperedni;
    QLineEdit *leTaryfDo150;
    QLineEdit *leTaryfPonad150;
    QLineEdit *leTaryfPonad800;

    QPushButton *bRozrahunok;

    QSettings settings;

    Rastchet rozrahunok;

    void writeDefaultSettings();
    void writeSettings();
    void readSettings();
private slots:
    void updateTime();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void onButtonRozrahunok();

};

#endif // MAINWINDOW_H
