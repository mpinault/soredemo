#ifndef ACTIVITE
#define ACTIVITE

/*!
 * \file activite.h
 * \brief les activites traditionnelles
 * \author Alice,Morgane
 * \version 0.1
 * \date 14 juin 2015
 *
 */

#include <QString>
#include <iostream>
#include "timing.h"
#include "tache.h"

using namespace std;
using namespace TIME;


/**
 * \class Evenement
 * \brief Classe non abstraite représentant un evenement.
 */

class Evenement {
private :
    QDate date; /*!< la date ou commence l'evenement*/
protected :
    Horaire horaire; /*!< l'horaire ou commence evenement*/
public :
    /**
     * \fn Evenement(const QDate& d, const TIME::Horaire& h)
     * \brief Constructeur
     * \param d : la date de l'evenement
     * \param h : l'horaire de l'evenement
     */
    Evenement(const QDate& d, const TIME::Horaire& h): date(d), horaire(h){
    //gestion des erreurs quand la horaire+durée dépasse la fin de la jounée
    //calculer la date de fin et rajouter l'évènement sur les jours suivants si nécessaire
    }
    /**
     * \fn virtual ~Evenement()
     * \brief Destructeur (virtuelle)
     */
    virtual ~Evenement() {}

    /**
     * \fn const QDate& getDate()
     * \brief Acceseur en lecture
     * \return une reference const de type QDate
     */
    const QDate& getDate() const {return date;}
    /**
     * \fn const Horaire& getHoraire()
     * \brief Acceseur en lecture
     * \return une reference const de type Horaire
     */
    const Horaire& getHoraire() const {return horaire;}
    /**
     * \fn virtual const QString& getTitre()
     * \brief Acceseur en lecture ( methode virtuelle pure), permet de connaitre le titre de l'activite ou de la tache
     * \return une reference const de type QString
     */
    virtual const QString& getTitre()=0;

    //Permet d'obtenir l'horaire de fin de l'évènement
    //Ici elle et virtuelle donc il faut la redéfinir dans ProgrammationActTrad et Programmationtache
    /**
     * \fn virtual Horaire& getHoraireFin()
     * \brief Acceseur en lecture ( methode virtuelle pure), permet de connaitre l'horaire de fin de l'evenement
     * \return une reference de type Horaire
     */
    virtual Horaire& getHoraireFin() =0;

};


/**
* \class ActiviteTrad
* \brief Classe non abstraite représentant une activite traditionnelle.
*/

class ActiviteTrad {
protected :
    QString titre; /*!< le titre de l'activite*/
    QString lieu;/*!< le lieu de l'activite*/
    Duree duree;/*!< la duree de l'activite*/
    QString type;/*!< le type de l'activite */
    bool prog;/*!< variable qui permet de savoir si l'activite a ete programme (prog=1 si oui)*/
public :
    /**
     * \fn ActiviteTrad(const QString& t, const QString& l, const Duree& d, const QString& ty)
     * \brief Constructeur
     * \param t : le titre de l'activite
     * \param l : le lieu de l'activite
     * \param d : la duree de l'activite
     * \param ty : le type de l'activite
     */
    ActiviteTrad(const QString& t, const QString& l, const Duree& d, const QString& ty) : titre(t), lieu(l), duree(d), type(ty),prog(0){}
    /**
     * \fn virtual ~ActiviteTrad()
     * \brief Destructeur
     */
    virtual ~ActiviteTrad(){}

    /**
     * \fn QString getTitre() const
     * \brief Acesseur en lecture pour connaitre le titre de l'acctivite
     * \return QString
     */
    QString getTitre() const {return titre;}

    /**
     * \fn QString getLieu() const
     * \brief Acesseur en lecture pour connaitre le lieu de l'activite
     * \return QString
     */
    QString getLieu() const {return lieu;}

    /**
     * \fn QString getType() const
     * \brief Acesseur en lecture pour connaitre le type de l'activite
     * \return QString
     */
    QString getType() const {return type;}

    /**
     * \fn bool getProg() const
     * \brief Acesseur en lecture pour connaitre la variable 'prog'
     * \return bool
     */
    bool getProg() const {return prog;}

    /**
     * \fn void setProg(int a)
     * \param a : la valeur qu'on veut donner a la variable 'prog'
     * \brief Acesseur en lecture pour connaitre la variable 'prog'
     * \return bool
     */
    void setProg(int a){prog=a;}

    /**
     * \fn const Duree&  getDuree() const
     * \brief Acesseur en lecture pour connaitre la duree de l'activite
     * \return une reference const de type Duree
     */
    const Duree&  getDuree() const {return duree;}
};


/**
* \class Rdv
* \brief Classe non abstraite représentant un rendez-vous.
*
* La classe Rdv herite publiquement de la classe ActiviteTrad.
*/
class Rdv : public ActiviteTrad {
    QString personnes;/*!< la liste des personnes participent a ce rendez-vous*/
public :
    /**
     * \fn Rdv(const QString& t,const QString& l,  const Duree& d,const QString& p)
     * \brief Constructeur
     * \param t : le titre du rendez-vous
     * \param l : le lieu du rendez-vous
     * \param d : la duree du rendez-vous
     * \param p : la liste des personnes presentes au rendez-vous
     */
    Rdv(const QString& t,const QString& l,  const Duree& d,const QString& p) : ActiviteTrad(t,l,d,QString("Rendez-vous")), personnes(p) {}
    /**
     * \fn virtual ~Rdv()
     * \brief Destructeur
     */
    virtual ~Rdv(){}

    /**
     * \fn  QString getPersonnes()
     * \brief Accesseur en lecture afin de connaitre la liste des personnes participant au rendez-vous
     * \return QString
     */
    QString getPersonnes() const {return personnes; }

};

/**
* \class Reunion
* \brief Classe non abstraite représentant une réunion.
*
* La classe Reunion herite publiquement de la classe ActiviteTrad.
*/
class Reunion : public ActiviteTrad {
    QString sujet;/*!< le sujet de la reunion*/
public :

    /**
     * \fn  Reunion(const QString& t, const QString& l,  const Duree& d,const QString& s)
     * \brief Constructeur
     * \param t : le titre de la reunion
     * \param l : le lieu de la reunion
     * \param d : la duree de la reunion
     * \param s : le sujet de la reunion
     */
    Reunion(const QString& t, const QString& l,  const Duree& d,const QString& s) : ActiviteTrad(t,l,d,QString("Réunion")),sujet(s){}
    /**
     * \fn virtual ~Reunion()
     * \brief Destructeur
     */
    virtual ~Reunion() {}

    /**
     * \fn  QString getSujet()
     * \brief Accesseur en lecture afin de connaitre la liste des personnes participant au rendez-vous
     * \return QString
     */
    QString getSujet() const {return sujet; }
};

/**
* \class ProgrammationActTrad
* \brief Classe non abstraite représentant la programmation d'une activite traditionnelle.
*
* La classe ProgrammationActTrad herite publiquement de la classe Evenement.
*/
class ProgrammationActTrad : public Evenement {
    ActiviteTrad * activite; /*!< l'activite sur lequel porte la programmation*/
public :

    /**
     * \fn  ProgrammationActTrad(const QDate& d, const Horaire& h,ActiviteTrad& a)
     * \brief Constructeur
     * \param d : la date a laquelle on veut programmer l'activité traditionnelle
     * \param h : l'horaire laquelle on veut programmer l'activité traditionnelle
     * \param a : l'activite traditionnelle
     */
    ProgrammationActTrad(const QDate& d, const Horaire& h,ActiviteTrad& a): Evenement(d, h), activite(&a){
        a.setProg(1);
    }
    /**
     * \fn virtual ~ProgrammationActTrad()
     * \brief Destructeur
     */
    virtual ~ProgrammationActTrad(){}

    /**
     * \fn  const QString& getTitre()override
     * \brief Accesseur en lecture afin de connaitre le titre de l'activite
     * \return une reference const de type QString
     */
    const QString& getTitre()override{return activite->getTitre();}
    /**
     * \fn  const Duree& getDuree()
     * \brief Accesseur en lecture afin de connaitre la duree de l'activite
     * \return une reference const de type Duree
     */
    const Duree& getDuree(){return activite->getDuree();}

    /**
     * \fn  Horaire& getHoraireFin()
     * \brief Accesseur en lecture afin de connaitre l'horaire de fin de l'activite
     * \return une reference de type Horaire
     */
   Horaire& getHoraireFin()override{
        return sommeH(horaire,activite->getDuree());
    }
};

/**
* \class ProgrammationTache
* \brief Classe non abstraite représentant la programmation d'une tache.
*
* La classe ProgrammationTache herite publiquement de la classe Evenement.
*/
class ProgrammationTache : public Evenement {
    Tache * tache; /*!< la tache sur lequel porte la programmation*/
public :

    /**
     * \fn ProgrammationTache(const QDate& d, const Horaire& h,Tache& a)
     * \brief Constructeur
     * \param d : la date a laquelle on veut programmer la tache
     * \param h : l'horaire laquelle on veut programmer la tache
     * \param a : la tache
     */
    ProgrammationTache(const QDate& d, const Horaire& h,Tache& a): Evenement(d, h), tache(&a){
        a.setProg(1);
    }

    /**
     * \fn virtual ~ProgrammationTache()
     * \brief Destructeur
     */
    virtual ~ProgrammationTache(){}

    /**
     * \fn const QString& getTitre()override
     * \brief Accesseur en lecture, afin de connaitre le titre de la tache
     * \return une reference const de type QString
     */
    const QString& getTitre()override{return tache->getTitre();}
    /**
     * \fn const Duree& getDuree()
     * \brief Accesseur en lecture, afin de connaitre la duree de la tache
     * \return une reference const de type Duree
     */
    const Duree& getDuree(){return tache->getDuree();}

    /**
     * \fn Horaire& getHoraireFin()
     * \brief Accesseur en lecture, afin de connaitre l'horaire de fin de la tachce
     * \return une reference de type Horaire
     */
   Horaire& getHoraireFin() override{
        return sommeH(horaire,tache->getDuree());
    }
};

#endif // ACTIVITE

