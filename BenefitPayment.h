#ifndef BENEFITPAYMENT_H
#define BENEFITPAYMENT_H

#include "AbstractPartPayment.h"

class BenefitPayment : public AbstractPartPayment
{
    int itsBenefitPercent;
public:
    BenefitPayment(IPayment* payment);
    BenefitPayment(IPayment* payment, int limit, float tariffForBenefit, int benefitPercent);
    virtual ~BenefitPayment();

    void setBenefitPercent(int benefitPercent);
    virtual float tariff() const;
    virtual void setTariff(float tariffForBenefit);
};

#endif // BENEFITPAYMENT_H
