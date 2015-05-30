#include "manager.h"
#include <QXmlStreamReader>
#include <QDate>
#include <QDebug>
#include <QFile>
using namespace TIME;
using namespace std;

//================================methodes de Tache==========================================================================

void Tache::afficher(ostream& f){
    f << "---Tache "<<titre<< "----------------------------------------- "<<"\n";
    f << "disponiblite=" << dispo << ",écheance=" << ech << ",duree=" << duree << "\n";
    extensionAffiche(f);
    if (precede.size()){
        for (std::vector<TacheUnitaire*>::const_iterator it = precede.cbegin(); it != precede.cend(); ++it)
            (*it)->afficher(f<<"===");
    }
    else  f << "pas de taches precedentes" << "\n\n";

}

//================================methodes de TacheUnitaire==================================================================

void TacheUnitaire::extensionAffiche(ostream& f){
    f << "preempte=" << preempte << "\n";
};

//================================methodes de TacheComposite=================================================================

void TacheComposite::extensionAffiche(ostream& f){
    if (compose.size()){
        for (std::vector<TacheUnitaire*>::const_iterator it = compose.cbegin(); it != compose.cend(); ++it)
            (*it)->afficher(f << "###");
    }
    else  f << "pas de taches composes" << "\n";

}

//================================methodes de Projet=========================================================================
Tache* Projet::trouverTache(const QString& ti)const{
    for (vector<Tache*>::const_iterator it = taches.cbegin(); it != taches.cend(); ++it)
        if (ti==(*it)->getTitre()) return *it;
    return 0;
}


Tache& Projet::ajouterTacheUnitaire(const QString& t, const Date& dispo, const Date& deadline, const Duree& dur, bool preempt){
    if (trouverTache(t)) throw CalendarException("erreur, TacheManager, tache deja existante");
    TacheUnitaire* newt = new TacheUnitaire(t, dur, dispo, deadline, preempt);
    addItem(newt);
    return *newt;
}

Tache& Projet::getTache(const QString& ti){
    Tache* t = trouverTache(ti);
    if (!t) throw CalendarException("erreur, Projet, tache inexistante");
    return *t;
}

const Tache& Projet::getTache(const QString& ti)const{
    return const_cast<Projet*>(this)->getTache(ti);
}


void Projet::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~Projet();
    file = f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
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
                bool preempt;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if (attributes.hasAttribute("preemptive")) {
                    QString val = attributes.value("preemptive").toString();
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

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
                ajouterTacheUnitaire(titre, disponibilite, echeance, duree, preempt);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  Projet::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for (vector<TacheUnitaire*>::const_iterator it = taches.cbegin(); it != taches.cend(); ++it){
        stream.writeStartElement("tache");
        stream.writeAttribute("preemptive", ((*it)->getPreempte()) ? "true" : "false");
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
    for (std::vector<Projet*>::const_iterator it = projet.cbegin(); it != projet.cend(); ++it)
        if ((*it)->getTitre()==titre) return *it;
    return 0;
}

Projet& ProjetManager::ajouterProjet(const QString& ti, const Date& dispo, const Date& deadline){
    if (trouverProjet(ti)) throw CalendarException("erreur, ProjetManager, tache deja existante");
    Projet* newt = new Projet(ti, dispo, deadline);
    addItem(newt);
    return *newt;
}

Projet& ProjetManager::getProjet(const QString& ti){
    Tache* t = trouverProjet(ti);
    if (!t) throw CalendarException("erreur, TacheManager, tache inexistante");
    return *t;
}

const ProjetManager& ProjetManager::getProjet(const QString& ti)const{
    return const_cast<ProjetManager*>(this)->getProjet(ti);
}


ProjetManager::Handler ProjetManager::handler = ProjetManager::Handler();

ProjetManager& ProjetManager::getInstance(){
    if (handler.instance == 0) handler.instance = new ProjetManager;
    return *(handler.instance);
}

void ProjetManager::libererInstance(){
    if (handler.instance != 0) delete handler.instance;
    handler.instance = 0;
}


void ProjetManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~ProjetManager();
    file = f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
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
                QString identificateur;
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
                        // We've found identificteur.
                        if (xml.name() == "identificateur") {
                            xml.readNext(); identificateur = xml.text().toString();
                            //qDebug()<<"id="<<identificateur<<"\n";
                        }

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
                ajouterTache(identificateur, titre, duree, disponibilite, echeance, preemptive);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  ProjetManager::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for (std::vector<Projet*>::const_iterator it = projet.cbegin(); it != projet.cend(); ++it){
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
