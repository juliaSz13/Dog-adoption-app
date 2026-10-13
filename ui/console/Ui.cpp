//
// Created by Szep Julia-Maria on 24.03.2026.
//

#include "Ui.h"
#include<string>
#include<iostream>
#include <cstdlib>


Ui::Ui(Service& service, UserService& userService)
    : service(service), userService(userService) {}

void Ui::addDog() {
   std::string breed,name,photo_link;
   int age;
   std::cout<<" Enter the breed -> ";
   std::cin>>breed;
   std::cout<<" Enter the name -> ";
   std::cin>>name;
   std::cout<<"Enter the age -> ";
   std::cin>>age;
   std::cout<<" Enter the photo link -> ";
   std::cin>>photo_link;
   try {
      service.addDog(breed,name,age,photo_link);
      std::cout<<" the dog has been added successfully "<<std::endl;
   }catch (std::exception& e) {
      std::cout<<e.what();
   }
}
void Ui::removeDog() {
   std::string breed,name;
   std::cout<<" Enter the breed -> ";
   std::cin>>breed;
   std::cout<<" Enter the name -> ";
   std::cin>>name;
   try {
      service.removeDog(breed,name);
      std::cout<<" the dog has been removed successfully "<<std::endl;
   }catch (std::exception& e) {
      std::cout<<e.what();
   }
}

void Ui::updateDog() {
   std::string oldBreed, oldName, newBreed, newName, photo, ageStr;

   std::cout << "Target Dog Breed: "; std::cin >> oldBreed;
   std::cout << "Target Dog Name: "; std::cin >> oldName;
   if (service.exists(oldBreed,oldName)==false) {
      std::cout<<"Target Dog not found!\n";
      return;
   }
   std::cout << "New Breed (or 'same'): "; std::cin >> newBreed;
   std::cout << "New Name (or 'same'): "; std::cin >> newName;
   std::cout << "New Age (or -1 for 'same'): "; std::cin >> ageStr;
   int newAge = std::stoi(ageStr);
   std::cout << "New Photo Link (or 'same'): "; std::cin >> photo;

   try {
      service.updateDog(oldBreed, oldName, newBreed, newName, newAge, photo);
      std::cout << "Update successful!\n";
   } catch (std::exception& e) {
      std::cout << "Error: " << e.what();
   }
}

void Ui::listAllDogs() {
    std::vector<Dog> dogs = service.listAllDogs();
    if (dogs.empty()) {
        std::cout << "There are no dogs in the list\n";
        return;
    }
    for (const Dog& d : dogs) {
        std::cout << "BREED:" << d.getBreed() << " | "
                  << "NAME:"  << d.getName()  << " | "
                  << "AGE:"   << d.getAge()   << " | "
                  << "PHOTO:" << d.getPhotoLink() << "\n";
    }
}

#include <limits>

void Ui::runAdminMenu() {
   int choice = -1;
   while (choice != 0) {
      std::cout << "\n1. Add dog\n";
      std::cout << "2. Remove dog\n";
      std::cout << "3. Update dog\n";
      std::cout << "4. List all dogs\n";
      std::cout << "0. Exit\n";
      std::cout << "Choice: ";
      if (!(std::cin >> choice)) {
         std::cout << "Invalid choice! Please enter a number.\n";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         choice = -1;
         continue;
      }

      if (choice == 1) addDog();
      else if (choice == 2) removeDog();
      else if (choice == 3) updateDog();
      else if (choice == 4) listAllDogs();
      else if (choice == 0) return;
      else {
         std::cout << "Invalid choice! Number out of range.\n";
      }
   }
}

void Ui::start_ui() {
   std::string choice;
   while (true) {
      std::cout<<"Welcome "<<std::endl;
      std::cout<<" please choose between administrator mode(admin)and user mode(user) ->  "<<std::endl;
      std::cin>>choice;
      if (choice == "admin")
         runAdminMenu();
      else if (choice=="user")
         runUserMeniu();
      else if (choice=="exit")
         break;
   }
}

void Ui::runUserMeniu() {
    int choice = -1;
    while (true) {
        std::cout << "\n1. See dogs one by one\n";
        std::cout << "2. Filter by breed and max age\n";
        std::cout << "3. See adoption list\n";
        std::cout << "0. Back\n";
        std::cout << "Choice -> ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (choice == 1) {
            std::vector<Dog> dogs = userService.filterDogs("", 9999);
            browseDogs(dogs);
        } else if (choice == 2) {
            std::string breed;
            int maxAge;
            std::cout << "Enter breed (or 'all' for no filter): ";
            std::cin >> breed;
            if (breed == "all") breed = "";
            std::cout << "Enter max age: ";
            std::cin >> maxAge;
            std::vector<Dog> dogs = userService.filterDogs(breed, maxAge);
            if (dogs.size() == 0) {
                std::cout << "No dogs found.\n";
                continue;
            }
            browseDogs(dogs);
        } else if (choice == 3) {
            showAdoptionList();
        } else if (choice == 0) {
            return;
        }
    }
}

void Ui::browseDogs(std::vector<Dog>& dogs) {
    if (dogs.size() == 0) {
        std::cout << "No dogs available.\n";
        return;
    }
    int index = 0;
    while (true) {
        Dog d = dogs[index % dogs.size()];
        std::cout << "\nBreed: " << d.getBreed()
                  << " | Name: " << d.getName()
                  << " | Age: " << d.getAge()
                  << " | Photo: " << d.getPhotoLink() << "\n";
        std::string cmd = "open \"" + d.getPhotoLink() + "\"";
        system(cmd.c_str());
        std::cout << "1. Adopt\n2. Next\n0. Back\nChoice -> ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        if (choice == 1) {
            userService.adoptDog(d);
            std::cout << "Added to adoption list!\n";
            index++;
        } else if (choice == 2) {
            index++;
        } else if (choice == 0) {
            return;
        }
    }
}

void Ui::showAdoptionList() {
    std::vector<Dog> list = userService.getAdoptionList();
    if (list.empty()) {
        std::cout << "No dogs adopted yet.\n";
        return;
    }
    userService.openAdoptionList();
}

/*Labrador,Rex,3,https://images.ctfassets.net/i3mh0tjpjx7v/srXUlu5v9MvSg2cvRdxV6/7b573d591a3e258fc59599e7cd0d628d/noemi-macavei-katocz-c7bUIRBqapA-unsplash.jpg
Poodle,Max,5,https://ask.woodgreen.org.uk/media/pages/images/99f12e906e-1737559438/miniature-poodle-900x900-crop.jpg
Bulldog,Buddy,2,https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTewxrOhGw4Q0TDWD68548o6PCt9XlpPiJGLA&s
Beagle,Charlie,4,https://petto.com.pl/cdn/shop/articles/SEOon_Beagle_d00b048e-5fb6-44b5-87ab-0bb697a39673.png?v=1747394114
Husky,Luna,1,https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTOnvrYMZLuRlTWba0jHnp9tk4AqkxpWZZiIQ&s
Poodle,Bella,6,https://cdn.britannica.com/44/233244-050-A65D4571/Chihuahua-dog.jpg
Rottweiler,Cooper,3,https://headsupfortails.com/cdn/shop/articles/Rottweiler_Dog_Breed_Guide-_Temperament_Appearance_Care_History.jpg?v=1758005579
Poodle,Daisy,7,https://www.burgesspetcare.com/wp-content/uploads/2024/09/shutterstock_2423158743.jpg
Boxer,Milo,2,https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQm7XAzcD7boqnGBqFqIula-lQMmPvhY7W1Iw&s
Pomeranian,Lola,4,https://www.akc.org/wp-content/uploads/2017/11/Pomeranian-On-White-01.jpg*/