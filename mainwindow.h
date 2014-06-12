#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QMutableListIterator>
#include <QComboBox>
#include <QTranslator>
#include "payment.h"
#include "XmlHistoryManager.h"

class MainWindow : public QWidget
{
Q_OBJECT
    QLocale locale;
    QTranslator translator;

    QDialog* languageDialog;
    QComboBox* languageComboBox;

    QLabel *lBenefitLimit;
    QLineEdit *leBenefit;
    QLineEdit *leLimit;

    QPushButton *bBackward;
    QLabel *lDate;
    QPushButton *bForward;

    QLabel *lCurrent;
    QLabel *lPrevious;
    QLabel *lConsumed;
    QLabel *lAmountConsumed;
    QLabel *lTariff;
    QLabel *lAmountPayment;
    QLabel *lBenefit;
    QLabel *lTo150;
    QLabel *lOver150;
    QLabel *lOver800;
    QLabel *lAmountBenefit;
    QLabel *lTariffBenefit;
    QLabel *lAmountTo150;
    QLabel *lAmountOver150;
    QLabel *lAmountOver800;
    QLabel *lAmountPaymentBenefit;
    QLabel *lAmountPaymentTo150;
    QLabel *lAmountPaymentOver150;
    QLabel *lAmountPaymentOver800;
    QLabel *lTotalPayment;
    QLabel *lTotal;

    QLineEdit *leCurrent;
    QLineEdit *lePrevious;
    QLineEdit *leTariffTo150;
    QLineEdit *leTariffOver150;
    QLineEdit *leTariffOver800;

    QPushButton *bPayment;

    IHistoryManager* xmlHistoryManager;

    QTimer *timer;

    QSettings settings;

    Payment payment;

    QList<QMap<QString, QString> >* itsHistory;
    int itsHistoryLimit;
    QMutableListIterator<QMap<QString, QString> > itsListIterator;

    void writeDefaultSettings();
    void writeSettings();
    void readSettings();
    void writeHistory();
    void setFromHistory(QMap<QString, QString> map);
private slots:
    void setupTime(int language);
    void updateTime();
    void backwardHistory();
    void forwardHistory();
    void setupLanguageDialog();
    void selectLanguage(int language);
    void updateWidgetText();
    void updateDialogText();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void onButtonPayment();

};

#endif // MAINWINDOW_H
