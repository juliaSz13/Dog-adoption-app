//
// Created by Szep Julia-Maria on 24.03.2026.
//

#ifndef A4_5_JULIASZ13_UI_H
#define A4_5_JULIASZ13_UI_H

#include "Service.h"
#include "UserService.h"

class Ui {
private:
    Service& service;
    UserService& userService;
    void addDog();
    void removeDog();
    void updateDog();
    void listAllDogs();
    void runAdminMenu();
    void runUserMeniu();
    void browseDogs(std::vector<Dog>& dogs);
    void showAdoptionList();
public:
    Ui(Service& service, UserService& userService);
    void start_ui();
};


#endif //A4_5_JULIASZ13_UI_H