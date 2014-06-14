#include "payment.h"

Payment::Payment():  
    itsCurrent(0)
  , itsPrevious(0)
  , itsPartsPayment(0)
{
}

Payment::Payment(int current, int previous):
    itsCurrent(current)
  , itsPrevious(previous)
  , itsPartsPayment(0)
{
}

Payment::Payment(int current,
                 int previous,
                 QList<AbstractPartPayment *> *partPayment):
    itsCurrent(current)
  , itsPrevious(previous)
  , itsPartsPayment(partPayment)
{
}

Payment::~Payment()
{
    for(int i = 0; i < itsPartsPayment->size(); ++i)
    {
        AbstractPartPayment* partPayment = itsPartsPayment->takeLast();
        itsPartsPayment->removeLast();
        delete partPayment;
        partPayment = 0;
    }

    delete itsPartsPayment;
    itsPartsPayment = 0;
}

void Payment::addPartPayment(AbstractPartPayment *partPayment)
{
    itsPartsPayment->append(partPayment);
}

int Payment::consumed() const
{
    if(itsCurrent > 0 && itsPrevious > 0 && itsCurrent > itsPrevious)
        return (itsCurrent - itsPrevious);
    return 0;
}

float Payment::amountTotal() const
{
    float amount = 0.0;

    for(int i = 0; i < itsPartsPayment->size(); ++i)
    {
        amount += itsPartsPayment->at(i)->amount();
    }

    return amount;
}

void Payment::setCurrent(int current)
{
    itsCurrent = current;
}

void Payment::setPrevious(int previous)
{
    itsPrevious = previous;
}

QList<AbstractPartPayment *> *Payment::partsPayment() const
{
    return itsPartsPayment;
}
