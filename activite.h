#ifndef ACTIVITE
#define ACTIVITE

/*!
 * \file activite.h
 * \brief les activites traditionnelles
 * \author Alice,Morgane
 * \version 0.1
 */

#include <QString>
#include <iostream>
#include "timing.h"
#include "tache.h"

using namespace std;
using namespace TIME;


///=====Evenement==================================================================================================
///Classe Abstraite
class Evenement {
private :
    QDate date;
protected :
    Horaire horaire;
public :

    ///***************Constructeur ET Destructeur****************************************
    Evenement(const QDate& d, const TIME::Horaire& h): date(d), horaire(h){
    //gestion des erreurs quand la horaire+durée dépasse la fin de la jounée
    //calculer la date de fin et rajouter l'évènement sur les jours suivants si nécessaire
    }
    virtual ~Evenement() {}

    ///***************Accesseurs****************************************
    const QDate& getDate() const {return date;}
    const Horaire& getHoraire() const {return horaire;}
    //afin de pouvoir connaitre le titre de l'activite ou de la tache
    virtual const QString& getTitre()=0;

    ///***************Méthodes****************************************
    //Permet d'obtenir l'horaire de fin de l'évènement
    //Ici elle et virtuelle donc il faut la redéfinir dans ProgrammationActTrad et Programmationtache
    virtual Horaire& getHoraireFin() =0;

};


///=====Activité traditionelle==================================================================================================
///Classe Non Abstraite
class ActiviteTrad {
protected :
    QString titre;
    QString lieu;
    Duree duree;
    QString type;
    bool prog;
public :
    ///***************Constructeur ET Destructeur****************************************
    ActiviteTrad(const QString& t, const QString& l, const Duree& d, const QString& ty) : titre(t), lieu(l), duree(d), type(ty),prog(0){}
    //le destructeur n'est pas nécessaire ici mais on le déclare en virtuelle si jamais on veut spécifier la classe
    virtual ~ActiviteTrad(){}

    ///***************Accesseurs****************************************
    QString getTitre() const {return titre;}
    QString getLieu() const {return lieu;}
    QString getType() const {return type;}
    bool getProg() const {return prog;}
    void setProg(int a){prog=a;}
    const Duree&  getDuree() const {return duree;}
    virtual void afficher(std::ostream& f= std::cout) const {
        f<<"***** Activite traditionelle********"<<"\n"<<"Titre="<<titre.toStdString()<<" lieu="<<lieu.toStdString()<<" Durée="
        //<<duree
        <<"Problème d'affichage de duree"
        <<" Type="<<type.toStdString()<<"\n";
    }
    //définir la méthode d'affichage
};


///=====Rendez-vous==================================================================================================
///Classe Non Abstraite
class Rdv : public ActiviteTrad {
    QString personnes;
public :
    ///***************Constructeur ET Destructeur****************************************
    Rdv(const QString& t,const QString& l,  const Duree& d,const QString& p) : ActiviteTrad(t,l,d,QString("Rendez-vous")), personnes(p) {
        std::cout<<"construction Rdv"<<this<<"\n";
    }
    virtual ~Rdv(){std::cout<<"destruction Rdv"<<this<<"\n";}

    ///***************Accesseurs****************************************
    QString getPersonnes() const {return personnes; }

    ///***************Méthodes****************************************
    /*
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" personnes="<<personnes.toStdString()<<"\n";
    }
    */
};

///=====Reunion==================================================================================================
///Classe Non Abstraite
class Reunion : public ActiviteTrad {
    QString sujet;
public :

    ///***************Constructeur ET Destructeur****************************************
    Reunion(const QString& t, const QString& l,  const Duree& d,const QString& s) : ActiviteTrad(t,l,d,QString("Réunion")),sujet(s){
        std::cout<<"construction Réunion"<<this<<"\n";
    }
    virtual ~Reunion() { std::cout<<"destruction Réunion"<<this<<"\n";}

    ///***************Accesseurs****************************************
    QString getSujet() const {return sujet; }

    ///***************Méthodes****************************************
    /*
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" sujet="<<sujet.toStdString()<<"\n";
    }*/

};

///=====ProgrammationActTrad==================================================================================================
///Classe Non Abstraite
class ProgrammationActTrad : public Evenement {
    ActiviteTrad * activite;
public :

    ///***************Constructeur ET Destructeur****************************************
    ProgrammationActTrad(const QDate& d, const Horaire& h,ActiviteTrad& a): Evenement(d, h), activite(&a){
        a.setProg(1);
    }
    virtual ~ProgrammationActTrad(){}

    ///***************Accesseurs****************************************
    ProgrammationActTrad * getProgrammationActTrad() const;
    const QString& getTitre()override{return activite->getTitre();}

    ///***************Méthodes****************************************
    //Permet d'obtenir l'horaire de fin de la tachce
   Horaire& getHoraireFin()override{
       qDebug()<<"On fait la somme de l'horaire er de la durée";
        return sommeH(horaire,activite->getDuree());
    }
};

///=====ProgrammationTache==================================================================================================
///Classe Non Abstraite
class ProgrammationTache : public Evenement {
    Tache * tache;
public :

    ///***************Constructeur ET Destructeur****************************************
    ProgrammationTache(const QDate& d, const Horaire& h,Tache& a): Evenement(d, h), tache(&a){
        a.setProg(1);
    }
    virtual ~ProgrammationTache(){}

    ///***************Accesseurs****************************************
    ProgrammationTache * getProgrammationTache() const;
    const QString& getTitre()override{return tache->getTitre();}

    ///***************Méthodes****************************************
    //Permet d'obtenir l'horaire de fin de la tachce
   Horaire& getHoraireFin() override{
        return sommeH(horaire,tache->getDuree());
    }
};

std::ostream& operator<<(std::ostream& f, const ActiviteTrad& a);
std::ostream& operator<<(std::ostream& f, const TIME::Duree& d);


#endif // ACTIVITE

