
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

void TacheComposite::ajouterTacheComparbre(QTreeWidgetItem* item){

    for (vector<Tache*>::const_iterator it = this->getCompose().begin(); it != this->getCompose().end(); ++it){
        QTreeWidgetItem* newTache = new QTreeWidgetItem(item, QStringList(QString("tache : %1").arg((*it)->getTitre())));
        //item.append(newTache);
        if (typeid(*it).name()=="14TacheComposite") dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(newTache);
    }
}

void TacheComposite::ajouterTacheComparbre(QTreeWidgetItem* item, QComboBox* cBox,int i){

    for (vector<Tache*>::const_iterator it = this->getCompose().begin(); it != this->getCompose().end(); ++it){
        QTreeWidgetItem* newTache = new QTreeWidgetItem(item, QStringList(QString("tache : %1").arg((*it)->getTitre())));
        //item.append(newTache);
        if (typeid(*it).name()=="14TacheComposite") dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(newTache,cBox,i);
        else cBox->insertItem(i,QString("tache : %1").arg((*it)->getTitre()));

    }
}
