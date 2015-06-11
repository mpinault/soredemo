/*!
 * \file actManager.cpp
 * \brief ActManager, manager des activites
 * \author Alice,Morgane
 * \version 0.1
 */

#include "activite.h"
#include "actmanager.h"

using namespace TIME;
using namespace std;


//================================methodes de ActManager=================================================


//singleton
ActManager::Handler ActManager::handler = ActManager::Handler();

//GetInstance : pareil qu'avec ProjetManager
ActManager& ActManager::getInstanceAct(){
    if (handler.instance == 0){
        handler.instance = new ActManager;
        handler.instance->setFile(QFileDialog::getOpenFileName());
        qDebug()<<"1";
        qDebug()<<handler.instance->file;
        //handler.instance->load(handler.instance->file);
    }
    return *(handler.instance);
}

void ActManager::libererInstanceAct(){
    if (handler.instance != 0) delete handler.instance;
    handler.instance = 0;
}


    //PRIVE//ajout d'une activite dans act (son manager)
void ActManager::ajouterAct(ActiviteTrad* p){
    act.push_back(p);
}

    //PRIVE//retrouve une activite
ActiviteTrad* ActManager::trouverActP(const QString& titre)const{
    for (std::vector<ActiviteTrad*>::const_iterator it = act.begin(); it != act.end(); ++it)
        if ((*it)->getTitre()==titre) return *it;
    return 0;
}
// si l'activite est une reunion, rendez-vous ou autres choses, le quatrieme parametre est respectivement, un sujet
//la liste des personnes, le type
ActiviteTrad& ActManager::creerAct(const QString& t, const QString& lieu, const Duree& dur, const QString& type, int a){
    if (isActExistant(t)) throw TimeException("erreur ActManager, activite deja existante");
    //si l'activite est une reunion, a=0
    if(a==0) {
        Reunion* newt = new Reunion(t,lieu,dur,type);
        ajouterAct(newt);
        return *newt;
    }
    //si l'activite est un rdv, a=1
    if(a==1) {
        Rdv* newt = new Rdv(t,lieu,dur,type);
        ajouterAct(newt);
        return *newt;
    }
    //si l'activite n'est ni une reunion ni un rdv, a=2
    if(a==2) {
        ActiviteTrad* newt = new ActiviteTrad(t,lieu,dur,type);
        ajouterAct(newt);
        return *newt;
    }
    else{throw TimeException("erreur ActManager, le parametre a ne convient pas");}
}



ActiviteTrad& ActManager::trouverActR(const QString& ti){
    ActiviteTrad* p=trouverActP(ti);
    if (!p) throw TimeException("erreur ActManager, activite existe pas");
    return *p;
}

//au niveau des fichiers
//a revoir !!
/*
void ActManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~ActManager();
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
            // If it's named activite, we'll go to the next.
            if (xml.name() == "activites") continue;
            // If it's named activite, we'll dig the information from there.
            if (xml.name() == "activite") {
                qDebug() << "new activite\n";
                QString titre;
                QString lieu;
                Duree dur;

                QXmlStreamAttributes attributes = xml.attributes();
                // Let's check that Task has attribute.
                if (attributes.hasAttribute("preemptive")) {
                    QString val = attributes.value("preemptive").toString();
                    preemptive = (val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named activite.


                while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "activite")) {
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
                //qDebug()<<"ajout activite "<<identificateur<<"\n";
                creerAct(titre,disponibilite, echeance);

            }
        }
    }
    // Error handling.
    if (xml.hasError()) {
        throw TimeException("Erreur lecteur fichier activites, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}


//a revoir !
void  ActManager::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw TimeException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("activites");
    for (std::vector<ActiviteTrad*>::const_iterator it = act.begin(); it != act.end(); ++it){
        stream.writeStartElement("activite");
        stream.writeTextElement("type", typeid(*it));
        stream.writeTextElement("titre", (*it)->getTitre());
        stream.writeTextElement("lieu", (*it)->getLieu());
        stream.writeTextElement("duree", (*it)->getDuree());
        //stream.writeTextElement("type", (*it)->get);

        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

*/

