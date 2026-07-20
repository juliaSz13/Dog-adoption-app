//
// Created by Szep Julia-Maria on 24.03.2026.
//

#ifndef A4_5_JULIASZ13_SERVICE_H
#define A4_5_JULIASZ13_SERVICE_H

#include "Repository.h"

class Service {
private:
    Repository& repo;
public:
    ///the constructor for the service
    /// @param repo
    Service(Repository& repo);

    /// adding the dog and make validation for the input data
    /// @param breed
    /// @param name
    /// @param age
    /// @param photo_link
    void addDog(const std::string& breed, const std::string& name,int age, const std::string& photo_link);

    /// removing the dog and also make validations for the input data
    /// @param breed
    /// @param name
    void removeDog(const std::string& breed, const std::string& name);

    /// updating the age and/or photo_link and also m,make the validations for the input data
    /// @param breed
    /// @param name
    /// @param age
    /// @param photo_link
    ///void updateDog(const std::string& breed, const std::string& name,int age,const std::string& photo_link);
    void updateDog(const std::string& oldBreed, const std::string& oldName,
                        const std::string& newBreed, const std::string& newName,
                        int newAge, const std::string& newPhoto);

    /// returning the entire  list of dogs
    /// @return
    std::vector<Dog> listAllDogs() const;

    bool exists(const std::string& breed, const std::string& name)const;

};


#endif //A4_5_JULIASZ13_SERVICE_H