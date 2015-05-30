#ifndef MANAGER
#define MANAGER


#include<iostream>
#include<QString>
#include <vector>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDate>
#include <QDebug>
#include <QFile>
#include "timing.h"

using namespace std;
namespace TIME {


    class TacheUnitaire;

    class Tache{

        QString titre;
        QDate dispo;
        QDate ech;
        Duree duree;

        typedef std::vector<Tache *> pred;
        pred precede;

    public:
        //constructuer et destruceur
        Tache::Tache(const QString& t, const QDate& d, const QDate& e, const Duree& du) :titre(t), dispo(d), ech(e), duree(du){
            precede.reserve(10);
            std::cout << "Construction Tache" << this << "\n";
        }
        virtual ~Tache(){ std::cout << "Destruction Tache" << this << "\n";}

        //accesseurs
        const QString& getTitre()const{ return titre; }
        const QDate& getDispo()const { return dispo; }
        const QDate& getEch()const { return ech; }
        const Duree& getDuree()const { return duree; }
        void setTitre(const QString& a){ titre = a; }
        void setDispo(const QDate& b){ dispo = b; }
        void setEch(const QDate& c){ ech = c; }
        void setDuree(const Duree& d){ duree = d; }

        //methodes
        // void Tache::afficher(ostream& f);
        virtual void extensionAffiche(ostream& f) = 0;
        virtual void ajouterTachePrec(Tache& t)=0;
     };



    class TacheUnitaire : public Tache{
    public:
        //constructeur et destructeur
        TacheUnitaire(const QString& t, const QDate& d, const QDate& e, const Duree& du, bool p) :Tache(t, d, e, du){
            if (du>12 || du=12) throw TimeException("erreur, la durée d'une tache unitaire (non preempte) ne peut pas exceder 12h");
            std::cout << "Construction TacheUnitaire" << this << "\n";
        }

        virtual ~TacheUnitaire(){std::cout << "Destruction TacheUnitaire" << this << "\n";}

        //methodes
        void extensionAffiche(ostream& f);
    };

    class TacheUnitaireNonPreempte : public TacheUnitaire{
    public:
        //constructeur et destructeur
        TacheUnitaireNonPreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du, bool p) :TacheUnitaire(t, d, e, du), preempte(p){
            std::cout << "Construction TacheUnitaireNonPreempte" << this << "\n";
        }
        virtual ~TacheUnitaireNonPreempte(){std::cout << "Destruction TacheUnitaireNonPreempte" << this << "\n";}
    };

    class Partie{
        Duree duree;
        Tache* tache;
    };

    class TacheUnitairePreempte : public TacheUnitaire{
        typedef std::vector<Partie*> par;
        par parties;

    public:
        //constructeur et destructeur
        TacheUnitairePreempte(const QString& t, const QDate& d, const QDate& e, const Duree& du) :titre(t), dispo(d), ech(e), duree(du){
            precede.reserve(10);
            std::cout << "Construction Tache" << this << "\n";
        }
        virtual ~TacheUnitairePreempte(){std::cout << "Destruction TacheUnitairePreempte" << this << "\n";}

        //methode
        //operateur + defini ??
        void ajouterPartie(Parties* p){
            parties.push_back(&p);
            setDuree(p->duree+getDuree());
        }

    };


    class TacheUnitaire : public Tache{
    public:
        //constructeur et destructeur
        virtual TacheUnitaire(const QString& t, const QDate& d, const QDate& e, const Duree& du, bool p) =0;
        virtual ~TacheUnitaire(){std::cout << "Destruction TacheUnitaire" << this << "\n";}

        //methodes
        void extensionAffiche(ostream& f);
    };



      class TacheComposite : public Tache{

        typedef std::vector<TacheUnitaire*> com;
        com compose;

      public:
        //constructeur et destructeur
        TacheComposite(const QString& t, const QDate& d, const QDate& e, const Duree& du):Tache(t, d, e, du){
            compose.reserve(10);
            std::cout << "Construction TacheComposite" << this << "\n";
        }
        virtual ~TacheComposite(){
            std::cout << "Destruction TacheComposite" << this << "\n";
        }

        //methodes
        // on peut rajouter des taches compose a des taches compose ?
        void extensionAffiche(ostream& f);
        void ajouterTacheUniComp(TacheUnitaire& t){
            cout << "je rajoute une tache unitaire qui compose cette tache"<<"\n";
                compose.push_back(&t);
        }
    };



    class Projet{

        QString titre;
        QDate dispo;
        QDate ech;
        QString file;

        typedef std::vector<Tache *> tac;
        tac taches;

        //constructeur et destructeur, recopie, affectation
        Projet(const QString& t, const QDate& d, const QDate& e) :titre(t), dispo(d), ech(e){
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
        Projet(const Projet& p);
        Projet& operator=(const Projet& p);

        //a implementer !!
        void addItem(Tache* t);

    public:
        //acceseurs en lecture
        const QString& getTitre()const{ return titre; }
        const QDate& getDispo()const { return dispo; }
        const QDate& getEch()const { return ech; }

        //methodes
        Tache* trouverTache(const QString& ti) const;
        virtual Tache& ajouterTache(const QString& t, const QDate& dispo, const QDate& deadline, const Duree& dur)=0;

        bool isTacheExistante(const QString& ti) const { return trouverTache(ti) != 0; }

        Tache& getTache(const QString& ti);
        const Tache& getTache(const QString& ti) const;

        void load(const QString& f);
        void save(const QString& f);
    };


    class ProjetManager{

        QString file;
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
        Projet& ajouterProjet(const QString& ti, const QDate& dispo, const QDate& deadline);

        bool isProjetExistant(const QString& ti) const { return trouverProjet(ti) != 0; }

        Projet& getProjet(const QString& ti);
        const Projet& getProjet(const QString& ti) const;

        void load(const QString& f);
        void save(const QString& f);

        static ProjetManager& getInstance();
        static void libererInstance();
    };


};

#endif // MANAGER

