// Ukoliko je potrebno dve klase znaju za postojanje one druge,
// ukoliko bismo u zaglavlju prve klase ukljucili zaglavlje druge klase
// i takodje u zaglavlju druge klase ukljucili zaglavlje prve klase,
// onda bi doslo do uzajamne rekurzije izmedju ukljucivanja zaglavlja.

// Ovaj problem se resava tako sto u zaglavlju prve klase
// navedemo obecavajucu deklaraciju (engl. forward declaration) druge klase
// i obrnuto (u zaglavlju druge klase navedemo obec. dekl. prve klase.

// Obecavajuca deklaracija je oblika:
// `class T;`

// Da bismo mogli da koristimo obecavajucu deklaraciju,
// u zaglavlju ne mozemo imati promenljive tipa `T` ili `T&`,
// vec samo mozemo kreirati `T*`
// ili koristiti tip `T` u kontekstima
// u kojima nam nije neophodno da znamo za definiciju klase `T`.

#include <memory>

#include "parent_class.h"
#include "child_class.h"

int main()
{
    auto t_ptr = std::make_shared<parent_class>();

    t_ptr->add_child(std::make_unique<child_class>(t_ptr));
    t_ptr->add_child(std::make_unique<child_class>(t_ptr));
    t_ptr->add_child(std::make_unique<child_class>(t_ptr));

    t_ptr->locate_children();

    return 0;
}