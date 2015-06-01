#include "manager.h"

using namespace TIME;
using namespace std;

//================================Methodes de Tache==========================================================================

//Methode virtuel mais qui a une definition dans la classe de base
void Tache::ajouterTachePrec(Tache& t){
    precede.push_back(&t);
}

//================================Methodes de TacheUnitaire==================================================================
//================================Methodes de TacheUnitaireNonPreempte=======================================================
//================================Methodes de TacheUnitairePreempte==========================================================

//On a besoin d'addition 2 durees.
//On va surcharger l'operateur '+'. -> voir "timing.h", classe "Duree"

void TacheUnitairePreempte::ajouterPartie(Partie* p){
    parties.push_back(p);
    setDuree(getDuree +p->getDuree());
}


//================================methodes de TacheComposite=================================================================

void TacheComposite::ajouterTacheComp(Tache& t){
    compose.push_back(&t);
}

//================================methodes de Projet=========================================================================
        //ajoute une Tache dans le projet
void Projet::ajouterTache(Tache* t){
    taches.push_back(t);
}

template<class T>
Tache& Projet::creerTache(const QString& t, const QDate& dispo, const QDate& deadline, const Duree& dur){
    if (isTacheExistante(t)) throw TimeException("erreur Projet, tache deja existante1");
    T newt = new T(t, dispo, deadline,dur);
    ajouterTache(newt);
    return *newt;
}

    //retrouver une Tache (const ou non-const) a partir de son titre
    //revoir la difference de ces trois methodes !!
Tache* Projet::trouverTache(const QString& ti)const{
    //si throw une erreur, sort de la fonction ? check
    if (isTacheExistante(ti)) throw TimeException("erreur Projet, tache deja existante2");
    for (vector<Tache*>::const_iterator it = taches.begin(); it != taches.end(); ++it){
        if (ti==(*it)->getTitre()) return it;
    }

    return 0;
}

Tache& Projet::getTache(const QString& ti)const{
    if (isTacheExistante(ti)) throw TimeException("erreur Projet, tache deja existante3");
    for (vector<Tache*>::iterator it = taches.begin(); it != taches.end(); ++it){
        if (ti==(*it)->getTitre()) return *it;
    }
    return 0;

}

const Tache& Projet::getTacheConst(const QString& ti)const{
    if (isTacheExistante(ti)) throw TimeException("erreur Projet, tache deja existante4");
    for (vector<Tache*>::const_iterator it = taches.begin(); it != taches.end(); ++it){
        if (ti==(*it)->getTitre()) return *it;
    }
    return 0;
}

        //au niveau des fichiers
void Projet::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~Projet();
    file = f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw TimeException("Erreur Projet, ouverture fichier");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while (!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if (token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if (token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if (xml.name() == "projet") continue;
            // If it's named tache, we'll dig the information from there.
            if (xml.name() == "projet") {
                qDebug() << "new tache\n";
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;

                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found titre.
                        if (xml.name() == "titre") {
                            xml.readNext(); titre = xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite
                        if (xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite = QDate::fromString(xml.text().toString(), Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if (xml.name() == "echeance") {
                            xml.readNext();
                            echeance = QDate::fromString(xml.text().toString(), Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if (xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                ajouterTache(titre, disponibilite, echeance, duree);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw TimeException("Erreur Projet, lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  Projet::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw TimeException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for (vector<TacheUnitaire*>::const_iterator it = taches.begin(); it != taches.end(); ++it){
        stream.writeStartElement("tache");
        stream.writeAttribute("preemptive", (typeid(*it).name==QString(TacheUnitairePreempte)) ? "true" : "false");
        stream.writeTextElement("titre", (*it)->getTitre());
        stream.writeTextElement("disponibilite", (*it)->getDispo().toString(Qt::ISODate));
        stream.writeTextElement("echeance", (*it)->getEch().toString(Qt::ISODate));
        QString str;
        str.setNum((*it)->getDuree().getDureeEnMinutes());
        stream.writeTextElement("duree", str);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


//================================methodes de ProjetManager=========================================================================

Projet* ProjetManager::trouverProjet(const QString& titre)const{
    for (std::vector<Projet*>::const_iterator it = projet.begin(); it != projet.end(); ++it)
        if ((*it)->getTitre()==titre) return *it;
    return 0;
}

Projet& ProjetManager::ajouterProjet(const QString& ti, const QDate& dispo, const QDate& deadline){
    if (trouverProjet(ti)) throw TimeException("erreur, ProjetManager, tache deja existante");
    Projet* newt = new Projet(ti, dispo, deadline);
    addItem(newt);
    return *newt;
}

Projet& ProjetManager::getProjet(const QString& ti){
    Tache* t = trouverProjet(ti);
    if (!t) throw TimeException("erreur, TacheManager, tache inexistante");
    return *t;
}

const ProjetManager& ProjetManager::getProjet(const QString& ti)const{
    return const_cast<ProjetManager*>(this)->getProjet(ti);
}

//singleton
ProjetManager::Handler ProjetManager::handler = ProjetManager::Handler();


ProjetManager& ProjetManager::getInstance(){
    if (handler.instance == 0) handler.instance = new ProjetManager;
    return *(handler.instance);
}

void ProjetManager::libererInstance(){
    if (handler.instance != 0) delete handler.instance;
    handler.instance = 0;
}

//au niveau des fichiers
void ProjetManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~ProjetManager();
    file = f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw TimeException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while (!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if (token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if (token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if (xml.name() == "taches") continue;
            // If it's named tache, we'll dig the information from there.
            if (xml.name() == "tache") {
                qDebug() << "new tache\n";
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if (attributes.hasAttribute("preemptive")) {
                    QString val = attributes.value("preemptive").toString();
                    preemptive = (val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if (xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found titre.
                        if (xml.name() == "titre") {
                            xml.readNext(); titre = xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite
                        if (xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite = QDate::fromString(xml.text().toString(), Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if (xml.name() == "echeance") {
                            xml.readNext();
                            echeance = QDate::fromString(xml.text().toString(), Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if (xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                Projet::creerTache(titre,disponibilite, echeance,duree);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw TimeException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  ProjetManager::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw TimeException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for (std::vector<Projet*>::const_iterator it = projet.begin(); it != projet.end(); ++it){
        stream.writeStartElement("projet");
        stream.writeTextElement("titre", (*it)->getTitre());
        stream.writeTextElement("disponibilite", (*it)->getDispo().toString(Qt::ISODate));

        stream.writeTextElement("echeance", (*it)->getEch().toString(Qt::ISODate));
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}
