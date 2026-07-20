//
// Created by Szep Julia-Maria on 24.03.2026.
//

#include "Repository.h"
#include <fstream>

Repository::Repository(const std::string &filename):filename(filename) {
    loadFormFile();
}

void Repository::SaveToFile() {
    std::ofstream out(filename);
    for (const Dog& d:dogs) {
        out<<d<<'\n';
    }
}

void Repository::loadFormFile() {
    std::ifstream in(filename);
    if (!in.is_open())
        return;
    Dog d;
    while (in>>d) {
        dogs.push_back(d);
    }
}

void Repository::addDog(const Dog &dog) {
    dogs.push_back(dog);
    SaveToFile();
}
void Repository::removeDog(const std::string& breed, const std::string& name) {
    auto shouldRemove = [&](const Dog& d) {
        return d.getBreed() == breed && d.getName() == name;
    };
    dogs.erase(
        std::remove_if(dogs.begin(), dogs.end(), shouldRemove),
        dogs.end()
    );
    SaveToFile();
}
void Repository::updateDog(const std::string& breed, const std::string& name, const Dog& newDog) {
    auto it=find_if(dogs.begin(),dogs.end(),[&](const Dog&d) {
        return d.getBreed()==breed && d.getName()==name;
    });
    if (it!=dogs.end()) {
        *it=newDog;
    }
    SaveToFile();
}
std::vector<Dog> Repository::listAllDogs() const{
    return dogs;
}
bool Repository::exists(const std::string& breed, const std::string& name)const {
    return std::any_of(dogs.begin(),dogs.end(),[&](const Dog&d) {
        return d.getBreed()==breed && d.getName()==name;
    });
}
