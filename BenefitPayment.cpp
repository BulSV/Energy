#include "BenefitPayment.h"

BenefitPayment::BenefitPayment(IPayment *payment):
    AbstractPartPayment(payment)
  , itsBenefitPercent(0)
{
}

BenefitPayment::BenefitPayment(IPayment *payment,
                               int limit,
                               float tariffForBenefit,
                               int benefitPercent):
    AbstractPartPayment(payment, limit, tariffForBenefit)
  , itsBenefitPercent(benefitPercent)
{
}

BenefitPayment::~BenefitPayment()
{
}

void BenefitPayment::setBenefitPercent(int benefitPercent)
{
    itsBenefitPercent = benefitPercent;
}

float BenefitPayment::tariff() const
{
    if(itsBenefitPercent)
        return ((100 - itsBenefitPercent)*itsTariff/100);
    return 0;
}

void BenefitPayment::setTariff(float tariffForBenefit)
{
    itsTariff = tariffForBenefit;
}
