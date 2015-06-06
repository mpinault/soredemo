#ifndef INTERFACE
#define INTERFACE

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


template <class T1,class T2>
void ouvrirFenetre(T1& parent) {
        T2 * fenetre = new T2;
        parent.close();
        fenetre->show();
}


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

    QVBoxLayout* couche;

public :
    Fenetre2();
public slots :
    void ouvrirFenetre10();
    void ouvrirFenetre15();
    void ouvrirFenetre8();
    void ouvrirFenetre4();
    void ouvrirFenetre5();
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
    void ouvrirFenetre10();

};

class Fenetre10: public QWidget{
    Q_OBJECT

    QLabel* identificateurLabel;
    QLineEdit* identificateur;

    QCheckBox* preemptive;

    QLabel* titreLabel;
    QTextEdit* titre;

    QLabel* projetLabel;
    QComboBox* projet;

    QLabel* dateDebutLabel;
    QDateEdit* dateDebut;

    QLabel* horaireDebutLabel;
    QDateEdit* horaireDebut;

    QLabel* disponibiliteLabel;
    QDateEdit* disponibilite;

    QLabel* echeanceLabel;
    QDateEdit* echeance;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* couche2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QHBoxLayout* coucheH7;
    QHBoxLayout* coucheH8;
    QVBoxLayout* couche;

    public:

    explicit Fenetre10();

public slots:
    void ouvrirFenetre2();

};

/*
class Interface : public QWidget
{
    Q_OBJECT

public :
    Interface();
private :
    QPushButton * ajouter_evenement;
    QPushButton * afficher_taches;
    QPushButton * exporter_programmation;
    QPushButton * lundi;
    QPushButton * mardi;
    QPushButton * mercredi;
    QPushButton * jeudi;
    QPushButton * vendredi;
    QPushButton * samedi;
    QPushButton * dimanche;
    QGridLayout * grille;
    QVBoxLayout * boutons;
    QHBoxLayout * cadre;

};
*/

class Fenetre8 : public QWidget{

    Q_OBJECT
    QLabel* identificateurLabel;
    QLineEdit* identificateur;

    QLabel* titreLabel;
    QTextEdit* titre;

    QLabel* lieuLabel;
    QTextEdit* lieu;

    QLabel* typeLabel;
    QComboBox* type;

    QLabel* dureeLabel;
    QSpinBox* hDuree;
    QSpinBox* mDuree;

    QPushButton* sauver;
    QPushButton* annuler;

    QHBoxLayout* coucheH1;
    QHBoxLayout* coucheH2;
    QHBoxLayout* coucheH3;
    QHBoxLayout* coucheH4;
    QHBoxLayout* coucheH5;
    QHBoxLayout* coucheH6;
    QVBoxLayout* couche;

    public:
    explicit Fenetre8();

public slots:
     void ouvrirFenetre2();


};

class Fenetre15 : public QWidget
{
    Q_OBJECT
    QLabel* titreLabel;
    QTextEdit* titre;

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
    QDateEdit* horaireDebut;

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
};

#endif // INTERFACE

