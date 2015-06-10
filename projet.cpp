/*!
 * \file projet.cpp
 * \brief projet qui est un manager des taches
 * \author Alice,Morgane
 * \version 0.1
 */


#include "tache.h"
#include "projet.h"
#include "manager.h"

using namespace std;

//================================methodes de Projet=========================================================================
    //PRIVE//ajoute une Tache dans le projet
void Projet::ajouterTache(Tache* t){
    taches.push_back(t);
}

    //PRIVE//retrouver une Tache
Tache* Projet::trouverTacheP(const QString& ti)const{
    for (vector<Tache*>::const_iterator it = taches.begin(); it != taches.end(); ++it){
        if (ti==(*it)->getTitre()) return *it;
    }
    return 0;
}

    //creer une Tache a partir d'un formulaire Qt dans le projet
Tache& Projet::creerTache(const QString& t, const QDate& dispo, const QDate& deadline, const Duree& dur, int a){
    if (isTacheExistante(t)) throw TimeException("erreur Projet, tache deja existante");
    if(a==0) {
        TacheUnitaireNonPreempte* newt = new TacheUnitaireNonPreempte(t, dispo, deadline,dur);
        ajouterTache(newt);
        return *newt;
    }
    if(a==1) {
        TacheUnitairePreempte* newt = new TacheUnitairePreempte(t, dispo, deadline,dur);
        ajouterTache(newt);
        return *newt;
    }
    if(a==2) {
        TacheComposite* newt = new TacheComposite(t, dispo, deadline,dur);
        ajouterTache(newt);
        return *newt;
    }
    else{throw TimeException("erreur Projet, le parametre a ne convient pas");}

}

    //retrouver une Tache a partir de son titre
Tache& Projet::trouverTacheR(const QString& ti) const{
    Tache* t=trouverTacheP(ti);
    if (!t) throw TimeException("erreur TacheManager, tache existe pas");
    return *t;
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
            if (xml.name() == "tache") {
                qDebug() << "new tache\n";
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;
                bool compose;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("compose")) {
                    QString val =attributes.value("compose").toString();
                    compose=(val == "true" ? true : false);
                }
                //qDebug()<<"compose="<<compose<<"\n";


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
                if(compose){
                    creerTache(titre, disponibilite, echeance, duree,2);
                }else{
                    if(preemptive){
                        creerTache(titre, disponibilite, echeance, duree,1);
                    }else{
                        creerTache(titre, disponibilite, echeance, duree,0);
                    }
                }


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
    for (vector<Tache*>::const_iterator it = taches.begin(); it != taches.end(); ++it){
        stream.writeStartElement("tache");
        //stream.writeAttribute("preemptive", (typeid(*it).name==QString(TacheUnitairePreempte)) ? "true" : "false");
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




