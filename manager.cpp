#include "tache.h"
#include "projet.h"
#include "manager.h"

using namespace TIME;
using namespace std;


//================================methodes de ProjetManager=================================================


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


    //PRIVE//ajout de projet dans tache
void ProjetManager::ajouterProjet(Projet* p){
    projet.push_back(p);
}

    //PRIVE//retrouve un projet
Projet* ProjetManager::trouverProjetP(const QString& titre)const{
    for (std::vector<Projet*>::const_iterator it = projet.begin(); it != projet.end(); ++it)
        if ((*it)->getTitre()==titre) return *it;
}

Projet& ProjetManager::creerProjet(const QString& ti, const QDate& dispo, const QDate& deadline){
    if (trouverProjetP(ti)) throw TimeException("erreur ProjetManager, projet deja existante");
    Projet* newt = new Projet(ti, dispo, deadline);
    ajouterProjet(newt);
    return *newt;
}

Projet& ProjetManager::trouverProjetR(const QString& ti){
    Projet* p=trouverProjetP(ti);
    if (!p) throw TimeException("erreur TacheManager, tache existe pas");
    return *p;
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
            // If it's named projet, we'll go to the next.
            if (xml.name() == "projets") continue;
            // If it's named projet, we'll dig the information from there.
            if (xml.name() == "projet") {
                qDebug() << "new projet\n";
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;

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
                ProjetManager::creerProjet(titre,disponibilite, echeance);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw TimeException("Erreur lecteur fichier projets, parser xml");
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
    stream.writeStartElement("projets");
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

