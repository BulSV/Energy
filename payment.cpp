#include "payment.h"

Payment::Payment():
    itsBenefit(0),
    itsLimit(0),
    itsCurrent(0),
    itsPrevious(0),
    itsTariffTo150(0),
    itsTariffOver150(0),
    itsTariffOver800(0)
{
}

Payment::Payment(int benefit,
                   int limit,
                   int current,
                   int previous,
                   float taryfDo150,
                   float taryfPonad150,
                   float taryfPonad800):
    itsBenefit(benefit),
    itsLimit(limit),
    itsCurrent(current),
    itsPrevious(previous),
    itsTariffTo150(taryfDo150),
    itsTariffOver150(taryfPonad150),
    itsTariffOver800(taryfPonad800)
{

}

int Payment::consumed() const
{
    if(itsCurrent > 0 && itsPrevious > 0 && (itsCurrent - itsPrevious) > 0)
        return (itsCurrent - itsPrevious);
    return 0;
}

int Payment::consumedBenefit() const
{
    if(consumed() <= itsLimit && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return consumed();
    if(itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return itsLimit;
    return 0;
}
int Payment::consumedTo150() const
{
    if((consumed() - consumedBenefit() > 0) && (consumed() - consumedBenefit() <= 150)
            && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumed() - consumedBenefit());
    if((consumed() - itsLimit > 0) && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return 150;
    return 0;
}
int Payment::consumedOver150() const
{
    if((consumed() - consumedBenefit() - consumedTo150() > 0)
            && (consumed() - consumedBenefit() - consumedTo150() <= 800)
            && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumed() - consumedBenefit() - consumedTo150());
    if((consumed() - consumedBenefit() - consumedTo150() > 0)
            && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return 800;
    return 0;
}

int Payment::consumedOver800() const
{
    if((consumed() - consumedBenefit() - consumedTo150() - consumedOver150() > 0)
            && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumed() - consumedBenefit() - consumedTo150() - consumedOver150());
    return 0;
}

float Payment::tariffBenefit() const
{
    if(itsBenefit)
        return ((100 - itsBenefit)*itsTariffTo150/100);
    return 0;
}
float Payment::tariffTo150() const
{
    return itsTariffTo150;
}
float Payment::tariffOver150() const
{
    return itsTariffOver150;
}

float Payment::tariffOver800() const
{
    return itsTariffOver800;
}

float Payment::amountBenefit() const
{
    if(consumed() > itsLimit && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return itsLimit*tariffBenefit();
    if(itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return consumed();
    return 0;
}
float Payment::amountTo150() const
{
    if(itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumedTo150()*itsTariffTo150);
    return 0;
}
float Payment::amountOver150() const
{
    if(consumed() > 150 && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumedOver150()*itsTariffOver150);
    return 0;
}

float Payment::amountOver800() const
{
    if(consumed() > 800 && itsCurrent > 0 && itsPrevious > 0 && consumed() > 0)
        return (consumedOver800()*itsTariffOver800);
    return 0;
}
float Payment::amountTotal() const
{
    return (amountBenefit() + amountTo150() + amountOver150() + amountOver800());
}

void Payment::setBenefit(int benefit)
{
    itsBenefit = benefit;
}

void Payment::setLimit(int limit)
{
    itsLimit = limit;
}

void Payment::setTariffTo150(float tariffTo150)
{
    itsTariffTo150 = tariffTo150;
}

void Payment::setTariffOver150(float tariffOver150)
{
    itsTariffOver150 = tariffOver150;
}

void Payment::setTariffOver800(float tariffOver800)
{
    itsTariffOver800 = tariffOver800;
}

void Payment::setCurrent(int current)
{
    itsCurrent = current;
}

void Payment::setPrevious(int previous)
{
    itsPrevious = previous;
}
