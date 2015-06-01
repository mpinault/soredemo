#ifndef MANAGER
#define MANAGER

#include "timing.h"

#include <typeinfo>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include<iostream>
#include<QString>
#include <vector>
#include <QDate>
#include <QDebug>
#include <QFile>

using namespace std;
namespace TIME {

//=====Tache==================================================================================================
//Classe Abstraite
class Tache{

    QString titre;
    QDate dispo;
    QDate ech;
    Duree duree;

    typedef std::vector<Tache *> pred;
    pred precede;

public:
    //Constructuer ET Destructeur
    Tache(const QString& t, const QDate& d, const QDate& e, const Duree& du):titre(t), dispo(d), ech(e), duree(du){
        precede.reserve(10);
    }
    virtual ~Tache(){}

    //Acceseurs en Lecture ET Ecriture
    const QString& getTitre()const{ return titre; }
    const QDate& getDispo()const { return dispo; }
    const QDate& getEch()const { return ech; }
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
        if (du.getDureeEnHeures()>12 || du.getDureeEnHeures()==12)
            throw TimeException("erreur TacheUnitaireNonPreempte, la durée d'une tache unitaire non preempte ne peut pas exceder 12h");
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
    //const Tache& getDuree()const{return *tache;}
};


//=====TacheUnitairePreempte============================================================================
//Classe NON Abstraite
class TacheUnitairePreempte : public TacheUnitaire{
    typedef std::vector<Partie*> par;
    par parties;

public:
    //Constructeur ET Destructeur
    TacheUnitairePreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du) :TacheUnitaire(t,d,e,du){}
    virtual ~TacheUnitairePreempte(){}

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

    //Methodes
    void ajouterTachePrec(Tache& t)override{}
    void ajouterTacheComp(Tache& t);
};


//=====Projet====================================================================================================
//Classe NON Abstraite
class Projet{

    QString titre;
    QDate dispo;
    QDate ech;
    QString file;    //le fichier qui contient tous les taches

    typedef std::vector<Tache *> tac;
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
        //ajoute une Tache dans le projet
    void ajouterTache(Tache* t);

public:
    //Acceseurs en Lecture ET Ecriture
    const QString& getTitre()const{ return titre; }
    const QDate& getDispo()const { return dispo; }
    const QDate& getEch()const { return ech; }
    void setTitre(const QString& s){ titre=s; }
    void setDispo(const QDate& d){dispo=d; }
    void setEch(const QDate& e){ ech=e; }

    //Methodes
        //ajoute une Tache a partir d'un formulaire Qt dans le projet
    template<class T>
    Tache& creerTache(const QString& t, const QDate& dispo, const QDate& deadline, const Duree& dur);

        //permet de savoir si la Tache existe ou pas a partir de son titre
    bool isTacheExistante(const QString& ti) const { return trouverTache(ti) != 0; }

        //retrouver une Tache (const ou non-const) a partir de son titre
    Tache* trouverTache(const QString& ti) const;
    Tache& getTache(const QString& ti)const;
    const Tache& getTacheConst(const QString& ti) const;

        //au niveau des fichiers
    void load(const QString& f);
    void save(const QString& f);
};


//=====Projet====================================================================================================
//Classe NON Abstraite
class ProjetManager{
    //fichier avec tous les noms des projets
    QString file;

    typedef std::vector<Projet *> proj;
    proj projet;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation
    ProjetManager(){
        projet.reserve(10);
    }
    ~ProjetManager(){
        if (file != "") save(file);
        projet.clear();
        projet.~vector();
        file = "";
    }
    ProjetManager(const ProjetManager& um);
    ProjetManager& operator=(const ProjetManager& um);

    //Methodes
    void addItem(Projet* t);
    Projet* trouverProjet(const QString& titre) const;

    //Singleton
    struct Handler{
        ProjetManager* instance;
        Handler() :instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:
    //Methodes
        //faire des template avec les methodes de la classe "Projet" !!
    Projet& ajouterProjet(const QString& ti, const QDate& dispo, const QDate& deadline);
    bool isProjetExistant(const QString& ti) const { return trouverProjet(ti) != 0; }
    Projet& getProjet(const QString& ti);
    const Projet& getProjet(const QString& ti) const;

        //au niveau des fichiers
    void load(const QString& f);
    void save(const QString& f);

        //pour le singleton
    static ProjetManager& getInstance();
    static void libererInstance();
};


};

#endif // MANAGER

