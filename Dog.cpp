//
// Created by Szep Julia-Maria on 24.03.2026.
//

#include "Dog.h"

#include <istream>


Dog::Dog(const std::string &breed, const std::string &name, int age, const std::string &photo_link) {
    this->breed = breed;
    this->name=name;
    this->age=age;
    this->photo_link=photo_link;
}
std::string Dog::getBreed() const{
    return this->breed;
}
std::string Dog::getName() const{
    return this->name;
}
std::string Dog::getPhotoLink() const{
    return this->photo_link;
}
int Dog::getAge() const{
    return this->age;
}
void Dog::setBreed(const std::string &breed) {
    this->breed = breed;
}
void Dog::setName(const std::string &name) {
    this->name = name;
}
void Dog::setPhotoLink(const std::string &photo_link) {
    this->photo_link = photo_link;
}
void Dog::setAge(int age) {
    this->age = age;
}
bool Dog::operator==(const Dog& other) const{
    return this->breed == other.breed && this->name == other.name;
}
std::ostream& operator <<(std::ostream& out, const Dog&d) {
    out<<d.getBreed()<<","<<d.getName()<<","<<d.getAge()<<","<<d.getPhotoLink();
    return out;

}
std::istream& operator >>(std::istream& in,  Dog&d) {
    std::string breed, name, link;
    int age;
    std::getline(in,breed,',');
    std::getline(in,name,',');
    in>>age;
    in.ignore();
    std::getline(in,link);
    d=Dog(breed,name,age,link);
    return  in;
}