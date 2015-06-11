#ifndef MANAGER
#define MANAGER

/*!
 * \file tache.h
 * \brief les differents types des taches
 * \author Alice,Morgane
 * \version 0.1
 */

#include <timing.h>
#include <typeinfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include<iostream>
#include<QString>
#include <vector>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

using namespace std;
using namespace TIME;

//=====07/06/15======Morgane============================================================================================
#include <QFileDialog>

//=====08/06/15======Morgane============================================================================================
#include<QTreeWidget>
#include<QComboBox>

//=====Tache==================================================================================================
//Classe Abstraite
class Tache{

    QString titre;
    QDate dispo;
    QDate ech;
    Duree duree;
    bool prog;

    typedef std::vector<Tache *> pred;
    pred precede;

public:
    //Constructuer ET Destructeur
    Tache(const QString& t, const QDate& d, const QDate& e, const Duree& du):titre(t), dispo(d), ech(e), duree(du),prog(0){
        precede.reserve(10);
    }
    virtual ~Tache(){}

    //Acceseurs en Lecture ET Ecriture
    const QString& getTitre()const{ return titre; }
    const QDate& getDispo()const { return dispo; }
    const QDate& getEch()const { return ech; }
    bool getProg()const { return prog; }
    void setProg(int a){prog=a;}
    const Duree& getDuree()const { return duree; }
    void setTitre(const QString& a){ titre = a; }
    void setDispo(const QDate& b){ dispo = b; }
    void setEch(const QDate& c){ ech = c; }
    void setDuree(const Duree& d){ duree = d; }

    //Methodes
    virtual void ajouterTachePrec(Tache& t)=0;
};

//definir ajouterTachePrec(Tache& t) dans les classes derives !!

//=====TacheUnitaire====================================================================================
//Classe Abstraite, herite de la classe "Tache"
class TacheUnitaire : public Tache{
public:
    //Constructeur ET Destructeur
    TacheUnitaire(const QString& t, const QDate& d, const QDate& e, const Duree& du) :Tache(t, d, e, du){}
    virtual ~TacheUnitaire(){}
};


//=====TacheUnitaireNonPreempte=========================================================================
//Classe NON Abstraite, herite de la classe "TacheUnitaire"
class TacheUnitaireNonPreempte : public TacheUnitaire{
public:
    //Constructeur ET Destructeur
    TacheUnitaireNonPreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du) :TacheUnitaire(t, d, e, du){
        if (du.getDureeEnHeures()>12 || du.getDureeEnHeures()==12){
            qDebug()<<du.getDureeEnHeures();
            throw TimeException("erreur TacheUnitaireNonPreempte, la durée d'une tache unitaire non preempte ne peut pas exceder 12h");
    }
    }
    virtual ~TacheUnitaireNonPreempte(){}

    //Methode
    void ajouterTachePrec(Tache& t)override{}
};


//=====Partie===========================================================================================
//Classe NON Abstraite
class Partie{
    Duree duree;
    Tache* tache;
public:
    //Constructeur ET Destructeur
    Partie(const Duree& du,Tache* t):duree(du),tache(t){}
    virtual ~Partie(){}

    //Acceseurs en Lecture ET Ecriture
    const Duree& getDuree()const{return duree;}
    void setDuree(const Duree& d){duree = d;}
    const Tache& getTache()const{return *tache;}
};


//=====TacheUnitairePreempte============================================================================
//Classe NON Abstraite
class TacheUnitairePreempte : public TacheUnitaire{
    Duree tpsPasse;

    typedef std::vector<Partie*> par;
    par parties;

public:
    //Constructeur ET Destructeur
    TacheUnitairePreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du) :TacheUnitaire(t,d,e,du){}
    virtual ~TacheUnitairePreempte(){}

    //Accesseurs en Lecture ET Ecriture
    const Duree& getDuree()const{ return tpsPasse;}
    void setDuree(const Duree& d){tpsPasse=d;}

    //Methode
    void ajouterTachePrec(Tache& t)override{}
    void ajouterPartie(Partie* p);

};


//=====TacheComposite=================================================================================
//Classe NON Abstraite
class TacheComposite : public Tache{

    typedef std::vector<Tache*> com;
    com compose;

public:
    //Constructeur ET Destructeur
    TacheComposite(const QString& t, const QDate& d, const QDate& e, const Duree& du):Tache(t, d, e, du){
        compose.reserve(10);
    }
    virtual ~TacheComposite(){}

    //accesseur
    const com& getCompose()const {return compose;}

    //Methodes
    void ajouterTachePrec(Tache& t)override{}
    void ajouterTacheComp(Tache& t);
    void ajouterTacheComparbre(QTreeWidgetItem* item);
    void ajouterTacheComparbre(QTreeWidgetItem* item, QComboBox* cBox,int i);
};



#endif // MANAGER
