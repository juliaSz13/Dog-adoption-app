//
// Created by Szep Julia-Maria on 24.03.2026.
//

#include "Service.h"
#include "Exceptions.h"
#include "Validator.h"
#include <algorithm>

 Service::Service(Repository& repo) :repo(repo){
 }

void Service::addDog(const std::string& breed, const std::string& name,int age, const std::string& photo_link) {
    Validator::validate(Dog(breed,name,age,photo_link));
    if (repo.exists(breed,name))
        throw RepositoryException("the dog already exists\n");
    repo.addDog(Dog(breed,name,age,photo_link));
}
void Service::removeDog(const std::string& breed, const std::string& name) {
    if (name.empty()||breed.empty())
        throw ValidationException("the name/breed of the dog cannot be empty\n");
    if (!repo.exists(breed,name))
        throw RepositoryException("the dog does not exist\n");
    repo.removeDog(breed,name);
}
void Service::updateDog(const std::string& oldBreed, const std::string& oldName,
                        const std::string& newBreed, const std::string& newName,
                        int newAge, const std::string& newPhoto) {

     std::vector<Dog> all = repo.listAllDogs();
     if (repo.exists(oldBreed,oldName)==false)
         throw RepositoryException("Dog not found\n");

     auto it=std::find_if(all.begin(), all.end(),
         [&](const Dog&d){return d.getBreed()==oldBreed&&d.getName()==oldName;});
     Dog& oldDog=*it;
     std::string finalBreed = (newBreed == "same") ? oldDog.getBreed() : newBreed;
     std::string finalName = (newName == "same") ? oldDog.getName() : newName;
     std::string finalPhoto = (newPhoto == "same") ? oldDog.getPhotoLink() : newPhoto;
     int finalAge = (newAge == -1) ? oldDog.getAge() : newAge;
     if (finalName.empty() || finalBreed.empty()) throw ValidationException("Fields cannot be empty\n");
     repo.updateDog(oldBreed, oldName, Dog(finalBreed, finalName, finalAge, finalPhoto));
 }
std::vector<Dog> Service::listAllDogs() const {
    return repo.listAllDogs();
}
bool Service::exists(const std::string& breed, const std::string& name)const {
     return repo.exists(breed,name);
 }