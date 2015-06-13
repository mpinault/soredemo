/*!
 * \file interface.cpp
 * \brief fenetres de l'application
 * \author Alice,Morgane
 * \version 0.1
 */

//=====07/06/15==============Morgane====================================================================================
#include "Interface.h"
#include "tache.h"
#include "projet.h"
#include "manager.h"
#include "evtmanager.h"
#include "actmanager.h"
#include "activite.h"
using namespace TIME;

Fenetre1::Fenetre1(){
    this->setWindowTitle(QString ("Fenêtre 1 : ProjectCalendar"));
    introduction = new QLabel("Bienvenue dans le projet Calendar, pour accéder aux différentes fonctionnalités appuyer sur START");

    start = new QPushButton("Start");
    start->setCursor(Qt::PointingHandCursor);

    couche = new QVBoxLayout;
    couche->addWidget(introduction);
    couche->addWidget(start);
    setLayout(couche);

    QObject::connect(start, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre1::ouvrirFenetre2() {ouvrirFenetre<Fenetre1,Fenetre2>(*this);}


Fenetre2::Fenetre2(){

    this->setWindowTitle(QString ("Fenêtre 2 : ProjectCalendar"));

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
    ouvrir = new QPushButton("Ajouter une Tache a une Tache Composite");
    quitter = new QPushButton("Quitter");

    creerTache->setCursor(Qt::PointingHandCursor);
    creerProjet->setCursor(Qt::PointingHandCursor);
    creerActTrad->setCursor(Qt::PointingHandCursor);
    vue_hebdomadaire->setCursor(Qt::PointingHandCursor);
    progEvt->setCursor(Qt::PointingHandCursor);
    vue_projets->setCursor(Qt::PointingHandCursor);
    ouvrir->setCursor(Qt::PointingHandCursor);
    quitter->setCursor(Qt::PointingHandCursor);

    couche = new QVBoxLayout;
    couche->addWidget(creerProjet);
    couche->addWidget(creerTache);
    couche->addWidget(creerActTrad);
    couche->addWidget(vue_hebdomadaire);
    couche->addWidget(progEvt);
    couche->addWidget(vue_projets);
    couche->addWidget(ouvrir);
    couche->addWidget(quitter);
    setLayout(couche);

    //QObject::connect(nouvel_evenement, SIGNAL(clicked()),this, SLOT(ouvrirFenetre3()));

    QObject::connect(creerTache, SIGNAL(clicked()),this, SLOT(ouvrirFenetre30()));
    QObject::connect(creerProjet, SIGNAL(clicked()),this, SLOT(ouvrirFenetre15()));
    QObject::connect(creerActTrad, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));
    QObject::connect(vue_hebdomadaire, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));
    QObject::connect(progEvt, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));
    QObject::connect(vue_projets, SIGNAL(clicked()),this, SLOT(ouvrirFenetre25()));
    QObject::connect(ouvrir, SIGNAL(clicked()),this, SLOT(ouvrirFenetre21()));
    QObject::connect(quitter, SIGNAL(clicked()),qApp, SLOT(quit()));
}



void Fenetre2::ouvrirFenetre30() {ouvrirFenetre<Fenetre2,Fenetre30>(*this);}
void Fenetre2::ouvrirFenetre15() {ouvrirFenetre<Fenetre2,Fenetre15>(*this);}
void Fenetre2::ouvrirFenetre8() {ouvrirFenetre<Fenetre2,Fenetre8>(*this);}
void Fenetre2::ouvrirFenetre4() {ouvrirFenetre<Fenetre2,Fenetre4>(*this);}
void Fenetre2::ouvrirFenetre5() {ouvrirFenetre<Fenetre2,Fenetre5>(*this);}
void Fenetre2::ouvrirFenetre21() {ouvrirFenetre<Fenetre2,Fenetre21>(*this);}
void Fenetre2::ouvrirFenetre25() {ouvrirFenetre<Fenetre2,Fenetre25>(*this);}


//on ne l'utilise pas pour l'instant ?
Fenetre3::Fenetre3(){
    this->setWindowTitle(QString ("Fenêtre 3 :ProjectCalendar"));
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
    this->setWindowTitle("Fenêtre 4 : Project Calendar");

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
    QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre6()));

}

void Fenetre4::ouvrirFenetre2() {ouvrirFenetre<Fenetre4,Fenetre2>(*this);}
void Fenetre4::ouvrirFenetre18() {ouvrirFenetre<Fenetre4,Fenetre18>(*this);}
void Fenetre4::ouvrirFenetre6() {
    Fenetre6* fenetre = new Fenetre6(jour_debut->date());
    this->close();
    fenetre->show();
}

Fenetre5::Fenetre5(){
    this->setWindowTitle("Fenêtre 5 : Project Calendar");

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
    this->setWindowTitle("Fenêtre 5 : Project Calendar");

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
//void Fenetre5::ouvrirFenetre10(){ouvrirFenetre<Fenetre5,Fenetre10>(*this);}




Fenetre30::Fenetre30(){
    this->setWindowTitle("Fenêtre 30 : Project Calendar");

    choix= new QLabel("Selectionner un projet:",this);

    projet=new QComboBox();
    ProjetManager& p=ProjetManager::getInstance();
    for (vector<Projet*>::const_iterator it = p.Pbegin(); it != p.Pend(); ++it){
        int i=1;
        projet->insertItem(i,(*it)->getTitre());
        i++;
    }

    indication = new QLabel("Sélectionner le type de tache :");
    uni = new QRadioButton("Tache Unitaire");
    compo= new QRadioButton("Tache Composite (tache composé à une tache du projet)");
    uni->setChecked(true);

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);

    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(choix);
    couche1->addWidget(projet);
    couche1->addStretch(1);

    couche3= new QVBoxLayout;
    couche3->addWidget(indication);
    couche3->addWidget(uni);
    couche3->addWidget(compo);

    couche2= new QHBoxLayout;
    couche2->addWidget(buttonBack);
    couche2->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche3);
    couche->addLayout(couche2);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetreC()));
}

void Fenetre30::ouvrirFenetre2(){ouvrirFenetre<Fenetre30,Fenetre2>(*this);}

void Fenetre30::ouvrirFenetreC() {
    if(uni->isChecked()){
        Fenetre10* fenetre = new Fenetre10(projet->currentText());
        this->close();
        fenetre->show();
    }
    if(compo->isChecked()){
        Fenetre27* fenetre = new Fenetre27(projet->currentText());
        this->close();
        fenetre->show();
    }

}


Fenetre31::Fenetre31(const QString& nomP):nomProjet(nomP){
    this->setWindowTitle("Fenêtre 31 : Project Calendar");

    indication= new QLabel("Selectionner la Tache Composite à laquelle vous voulez ajouter une tache:",this);

    tacheC=new QComboBox();
    ProjetManager& pM=ProjetManager::getInstance();
    Projet* projetCurrent=pM.trouverProjetP(nomProjet);
    for (vector<Tache*>::const_iterator it = projetCurrent->Tbegin(); it != projetCurrent->Tend(); ++it){
        int i=1;
        if (typeid(**it)==typeid(TacheComposite))tacheC->insertItem(i,(*it)->getTitre());
        else qDebug()<<typeid(**it).name();
        i++;
    }

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);

    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(indication);
    couche1->addWidget(tacheC);

    couche2= new QHBoxLayout;
    couche2->addWidget(buttonBack);
    couche2->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    setLayout(couche);

    qDebug()<<tacheC->currentText();
    qDebug()<<nomProjet;
    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre21()));
    QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre32()));
}

void Fenetre31::ouvrirFenetre21(){
    Fenetre21 * fenetre = new Fenetre21;
    this->close();
    fenetre->show();
}

void Fenetre31::ouvrirFenetre32() {
    qDebug()<<"fenetre31";
    qDebug()<<tacheC->currentText();
    qDebug()<<nomProjet;
        Fenetre32* fenetre = new Fenetre32(tacheC->currentText(),nomProjet);
        this->close();
        fenetre->show();
}

Fenetre32::Fenetre32(const QString& nomTacheC, const QString& nomP):nomProjet(nomP),nomTache(nomTacheC){
    this->setWindowTitle("Fenêtre 32 : Project Calendar");
    qDebug()<<"fenetre32\n";
    qDebug()<<nomTacheC;
    qDebug()<<nomProjet;


    indication= new QLabel("Selectionner la Tache  que vous voulez ajouter a la Tache Composite:",this);

    tacheC=new QComboBox();
    ProjetManager& pM=ProjetManager::getInstance();
    Projet* projetCurrent=pM.trouverProjetP(nomProjet);
    for (vector<Tache*>::const_iterator it = projetCurrent->Tbegin(); it != projetCurrent->Tend(); ++it){
        int i=1;
        if (((*it)->getTitre()!=nomTacheC)&&
                //(typeid(**it)!=typeid(TacheComposite))&&
                (!(*it)->getEstCompose()))tacheC->insertItem(i,(*it)->getTitre());
        qDebug()<<"Dans fenetre 32 : type de la tache : ";
        qDebug()<<typeid(**it).name();
        i++;
    }

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);

    buttonBack->setCursor(Qt::PointingHandCursor);
    buttonForward->setCursor(Qt::PointingHandCursor);

    couche1= new QVBoxLayout;
    couche1->addWidget(indication);
    couche1->addWidget(tacheC);

    couche2= new QHBoxLayout;
    couche2->addWidget(buttonBack);
    couche2->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(couche2);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre31()));
    QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirS()));
}


void Fenetre32::ouvrirFenetre31(){
    Fenetre31 * fenetre = new Fenetre31(nomProjet);
    this->close();
    fenetre->show();
}

void Fenetre32::ouvrirS() {

    ProjetManager& pM=ProjetManager::getInstance();
    Projet& projC=pM.trouverProjetR(nomProjet);
    //TacheComposite& tc=dynamic_cast<TacheComposite&>projC.trouverTacheR(nomTacheC);
    Tache& tc=projC.trouverTacheR(nomTache);

    Tache& tVacompose=projC.trouverTacheR(tacheC->currentText());
    dynamic_cast<TacheComposite&>(tc).ajouterTacheComp(tVacompose);
    QMessageBox::information(this, "Fenetre32", "Tache placé dans la Tache Composé selectionné!");
    ouvrirFenetre<Fenetre32,Fenetre2>(*this);

}

//=====10/06/15======Morgane============================================================================================
//La Fenêtre 6 affiche une vue hebdomadaire sous forme de tableau avec les évènements programmés
Fenetre6::Fenetre6(const QDate& d){
    this->setWindowTitle(QString ("Fenêtre 6 : ProjectCalendar"));
    this->setFixedSize(500,500);

    QVBoxLayout* couche;

    retour = new QPushButton("Retour au Menu");
    exporter = new QPushButton("Exporter la programmation");

    QDate firstDay = d;

    tab = new QTableWidget(24,7,this);
    tab->adjustSize();
    QStringList jours;
    for(unsigned int i=0; i<7; i++){
        jours.append(QString(firstDay.addDays(i).toString()));
    }
    tab->setHorizontalHeaderLabels(jours);

    QStringList heures;
    for(unsigned int i=0; i<25; i++){
        heures.append(QString(tr("%1 h").arg(i)));
    }
    tab->setVerticalHeaderLabels(heures);

    for(unsigned int i=0; i<24;i++){
        for(unsigned int j=0; j<7; j++){
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("0"));
                tab->setItem(i, j, newItem);
        }
    }

    EvtManager& e=EvtManager::getInstanceEvt();
    for(vector<Evenement*>::const_iterator eit = e.getEvenement().begin(); eit != e.getEvenement().end(); ++eit){
        qDebug()<<"La date de l'évènement est :";
        qDebug()<<(*eit)->getDate();

        if ((*eit)->getDate()>=d && (*eit)->getDate()<=d.addDays(7)){
            qDebug()<<"On est dans le if : la date est comprise dans l'intervalle";
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("1"));
            qDebug()<<"On est dans le if : l'heure de fin :";
            qDebug()<<(*eit)->getHoraire().getHeure();
            qDebug()<<"On est dans le if : le jour' :";
            qDebug()<<(*eit)->getDate().addDays(-d.day()).day();

            //On rajoute un 1 à l'heure de début quelque soit le type
            if((*eit)->getDate().addDays(-d.day()).day()==31)
                tab->setItem((*eit)->getHoraire().getHeure(),0, newItem);
            else tab->setItem((*eit)->getHoraire().getHeure(),(*eit)->getDate().addDays(-d.day()).day(), newItem);
        }

        qDebug()<<typeid(**eit).name();
       if(typeid(**eit)==typeid(ProgrammationActTrad)){
            qDebug()<<dynamic_cast<ProgrammationActTrad*>(*eit)->getDuree().getHeure();

        }
       if(typeid(**eit)==typeid(ProgrammationTache)){
            qDebug()<<dynamic_cast<ProgrammationTache*>(*eit)->getDuree().getHeure();
            for(unsigned int i=1 ; i<dynamic_cast<ProgrammationTache*>(*eit)->getDuree().getHeure();i++){
                QTableWidgetItem *newItem = new QTableWidgetItem(tr("1"));
                if((*eit)->getDate().addDays(-d.day()).day()==31)
                    tab->setItem((*eit)->getHoraire().getHeure()+i,0, newItem);
                else tab->setItem((*eit)->getHoraire().getHeure()+i,(*eit)->getDate().addDays(-d.day()).day(), newItem);
            }

        }

       //Rajouter le cas de programmation Partie de taches si on traite les taches préemptées.


        /*
        for (vector<Tache*>::const_iterator it = (*mit)->getTaches().begin(); it != (*mit)->getTaches().end(); ++it){
            QTreeWidgetItem* newTache = new QTreeWidgetItem(mainBranch, QStringList(QString("tache : %1").arg((*it)->getTitre())));
            items.append(newTache);
            if (typeid(*(*it))==typeid(TacheComposite))
                dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(newTache);
            qDebug()<<"sortie du if";
        }*/
    }
    couche = new QVBoxLayout;
    couche->addWidget(tab);
    setLayout(couche);
    couche->addWidget(retour);
    couche->addWidget(exporter);
    setLayout(couche);

    QObject::connect(retour, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre6::ouvrirFenetre2() {ouvrirFenetre<Fenetre6,Fenetre2>(*this);}


//fenetre pour choisir le type d'activite traditionnelle
Fenetre8::Fenetre8(){
    this->setWindowTitle("Fenêtre 8 : Project Calendar");

    titre= new QLabel("Selectionner le type d'Activité Traditionnelle que vous voulez créer:",this);

    reunion =new QPushButton("Réunion",this);
    rdv =new QPushButton("Rendez-Vous",this);
    autres =new QPushButton("Autres",this);

    annuler =new QPushButton("Annuler",this);

    reunion->setCursor(Qt::PointingHandCursor);
    rdv->setCursor(Qt::PointingHandCursor);
    autres->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);


    couche=new QVBoxLayout;
    couche->addWidget(titre);
    couche->addWidget(reunion);
    couche->addWidget(rdv);
    couche->addWidget(autres);
    couche->addWidget(annuler);
    setLayout(couche);

    QObject::connect(reunion, SIGNAL(clicked()),this, SLOT(ouvrirFenetre23()));
    QObject::connect(rdv, SIGNAL(clicked()),this, SLOT(ouvrirFenetre24()));
    QObject::connect(autres, SIGNAL(clicked()),this, SLOT(ouvrirFenetre22()));
    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre8::ouvrirFenetre2(){ouvrirFenetre<Fenetre8,Fenetre2>(*this);}
void Fenetre8::ouvrirFenetre22(){ouvrirFenetre<Fenetre8,Fenetre22>(*this);}
void Fenetre8::ouvrirFenetre23(){ouvrirFenetre<Fenetre8,Fenetre23>(*this);}
void Fenetre8::ouvrirFenetre24(){ouvrirFenetre<Fenetre8,Fenetre24>(*this);}

//formulaire reunion
Fenetre23::Fenetre23():QWidget(){

    this->setWindowTitle("Fenêtre 23 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Titre", this);
    titre=new QLineEdit(0, this);

    lieuLabel=new QLabel("Lieu", this);
    lieu=new QTextEdit(0, this);

    sujetLabel= new QLabel("Sujet",this);
    sujet= new QTextEdit(0,this);

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
    coucheH4->addWidget(sujetLabel);
    coucheH4->addWidget(sujet);

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

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverReunion()));

}


void Fenetre23::sauverReunion(){
    if (hDuree->value()<=12){
    ActManager& m=ActManager::getInstanceAct();

    m.creerAct(titre->text(),lieu->toPlainText(),Duree(hDuree->value(),mDuree->value()),sujet->toPlainText(),0);
    QMessageBox::information(this, "Sauvegarde", "Activité sauvegardée!");
    ouvrirFenetre<Fenetre23,Fenetre2>(*this);
    }
    else QMessageBox::information(this, "Fenetre23", "Durée d'une réunion ne peut excéder 12heures (on est pas des robots)' ");

    //faire la gestion des erreurs-> si le meme titre
    /*
    if (m.isActExistant(titre->text()))
    QMessageBox::warning(this, "Sauvegarde impossible", "Ce titre est deja utilisé!");
    else{
        m.creerAct(titre->text(),lieu->toPlainText(),sujet->toPlainText(),Duree(hDuree->depth(),mDuree->depth()),0);
        QMessageBox::information(this, "Sauvegarde", "Projet sauvegardée!");
    }*/
}

void Fenetre23::ouvrirFenetre8(){ouvrirFenetre<Fenetre23,Fenetre8>(*this);}

//formulaire rendez-vous
Fenetre24::Fenetre24():QWidget(){

    this->setWindowTitle("Fenêtre 24 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Titre", this);
    titre=new QLineEdit(0, this);

    lieuLabel=new QLabel("Lieu", this);
    lieu=new QTextEdit(0, this);

    persoLabel= new QLabel("Listes des Personnes");
    perso= new QTextEdit(0,this);

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
    coucheH4->addWidget(persoLabel);
    coucheH4->addWidget(perso);

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

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverRdv()));

}

void Fenetre24::ouvrirFenetre8(){ouvrirFenetre<Fenetre24,Fenetre8>(*this);}

void Fenetre24::sauverRdv(){

    if(hDuree->value()<=12){
    ActManager& m=ActManager::getInstanceAct();

    m.creerAct(titre->text(),lieu->toPlainText(),Duree(hDuree->value(),mDuree->value()),perso->toPlainText(),1);
    QMessageBox::information(this, "Sauvegarde", "Rdv sauvegardée!");
    ouvrirFenetre<Fenetre24,Fenetre2>(*this);

    }
    else QMessageBox::information(this, "Fenetre24", "Durée d'un rendez-vous ne peut excéder 12heures  ");

    //faire la gestion des erreurs-> si le meme titre
}


//formulaire autres
Fenetre22::Fenetre22():QWidget(){

    this->setWindowTitle("Fenêtre 22 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Titre", this);
    titre=new QLineEdit(0, this);

    lieuLabel=new QLabel("Lieu", this);
    lieu=new QTextEdit(0, this);

    typeLabel=new QLabel("Type de l'Activite", this);
    type=new QTextEdit(0, this);

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

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverAutres()));

}

void Fenetre22::ouvrirFenetre8() {ouvrirFenetre<Fenetre22,Fenetre8>(*this);}

void Fenetre22::sauverAutres(){

    if(hDuree->value()<=12){
    ActManager& a=ActManager::getInstanceAct();
    //if (EvenementManager::getInstance().trouverProjetR(projet->accessibleDescription()).isTacheExistante(titre->accessibleDescription()))
    //QMessageBox::warning(this, "Sauvegarde impossible", "Ce titre est deja utilisé!");

    a.creerAct(titre->text(),lieu->toPlainText(),Duree(hDuree->value(),mDuree->value()),type->toPlainText() ,2);

    QMessageBox::information(this, "Sauvegarde", "Activite sauvegardée!");
    ouvrirFenetre<Fenetre22,Fenetre2>(*this);
    }
    else QMessageBox::information(this, "Fenetre22", "Durée d'une activité ne peut excéder 12heures ");

}


Fenetre10::Fenetre10(QString recp){

    nomProjet=recp;

    this->setWindowTitle("Fenêtre 10 : Project Calendar");
    setFixedSize(800,500);

    preemptive=new QCheckBox("preemptive",this);

    titreLabel=new QLabel("titre", this);
    titre=new QLineEdit(0, this);

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

    sauver->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);
    coucheH2->addWidget(preemptive);

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
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH7);
    couche->addLayout(coucheH8);
    setLayout(couche);

     QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre30()));
     QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverTache()));
}

void Fenetre10::ouvrirFenetre30() {ouvrirFenetre<Fenetre10,Fenetre30>(*this);}

void Fenetre10::sauverTache(){
    if(echeance->date()>=disponibilite->date()){
    ProjetManager& p=ProjetManager::getInstance();
    if (preemptive->isChecked()){
         if (!(disponibilite->date().addDays((hDuree->value())/24)>echeance->date())){
         p.trouverProjetR(nomProjet).creerTache(titre->text(),disponibilite->date(),echeance->date(),Duree(hDuree->value(),mDuree->value()),1);
         QMessageBox::information(this, "Fenetre10", "Tache Preempte sauvegardée!");
         ouvrirFenetre<Fenetre10,Fenetre2>(*this);
         }
         else QMessageBox::information(this, "Fenetre10", "Date Début + durée > date échéance => ERREUR ");
    } else{
        if (!((hDuree->value()>12) ||(hDuree->value()>=12 && mDuree->value()>0))){
            p.trouverProjetR(nomProjet).creerTache(titre->text(),disponibilite->date(),echeance->date(),Duree(hDuree->value(),mDuree->value()),0);
            QMessageBox::information(this, "Fenetre10", "Tache Non Preempte sauvegardée!");
            ouvrirFenetre<Fenetre10,Fenetre2>(*this);
        }
        else
            QMessageBox::information(this, "Fenetre10", "Tache Non Preempte doit avoir une durée <12h !");

    }

}
    else 
        QMessageBox::information(this, "Fenetre10", "La date d'échéance doit être supérieure à la date de disponibilité !");
}        


Fenetre27::Fenetre27(QString recp){

    nomProjet=recp;
    this->setWindowTitle("Fenêtre 27 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("titre", this);
    titre=new QLineEdit(0, this);

    projetLabel=new QLabel("Vous pouvez créer une tache composite a partir de ce formulaire.\n"
                           " Pour y ajouter des taches, retourner au Menu et choisisez l'option :\n"
                           "       - 'Ajouter des taches a un tache Composite'.", this);

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

    sauver->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

    couche2 = new QHBoxLayout;
    couche2->addWidget(projetLabel);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

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
    couche->addLayout(couche2);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH7);
    couche->addLayout(coucheH8);
    setLayout(couche);

     QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre30()));
     QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverTacheCompo()));

}

void Fenetre27::ouvrirFenetre30() {ouvrirFenetre<Fenetre27,Fenetre30>(*this);}


void Fenetre27::sauverTacheCompo(){

    if (!(disponibilite->date().addDays((hDuree->value())/24)>echeance->date())){
       ProjetManager& man=ProjetManager::getInstance();
       man.trouverProjetR(nomProjet).creerTache(titre->text(),disponibilite->date(),echeance->date(),Duree(hDuree->value(),mDuree->value()),2);
       QMessageBox::information(this, "Fenetre27", "Tache Composite sauvegardée!");
       ouvrirFenetre<Fenetre27,Fenetre2>(*this);
    }
    else QMessageBox::information(this, "Fenetre27", "Date Début + durée > date échéance => ERREUR ");
}




Fenetre15::Fenetre15(){

    this->setWindowTitle("Fenêtre 15 : Project Calendar");
    setFixedSize(500,300);

    titreLabel=new QLabel("titre", this);

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());
    titre=new QLineEdit(0, this);

    echeanceLabel= new QLabel ("Echéance",this);
    echeance = new QDateEdit (QDate::currentDate());

    valider=new QPushButton("Valider", this);
    annuler=new QPushButton ("Annuler",this);

    valider->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

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
     QObject::connect(valider, SIGNAL(clicked()),this, SLOT(sauverProjet()));

}


void Fenetre15::sauverProjet(){

    ProjetManager& p=ProjetManager::getInstance();

    if (p.isProjetExistant(titre->text()))
    QMessageBox::warning(this, "Sauvegarde impossible", "Ce titre est deja utilisé!");
    else{
        if (echeance->date()<dateDebut->date()) QMessageBox::information(this, "Sauvegarde", "Il faut que l'échéance soit supérieure ou égale à la date de début!");
        else {
            p.creerProjet(titre->text(),dateDebut->date(),echeance->date());
            QMessageBox::information(this, "Sauvegarde", "Projet sauvegardée!");
            ouvrirFenetre<Fenetre15,Fenetre2>(*this);
        }
    }

}


void Fenetre15::ouvrirFenetre2() {ouvrirFenetre<Fenetre15,Fenetre2>(*this);}

Fenetre18::Fenetre18(){

    this->setWindowTitle("Fenêtre 18 : Project Calendar");
    setFixedSize(700,500);

    titreLabel1=new QLabel("Si vous voulez ajouter une Tache, selectionner un projet:", this);
    choix1=new QComboBox();
    ProjetManager& p=ProjetManager::getInstance();
    for (vector<Projet*>::const_iterator it = p.Pbegin(); it != p.Pend(); ++it){
        int i=1;
        choix1->insertItem(i,(*it)->getTitre());
        i++;
    }


    valider1=new QPushButton("Valider", this);
    valider1->setCursor(Qt::PointingHandCursor);

    titreLabel2=new QLabel("Sinon pour une Activité Traditionnelle, selectionner ci-dessous:", this);
    choix2=new QComboBox();
    ActManager& e=ActManager::getInstanceAct();
    for (vector<ActiviteTrad*>::const_iterator it = e.Abegin(); it != e.Aend(); ++it){
        int i=1;
        if(!(*it)->getProg()) choix2->insertItem(i,(*it)->getTitre());
        i++;
    }

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    horaireDebutLabel= new QLabel ("Horaire",this);
    horaireDebut = new QTimeEdit (QTime::currentTime());

    valider2=new QPushButton("Valider", this);
    valider2->setCursor(Qt::PointingHandCursor);

    annuler=new QPushButton ("Annuler",this);
    annuler->setCursor(Qt::PointingHandCursor);

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
    QObject::connect(valider1, SIGNAL(clicked()),this, SLOT(ouvrirFenetre19()));

}

void Fenetre18::ouvrirFenetre4() {ouvrirFenetre<Fenetre18,Fenetre4>(*this);}
void Fenetre18::ouvrirFenetre19() {
        Fenetre19* fenetre = new Fenetre19(choix1->currentText());
        this->close();
        fenetre->show();
}

Fenetre21::Fenetre21(){

    this->setWindowTitle("Fenêtre 21 : Project Calendar");
    //setFixedSize(800,500);

    titreLabel=new QLabel("Selectionner le projet:", this);
    choix=new QComboBox();
    ProjetManager& p=ProjetManager::getInstance();
    for (vector<Projet*>::const_iterator it = p.Pbegin(); it != p.Pend(); ++it){
        int i=1;
        choix->insertItem(i,(*it)->getTitre());
        i++;
    }

    valider=new QPushButton("Valider", this);
    annuler=new QPushButton ("Annuler",this);
    valider->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

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
    QObject::connect(valider, SIGNAL(clicked()),this, SLOT(ouvrirFenetreTC()));

}

void Fenetre21::ouvrirFenetre2() {ouvrirFenetre<Fenetre21,Fenetre2>(*this);}
void Fenetre21::ouvrirFenetreTC() {
        Fenetre31* fenetre = new Fenetre31(choix->currentText());
        this->close();
        fenetre->show();
}

Fenetre28::Fenetre28(const QString &titreTache, const QString &titreProjet):projCurr(ProjetManager::getInstance().trouverProjetR(titreProjet)),tachCurr(titreTache){
    this->setWindowTitle("Fenêtre 28 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Tache Unitaire Preempté \n \nSelectionner les données ci-dessous pour programmer les evenements: ", this);

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    horaireDebutLabel= new QLabel ("Horaire début", this);
    horaire=new QTimeEdit(QTime::currentTime());

    dureeLabel= new QLabel ("Durée",this);
    hDuree=new QSpinBox(this);
    hDuree->setMinimum(0);
    hDuree->setSuffix(" heure(s)");
    mDuree=new QSpinBox(this);
    mDuree->setMinimum(0);
    mDuree->setRange(0,59);
    mDuree->setSuffix(" minute(s)");

    sauver=new QPushButton("Sauver", this);
    annuler=new QPushButton ("Annuler",this);

    sauver->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);

    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(dateDebutLabel);
    coucheH3->addWidget(dateDebut);

    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(horaireDebutLabel);
    coucheH4->addWidget(horaire);

    coucheH5 = new QHBoxLayout;
    coucheH5->addWidget(dureeLabel);
    coucheH5->addWidget(hDuree);
    coucheH5->addWidget(mDuree);

    coucheH8 = new QHBoxLayout;
    coucheH8->addWidget(annuler);
    coucheH8->addWidget(sauver);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH8);
    setLayout(couche);

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    //QObject::connect(valider, SIGNAL(clicked()),this, SLOT(ouvrirFenetreTC()));

}

void Fenetre28::ouvrirFenetre2() {ouvrirFenetre<Fenetre28,Fenetre2>(*this);}

Fenetre29::Fenetre29(const QString& titreTache,const QString& titreProjet):projCurr(ProjetManager::getInstance().trouverProjetR(titreProjet)),tachCurr(titreTache){
    this->setWindowTitle("Fenêtre 29 : Project Calendar");
    setFixedSize(800,500);

    titreLabel=new QLabel("Tache Unitaire Non Preempté \n \nSelectionner les données ci-dessous pour programmer les evenements: ", this);

    dateDebutLabel= new QLabel ("Date début", this);
    dateDebut= new QDateEdit(QDate::currentDate());

    horaireDebutLabel= new QLabel ("Horaire début", this);
    horaire=new QTimeEdit(QTime::currentTime());

    sauver=new QPushButton("Sauver", this);
    annuler=new QPushButton ("Annuler",this);

    sauver->setCursor(Qt::PointingHandCursor);
    annuler->setCursor(Qt::PointingHandCursor);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);

    coucheH3 = new QHBoxLayout;
    coucheH3->addWidget(dateDebutLabel);
    coucheH3->addWidget(dateDebut);

    coucheH4 = new QHBoxLayout;
    coucheH4->addWidget(horaireDebutLabel);
    coucheH4->addWidget(horaire);

    coucheH8 = new QHBoxLayout;
    coucheH8->addWidget(annuler);
    coucheH8->addWidget(sauver);

    couche=new QVBoxLayout;
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH8);
    setLayout(couche);

    QObject::connect(annuler, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    QObject::connect(sauver, SIGNAL(clicked()),this, SLOT(sauverTache()));

}

void Fenetre29::ouvrirFenetre2() {ouvrirFenetre<Fenetre29,Fenetre2>(*this);}

void Fenetre29::sauverTache() {
    Tache& laTache=projCurr.trouverTacheR(tachCurr);
    QTime a=horaire->time();
    unsigned int heure=a.hour();
    unsigned int min=a.minute();
    Horaire h=Horaire(heure, min);

    if ((laTache.getDispo()<=dateDebut->date())&&(dateDebut->date().addDays((h.getHeure()+laTache.getDuree().getHeure())/24)<=laTache.getEch())){
         EvtManager& m=EvtManager::getInstanceEvt();
         Evenement& evt = m.creerEvenementTache(dateDebut->date(),h,laTache);
         QMessageBox::information(this, "Fenetre29", "evenement de Tache Preempte sauvegardé!");
         ouvrirFenetre<Fenetre29,Fenetre2>(*this);
    }
    else QMessageBox::information(this, "Fenetre29", "la date ou la durée n'est pas comprise dans la plage de disponibilité de la tache ");


}

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

//Fenêtre 19 :
Fenetre19::Fenetre19(const QString& nomProjet){
    p = ProjetManager::getInstance().trouverProjetP(nomProjet);
    this->setWindowTitle(QString ("Fenetre 19 : Ajout Evenement"));

    projet=new QLabel("Selectionner la tache :", this);
    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel(nomProjet);
    retour = new QPushButton("Annuler",this);
    valider = new QPushButton("Valider",this);
    retour->setCursor(Qt::PointingHandCursor);
    valider->setCursor(Qt::PointingHandCursor);
    cBox=new QComboBox();

    int i=1;

    QList<QTreeWidgetItem *> items;
    for (vector<Tache*>::const_iterator it = p->getTaches().begin(); it != p->getTaches().end(); ++it){
        if(!(*it)->getEstCompose()){
            QTreeWidgetItem* mainbranch = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("%1").arg((*it)->getTitre())));
            items.append(mainbranch);
            i++;
            if (typeid(*(*it))==typeid(TacheComposite))
                dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(mainbranch,cBox,i);
            else if (!(*it)->getProg()) cBox->insertItem(i,QString("%1").arg((*it)->getTitre()));
    }
    }
    treeWidget->insertTopLevelItems(0, items);

    ligne= new QHBoxLayout;
    ligne->addWidget(retour);
    ligne->addWidget(valider);
    couche = new QVBoxLayout;
    couche->addWidget(treeWidget);
    couche->addWidget(projet);
    couche->addWidget(cBox);
    couche->addLayout(ligne);
    setLayout(couche);
    qDebug()<<"8";

    QObject::connect(retour, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    QObject::connect(valider, SIGNAL(clicked()),this, SLOT(ouvrirFenetreChoix()));
}

void Fenetre19::ouvrirFenetre2() {ouvrirFenetre<Fenetre19,Fenetre2>(*this);}

void Fenetre19::ouvrirFenetreChoix() {
     //ProjetManager& pM=ProjetManager::getInstance();
    qDebug()<<"Fenetre19";
    qDebug()<<cBox->currentText();
    qDebug()<<p->getTitre();
    //qDebug()<<typeid(p->trouverTacheR(cBox->currentText()));


    //Tache Unitaire Preempte
    if( typeid(p->trouverTacheR(cBox->currentText()))==typeid(TacheUnitairePreempte)){
        qDebug()<<" preempte, on dirait ! ";
        Fenetre28* fenetre = new Fenetre28(cBox->currentText(),p->getTitre());
        this->close();
        fenetre->show();
    }
    //Tache Unitaire Non Preempte
    if(typeid(p->trouverTacheR(cBox->currentText()))==typeid(TacheUnitaireNonPreempte)){
         qDebug()<<"NON preempte, on dirait ! ";
        Fenetre29* fenetre = new Fenetre29(cBox->currentText(),p->getTitre());
        this->close();
        fenetre->show();
    }
}

//Elle est faite mais je ne vois pas trop quand est ce qu'elle est utile, je la laisse quand même pour l'instant...
//La Fenêtre 7 permet l'affichage d'un projet sous forme de TreeView
Fenetre7::Fenetre7(const Projet& p){
    this->setWindowTitle(QString ("Fenetre 7 : Affichage d'un projet"));

    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    retour = new QPushButton("Annuler",this);
    valider = new QPushButton("Valider",this);

    QList<QTreeWidgetItem *> items;
    for (vector<Tache*>::const_iterator it = p.getTaches().begin(); it != p.getTaches().end(); ++it){
        QTreeWidgetItem* mainbranch = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("tache : %1").arg((*it)->getTitre())));
        items.append(mainbranch);
        if (typeid(*(*it))==typeid(TacheComposite))
            dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(mainbranch);
    }
    treeWidget->insertTopLevelItems(0, items);

    ligne= new QHBoxLayout;
    ligne->addWidget(retour);
    ligne->addWidget(valider);
    couche = new QVBoxLayout;
    couche->addWidget(treeWidget);
    couche->addLayout(ligne);
    setLayout(couche);

    QObject::connect(retour, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre7::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre7,Fenetre2>(*this);
}



//Fenêtre 25 terminée
//La Fenêtre 25 permet d'avor une vue d'ensemble de tous les projets
Fenetre25::Fenetre25(){
    this->setWindowTitle(QString ("Fenetre 25 : Vue de l'ensemble des Projets"));
    ProjetManager& m=ProjetManager::getInstance();
    treeWidget = new QTreeWidget();
    treeWidget->setColumnCount(1);
    treeWidget->setHeaderLabel(QString("Ensemble des Projets :"));
    retour = new QPushButton("Retour au menu",this);

    QList<QTreeWidgetItem *> items;
    for(vector<Projet*>::const_iterator mit = m.getProjet().begin(); mit != m.getProjet().end(); ++mit){
        QTreeWidgetItem* mainBranch = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("%1").arg((*mit)->getTitre())));
        items.append(mainBranch);
        for (vector<Tache*>::const_iterator it = (*mit)->getTaches().begin(); it != (*mit)->getTaches().end(); ++it){
            if(!(*it)->getEstCompose()){
            QTreeWidgetItem* newTache = new QTreeWidgetItem(mainBranch, QStringList(QString("%1").arg((*it)->getTitre())));
            items.append(newTache);
            if (typeid(*(*it))==typeid(TacheComposite))
                dynamic_cast<TacheComposite*>(*it)->TacheComposite::ajouterTacheComparbre(newTache);
        }
        }
    }
    treeWidget->insertTopLevelItems(0, items);

    couche = new QVBoxLayout;
    couche->addWidget(treeWidget);
    couche->addWidget(retour);
    setLayout(couche);

    QObject::connect(retour, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre25::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre25,Fenetre2>(*this);
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
