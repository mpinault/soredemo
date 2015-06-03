
#include "activite.h"


std::ostream& operator<<(std::ostream& f, const ActiviteTrad& a){
    a.afficher(f);
    return f;
}

std::ostream& operator<<(std::ostream& f, const TIME::Duree& d){
    d.afficher(f);
    return f;
}
