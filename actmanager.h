#ifndef ACTMANAGER
#define ACTMANAGER

/*!
 * \file actmanager.h
 * \brief ActManager, manager des activites
 * \author Alice,Morgane
 * \version 0.1
 */


#include "timing.h"
#include "activite.h"

using namespace std;
using namespace TIME;


//=====ActManager========================================================================================
//Classe NON Abstraite
class ActManager{

    friend ActManager& getInstanceAct();

    //fichier avec tous les noms des activites
    QString file;

    typedef std::vector<ActiviteTrad*> ac;
    ac act;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation
    ActManager(){
        act.reserve(10);
    }
    ~ActManager(){
        //de-commente apres verification de la methode save
        //if (file != "") save(file);
        act.clear();
        act.~vector();
        //file = "";
    }
    ActManager(const ActManager& um);
    ActManager& operator=(const ActManager& um);


    //Methodes
        //ajoute une activite
    void ajouterAct(ActiviteTrad* p);
        //trouve une activite
    ActiviteTrad* trouverActP(const QString& titre) const;

    //Singleton
    struct Handler{
        ActManager* instance;
        Handler() :instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:
    //Methodes
        //Accesseur
    void setFile(const QString& f){file=f;}
    const ac& getAct() const {return act;}

        //ajouter un evenement a partir d'un formulaire
    ActiviteTrad& creerAct(const QString& t, const QString& lieu, const Duree& dur, const QString& type, int a);

    ActiviteTrad& trouverActR(const QString& ti);

        //permet de savoir si le evenement existe a partir de son titre
    bool isActExistant(const QString& ti) const { return trouverActP(ti) != 0; }

        //au niveau des fichiers
   // void load(const QString& f);
    //void save(const QString& f);

        //pour les iterateurs
    vector<ActiviteTrad*>::const_iterator Abegin(){return act.begin();}
    vector<ActiviteTrad*>::const_iterator Aend(){return act.end();}

        //pour le singleton
    static ActManager& getInstanceAct();
    static void libererInstanceAct();
};



#endif // ACTMANAGER

