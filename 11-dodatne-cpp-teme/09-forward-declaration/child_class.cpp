#include "child_class.h"

#include <utility>

child_class::child_class(std::shared_ptr<parent_class> parent)
    : parent_(std::move(parent))
{}

std::ostream & operator<<(std::ostream & out, const child_class & obj)
{
    return out << "Parent's address is " << obj.parent_.get();
}