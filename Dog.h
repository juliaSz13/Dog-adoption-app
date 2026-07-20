//
// Created by Szep Julia-Maria on 24.03.2026.
//

#ifndef A4_5_JULIASZ13_DOG_H
#define A4_5_JULIASZ13_DOG_H

#include<string>
class Dog
{
private:
    std::string breed;
    std:: string name;
    int age;
    std::string photo_link;
public:
    // constructor for the class dog
    /// @param breed
    /// @param name
    /// @param age
    /// @param photo_link
    Dog(const std::string &breed="", const std:: string &name="", int age=0, const std::string &photo_link="");

    //getterrs

    /// getter for breed
    /// @return
    std::string getBreed()const;

    /// getter for name
    /// @return
    std:: string getName()const;

    /// getter for photo link
    /// @return
    int getAge()const;

    ///  getter for age
    /// @return
    std:: string getPhotoLink()const;
    //setters

    /// setter for the breed
    /// @param breed
    void setBreed(const std:: string &breed);

    // setter for name
    /// @param name
    void setName(const std:: string &name);

    /// setter for photo link
    /// @param photo_link
    void setAge(int age);

    /// setter for age
    /// @param age
    void setPhotoLink(const std:: string &photo_link);

    /// verify if an object dog is already assigned in the elements array
    /// @param other
    /// @return
    bool operator==(const Dog& other)const;

};
std::ostream& operator <<(std::ostream& out, const Dog& d);
std::istream& operator >>(std::istream& in, Dog& d);

#endif //A4_5_JULIASZ13_DOG_H