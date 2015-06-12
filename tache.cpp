/*!
 * \file tache.cpp
 * \brief les differents types des taches
 * \author Alice,Morgane
 * \version 0.1
 */

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
    QString nomProjet;
    int position;
    ProjetManager& m = ProjetManager::getInstance();
    int i=0;
    for(std::vector<Projet*>::iterator mit = m.getProjetNC().begin(); mit != m.getProjetNC().end(); ++mit){
        for (std::vector<Tache*>::const_iterator it = (*mit)->getTaches().begin(); it != (*mit)->getTaches().end(); ++it){
            if ((*it)==&t) {
                qDebug()<<"On trouve bien la tache";
                position=i;
                (*mit)->getTachesNC().erase((*mit)->getTachesNC().begin()+position);
                qDebug()<<"Après la suppression";
            }
            i++;
        }
    }
    Projet* p = m.trouverProjetP(nomProjet);
    //supprimer la tache ajoute dans la tache compose du projet
    //utiliser un for , iterator et supprimer du vector de la tache
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
