#ifndef INTERFACE
#define INTERFACE

/*!
 * \file interface.h
 * \brief fenetres de l'application
 * \author Alice,Morgane
 * \version 0.1
 */

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QBoxLayout>
#include <QMessageBox>
#include <QLabel>
#include <QString>
#include <QGroupBox>
#include <QRadioButton>
#include <QObject>
#include <QCalendarWidget>
#include <QKeySequenceEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>
#include <QLineEdit>
#include <QCheckBox>
#include <QTableWidget>

//=====07/06/15==============Morgane====================================================================================
//ajouts pour la fenêtre 19


#include "tache.h"
#include "projet.h"
#include "manager.h"



template <class T1,class T2>
void ouvrirFenetre(T1& parent) {
        T2 * fenetre = new T2;
        parent.close();
        fenetre->show();
}
/*
template <class T1,class T2>
void ouvrirFenetre(T1& parent,const Projet& p) {
        T2 * fenetre = new T2(p);
        parent.close();
        fenetre->show();
}
*/
class Fenetre1 : public QWidget
{
    Q_OBJECT
    QLabel* introduction;
    QPushButton* start;
    QVBoxLayout* couche;

public :
    Fenetre1();
public slots :
    void ouvrirFenetre2();

};


class Fenetre2 : public QWidget
{
    Q_OBJECT
    QPushButton* creerTache;
    QPushButton* creerProjet;
    QPushButton* creerActTrad;
    QPushButton* vue_hebdomadaire;
    QPushButton* progEvt;
    QPushButton* vue_projets;
    QPushButton* ouvrir;
    QPushButton* quitter;

    QVBoxLayout* couche;

public :
    Fenetre2();
public slots :
    void ouvrirFenetre30();
    void ouvrirFenetre15();
    void ouvrirFenetre8();
    void ouvrirFenetre4();
    void ouvrirFenetre5();
    void ouvrirFenetre21();
    void ouvrirFenetre25();
};



class Fenetre3 : public QDialog
{
    Q_OBJECT
    QGroupBox* type_evenement;
    QGroupBox* type_entree;
    QRadioButton* activite_traditionnelle;
    QRadioButton* tache;
    QRadioButton* formulaire;
    QRadioButton* importer;
    QPushButton* retour_menu;
    QPushButton* valider;
    QHBoxLayout* coucheH;
    QVBoxLayout* couche_t_evenement;
    QVBoxLayout* couche_t_entree;
    QVBoxLayout* couche;
public :
    Fenetre3();
public slots :
    void ouvrirFenetre2();
    void ouvrirFenetreChoix();
};

class Fenetre4 : public QDialog {
    Q_OBJECT
    QLabel* choix;
    QLabel* indication;

    QPushButton* buttonBack;
    QPushButton* buttonForward;
    QPushButton* ajoutEvt;

    QCalendarWidget* calend;
    QDateEdit* jour_debut;

    QVBoxLayout* couche1;
    QHBoxLayout* coucheB;
    QVBoxLayout* couche;
public :
    Fenetre4();
public slots :
    void ouvrirFenetre2();
    void ouvrirFenetre18();
    void ouvrirFenetre6();
};



class Fenetre5 : public QDialog {
    Q_OBJECT
    QLabel* choix;
    QPushButton* buttonBack;
    QPushButton* buttonForward;

    QVBoxLayout* couche1;
    QHBoxLayout* couche2;
    QVBoxLayout* couche;

    QComboBox* projet;
public :
    Fenetre5();
    Fenetre5(int i);

public slots :
    void ouvrirFenetre2();
    //void ouvrirFenetre7();
    //void ouvrirFenetre9();
    //void ouvrirFenetre10();

};


class Fenetre30 : public QDialog {
    Q_OBJECT
    QLabel* indication;
    QLabel* choix;
    QRadioButton* uni;
    QRadioButton* compo;
    QPushButton* buttonBack;
    QPushButton* buttonForward;

    QVBoxLayout* couche1;
    QHBoxLayout* couche2;
    QVBoxLayout* couche3;
    QVBoxLayout* couche;

    QComboBox* projet;
public :
    Fenetre30();

public slots :
    void ouvrirFenetre2();
    void ouvrirFenetreC();
};

//pour choisir la tache compose
class Fenetre31 : public QDialog {
    Q_OBJECT
    QLabel* indication;
    QComboBox* tacheC;

    QPushButton* buttonBack;
    QPushButton* buttonForward;

    QVBoxLayout* couche1;
    QHBoxLayout* couche2;
    QVBoxLayout* couche;

    QString nomProjet;
public :
    Fenetre31(const QString& nomProjet);
public slots :
    void ouvrirFenetre21();
    void ouvrirFenetre32();
};


//pour choisir la tache qu'on veut mettre dans une tache compose
class Fenetre32 : public QDialog {
    Q_OBJECT
    QLabel* indication;
    QComboBox* tacheC;

    QPushButton* buttonBack;
    QPushButton* buttonForward;

    QVBoxLayout* couche1;
    QHBoxLayout* couche2;
    QVBoxLayout* couche;

     QString nomProjet;
     QString nomTache;

public :
    Fenetre32(const QString& nomTacheC, const QString& nomP);
public slots :
    void ouvrirFenetre31();
    void ouvrirS();
};

//=====10/06/15==============Morgane====================================================================================
//La Fenêtre 6 affiche une vue hebdomadaire sous forme de tableau avec les évènements programmés
class Fenetre6 : public QWidget {

    Q_OBJECT

    QPushButton* retour;
    QPushButton* exporter;
    QVBoxLayout* couche;

    QTableWidget* tab;
public :
    Fenetre6(const QDate &d);
public slots :
    void ouvrirFenetre2();


};


class Fenetre10: public QWidget{
    Q_OBJECT

    QCheckBox* preemptive;

    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* projetLabel;
    QComboBox* pro;

    QLabel* disponibiliteLabel;
    QDateEdit* disponibilite;

    QLabel* echeanceLabel;
    QDateEdit* echeance;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* couche2;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QHBoxLayout* coucheH7;
    QHBoxLayout* coucheH8;
    QVBoxLayout* couche;

    QString nomProjet;
    //Projet* projetChoisie;

    public:
    explicit Fenetre10(QString recp);

public slots:
    void ouvrirFenetre30();
    void sauverTache();


};


//fenetre formulaire  pour creer des taches composite
//ouvert par la fenetre30
class Fenetre27: public QWidget{
    Q_OBJECT

    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* projetLabel;

    QLabel* horaireDebutLabel;
    QTimeEdit* horaire;

    QLabel* disponibiliteLabel;
    QDateEdit* disponibilite;

    QLabel* echeanceLabel;
    QDateEdit* echeance;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* couche2;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QHBoxLayout* coucheH7;
    QHBoxLayout* coucheH8;
    QVBoxLayout* couche;

    QString nomProjet;
    Projet* p;

    public:
    explicit Fenetre27(QString recp);

public slots:
    void ouvrirFenetre30();
    void sauverTacheCompo();

};

class Fenetre8 : public QWidget
{
    Q_OBJECT
    QLabel* titre;
    QPushButton* reunion;
    QPushButton* rdv;
    QPushButton* annuler;

    QPushButton* autres;
    QVBoxLayout* couche;


public :
    Fenetre8();
public slots :
    void ouvrirFenetre2();
    void ouvrirFenetre22();
    void ouvrirFenetre23();
    void ouvrirFenetre24();

};

class Fenetre23 : public QWidget{

    Q_OBJECT
    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* lieuLabel;
    QTextEdit* lieu;

    QLabel* sujetLabel;
    QTextEdit* sujet;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QVBoxLayout* couche;

    public:
    explicit Fenetre23();

public slots:
     void ouvrirFenetre8();
     void sauverReunion();
};

//formulaire rdv
class Fenetre24 : public QWidget{

    Q_OBJECT
    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* lieuLabel;
    QTextEdit* lieu;

    QLabel* persoLabel;
    QTextEdit* perso;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QVBoxLayout* couche;

    public:
    explicit Fenetre24();

public slots:
     void ouvrirFenetre8();
     void sauverRdv();
};


class Fenetre22 : public QWidget{

    Q_OBJECT
    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* lieuLabel;
    QTextEdit* lieu;

    QLabel* typeLabel;
    QTextEdit* type;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QVBoxLayout* couche;

    public:
    explicit Fenetre22();

public slots:
     void ouvrirFenetre8();
     void sauverAutres();


};

class Fenetre15 : public QWidget
{
    Q_OBJECT
    QLabel* titreLabel;
    QLineEdit* titre;

    QLabel* dateDebutLabel;
    QDateEdit* dateDebut;

    QLabel* echeanceLabel;
    QDateEdit* echeance;

    QPushButton* annuler;
    QPushButton* valider;

    QHBoxLayout* couche1;
    QHBoxLayout* couche2;
    QHBoxLayout* couche3;
    QHBoxLayout* couche4;

    QVBoxLayout* couche;

public :
    Fenetre15();
public slots :
    void ouvrirFenetre2();
    void sauverProjet();
};

class Fenetre18 : public QWidget
{
    Q_OBJECT
    QLabel* titreLabel1;
    QComboBox* choix1;
    QPushButton* valider1;

    QLabel* titreLabel2;
    QComboBox* choix2;

    QLabel* dateDebutLabel;
    QDateEdit* dateDebut;

    QLabel* horaireDebutLabel;
    QTimeEdit* horaireDebut;

    QPushButton* valider2;
    QPushButton* annuler;

    QVBoxLayout* couche1;
    QVBoxLayout* couche2;
    QHBoxLayout* couche3;
    QHBoxLayout* couche4;
    QHBoxLayout* couche5;
    QVBoxLayout* couche;

public :
    Fenetre18();
public slots :
        void ouvrirFenetre4();
        void ouvrirFenetre19();
        //void sauverTache();
};

//fenetre qui permet de selectionner un projet
class Fenetre21 : public QWidget
{
    Q_OBJECT
    QLabel* titreLabel;
    QComboBox* choix;

    QPushButton* valider;
    QPushButton* annuler;

    QVBoxLayout* couche1;
    QHBoxLayout* couche2;
    QVBoxLayout* couche;
public :
    Fenetre21();
public slots :
    void ouvrirFenetre2();
    void ouvrirFenetreTC();
};

class Fenetre28: public QWidget{
    Q_OBJECT

    QLabel* titreLabel;

    QLabel* dateDebutLabel;
    QDateEdit* dateDebut;

    QLabel* horaireDebutLabel;
    QTimeEdit* horaire;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH8;
    QVBoxLayout* couche;

    Projet& projCurr;
    QString tachCurr;

    public:
    explicit Fenetre28(const QString& titreTache,const QString& titreProjet);

public slots:
    void ouvrirFenetre2();
};

class Fenetre29: public QWidget{
    Q_OBJECT

    QLabel* titreLabel;

    QLabel* dateDebutLabel;
    QDateEdit* dateDebut;

    QLabel* horaireDebutLabel;
    QTimeEdit* horaire;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH8;
    QVBoxLayout* couche;

    Projet& projCurr;
    QString tachCurr;

    public:
    explicit Fenetre29(const QString& titreTache,const QString& titreProjet);

public slots:
    void ouvrirFenetre2();
    void sauverTache();
};


//=====07/06/15==============Morgane====================================================================================
//la fenêtre 19 est pour l'ajout d'évènement en tant que programmation d'un tache :
class Fenetre19 : public QWidget
{
    Q_OBJECT
    QTreeWidget* treeWidget;
    QLabel* projet;

    QHBoxLayout* ligne;
    QVBoxLayout* couche;

    QPushButton* retour;
    QPushButton* valider;

    QComboBox* cBox;
    Projet* p;

public :
    Fenetre19(const QString &nomProjet);
    QComboBox* getCBox()const {return cBox;}
public slots :
    void ouvrirFenetre2();
    void ouvrirFenetreChoix();

};

//La fenêtre 16 regroupe 16, 17 et 20 grâce à un constructeur avec un QString en paramètre
class Fenetre16 : public QWidget
{
    Q_OBJECT
    QLabel* text;
    QPushButton* menu;
    QVBoxLayout* couche;


public :
    Fenetre16(QString t);
public slots :
    void ouvrirFenetre2();

};

///Fenêtre7 : Elle est faite mais je ne vois pas trop quand est ce qu'elle est utile, je la laisse quand même pour l'instant...
//La Fenêtre 7 permet d'afficher un projet avec les taches qui lui sont rattachées sous forme de treeView
//permet d'appeler la fenêtre d'ajout d'une tache (Fenêtre ???)
class Fenetre7 : public QWidget
{
    Q_OBJECT
    QTreeWidget* treeWidget;
    QHBoxLayout* ligne;
    QVBoxLayout* couche;
    QPushButton* retour;
    QPushButton* valider;

    QComboBox* taches;

public :
    Fenetre7(const Projet& p);
public slots :
    void ouvrirFenetre2();
};

///Fenêtre 25 terminée
//la fenêtre 25 permet d'afficher une vue d'ensemble des projets (les différentes projets et leurs taches sous forme de TreeView)
class Fenetre25 : public QWidget
{
    Q_OBJECT
    QTreeWidget* treeWidget;
    QVBoxLayout* couche;
    QPushButton* retour;


public :
    Fenetre25();
public slots :
    void ouvrirFenetre2();

};
#endif // INTERFACE

