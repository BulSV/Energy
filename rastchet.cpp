#include "rastchet.h"

Rastchet::Rastchet():
    itsPilga(0),
    itsLimit(0),
    itsPotochni(0),
    itsPoperedni(0),
    itsTaryfDo150(0),
    itsTaryfPonad150(0),
    itsTaryfPonad800(0)
{
}

Rastchet::Rastchet(int pilga,
                   int limit,
                   int potochni,
                   int poperedni,
                   float taryfDo150,
                   float taryfPonad150,
                   float taryfPonad800):
    itsPilga(pilga),
    itsLimit(limit),
    itsPotochni(potochni),
    itsPoperedni(poperedni),
    itsTaryfDo150(taryfDo150),
    itsTaryfPonad150(taryfPonad150),
    itsTaryfPonad800(taryfPonad800)
{

}

int Rastchet::spozhyto() const
{
    if(itsPotochni > 0 && itsPoperedni > 0 && (itsPotochni - itsPoperedni) > 0)
        return (itsPotochni - itsPoperedni);
    return 0;
}

int Rastchet::spozhytoPilgovi() const
{
    if(spozhyto() <= itsLimit && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return spozhyto();
    if(itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return itsLimit;
    return 0;
}
int Rastchet::spozhytoDo150() const
{
    if((spozhyto() - spozhytoPilgovi() > 0) && (spozhyto() - spozhytoPilgovi() <= 150)
            && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhyto() - spozhytoPilgovi());
    if((spozhyto() - itsLimit > 0) && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return 150;
    return 0;
}
int Rastchet::spozhytoPonad150() const
{
    if((spozhyto() - spozhytoPilgovi() - spozhytoDo150() > 0)
            && (spozhyto() - spozhytoPilgovi() - spozhytoDo150() <= 800)
            && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhyto() - spozhytoPilgovi() - spozhytoDo150());
    if((spozhyto() - 150 > 0) && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return 800;
    return 0;
}

int Rastchet::spozhytoPonad800() const
{
    if((spozhyto() - spozhytoPilgovi() - spozhytoDo150() - spozhytoPonad150() > 0)
            && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhyto() - spozhytoPilgovi() - spozhytoDo150() - spozhytoPonad150());
    return 0;
}

float Rastchet::taryfPilgovi() const
{
    if(itsPilga)
        return ((100 - itsPilga)*itsTaryfDo150/100);
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

float Rastchet::taryfPonad800() const
{
    return itsTaryfPonad800;
}

float Rastchet::summaPilgovi() const
{
    if(spozhyto() > itsLimit && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return itsLimit*taryfPilgovi();
    if(itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return spozhyto();
    return 0;
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

float Rastchet::summaPonad800() const
{
    if(spozhyto() > 800 && itsPotochni > 0 && itsPoperedni > 0 && spozhyto() > 0)
        return (spozhytoPonad800()*itsTaryfPonad800);
    return 0;
}
float Rastchet::summaZagalna() const
{
    return (summaPilgovi() + summaDo150() + summaPonad150() + summaPonad800());
}

void Rastchet::setPilga(int pilga)
{
    itsPilga = pilga;
}

void Rastchet::setLimit(int limit)
{
    itsLimit = limit;
}

void Rastchet::setTaryfDo150(float taryfDo150)
{
    itsTaryfDo150 = taryfDo150;
}

void Rastchet::setTaryfPonad150(float taryfPonad150)
{
    itsTaryfPonad150 = taryfPonad150;
}

void Rastchet::setTaryfPonad800(float taryfPonad800)
{
    itsTaryfPonad800 = taryfPonad800;
}

void Rastchet::setPotochni(int potochni)
{
    itsPotochni = potochni;
}

void Rastchet::setPoperedni(int poperedni)
{
    itsPoperedni = poperedni;
}
