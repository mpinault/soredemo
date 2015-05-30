

#include "Interface.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Fenetre4 fenetre4;
    fenetre4.show();

    Fenetre10 fenetre10;
    fenetre10.show();
    return app.exec();
}
