//
// Created by Szep Julia-Maria on 22.04.2026.
//

#ifndef A6_7_JULIASZ13_ADOPTIONLIST_H
#define A6_7_JULIASZ13_ADOPTIONLIST_H

#include<string>
#include"Dog.h"
#include<vector>
class AdoptionList {

protected:
    std::string filename;
    std::vector<Dog> dogs;
public:
    AdoptionList( const std:: string & filename);
    virtual ~AdoptionList()=default;

    virtual void  save() const=0;
    virtual void open() const=0;

    void adoptDog(const Dog& dog);
    bool isAdopted(const std::string& breed, const std::string& name) const;
    std::vector<Dog> getAdoptionList() const;
};

class CSVAdoptionList : public AdoptionList{
public:
    CSVAdoptionList(const std::string& filename="adoption_list");
    void save() const override;
    void open() const override;
};

class HTMLAdoptionList : public AdoptionList{
public:
    HTMLAdoptionList(const std::string& filename="adoption_list");
    void save() const override;
    void open() const override;
};


#endif //A6_7_JULIASZ13_ADOPTIONLIST_H