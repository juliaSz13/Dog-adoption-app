//
// Created by Szep Julia-Maria on 22.04.2026.
//

#include "AdoptionList.h"
#include<fstream>
#include <algorithm>
#include <cstdlib>
 AdoptionList::AdoptionList( const std:: string & filename):filename(filename) {
 }

void AdoptionList::adoptDog(const Dog &dog) {
   dogs.push_back(dog);
     save();
}

bool AdoptionList::isAdopted(const std::string& breed, const std::string& name) const {
     auto it=std::find_if(dogs.begin(),dogs.end(),[&](const Dog&d) {
           return d.getBreed()==breed && d.getName()==name;
       });
     return it!=dogs.end();
 }
std::vector<Dog>  AdoptionList::getAdoptionList() const {
     return dogs;
 }

 CSVAdoptionList::CSVAdoptionList(const std::string& filename):AdoptionList(filename) {
 }
void CSVAdoptionList::save() const {
     std::ofstream out(filename+".csv");
     out << "Breed,Name,Age,Photo\n";
     for (const Dog& d : dogs)
         out << d << "\n";
 }

void CSVAdoptionList::open() const {
     system(("open "+filename+".csv").c_str());
 }

HTMLAdoptionList::HTMLAdoptionList(const std::string& filename):AdoptionList(filename) {
 }
void HTMLAdoptionList::save() const {
     std::ofstream out(filename+".html");
     out << "<html><body>\n";
     out << "<table border='1'>\n";
     out << "<tr><th>Breed</th><th>Name</th><th>Age</th><th>Photo</th></tr>\n";
     for (const Dog& d : dogs)
         out << "<tr><td>" << d.getBreed() << "</td><td>" << d.getName()
             << "</td><td>" << d.getAge() << "</td><td>" << d.getPhotoLink()
             << "</td></tr>\n";
     out << "</table>\n</body></html>\n";
 }
void HTMLAdoptionList::open() const {
     system(("open "+filename+".html").c_str());
 }

