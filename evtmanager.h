#ifndef EVTMANAGER
#define EVTMANAGER

/*!
 * \file evtManager.h
 * \brief EvtManager, manager des evenements
 * \author Alice,Morgane
 * \version 0.1
 */


#include "timing.h"
#include "activite.h"

using namespace std;
using namespace TIME;


//=====EvtManager========================================================================================
//Classe NON Abstraite
class EvtManager{

    friend EvtManager& getInstanceEvt();

    //fichier avec tous les noms des evenements
    QString file;

    typedef std::vector<Evenement*> ev;
    ev evt;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation
    EvtManager(){
        evt.reserve(10);
    }
    ~EvtManager(){
        //de-commente apres verification de la methode save
        //if (file != "") save(file);
        evt.clear();
        evt.~vector();
        //file = "";
    }
    EvtManager(const EvtManager& um);
    EvtManager& operator=(const EvtManager& um);

    //Methodes
        //ajoute un evenement
    void ajouterEvenement(Evenement* p);
        //trouve un evenement
    Evenement* trouverEvenementP(const QString& titre) const;

    //Singleton
    struct Handler{

        EvtManager* instance;
        Handler() :instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:
    //Methodes
        //Accesseur
    void setFile(const QString& f){file=f;}
    const ev& getEvenement() const {return evt;}

        //ajouter un evenement a partir d'un formulaire   
    Evenement& creerEvenementTache(const QDate& d, const Horaire &h, Tache &t);
    Evenement& creerEvenementAct(const QDate& d,const Horaire& h,ActiviteTrad& a);

    Evenement& trouverEvenementR(const QString& ti);

        //permet de savoir si le evenement existe a partir de son titre
    bool isEvenementExistant(const QString& ti) const { return trouverEvenementP(ti) != 0; }

        //au niveau des fichiers
    //void load(const QString& f);
    //void save(const QString& f);

        //pour les iterateurs
    vector<Evenement*>::const_iterator Ebegin(){return evt.begin();}
    vector<Evenement*>::const_iterator Eend(){return evt.end();}

        //pour le singleton
    static EvtManager& getInstanceEvt();
    static void libererInstanceEvt();
};

#endif // EVTMANAGER

