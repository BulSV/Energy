#include "rastchet.h"

Rastchet::Rastchet():
        itsPotochni(0),
        itsPoperedni(0),
        itsTaryfDo150(0),
        itsTaryfPonad150(0)
{
}

Rastchet::Rastchet(int potochni, int poperedni, float taryfDo150, float taryfPonad150):
        itsPotochni(potochni),
        itsPoperedni(poperedni),
        itsTaryfDo150(taryfDo150),
        itsTaryfPonad150(taryfPonad150)
{

}

int Rastchet::spozhyto() const
{
    if(itsPotochni > 0 && itsPoperedni > 0 && (itsPotochni - itsPoperedni) > 0)
        return (itsPotochni - itsPoperedni);
    return 0;
}
int Rastchet::spozhytoDo150() const
{
    if(spozhyto() <= 150 && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return spozhyto();
    if(itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return 150;
    return 0;
}
int Rastchet::spozhytoPonad150() const
{
    if(spozhyto() > 150 && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhyto() - 150);
    return 0;
}
float Rastchet::taryfDo150() const
{
    return itsTaryfDo150;
}
float Rastchet::taryfPonad150() const
{
    return itsTaryfPonad150;
}
float Rastchet::summaDo150() const
{
    if(itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhytoDo150()*itsTaryfDo150);
    return 0;
}
float Rastchet::summaPonad150() const
{
    if(spozhyto() > 150 && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhytoPonad150()*itsTaryfPonad150);
    return 0;
}
float Rastchet::summaZagalna() const
{
    return (summaDo150() + summaPonad150());
}
void Rastchet::setTaryfDo150(float taryfDo150)
{
    itsTaryfDo150 = taryfDo150;
}

void Rastchet::setTaryfPonad150(float taryfPonad150)
{
    itsTaryfPonad150 = taryfPonad150;
}

void Rastchet::setPotochni(int potochni)
{
    itsPotochni = potochni;
}

void Rastchet::setPoperedni(int poperedni)
{
    itsPoperedni = poperedni;
}
