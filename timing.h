#if !defined(CTIME)
#define CTIME
/*!
 * \file timing.h
 * \brief les differents structures pour la gestion du temps
 * \author Antoine Jouglet, modifié par Alice et Morgane
 * \version 0.1
 * \date 14 juin 2015
 */

#include <QString>
#include <QDate>
#include <QTextStream>
#include<iostream>
#include<iomanip>

namespace TIME {


        /*! \class TimeException
                        \brief Classe permettant de gérer les exceptions des classes du namespace TIME
        */
        class TimeException{
        public:
                //! Constructeur ? partir d'une QString
                TimeException(const QString& m):info(m){}
                const QString& GetInfo() const { return info; } //<! Retourne l'information stockée dans la classe
        private:
                QString info;
        };





        /*! \class Duree
                \brief Classe permettant de manipuler des durees
                L'utilisation de cette classe n?cessite des dates valides au sens commun du terme.
                D?clenchement d'exception dans le cas contraire
        */
        class Duree{
        public:
            //! Constructeur ? partir de heure et minute
            /*! \param h heure avec h>=0
                \param m minute avec 0<=m<=59
                */
            Duree(unsigned int h, unsigned int m):nb_minutes(h*60+m) {if (m>59) throw TimeException("erreur: initialisation duree invalide");}
            //! Constructeur ? partir de minute
            /*! \param m minute avec m>=0
                */
            Duree(unsigned int m=0):nb_minutes(m) {}
            void setDuree(unsigned int minutes) { nb_minutes=minutes; }
            void setDuree(unsigned int heures, unsigned int minutes) { if (heures==0 && minutes>59) throw TimeException("erreur: initialisation duree invalide"); nb_minutes=heures*60+minutes; }
            unsigned int getDureeEnMinutes() const { return nb_minutes; } //<!Retourne la duree en minutes
            double getDureeEnHeures() const { return double(nb_minutes)/60; } //<!Retourne la duree en heures
            unsigned int getMinute() const { return nb_minutes%60; }
            unsigned int getHeure() const { return nb_minutes/60; }
            void afficher(QTextStream& f) const; //<!Affiche la duree sous le format hhHmm

        private:
            unsigned int nb_minutes;
        };


        // A RAJOUTE
        namespace {
         unsigned int sommeD(const Duree& d1,const Duree& d2){
            return d1.getMinute()+d2.getMinute();
        }
        }
        // A RAJOUTE

        QTextStream& operator<<(QTextStream& f, const Duree & d);
        QTextStream& operator>>(QTextStream&, Duree&); //lecture format hhHmm





        /*! \class Horaire
                        \brief Classe permettant de manipuler des horaires
                        L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
                        Déclenchement d'exception dans le cas contraire
        */

        class Horaire{
        public:
                //! Constructeur ? partir de heure et minute
                // \param h heure avec 0<=h<=23
                 //       \param m minute avec 0<=m<=59
                Horaire(unsigned short int  h, unsigned short int  m):heure(h),minute(m) {if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide");}
                void setHoraire(unsigned short int h, unsigned short int m) { if (h>23||m>59) throw TimeException("erreur: initialisation horaire invalide"); heure=h; minute=m; }
                //void afficher(QTextStream& f=std::cout) const { f<<std::setfill('0')<<std::setw(2)<<heure<<"H"<<std::setfill('0')<<std::setw(2)<<minute<<std::setfill(' '); } //<!Affiche l'horaire sous le format hhHmm
                unsigned short int getHeure() const { return heure; } //<!Retourne l'heure de l'horaire
                unsigned short int getMinute() const { return minute; } //<!Retourne les minutes de l'horaire
                bool operator<(const Horaire& h) const; //<! h1<h2 retourne true si h1 est avant h2 dans le temps
        private:
                unsigned short int  heure;
                unsigned short int  minute;
        };



        //A RAJOUTE (ALice,11/06)
        namespace {
            Horaire&  sommeH(Horaire& h,const Duree& d){
                if(d.getMinute()<60){
                    unsigned int min= h.getMinute()+d.getMinute();
                    h.setHoraire(h.getHeure(),min);
                    return h;
                }
                else{
                    unsigned int he= h.getMinute()+d.getHeure();
                    unsigned int min= h.getMinute()+ (d.getMinute() -d.getHeure());
                    h.setHoraire(he,min);
                    return h;
                }
            }
        }
        //A RAJOUTER (ALice,11/06)



}


std::istream& operator>>(std::istream&, QDate&); // lecture format JJ/MM/AAAA
std::istream& operator>>(std::istream&, TIME::Duree&); //lecture format hhHmm

#endif

