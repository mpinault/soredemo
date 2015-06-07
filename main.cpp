#include "Interface.h"
#include "manager.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //TacheManager& m=TacheManager::getInstance();

    Fenetre1 fenetre1;
    fenetre1.show();

    return app.exec();
}
