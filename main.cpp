/*!
 * \file main.cpp
 * \brief programme principale
 * \author Alice,Morgane
 * \version 0.1
 */

#include "Interface.h"
#include "activite.h"
#include "evtmanager.h"
#include "actmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    try{


        ProjetManager& pManager=ProjetManager::getInstance();
        EvtManager& mManager=EvtManager::getInstanceEvt();
        ActManager& aManager=ActManager::getInstanceAct();
     

        Fenetre1 fenetre1;
        fenetre1.show();

        return app.exec();
    }
    catch (const TimeException& e){
        qDebug()<<e.GetInfo();
    }
    return 0;
}
