#ifndef MANAGER
#define MANAGER

#include<string>
#include<iostream>
#include<QString>
#include <vector>
#include "timing.h"

using namespace std;
namespace TIME {

    class CalendarException{
        string info;
    public:
        CalendarException(const string& message) :info(message){}
        string getInfo() const { return info; }
    };

    class TacheUnitaire;

    class Tache{
        string titre;
        Date dispo;
        Date ech;
        Duree duree;

        typedef std::vector<TacheUnitaire *> pred;
        pred precede;

    public:
        //constructuer et destruceur
        Tache(const string& t, const Date& d, const Date& e, const Duree& du) :titre(t), dispo(d), ech(e), duree(du){
            precede.reserve(10);
            std::cout << "Construction Tache" << this << "\n";
        }
        virtual ~Tache(){
            std::cout << "Destruction Tache" << this << "\n";
        }

        //accesseurs
        const string& getTitre()const{ return titre; }
        const Date& getDispo()const { return dispo; }
        const Date& getEch()const { return ech; }
        const Duree& getDuree()const { return duree; }
        void setTitre(const string& a){ titre = a; }
        void setDispo(const Date& b){ dispo = b; }
        void setEch(const Date& c){ ech = c; }
        void setDuree(const Duree& d){ duree = d; }

        //methodes
        void Tache::afficher(ostream& f);
        virtual void extensionAffiche(ostream& f) = 0;
        void ajouterTacheUniPrec(TacheUnitaire& t){
            cout << "je rajoute une tache qui precede a cette tache" << "\n\n";
            precede.push_back(&t);
        }

     };

    class TacheUnitaire : public Tache{
        bool preempte;
    public:
        //constructeur et destructeur
        TacheUnitaire(const string& t, const Date& d, const Date& e, const Duree& du, bool p) :Tache(t, d, e, du), preempte(p){
            std::cout << "Construction TacheUnitaire" << this << "\n";
        }
        virtual ~TacheUnitaire(){
            std::cout << "Destruction TacheUnitaire" << this << "\n";
        }

        //accesseurs
        bool getPreempte()const { return preempte; }

        //methodes
        void extensionAffiche(ostream& f);
    };

      class TacheComposite : public Tache{
        typedef std::vector<TacheUnitaire*> com;
        com compose;
      public:
        //constructeur et destructeur
        TacheComposite(const string& t, const Date& d, const Date& e, const Duree& du):Tache(t, d, e, du){
            compose.reserve(10);
            std::cout << "Construction TacheComposite" << this << "\n";
        }
        virtual ~TacheComposite(){
            std::cout << "Destruction TacheComposite" << this << "\n";
        }
        //methodes
        void extensionAffiche(ostream& f);
        void ajouterTacheUniComp(TacheUnitaire& t){
            cout << "je rajoute une tache qui compose cette tache"<<"\n";
                compose.push_back(&t);
        }
    };


    class Projet{
        string titre;
        Date dispo;
        Date ech;

        typedef std::vector<Tache *> tac;
        tac taches;

        //constructeur et destructeur, recopie, affectation
        Projet(const QString& t, const Date& d, const Date& e) :titre(t), dispo(d), ech(e){
            taches.reserve(10);
            std::cout << "Construction Projet" << this << "\n";
        }
        ~Projet(){
            if (file != "") save(file);
            // detruit vraiment le vecteur ??
            taches.clear();
            taches.~vector();
            file = "";
            std::cout << "Destruction TacheComposite" << this << "\n";
        }
        Projet(const Projet& um);
        Projet& operator=(const Projet& um);

        //a implementer !!
        void addItem(Tache* t);

        QString file;
        Tache* trouverTache(const QString& ti) const;

    public:
        //acceseurs en lecture
        const string& getTitre()const{ return titre; }
        const Date& getDispo()const { return dispo; }
        const Date& getEch()const { return ech; }

        //methodes
        Tache& ajouterTacheUnitaire(const QString& t, const Date& dispo, const Date& deadline, const Duree& dur, bool preempt = false);
        Tache& getTache(const QString& ti);
        bool isTacheExistante(const QString& ti) const { return trouverTache(ti) != 0; }
        const Tache& getTache(const QString& ti) const;
        void load(const QString& f);
        void save(const QString& f);
    };


    class ProjetManager{

        typedef std::vector<Projet *> proj;
        proj projet;

        //constructeur et destructeur, recopie, affectation
        ProjetManager(){
            projet.reserve(10);
            std::cout << "Construction ProjetManager" << this << "\n";
        }
        ~ProjetManager(){
            if (file != "") save(file);
            // detruit vraiment le vecteur ??
            projet.clear();
            projet.~vector();
            file = "";
            std::cout << "Destruction TacheComposite" << this << "\n";
        }
        ProjetManager(const ProjetManager& um);
        ProjetManager& operator=(const ProjetManager& um);

        //a implementer !!
        void addItem(Projet* t);

        QString file;
        Projet* trouverProjet(const QString& titre) const;

        //singleton
        struct Handler{
            ProjetManager* instance;
            Handler() :instance(0){}
            // destructeur appelé à la fin du programme
            ~Handler(){ if (instance) delete instance; }
        };
        static Handler handler;

    public:
        //methodes
        Projet& ajouterProjet(const QString& ti, const Date& dispo, const Date& deadline);
        Projet& getProjet(const QString& ti);
        bool isProjetExistante(const QString& ti) const { return trouverProjet(ti) != 0; }
        const Projet& getProjet(const QString& ti) const;
        void load(const QString& f);
        void save(const QString& f);

        static ProjetManager& getInstance();
        static void libererInstance();
    };


};

#endif // MANAGER

