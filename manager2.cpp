#include "tache.h"
#include "projet.h"
#include "manager.h"

using namespace TIME;
using namespace std;


//================================methodes de Manager=================================================


//singleton
Manager::Handler Manager::handler = Manager::Handler();

Manager& Manager::getInstance(){
    if (handler.instance == 0) handler.instance = new Manager;
    return *(handler.instance);
}

void Manager::libererInstance(){
    if (handler.instance != 0) delete handler.instance;
    handler.instance = 0;
}


    //PRIVE//ajout de T dans tool
template<class T>
void Manager<T>::ajouterT(T* p){
    tool.push_back(p);
}

    //PRIVE//retrouve un T
template<class T>
T* Manager<T>::trouverTP(const QString& titre)const{
    for (std::vector<T*>::const_iterator it = tool.begin(); it != tool.end(); ++it)
        if ((*it)->getTitre()==titre) return *it;
}

template<class T>
T& Manager<T>::creerT(const QString& ti, const QDate& dispo, const QDate& deadline){
    if (trouverTP(ti)) throw TimeException("erreur Manager, tool deja existante");
    T* newt = new T(ti, dispo, deadline);
    ajouterT(newt);
    return *newt;
}

template<class T>
T& Manager<T>::trouverTR(const QString& ti){
    T* p=trouverTP(ti);
    if (!p) throw TimeException("erreur Manager, tache existe pas");
    return *p;
}

//au niveau des fichiers
void Manager::load(const QString& f){
    //qDebug()<<"debut load\n";
    this->~Manager();
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
                creerT(titre,disponibilite, echeance);

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

template<class T>
void  Manager<T>::save(const QString& f){
    file = f;
    QFile newfile(file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw TimeException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("taches");
    for (std::vector<T*>::const_iterator it = tool.begin(); it != tool.end(); ++it){
        stream.writeStartElement("tool");
        stream.writeTextElement("titre", (*it)->getTitre());
        stream.writeTextElement("disponibilite", (*it)->getDispo().toString(Qt::ISODate));

        stream.writeTextElement("echeance", (*it)->getEch().toString(Qt::ISODate));
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


