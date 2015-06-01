#ifndef ACTIVITE
#define ACTIVITE

#include <QString>
#include <iostream>
#include "timing.h"

using namespace std;
using namespace TIME;


template <class T>
class Evenement {
private :
    const T * activite;
    QDate date;
    Horaire horaire;
public :
    Evenement(const T& a, QDate& d, const Horaire& h): activite(&a), date(d), horaire(h){
    //gestion des erreurs quand la horaire+durée dépasse la fin de la jounée
    //calculer la date de fin et rajouter l'évènement sur les jours suivants si nécessaire
    }
    virtual ~Evenement() {}
    QDate& getDate() const {return date;}
    const Horaire& getHoraire() const {return horaire;}
    const T& getactivite() const {return activite;}
    QDate& getHoraireFin() const {
        return (horaire + activite->duree);
    }
        //Je sais pas trop comment l'implémenter vu que durée est de type Duree et date de type QDate...
};

class ActiviteTrad {
protected :
    QString titre;
    QString lieu;
    Duree duree;
    QString type;
public :
    ActiviteTrad(QString& t, QString& l, const Duree& d, QString& ty) : titre(t), lieu(l), duree(d), type(ty){}
    QString getTitre() const {return titre;}
    QString getLieu() const {return lieu;}
    QString getType() const {return type;}
    const Duree&  getDuree() const {return duree;}
    //void afficher(std::ostream& f= std::cout) const {
      //  f<<"***** Activite traditionelle********"<<"\n"<<"Titre="<<titre<<" lieu="<<lieu<<" Durée="<<duree<<" Type="<<type<<"\n";
    //}
    //définir la méthode d'affichage
};

class Rdv : public ActiviteTrad {
    QString personnes;
public :
    Rdv(QString& t, QString& l,  const Duree& d, QString& p, QString& ty="rendez-vous") : ActiviteTrad(t,l,d,ty), personnes(p) {
        type=QString("Rendez-vous");
        std::cout<<"construction Rdv"<<this<<"\n";
    }
    QString getPersonnes() const {return personnes; }
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" personnes="<<personnes<<"\n";
    }
    ~Rdv() { std::cout<<"destruction Rdv"<<this<<"\n";}
    };

class Reunion : public ActiviteTrad {
    QString sujet;
public :
    Reunion(QString& t, QString& l,  const Duree& d, QString& s, QString& ty="reunion") : ActiviteTrad(t,l,d,ty), sujet(s) {
        type="Réunion";
        std::cout<<"construction Réunion"<<this<<"\n";
    }
    QString getSujet() const {return sujet; }
    void afficher(std::ostream& f= std::cout) const {
        ActiviteTrad::afficher(f);
        f<<" sujet="<<sujet<<"\n";
    }
    ~Reunion() { std::cout<<"destruction Réunion"<<this<<"\n";}
    };
/*
class ProgrammationActTrad : public Evenement<ActiviteTrad> {
public :
    ProgrammationActTrad();
    ~ProgrammationActTrad();
    ProgrammationActTrad * getProgrammationActTrad() const;
};
*/


#endif // ACTIVITE

