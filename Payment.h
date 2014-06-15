#ifndef PAYMENT_H
#define PAYMENT_H

#include "IPayment.h"
#include "AbstractPartPayment.h"
#include <QObject>
#include <QList>

class Payment: public QObject, public IPayment
{
    Q_OBJECT
    int itsCurrent;
    int itsPrevious;
    QList<AbstractPartPayment*>* itsPartsPayment;
public:
    Payment();
    Payment(int current,
            int previous);
    Payment(int current,
            int previous,
            QList<AbstractPartPayment*>* partPayment);
    virtual ~Payment();

    void addPartPayment(AbstractPartPayment* partPayment);
    virtual int consumed() const;
    float amountTotal() const;    
    void setCurrent(int current);
    void setPrevious(int previous);
    QList<AbstractPartPayment*>* partsPayment() const;
};

#endif // PAYMENT_H
