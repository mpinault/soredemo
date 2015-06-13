#include <iomanip>
#include "timing.h"
#include <ctime>

/*!
 * \file tache.cpp
 * \brief les differents types des taches
 * \author Antoine Jouglet, modifié par Alice et Morgane
 * \version 0.1
 * \date 14 juin 2015
 */

using namespace TIME;

std::istream& operator>>(std::istream& flot, QDate& date){
    unsigned int short j,m,a;
    bool ok=true;
    flot>>j;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='/') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }
    if(flot.peek()=='/') {
        flot.ignore();
        flot>>a;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }

    if (ok) date=QDate(j,m,a); else flot.clear(std::ios::failbit);
    return flot;
}

std::istream& operator>>(std::istream& flot, TIME::Duree& duree){
    unsigned int h,m;
    bool ok=true;
    flot>>h;
    if (flot) while (flot.peek()==' ') flot.ignore(); // passe les espaces
    else ok=false;

    if (!flot) ok=false;

    if(flot.peek()=='H') {
        flot.ignore();
        flot>>m;
        if (!flot) ok=false;
    }
    else {
        ok=false;
    }
    if (ok) duree=Duree(h,m); else flot.clear(std::ios::failbit);
    return flot;
}
