#ifndef PROJETMANAGER
#define PROJETMANAGER
#include "timing.h"

using namespace std;
using namespace TIME;


//=====ProjetManager========================================================================================
//Classe NON Abstraite
class ProjetManager{
    //fichier avec tous les noms des projets
    QString file;

    typedef std::vector<Projet *> proj;
    proj projet;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation

    //Le constructeur de ProjetManager ne pouvait pas loader un fichier alors qu'il n'était pas initialiser du coup c'est get instance qui s'en occupe.
    ProjetManager(){
        projet.reserve(10);
    }
    //J'ai été obligée de mettre une ligne du destrcuteur en commentaire pcq sinon il détruisait le nom du fichier à loader dans la méthode load et
    //du coup ça plantait car il n'avait aucun fichier à ouvrir...
    ~ProjetManager(){
        if (file != "") save(file);
        projet.clear();
        projet.~vector();
        //file = "";
    }
    ProjetManager(const ProjetManager& um);
    ProjetManager& operator=(const ProjetManager& um);

    //Methodes
        //ajoute un projet
    void ajouterProjet(Projet* p);
        //trouve un projet
    Projet* trouverProjetP(const QString& titre) const;

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
        //Accesseur
    void setFile(const QString& f){file=f;}

        //ajouter un projet a partir d'un formulaire
    Projet& creerProjet(const QString& ti, const QDate& dispo, const QDate& deadline);
    Projet& trouverProjetR(const QString& ti);

        //permet de savoir si le projet existe a partir de son titre
    bool isProjetExistant(const QString& ti) const { return trouverProjetP(ti) != 0; }

        //au niveau des fichiers
    void load(const QString& f);
    void save(const QString& f);

        //pour le singleton
    static ProjetManager& getInstance();
    static void libererInstance();
};



#endif // PROJETMANAGER

