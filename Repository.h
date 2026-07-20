//
// Created by Szep Julia-Maria on 24.03.2026.
//

#ifndef A4_5_JULIASZ13_REPOSITORY_H
#define A4_5_JULIASZ13_REPOSITORY_H

#include "Dog.h"
#include <vector>
class Repository {
private:
    std::vector<Dog> dogs;
    std::string filename;
     void loadFormFile();
    void SaveToFile();

public:
    /// the constructor for the repository
    ///
    Repository( const std::string& filename);

    /// adding the object called Dog to the dynamic array
    /// @param dog
    void addDog(const Dog& dog);

    /// removing the object called dog from the dynamic array
    /// @param breed
    /// @param name
    void removeDog(const std::string& breed, const std::string& name);

    ///  updating the elements that define the object dog
    /// @param breed
    /// @param name
    /// @param newDog
    void updateDog(const std::string& breed, const std::string& name,const Dog& newDog);

    /// return the list of all objects called dog
    /// @return
   std::vector<Dog> listAllDogs() const;

    /// verify if an object called Dog exists in  the dynamic array
    /// @param breed
    /// @param name
    /// @return
    bool exists(const std::string& breed, const std::string& name)const;
};


#endif //A4_5_JULIASZ13_REPOSITORY_H