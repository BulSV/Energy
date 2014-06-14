#include "AbstractPartPayment.h"

int AbstractPartPayment::consumedCalculated() const
{
    if(itsPayment->consumed() >= 0 && (itsPayment->consumed() < itsLimit || itsLimit == 0))
    {
        return itsPayment->consumed();
    }
    else
    {
        return itsLimit;
    }
}

AbstractPartPayment::AbstractPartPayment(IPayment *payment):
    itsPayment(payment)
  , itsLimit(0)
  , itsTariff(0)
{
}

AbstractPartPayment::AbstractPartPayment(IPayment *payment, float limit, float tariff):
    itsPayment(payment)
  , itsLimit(limit)
  , itsTariff(tariff)
{
}

AbstractPartPayment::~AbstractPartPayment()
{
}

int AbstractPartPayment::consumed() const
{
    return itsPayment->consumed() - consumedCalculated();
}

void AbstractPartPayment::setLimit(float limit)
{
    itsLimit = limit;
}

float AbstractPartPayment::tariff() const
{
    return itsTariff;
}

void AbstractPartPayment::setTariff(float tariff)
{
    itsTariff = tariff;
}

float AbstractPartPayment::amount() const
{
    return consumedCalculated()*tariff();
}
