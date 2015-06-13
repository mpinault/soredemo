#ifndef MANAGER
#define MANAGER

/*!
 * \file tache.h
 * \brief les structures des differentes types de taches
 * \author Alice,Morgane
 * \version 0.1
 * \date 14 juin 2015
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
#include<algorithm>
#include <QFileDialog>
#include<QTreeWidget>
#include<QComboBox>

using namespace std;
using namespace TIME;




/**
* \class Tache
* \brief Classe abstraite représentant une tache
*/
class Tache{

    QString titre; /*!< le titre de la tache*/
    QDate dispo;/*!< la date de disponibilite de la tache*/
    QDate ech;/*!< la date de echeance de la tache*/
    Duree duree;/*!< la duree de la tache*/
    bool prog;/*!< permet de savoir si la tache est programme (prog=1 si oui)*/
    bool estCompose;/*!< permet de savoir si la tache est une sous tache d'une tache composite (estCompose=1 si oui)*/

    typedef std::vector<Tache *> pred; /**  \typedef  pred: un vecteur de pointeurs tache*/
    pred precede;/*!< */

public:
    //Constructuer ET Destructeur
    Tache(const QString& t, const QDate& d, const QDate& e, const Duree& du):titre(t), dispo(d), ech(e), duree(du),prog(0),estCompose(0){
        precede.reserve(10);
    }
    virtual ~Tache(){}

    //Acceseurs en Lecture ET Ecriture
    const QString& getTitre()const{ return titre; }
    const QDate& getDispo()const { return dispo; }
    const QDate& getEch()const { return ech; }
    bool getProg()const { return prog; }
    void setProg(int a){prog=a;}
    bool getEstCompose()const { return estCompose; }
    void setEstCompose(int a){estCompose=a;}
    const Duree& getDuree()const { return duree; }
    void setTitre(const QString& a){ titre = a; }
    void setDispo(const QDate& b){ dispo = b; }
    void setEch(const QDate& c){ ech = c; }
    void setDuree(const Duree& d){ duree = d; }

    //Methodes
    virtual void ajouterTachePrec(Tache& t)=0;
};

//definir ajouterTachePrec(Tache& t) dans les classes derives !!

/**
* \class TacheUnitaire
* \brief Classe abstraite représentant une tache unitaire
*
* La classe TacheUnitaire herite publiquement de la classe Tache.
*/

class TacheUnitaire : public Tache{
public:
    //Constructeur ET Destructeur
    TacheUnitaire(const QString& t, const QDate& d, const QDate& e, const Duree& du) :Tache(t, d, e, du){}
    virtual ~TacheUnitaire(){}
};


/**
* \class TacheUnitaireNonPreempte
* \brief Classe non abstraite représentant une tache unitaire non preempte
*
* La classe TacheUnitaireNonPreempte herite publiquement de la classe TacheUnitaire.
*/
class TacheUnitaireNonPreempte : public TacheUnitaire{
public:
    //Constructeur ET Destructeur
    TacheUnitaireNonPreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du) :TacheUnitaire(t, d, e, du){
        if (du.getDureeEnHeures()>12){
            qDebug()<<du.getDureeEnHeures();
            throw TimeException("erreur TacheUnitaireNonPreempte, la durée d'une tache unitaire non preempte ne peut pas exceder 12h");
    }
    }
    virtual ~TacheUnitaireNonPreempte(){}

    //Methode
    void ajouterTachePrec(Tache& t)override{}
};


/**
* \class Partie
* \brief Classe non abstraite représentant une partie d'une tache unitaire preempte
*/
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


/**
* \class TacheUnitairePremmpte
* \brief Classe non abstraite représentant une tache unitaire preempte
*
* La classe TacheUnitairePreempte herite publiquement de la classe TacheUnitaire.
*/
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


/**
* \class TacheComposite
* \brief Classe non abstraite représentant une tache composite
*
* La classe TacheComposite herite publiquement de la classe Tache.
*/
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
    void ajouterTacheComp(Tache &t);
    void ajouterTacheComparbre(QTreeWidgetItem* item);
    void ajouterTacheComparbre(QTreeWidgetItem* item, QComboBox* cBox,int i);
};



#endif // MANAGER
