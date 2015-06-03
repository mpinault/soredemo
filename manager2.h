#ifndef MANAGER
#define MANAGER

using namespace std;
namespace TIME {


//=====Manager==============================================================================================
//Classe NON Abstraite,( un "tool" est soit un projet soit un evenement)
template <class T>
class Manager{
    //fichier avec tous les noms des tools
    QString file;

    typedef std::vector<T *> to;
    to tool;

    //Constructeur, Destructeur, Constructeur de recopie ET operateur d'affectation
    Manager(){tool.reserve(10); load(file);}
    ~Manager(){
        if (file != "") save(file);
        tool.clear();
        tool.~vector();
        file = "";
    }
    Manager(const manager& um);
    Manager& operator=(const manager& um);

    //Methodes
        //ajoute un tool
    void ajouterTool(T* p);
        //trouve un tool
    T* trouverTP(const QString& titre) const;

    //Singleton
    struct Handler{
        Manager* instance;
        Handler() :instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:
    //Methodes
        //ajouter un tool a partir d'un formulaire
    T& creerT(const QString& ti, const QDate& dispo, const QDate& deadline);
    T& trouverTR(const QString& ti);

        //permet de savoir si le tool existe a partir de son titre
    bool isTExistant(const QString& ti) const { return trouverTP(ti) != 0; }

        //au niveau des fichiers
    void load(const QString& f);
    void save(const QString& f);

        //pour le singleton
    static Manager& getInstance();
    static void libererInstance();
};


}



#endif // manager

