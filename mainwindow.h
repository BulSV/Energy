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
QLabel *lPotochni;
QLabel *lPoperedni;
QLabel *lSpozhyto;
QLabel *lSummaSpozhyto;
QLabel *lTaryf;
QLabel *lSummaDoSplaty;
QLabel *lDo150;
QLabel *lPonad150;
QLabel *lSummaDo150;
QLabel *lSummaPonad150;
QLabel *lSummaDoSplatyDo150;
QLabel *lSummaDoSplatyPonad150;
QLabel *lVsegoDosplaty;
QLabel *lVsego;

QLineEdit *lePotochni;
QLineEdit *lePoperedni;
QLineEdit *leTaryfDo150;
QLineEdit *leTaryfPonad150;

QPushButton *bRozrahunok;

QSettings settings;

Rastchet rozrahunok;

void writeDefaultSettings();
void writeSettings();
void readSettings();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void onButtonRozrahunok();

};

#endif // MAINWINDOW_H
