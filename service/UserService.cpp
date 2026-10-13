#include "UserService.h"
#include<fstream>
#include <algorithm>
#include <iterator>
UserService::UserService(Repository& repo,const std::string & typefile,const std::string& filename) : repo(repo) {
    if (typefile == "CSV")
        adoptionList = std::make_unique<CSVAdoptionList>(filename);
    else
        adoptionList = std::make_unique<HTMLAdoptionList>(filename);
}


std::vector<Dog> UserService::filterDogs(const std::string& breed, int maxAge) const {
    std::vector<Dog> all = repo.listAllDogs();
    std::vector <Dog>result;
    std::copy_if(all.begin(),all.end(),std::back_inserter(result),[&](const Dog&d) {
       bool BreedMatch=breed.empty()||d.getBreed()==breed;
        bool AgeMatch=d.getAge()<maxAge;
        return BreedMatch && AgeMatch;
    });
    return result;
}

void UserService::saveAdoptionList() const {
   adoptionList->save();
}

void UserService::openAdoptionList() const {
   adoptionList->open();
}

void UserService::adoptDog(const Dog& dog) {
    if (!isAdopted(dog.getBreed(), dog.getName())) {
        adoptionList->adoptDog(dog);
        repo.removeDog(dog.getBreed(),dog.getName());
        saveAdoptionList();
    }
}

std::vector<Dog> UserService::getAdoptionList() const {
    return adoptionList->getAdoptionList();
}

bool UserService::isAdopted(const std::string& breed, const std::string& name) const {
   return adoptionList->isAdopted(breed,name);
}