
#include "Interface.h"
#include "activite.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
try{
    int i;
    ProjetManager& pManager=ProjetManager::getInstance();
    qDebug()<<"2";
    Projet& project = pManager.creerProjet(QString("Projet X1"),QDate(),QDate());
    Projet& project2 = pManager.creerProjet(QString("Projet X2"),QDate(),QDate());
    Projet& project3 = pManager.creerProjet(QString("Projet X3"),QDate(),QDate());
    qDebug()<<"3";
    qDebug()<<project.getTitre();
    Tache& tache1 = project.creerTache(QString("Première tache"),QDate(),QDate(),Duree(),0);
    Tache& tache2 = project.creerTache(QString("Deuxième tache"),QDate(),QDate(),Duree(),1);
    Tache& tache3 = project.creerTache(QString("Troisième tache"),QDate(),QDate(),Duree(),2);
    dynamic_cast<TacheComposite&>(tache3).ajouterTacheComp(tache2);
    qDebug()<<"4";
    qDebug()<<tache1.getTitre();
    qDebug()<<typeid(tache1).name();
    qDebug()<<typeid(tache2).name();
    qDebug()<<typeid(tache3).name();

    Fenetre19 fenetre19(pManager);
    fenetre19.show();

    return app.exec();
    }
catch (const TimeException& e){
    qDebug()<<e.GetInfo();
    }
    return 0;
}
