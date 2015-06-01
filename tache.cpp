#include "tache.h"
#include "projet.h"
#include "manager.h"

using namespace TIME;
using namespace std;

//================================Methodes de Tache==========================================================================

//Methode virtuel mais qui a une definition dans la classe de base
void Tache::ajouterTachePrec(Tache& t){
    precede.push_back(&t);
}

//================================Methodes de TacheUnitaire==================================================================
//================================Methodes de TacheUnitaireNonPreempte=======================================================
//================================Methodes de TacheUnitairePreempte==========================================================

//On a besoin d'addition 2 durees.
//On va surcharger l'operateur '+'. -> voir "timing.h", classe "Duree"

void TacheUnitairePreempte::ajouterPartie(Partie* p){
    parties.push_back(p);
    unsigned int res=TIME::sommeD(this->getDuree(),p->getDuree());
    Duree d=Duree(res);
    const Duree& dc=d;
    setDuree(dc);
}


//================================methodes de TacheComposite=================================================================

void TacheComposite::ajouterTacheComp(Tache& t){
    compose.push_back(&t);
}
