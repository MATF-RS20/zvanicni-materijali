#ifndef CHILD_CLASS_H
#define CHILD_CLASS_H

#include <memory>
#include <iostream>

// Obecavajuca deklaracija roditeljske klase
class parent_class;
// Primetimo da u kodu ispod
// nigde ne koristimo informacije iz definicije klase `parent_class`.
// Zbog toga nam nije ni potrebno da ukljucimo odgovorajuce zaglavlje,
// vec samo da obecamo da ce ona biti definisana u nekom trenutku.

class child_class
{
public:
    explicit child_class(std::shared_ptr<parent_class> parent);

private:
    friend std::ostream & operator<<(std::ostream & out, const child_class & obj);
    std::shared_ptr<parent_class> parent_;
};

std::ostream & operator<<(std::ostream & out, const child_class & obj);

#endif //CHILD_CLASS_H
