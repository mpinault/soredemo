
//=====07/06/15==============Morgane====================================================================================
#include "Interface.h"
#include "tache.h"
#include "projet.h"
#include "manager.h"
#include "activite.h"
using namespace TIME;

Fenetre1::Fenetre1(){
    this->setWindowTitle(QString ("ProjectCalendar"));
    introduction = new QLabel("Bienvenue dans le projet Calendar, pour accéder aux différentes fonctionnalités appuyer sur START");
    start = new QPushButton("Start");
    couche = new QVBoxLayout;
    couche->addWidget(introduction);
    couche->addWidget(start);
    setLayout(couche);

    QObject::connect(start, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre1::ouvrirFenetre2() {ouvrirFenetre<Fenetre1,Fenetre2>(*this);}


Fenetre2::Fenetre2(){

    this->setWindowTitle(QString ("ProjectCalendar"));

    QPushButton* creerTache;
    QPushButton* creerProjet;
    QPushButton* creerActTrad;
    QPushButton* vue_hebdomadaire;
    QPushButton* progEvt;
    QPushButton* vue_projets;

    QVBoxLayout* couche;

    creerTache = new QPushButton("Creer une nouvelle Tache");
    creerProjet = new QPushButton("Creer un nouveau Projet");
    creerActTrad = new QPushButton("Creer une nouvelle Activite Traditionnelle");
    vue_hebdomadaire = new QPushButton("Vue Hebdomadaire");
    progEvt = new QPushButton("Programmer un Evenement");
    vue_projets = new QPushButton("Vue ensemble des projets");
    ouvrir = new QPushButton("Ouvrir un agenda existant");
    quitter = new QPushButton("Quitter");

    couche = new QVBoxLayout;
    couche->addWidget(creerTache);
    couche->addWidget(creerProjet);
    couche->addWidget(creerActTrad);
    couche->addWidget(vue_hebdomadaire);
    couche->addWidget(progEvt);
    couche->addWidget(vue_projets);
    couche->addWidget(ouvrir);
    couche->addWidget(quitter);
    setLayout(couche);

    //QObject::connect(nouvel_evenement, SIGNAL(clicked()),this, SLOT(ouvrirFenetre3()));

    QObject::connect(creerTache, SIGNAL(clicked()),this, SLOT(ouvrirFenetre10()));
    QObject::connect(creerProjet, SIGNAL(clicked()),this, SLOT(ouvrirFenetre15()));
    QObject::connect(creerActTrad, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));
    QObject::connect(vue_hebdomadaire, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));
    QObject::connect(progEvt, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));
    QObject::connect(vue_projets, SIGNAL(clicked()),this, SLOT(ouvrirFenetre5()));
    QObject::connect(ouvrir, SIGNAL(clicked()),this, SLOT(ouvrirFenetre21()));
    //QObject::connect(quitter, SIGNAL(clicked()),this, SLOT(ouvrirFenetre5()));
}



void Fenetre2::ouvrirFenetre10() {ouvrirFenetre<Fenetre2,Fenetre10>(*this);}
void Fenetre2::ouvrirFenetre15() {ouvrirFenetre<Fenetre2,Fenetre15>(*this);}
void Fenetre2::ouvrirFenetre8() {ouvrirFenetre<Fenetre2,Fenetre8>(*this);}
void Fenetre2::ouvrirFenetre4() {ouvrirFenetre<Fenetre2,Fenetre4>(*this);}
void Fenetre2::ouvrirFenetre5() {ouvrirFenetre<Fenetre2,Fenetre5>(*this);}
void Fenetre2::ouvrirFenetre21() {ouvrirFenetre<Fenetre2,Fenetre21>(*this);}


Fenetre3::Fenetre3(){
    this->setWindowTitle(QString ("ProjectCalendar"));
    type_evenement = new QGroupBox("Sélectionner le type d'événement");
    activite_traditionnelle = new QRadioButton("Activité traditionelle");
    tache = new QRadioButton("Tâche liée à un projet");
    activite_traditionnelle->setChecked(true);
    couche_t_evenement = new QVBoxLayout;
    couche_t_evenement->addWidget(activite_traditionnelle);
    couche_t_evenement->addWidget(tache);
    couche_t_evenement->addStretch(1);
    type_evenement->setLayout(couche_t_evenement);

    type_entree = new QGroupBox("Sélectionner le type d'entrée");
    formulaire = new QRadioButton("Formulaire");
    importer = new QRadioButton("Importer");
    formulaire->setChecked(true);
    couche_t_entree = new QVBoxLayout;
    couche_t_entree->addWidget(formulaire);
    couche_t_entree->addWidget(importer);
    couche_t_evenement->addStretch(1);
    type_entree->setLayout(couche_t_entree);

    retour_menu = new QPushButton("Revenir au Menu");
    valider = new QPushButton("valider");
    coucheH = new QHBoxLayout;
    coucheH->addWidget(retour_menu);
    coucheH->addWidget(valider);

    couche = new QVBoxLayout;
    couche->addWidget(type_evenement);
    couche->addWidget(type_entree);
    couche->addLayout(coucheH);
    setLayout(couche);

    QObject::connect(retour_menu, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    QObject::connect(valider, SIGNAL(clicked()),this, SLOT(ouvrirFenetreChoix()));
}

void Fenetre3::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre3,Fenetre2>(*this);
}

void Fenetre3::ouvrirFenetreChoix() {
    /*
    if (activite_traditionnelle->isChecked() && formulaire->isChecked())
        ouvrirFenetre<Fenetre3,Fenetre8>(*this);
    if (activite_traditionnelle->isChecked() && importer->isChecked())
        ouvrirFenetre<Fenetre3,Fenetre8>(*this);
            */
    if (tache->isChecked() && formulaire->isChecked()){
        Fenetre5 * fenetre = new Fenetre5(0);
        this->close();
        fenetre->show();
    }

    if (tache->isChecked() && importer->isChecked()){
            Fenetre5 * fenetre = new Fenetre5(1);
            this->close();
            fenetre->show();
        }
}

Fenetre4::Fenetre4()
{
    this->setWindowTitle("Project Calendar");

    choix= new QLabel("Sélectionner le premier jour (pour avoir une vue):",this);
    indication= new QLabel("Pour pouvoir vous aider a choisir la semaine :",this);

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);
    ajoutEvt =new QPushButton("Ajouter un Evenement",this);

    jour_debut = new QDateEdit(QDate::currentDate());
    calend= new QCalendarWidget(0);
    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(choix);
    couche1->addWidget(jour_debut);
    couche1->addWidget(indication);
    couche1->addWidget(calend);

    coucheB= new QHBoxLayout;
    coucheB->addWidget(buttonBack);
    coucheB->addWidget(ajoutEvt);
    coucheB->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(coucheB);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    QObject::connect(ajoutEvt, SIGNAL(clicked()),this, SLOT(ouvrirFenetre18()));

}

void Fenetre4::ouvrirFenetre2() {ouvrirFenetre<Fenetre4,Fenetre2>(*this);}
void Fenetre4::ouvrirFenetre18() {ouvrirFenetre<Fenetre4,Fenetre18>(*this);}


Fenetre5::Fenetre5(){
    this->setWindowTitle("Project Calendar");

    choix= new QLabel("Selectionner un projet:",this);

    projet=new QComboBox();
    projet->insertItem(1,"projet A");
    projet->insertItem(2,"projet B");
    projet->insertItem(3,"projet C");

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);

    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(choix);
    couche1->addWidget(projet);
    couche1->addStretch(1);

    couche2= new QHBoxLayout;
    couche2->addWidget(buttonBack);
    couche2->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    //QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre7()));
    }

Fenetre5::Fenetre5(int i){
    this->setWindowTitle("Project Calendar");

    choix= new QLabel("Selectionner un projet:",this);

    projet=new QComboBox();
    projet->insertItem(1,"projet A");
    projet->insertItem(2,"projet B");
    projet->insertItem(3,"projet C");

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);

    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(choix);
    couche1->addWidget(projet);
    couche1->addStretch(1);

    couche2= new QHBoxLayout;
    couche2->addWidget(buttonBack);
    couche2->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    /*
    if (i==-1)
        QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre7()));
    if (i==1)
        QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre9()));
    */
    if (i==0)
        QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre10()));
}

void Fenetre5::ouvrirFenetre2(){ouvrirFenetre<Fenetre5,Fenetre2>(*this);}
void Fenetre5::ouvrirFenetre10(){ouvrirFenetre<Fenetre5,Fenetre10>(*this);}

Fenetre8::Fenetre8():QWidget(){

    this->setWindowTitle("Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Titre", this);
    titre=new QTextEdit(0, this);

    lieuLabel=new QLabel("Lieu", this);
    lieu=new QTextEdit(0, this);

    typeLabel= new QLabel("Type:",this);

    type=new QComboBox();
    type->insertItem(1,"Reunion");
    type->insertItem(2,"Rendez-vous");
    type->insertItem(3,"Autre");

    dureeLabel= new QLabel ("Durée",this);
    hDuree=new QSpinBox(this);
    hDuree->setMinimum(0);
    hDuree->setSuffix(" heure(s)");
    mDuree=new QSpinBox(this);
    mDuree->setMinimum(0);
    mDuree->setRange(0,59);
    mDuree->setSuffix(" minute(s)");


    sauver=new QPushButton("Valider", this);
    annuler=new QPushButton ("Revenir à la page précédente",this);

    sauver->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(lieuLabel);
    coucheH3->addWidget(lieu);

    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(typeLabel);
    coucheH4->addWidget(type);

    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(dureeLabel);
    coucheH5->addWidget(hDuree);
    coucheH5->addWidget(mDuree);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(annuler);
    coucheH6->addWidget(sauver);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH6);
    setLayout(couche);

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    //QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverActTrad()));

}

void Fenetre8::ouvrirFenetre2() {ouvrirFenetre<Fenetre8,Fenetre2>(*this);}
/*
void Fenetre8::sauverActTrad(){
    // on n'a pas EvenementManager !
    //if (EvenementManager::getInstance().trouverProjetR(projet->accessibleDescription()).isTacheExistante(titre->accessibleDescription()))
    QMessageBox::warning(this, "Sauvegarde impossible", "Ce titre est deja utilisé!");

    if (type->accessibleDescription()=="Reunion")Reunion(titre->accessibleDescription(),lieu->accessibleDescription(),0,Duree(hDuree->depth(),mDuree->depth()),type);
    if (type==2)Rdv(titre->accessibleDescription(),lieu->accessibleDescription(),Duree(hDuree->depth(),0,mDuree->depth()),type);
    else ActiviteTrad(titre->accessibleDescription(),lieu->accessibleDescription(),Duree(hDuree->depth(),mDuree->depth()),type);

    QMessageBox::information(this, "Sauvegarde", "Tache sauvegardée!");
}*/


Fenetre10::Fenetre10(){

    this->setWindowTitle("Project Calendar");
    setFixedSize(800,500);

    preemptive=new QCheckBox("preemptive",this);

    titreLabel=new QLabel("titre", this);
    titre=new QTextEdit(0, this);

    projetLabel=new QLabel("Projet associé a la tache:", this);
    projet=new QComboBox();

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    horaireDebutLabel= new QLabel ("Horaire début", this);
    horaireDebut= new QDateEdit(QDate::currentDate());

    dureeLabel= new QLabel ("Durée",this);
    hDuree=new QSpinBox(this);
    hDuree->setMinimum(0);
    hDuree->setSuffix(" heure(s)");
    mDuree=new QSpinBox(this);
    mDuree->setMinimum(0);
    mDuree->setRange(0,59);
    mDuree->setSuffix(" minute(s)");

    disponibiliteLabel= new QLabel("Disponibilité",this);
    disponibilite=new QDateEdit(QDate::currentDate());

    echeanceLabel= new QLabel ("Echéance",this);
    echeance = new QDateEdit (QDate::currentDate());

    sauver=new QPushButton("Sauver", this);
    annuler=new QPushButton ("Annuler",this);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH2->addWidget(preemptive);

    couche2 = new QHBoxLayout;
    couche2->addWidget(projetLabel);
    couche2->addWidget(projet);

    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(dateDebutLabel);
    coucheH3->addWidget(dateDebut);

    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(horaireDebutLabel);
    coucheH4->addWidget(horaireDebut);


    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(dureeLabel);
    coucheH5->addWidget(hDuree);
    coucheH5->addWidget(mDuree);

    coucheH6 = new QHBoxLayout;
    coucheH6->addWidget(disponibiliteLabel);
    coucheH6->addWidget(disponibilite);

    coucheH7 = new QHBoxLayout;
    coucheH7->addWidget(echeanceLabel);
    coucheH7->addWidget(echeance);

    coucheH8 = new QHBoxLayout;
    coucheH8->addWidget(annuler);
    coucheH8->addWidget(sauver);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH2);
    couche->addLayout(couche2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH7);
    couche->addLayout(coucheH8);
    setLayout(couche);

     QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
     QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverTache()));

}

void Fenetre10::ouvrirFenetre2() {ouvrirFenetre<Fenetre10,Fenetre2>(*this);}


void Fenetre10::sauverTache(){
    // ou creer l'instance de manager ?? (Alice , 07/06)
    if (ProjetManager::getInstance().trouverProjetR(projet->accessibleDescription()).isTacheExistante(titre->accessibleDescription()))
    QMessageBox::warning(this, "Sauvegarde impossible", "Ce titre est deja utilisé!");

    if (preemptive->isChecked())
        TacheUnitairePreempte(titre->accessibleDescription(),disponibilite->date(),echeance->date(),Duree(hDuree->depth(),mDuree->depth()));
    else TacheUnitaireNonPreempte(titre->accessibleDescription(),disponibilite->date(),echeance->date(),Duree(hDuree->depth(),mDuree->depth()));

    QMessageBox::information(this, "Sauvegarde", "Tache sauvegardée!");
}


Fenetre15::Fenetre15(){

    this->setWindowTitle("Project Calendar");
    setFixedSize(500,300);

    titreLabel=new QLabel("titre", this);
    titre=new QTextEdit(0, this);

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    echeanceLabel= new QLabel ("Echéance",this);
    echeance = new QDateEdit (QDate::currentDate());

    valider=new QPushButton("Valider", this);
    annuler=new QPushButton ("Annuler",this);

    couche1 = new QHBoxLayout;
    couche1->addWidget(titreLabel);
    couche1->addWidget(titre);

    couche2 = new QHBoxLayout;
    couche2->addWidget(dateDebutLabel);
    couche2->addWidget(dateDebut);

    couche3 = new QHBoxLayout;
    couche3->addWidget(echeanceLabel);
    couche3->addWidget(echeance);

    couche4 = new QHBoxLayout;
    couche4->addWidget(annuler);
    couche4->addWidget(valider);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    couche->addLayout(couche3);
    couche->addLayout(couche4);
    setLayout(couche);

     QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));

}

void Fenetre15::ouvrirFenetre2() {ouvrirFenetre<Fenetre15,Fenetre2>(*this);}

Fenetre18::Fenetre18(){

    this->setWindowTitle("Project Calendar");
    //setFixedSize(800,500);

    titreLabel1=new QLabel("Si vous voulez ajouter une Tache, selectionner un projet:", this);
    choix1=new QComboBox();

    valider1=new QPushButton("Valider", this);

    titreLabel2=new QLabel("Sinon pour une Tache Traditionnelle, selctionner ci-dessous:", this);
    choix2=new QComboBox();

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    horaireDebutLabel= new QLabel ("Echéance",this);
    horaireDebut = new QDateEdit (QDate::currentDate());

    valider2=new QPushButton("Valider", this);

    annuler=new QPushButton ("Annuler",this);

    couche1 = new QVBoxLayout;
    couche1->addWidget(titreLabel1);
    couche1->addWidget(choix1);
    couche1->addWidget(valider1);

    couche2 = new QVBoxLayout;
    couche2->addWidget(titreLabel2);
    couche2->addWidget(choix2);

    couche3 = new QHBoxLayout;
    couche3->addWidget(dateDebutLabel);
    couche3->addWidget(dateDebut);

    couche4 = new QHBoxLayout;
    couche4->addWidget(horaireDebutLabel);
    couche4->addWidget(horaireDebut);


    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    couche->addLayout(couche3);
    couche->addLayout(couche4);
    couche->addWidget(valider2);
    couche->addWidget(annuler);
    setLayout(couche);
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));

}

void Fenetre18::ouvrirFenetre4() {ouvrirFenetre<Fenetre18,Fenetre4>(*this);}

Fenetre21::Fenetre21(){

    this->setWindowTitle("Project Calendar");
    //setFixedSize(800,500);

    titreLabel=new QLabel("Selectionner l'agenda que vous voulez exporter:", this);
    choix=new QComboBox();

    valider=new QPushButton("Valider", this);
    annuler=new QPushButton ("Annuler",this);

    couche1 = new QVBoxLayout;
    couche1->addWidget(titreLabel);
    couche1->addWidget(choix);

    couche2 = new QHBoxLayout;
    couche2->addWidget(annuler);
    couche2->addWidget(valider);


    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    setLayout(couche);

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));

}

void Fenetre21::ouvrirFenetre2() {ouvrirFenetre<Fenetre21,Fenetre2>(*this);}

//=====07/06/15======Morgane============================================================================================

//La fenêtre 16 regroupe 16, 17 et 20 grâce à un constructeur avec un QString en paramètre
//Elle affiche une fenêtre qui indique que le résultat de lacréation ou de l'ajout
//peut être appelée par les fenêtres 15, 18, 19. Il passent en paramètre une chaîne de caractère qui indique le résultat (Echec/Succès de la création/ajout..)
Fenetre16::Fenetre16(QString t){
    this->setWindowTitle("Fenêtre 16 : Résultat de la création ou de l'ajout");
    text = new QLabel(t);
    menu = new QPushButton("Retour au menu");
    couche = new QVBoxLayout;
    couche->addWidget(text);
    couche->addWidget(menu);
    setLayout(couche);

    QObject::connect(menu, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre16::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre16,Fenetre2>(*this);
}

Fenetre19::Fenetre19(){
    this->setWindowTitle(QString ("Fenetre 19 : Ajout Evenement"));
    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);

    ProjetManager& pManager=ProjetManager::getInstance();
    Projet& project = pManager.creerProjet(QString("Projet A"),QDate(),QDate());
    Tache& tache1 = project.creerTache(QString("Première tache"),QDate(),QDate(),Duree(),0);

    QList<QTreeWidgetItem *> items;
    for (int i = 0; i < 1; ++i){
        QTreeWidgetItem* mainBranch = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("Projet 1 : %2").arg(i).arg(project.getTitre())));
        items.append(mainBranch);
        items.append(new QTreeWidgetItem(mainBranch, QStringList(QString("tache %1 : %2").arg(i).arg(tache1.getTitre()))));
    }
    treeWidget->insertTopLevelItems(0, items);

    couche = new QVBoxLayout;
    couche->addWidget(treeWidget);
    setLayout(couche);
}

/*
Interface::Interface() : QWidget()
{

    ajouter_evenement = new QPushButton("Ajouter évènement");
    afficher_taches = new QPushButton("Afficher tâches");
    exporter_programmation = new QPushButton("Exporter Programmation");

    boutons = new QVBoxLayout;
    boutons->addWidget(ajouter_evenement);
    boutons->addWidget(afficher_taches);
    boutons->addWidget(exporter_programmation);

    lundi = new QPushButton("lundi");
    mardi = new QPushButton("mardi");
    mercredi = new QPushButton("mercredi");
    jeudi = new QPushButton("jeudi");
    vendredi = new QPushButton("vendredi");
    samedi = new QPushButton("samedi");
    dimanche = new QPushButton("dimanche");

    grille = new QGridLayout;
    grille->addWidget(lundi,0,0);
    grille->addWidget(mardi,1,0);
    grille->addWidget(mercredi,2,0);
    grille->addWidget(jeudi,3,0);
    grille->addWidget(vendredi,4,0);
    grille->addWidget(samedi,5,0);
    grille->addWidget(dimanche,6,0);

    cadre = new QHBoxLayout;
    cadre->addLayout(grille);
    cadre->addLayout(boutons);
    setLayout(cadre);

    QObject::connect(m_slider, SIGNAL(valueChanged(int)), this, SLOT(changerLargeur(int))) ;
    QObject::connect(m_slider_h, SIGNAL(valueChanged(int)), this, SLOT(changerHauteur(int))) ;
    QObject::connect(this, SIGNAL(agrandissementMax()), qApp, SLOT(quit())) ;
    QObject::connect(m_boutonDialogue, SIGNAL(clicked()), this, SLOT(ouvrirDialogue())) ;
    QObject::connect(m_boutonDialoguePolice, SIGNAL(clicked()), this, SLOT(ouvrirDialoguePolice())) ;
    QObject::connect(m_boutonDialogueCouleur, SIGNAL(clicked()), this, SLOT(ouvrirDialogueCouleur())) ;
    QObject::connect(m_boutonDialogueFichier, SIGNAL(clicked()), this, SLOT(ouvrirDialogueFichier())) ;
    QObject::connect(m_boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit())) ;

    QObject::connect(m_boutonFenetre, SIGNAL(clicked()), this, SLOT(ouvrirSecondeFenetre())) ;

}
void MaFenetre::changerLargeur(int largeur)
{
    setFixedSize(largeur, height());
    if (largeur==600)
    {
        emit agrandissementMax();
    }
}

void MaFenetre::changerHauteur(int hauteur)
{
    setFixedSize(width(), hauteur);
}


void MaFenetre::ouvrirDialogue()
{
    bool ok = false;
    QString pseudo = QInputDialog::getText(this, "Pseudo", "Quel est votre pseudo ?", QLineEdit::Normal, QString(), &ok);

    if (ok && !pseudo.isEmpty())
    {
        m_boutonDialogue->setText("Bonjour " + pseudo + ", ça va ?");
        QMessageBox::information(this, "Pseudo", "Bonjour " + pseudo + ", ça va ?");
    }
    else
    {
        QMessageBox::critical(this, "Pseudo", "Vous n'avez pas voulu donner votre nom… snif.");
    }
}

void MaFenetre::ouvrirDialoguePolice()
{
    bool ok = false;

    QFont police = QFontDialog::getFont(&ok, m_boutonDialoguePolice->font(), this, "Choisissez une police");

    if (ok)
    {
        m_boutonDialoguePolice->setFont(police);
    }
}

void MaFenetre::ouvrirDialogueCouleur()
{
    QColor couleur = QColorDialog::getColor(Qt::white, this);

    QPalette palette;
    palette.setColor(QPalette::ButtonText, couleur);
    m_boutonDialogueCouleur->setPalette(palette);
}

void MaFenetre::ouvrirDialogueFichier()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
}

void MaFenetre::ouvrirSecondeFenetre()
{
    QDialog * secondeFenetre = new QDialog;
    QVBoxLayout * sec_couche = new QVBoxLayout;

    QLabel *texte = new QLabel(secondeFenetre);

    QLabel *image = new QLabel;
    image->setPixmap((QPixmap("10003086_10203198988237029_1713421257_n.jpg")));
    texte->setText("Seconde Fenêtre ! Youpi ça marche !");

    sec_couche->addWidget(image);
    sec_couche->addWidget(texte);

    secondeFenetre->setLayout((sec_couche));

    secondeFenetre->exec();
}
*/
