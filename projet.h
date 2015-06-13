#ifndef PROJET
#define PROJET

/*!
 * \file projet.h
 * \brief projet qui est un manager des taches
 * \author Alice,Morgane
 * \version 0.1
 */

#include "timing.h"
#include "tache.h"

using namespace std;

//=====Projet====================================================================================================
//Classe NON Abstraite
class Projet{

     friend class ProjetManager;

    QString titre;
    QDate dispo;
    QDate ech;
    QString file;    //le fichier qui contient tous les taches

    typedef std::vector<Tache*> tac;
    tac taches;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation
    Projet(const QString& t, const QDate& d, const QDate& e) :titre(t), dispo(d), ech(e){
        taches.reserve(10);
    }
    ~Projet(){
        if (file != "") save(file);
        taches.clear();
        taches.~vector();
        file = "";
    }
    Projet(const Projet& p);
    Projet& operator=(const Projet& p);

    //Methodes
    Tache* trouverTacheP(const QString& ti) const;

    //ajoute une Tache dans le projet
    void ajouterTache(Tache* t);

public:
    //Acceseurs en Lecture ET Ecriture
    const QString& getTitre()const{ return titre; }
    const QDate& getDispo()const { return dispo; }
    const QDate& getEch()const { return ech; }
    const tac& getTaches() const {return taches;}
    tac& getTachesNC(){return taches;}
    void setTitre(const QString& s){ titre=s; }
    void setDispo(const QDate& d){dispo=d; }
    void setEch(const QDate& e){ ech=e; }

    //Methodes
        //creer une Tache a partir d'un formulaire Qt dans le projet
    Tache& creerTache(const QString& t, const QDate& dispo, const QDate& deadline, const Duree& dur,int a=2);

        //permet de savoir si la Tache existe ou pas a partir de son titre
    bool isTacheExistante(const QString& ti) const { return trouverTacheP(ti) != 0; }

        //retrouver une Tache a partir de son titre
    Tache& trouverTacheR(const QString& ti) const;

    //permet de tester la validité des dates et des horaires pour l'ajout d'une tache
    bool isValide(const QDate& d, const QDate& dl);

        //pour les iterateurs
    vector<Tache*>::const_iterator Tbegin(){return taches.begin();}
    vector<Tache*>::const_iterator Tend(){return taches.end();}

        //au niveau des fichiers
    void load(const QString& f);
    void save(const QString& f);
};



#endif // PROJET

