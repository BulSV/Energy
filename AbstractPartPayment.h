#ifndef ABSTRACTPARTPAYMENT_H
#define ABSTRACTPARTPAYMENT_H

#include "IPayment.h"

class AbstractPartPayment : public IPayment
{
protected:
    IPayment* itsPayment;
    int itsLimit;
    float itsTariff;

    virtual int consumedCalculated() const;
public:
    AbstractPartPayment(IPayment* payment);
    AbstractPartPayment(IPayment* payment, float limit, float tariff);
    virtual ~AbstractPartPayment();

    virtual int consumed() const;
    virtual void setLimit(float limit);
    virtual float tariff() const;
    virtual void setTariff(float tariff);
    virtual float amount() const;
};

#endif // ABSTRACTPARTPAYMENT_H
