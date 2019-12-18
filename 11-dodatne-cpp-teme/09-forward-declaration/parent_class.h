#ifndef PARENT_CLASS_H
#define PARENT_CLASS_H

#include <vector>
#include <memory>

// Obecavajuca deklaracija dete klase
class child_class;
// Primetimo da u kodu ispod
// nigde ne koristimo informacije iz definicije klase `child_class`.
// Zbog toga nam nije ni potrebno da ukljucimo odgovorajuce zaglavlje,
// vec samo da obecamo da ce ona biti definisana u nekom trenutku.

class parent_class
{
public:
    void locate_children() const;
    void add_child(std::unique_ptr<child_class> child);
private:
    std::vector<std::unique_ptr<child_class>> children_;
};

#endif //PARENT_CLASS_H
