// Zadatak: Dat je vektor pojmova (niski). 
// Konstruisati novi vektor koji odgovara datom,
// tako da ukoliko je pojam odabran (pocinje karakterom '*'), 
// onda vektor na toj poziciji ima vrednost true,
// a u suprotnom ima vrednost false.

#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

bool is_selected(const std::string &item)
{
    return item[0] == '*';
}

int main(int argc, char *argv[])
{
    std::vector<std::string> items {
            "aardvark",
            "compunctious",
            "**congratulations**",
            "contrafribblarity",
            "contrary",
            "dictionary",
            "**interphrastical**",
            "**patronise**",
            "**pericombobulation**",
            "phrasmotic",
            "**syllables**"
        };

    std::vector<bool> selection_markers(items.size());

    std::transform(std::cbegin(items), std::cend(items),
                   std::begin(selection_markers),
                   is_selected);

    std::copy(std::begin(selection_markers), std::end(selection_markers),
              std::ostream_iterator<bool>(std::cout, "\n"));

    return 0;
}
