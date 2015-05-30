
#include "Interface.h"

Fenetre1::Fenetre1(){
    this->setWindowTitle(QString ("ProjectCalendar"));
    introduction = new QLabel("Bienvenue dans le projet Calendar, pour accéder aux différentes fonctionnallités appuyer sur START");
    start = new QPushButton("Start");
    couche = new QVBoxLayout;
    couche->addWidget(introduction);
    couche->addWidget(start);
    setLayout(couche);

    QObject::connect(start, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
}

void Fenetre1::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre1,Fenetre2>(*this);
}

Fenetre2::Fenetre2(){
    this->setWindowTitle(QString ("ProjectCalendar"));
    nouvel_evenement = new QPushButton("Nouvel événement");
    vue_hebdomadaire = new QPushButton("Vue Hebdomadaire");
    vue_projets = new QPushButton("Vue ensemble des projets");
    couche = new QVBoxLayout;
    couche->addWidget(nouvel_evenement);
    couche->addWidget(vue_hebdomadaire);
    couche->addWidget(vue_projets);
    setLayout(couche);

    QObject::connect(nouvel_evenement, SIGNAL(clicked()),this, SLOT(ouvrirFenetre3()));
    QObject::connect(vue_hebdomadaire, SIGNAL(clicked()),this, SLOT(ouvrirFenetre4()));
    QObject::connect(vue_projets, SIGNAL(clicked()),this, SLOT(ouvrirFenetre5()));
}


void Fenetre2::ouvrirFenetre3() {
    ouvrirFenetre<Fenetre2,Fenetre3>(*this);

}

void Fenetre2::ouvrirFenetre4() {
    ouvrirFenetre<Fenetre2,Fenetre4>(*this);

}

void Fenetre2::ouvrirFenetre5() {
    ouvrirFenetre<Fenetre2,Fenetre5>(*this);
}


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

    choix= new QLabel("Sélectionner une semaine:",this);
    indication= new QLabel("Pour pouvoir vous aider a choisir la semaine :",this);

    buttonBack =new QPushButton("Revenir au Menu",this);
    buttonForward =new QPushButton("Valider",this);
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
    coucheB->addWidget(buttonForward);

    couche=new QVBoxLayout;
    couche->addLayout(couche1);
    couche->addLayout(coucheB);
    setLayout(couche);

    QObject::connect(buttonBack, SIGNAL(clicked()),this, SLOT(ouvrirFenetre2()));
    //QObject::connect(buttonForward, SIGNAL(clicked()),this, SLOT(ouvrirFenetre8()));

}

void Fenetre4::ouvrirFenetre2() {
    ouvrirFenetre<Fenetre4,Fenetre2>(*this);
}

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

void Fenetre5::ouvrirFenetre2(){
    ouvrirFenetre<Fenetre5,Fenetre2>(*this);
}

void Fenetre5::ouvrirFenetre10(){
    ouvrirFenetre<Fenetre5,Fenetre10>(*this);
}

Fenetre10::Fenetre10(){

    this->setWindowTitle("Project Calendar");
    setFixedSize(800,500);

    identificateurLabel= new QLabel ("identificateur", this);
    identificateur= new QLineEdit(0,this);

    preemptive=new QCheckBox("preemptive",this);

    titreLabel=new QLabel("titre", this);
    titre=new QTextEdit(0, this);

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
    //sauver->setEnabled(false);
    annuler=new QPushButton ("Annuler",this);

    coucheH1 = new QHBoxLayout;
    coucheH1->addWidget(identificateurLabel);
    coucheH1->addWidget(identificateur);
    coucheH1->addWidget(preemptive);

    coucheH2 = new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

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
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(coucheH5);
    couche->addLayout(coucheH6);
    couche->addLayout(coucheH7);
    couche->addLayout(coucheH8);
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
