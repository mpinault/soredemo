#ifndef ACTIVITE
#define ACTIVITE

#include <QString>
#include <iostream>
#include "timing.h"

using namespace std;
using namespace TIME;



///=====Evenement==================================================================================================
///Classe Abstraite
class Evenement {
private :
    QDate date;
protected :
    TIME::Horaire horaire;
public :

    ///***************Constructeur ET Destructeur****************************************
    Evenement(QDate& d, const TIME::Horaire& h): date(d), horaire(h){
    //gestion des erreurs quand la horaire+durée dépasse la fin de la jounée
    //calculer la date de fin et rajouter l'évènement sur les jours suivants si nécessaire
    }
    virtual ~Evenement() {}

    ///***************Accesseurs****************************************
    const QDate& getDate() const {return date;}
    const Horaire& getHoraire() const {return horaire;}

    ///***************Méthodes****************************************
    //Permet d'obtenir l'horaire de fin de l'évènement
    //Ici elle et virtuelle donc il faut la redéfinir dans ProgrammationActTrad et Programmationtache
    virtual QDate& getHoraireFin() const =0;

};


///=====Activité traditionelle==================================================================================================
///Classe Non Abstraite
class ActiviteTrad {
protected :
    QString titre;
    QString lieu;
    Duree duree;
    QString type;
public :
    ///***************Constructeur ET Destructeur****************************************
    ActiviteTrad(QString& t, QString& l, const Duree& d, QString& ty) : titre(t), lieu(l), duree(d), type(ty){}
    //le destructeur n'est pas nécessaire ici mais on le déclare en virtuelle si jamais on veut spécifier la classe
    virtual ~ActiviteTrad(){}

    ///***************Accesseurs****************************************
    QString getTitre() const {return titre;}
    QString getLieu() const {return lieu;}
    QString getType() const {return type;}
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
    Rdv(QString& t, QString& l,  const Duree& d, QString& p, QString ty) : ActiviteTrad(t,l,d,ty), personnes(p) {
        type=QString("Rendez-vous");
        std::cout<<"construction Rdv"<<this<<"\n";
    }
    virtual ~Rdv(){std::cout<<"destruction Rdv"<<this<<"\n";}

    ///***************Accesseurs****************************************
    QString getPersonnes() const {return personnes; }

    ///***************Méthodes****************************************
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" personnes="<<personnes.toStdString()<<"\n";
    }
};

///=====Reunion==================================================================================================
///Classe Non Abstraite
class Reunion : public ActiviteTrad {
    QString sujet;
public :

    ///***************Constructeur ET Destructeur****************************************
    Reunion(QString& t, QString& l,  const Duree& d, QString& s, QString ty="reunion") : ActiviteTrad(t,l,d,ty), sujet(s) {
        type="Réunion";
        std::cout<<"construction Réunion"<<this<<"\n";
    }
    virtual ~Reunion() { std::cout<<"destruction Réunion"<<this<<"\n";}

    ///***************Accesseurs****************************************
    QString getSujet() const {return sujet; }

    ///***************Méthodes****************************************
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" sujet="<<sujet.toStdString()<<"\n";
    }

};

///=====ProgrammationActTrad==================================================================================================
///Classe Non Abstraite
class ProgrammationActTrad : public Evenement {
    ActiviteTrad * activite;
public :

    ///***************Constructeur ET Destructeur****************************************
    ProgrammationActTrad(QDate& d, const Horaire& h, ActiviteTrad& a): Evenement(d, h), activite(&a){}
    virtual ~ProgrammationActTrad();

    ///***************Accesseurs****************************************
    ProgrammationActTrad * getProgrammationActTrad() const;

    ///***************Méthodes****************************************
    //Permet d'obtenir l'horaire de fin de l'évènement
   // QDate& getHoraireFin() const {
     //   return (horaire + activite->duree);
    //}
        //Je sais pas trop comment l'implémenter vu que durée est de type Duree et date de type QDate...
};

std::ostream& operator<<(std::ostream& f, const ActiviteTrad& a);
std::ostream& operator<<(std::ostream& f, const TIME::Duree& d);

#endif // ACTIVITE

