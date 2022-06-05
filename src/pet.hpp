#if !defined(PET_H)
#define PET_H

#include <string>

struct Pet
{
    enum Kind {
        Dog = 0,
        Cat
    };

    struct Attributes
    {
        float age = 0;
    };

    Pet(const std::string &name, Kind type): name(name), type(type) { }

    std::string name;
    Kind type;
    Attributes attr;

};


#endif // PET_H
