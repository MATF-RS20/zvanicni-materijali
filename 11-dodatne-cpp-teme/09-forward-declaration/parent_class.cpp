#include "parent_class.h"
// U kodu ispod koristimo informacije iz klase `child_class`,
// pa zato moramo da ukljucimo zaglavlje `child_class.h`
#include "child_class.h"

#include <iostream>

void parent_class::locate_children() const
{
    for (const auto & child_ptr : children_)
    {
        std::cout << "Found child at address " << child_ptr.get() << std::endl;
        std::cout << '\t' << *child_ptr << std::endl;
    }
}

void parent_class::add_child(std::unique_ptr<child_class> child)
{
    children_.push_back(std::move(child));
}
