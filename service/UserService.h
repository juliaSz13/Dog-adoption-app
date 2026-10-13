#ifndef A4_5_JULIASZ13_USERSERVICE_H
#define A4_5_JULIASZ13_USERSERVICE_H

#include "Repository.h"
#include"AdoptionList.h"
#include <memory>
class UserService {
private:
    Repository& repo;
    std::unique_ptr<AdoptionList> adoptionList;
    std::string typefile;
    std::string filename;
    void saveHTML() const;
    void saveCSV() const;
public:
    UserService(Repository& repo,const std::string& typefile, const std::string& filename="adoption_list");

    /// returns all the filter dogs by breed and age
    /// @param breed
    /// @param maxAge
    /// @return
    std::vector<Dog> filterDogs(const std::string& breed, int maxAge) const;

    /// add a dog into the adoption list
    /// @param dog
    void adoptDog(const Dog& dog);

    ///
    /// @return the adoption list
    std::vector<Dog> getAdoptionList() const;

    /// it verify if the dog is already adopted
    /// @param breed
    /// @param name
    /// @return
    bool isAdopted(const std::string& breed, const std::string& name) const;

    void saveAdoptionList() const;
    void openAdoptionList() const;
};

#endif