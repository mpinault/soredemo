/*!
 * \file evtManager.cpp
 * \brief EvtManager, manager des evenements
 * \author Alice,Morgane
 * \version 0.1
 */

#include "activite.h"
#include "evtmanager.h"

using namespace TIME;
using namespace std;



//================================methodes de EvtManager=================================================


//singleton
EvtManager::Handler EvtManager::handler = EvtManager::Handler();

//GetInstance : pareil qu'avec ProjetManager
EvtManager& EvtManager::getInstanceEvt(){
    if (handler.instance == 0){
        handler.instance = new EvtManager;
        handler.instance->setFile(QFileDialog::getOpenFileName());
        qDebug()<<"1";
        qDebug()<<handler.instance->file;
        //handler.instance->load(handler.instance->file);
    }
    return *(handler.instance);
}

void EvtManager::libererInstanceEvt(){
    if (handler.instance != 0) delete handler.instance;
    handler.instance = 0;
}


    //PRIVE//ajout d'un evenement dans evt (son manager)
void EvtManager::ajouterEvenement(Evenement* p){
    evt.push_back(p);

}

    //PRIVE//retrouve un evenement

Evenement* EvtManager::trouverEvenementP(const QString& titre)const{
    for (std::vector<Evenement*>::const_iterator it = evt.begin(); it != evt.end(); ++it)
        if ((*it)->getTitre()==titre) return *it;
    return 0;
}


// pour creer une programmation de tache dans evenement
Evenement& EvtManager::creerEvenementTache(const QDate& d,const Horaire& h,Tache& t){

    // si le titre exise deja !
    if (trouverEvenementP(t.getTitre())) throw TimeException("Evenement déjà existant(tâche déjà programmée)");

    else {ProgrammationTache* newt = new ProgrammationTache(d,h,t);
    evt.push_back(newt);
    return *newt;
    }
}

// pour creer une programmation de act dans evenement
Evenement& EvtManager::creerEvenementAct(const QDate& d,const Horaire& h,ActiviteTrad& a){
    // si le titre exise deja !
    //if (trouverEvenementP(ti)) throw TimeException("erreur EvtManager, evenement deja existante");
        ProgrammationActTrad* newt = new ProgrammationActTrad(d,h,a);
       // ajouterEvenement(newt);
        return *newt;
}

Evenement& EvtManager::trouverEvenementR(const QString& ti){
    Evenement* p=trouverEvenementP(ti);
    if (!p) throw TimeException("erreur TacheManager, evenement existe pas");
    return *p;
}

//au niveau des fichiers
//a revoir !!
/*
void EvtManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~EvtManager();
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
            // If it's named evenement, we'll go to the next.
            if (xml.name() == "evenements") continue;
            // If it's named evenement, we'll dig the information from there.
            if (xml.name() == "evenement") {
                qDebug() << "new evenement\n";
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;

                QXmlStreamAttributes attributes = xml.attributes();
                // Let's check that Task has attribute.
                if (attributes.hasAttribute("preemptive")) {
                    QString val = attributes.value("preemptive").toString();
                    preemptive = (val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named evenement.


                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "evenement")) {
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
                //qDebug()<<"ajout evenement "<<identificateur<<"\n";
                creerEvenement(titre,disponibilite, echeance);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw TimeException("Erreur lecteur fichier evenements, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}


//a revoir !
void  EvtManager::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw TimeException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("evenements");
    for (std::vector<Evenement*>::const_iterator it = evt.begin(); it != evt.end(); ++it){
        stream.writeStartElement("evenement");
        stream.writeTextElement("titre", (*it)->getTitre());
        stream.writeTextElement("disponibilite", (*it)->getDispo().toString(Qt::ISODate));

        stream.writeTextElement("echeance", (*it)->getEch().toString(Qt::ISODate));
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

*/
/*

bool EvtManager::isHoraireValide(const QDate& d, const Horaire& debut, const Horaire& fin) const{
    for(std::vector<Evenement*>::const_iterator it = evt.begin(); it != evt.end(); ++it){
            if (typeid(*(*it))==typeid(ProgrammationActTrad)) {
                qDebug()<<"Programmation Activité Traditionelle";
                Duree& d = dynamic_cast<ProgrammationActTrad*>(*it)->getActivite()->getDuree();
                Horaire& htid = (*it)->getHoraire();
                Horaire& htif = sommeH(htid,d);
                if ((htid>=debut && htid<=fin)|| (htif>=debut && htif<=fin)||(htid<=debut && htif>=fin))
                    return 0;
            }
            else
                if (typeid(*(*it))==typeid(ProgrammationTache)) {
                    qDebug()<<"Programmation Tache";
                    Duree& d = dynamic_cast<ProgrammationTache*>(*it)->getTache()->getDuree();
                    Horaire& htid = (*it)->getHoraire();
                    Horaire& htif = (*it)->getHoraireFin();
                    if ((htid>=debut && htid<=fin)|| (htif>=debut && htif<=fin)||(htid<=debut && htif>=fin))
                        return 0;
                }
            else qDebug()<<"Programmation inconnue";
    }
    return 1;
}
*/
