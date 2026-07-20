//
// Created by Szep Julia-Maria on 13.04.2026.
//

#include "Validator.h"
#include "Exceptions.h"

void Validator::validate(const Dog& d) {
    if (d.getName().empty())
        throw ValidationException("Name cannot be empty!");
    if (d.getBreed().empty())
        throw ValidationException("Breed cannot be empty!");
    if (d.getAge() < 0)
        throw ValidationException("Age cannot be negative!");
}
