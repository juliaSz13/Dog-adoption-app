// Command.h
#pragma once
#include "Service.h"
#include <memory>

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class AddCommand : public Command {
    Service& service;
    Dog dog;
public:
    AddCommand(Service& s, const Dog& d) : service(s), dog(d) {}
    void execute() override {
        service.addDog(dog.getBreed(), dog.getName(), dog.getAge(), dog.getPhotoLink());
    }
    void undo() override {
        service.removeDog(dog.getBreed(), dog.getName());
    }
};


class RemoveCommand : public Command {
    Service& service;
    Dog dog;
public:
    RemoveCommand(Service& s, const Dog& d) : service(s), dog(d) {}
    void execute() override {
        service.removeDog(dog.getBreed(), dog.getName());
    }
    void undo() override {
        service.addDog(dog.getBreed(), dog.getName(), dog.getAge(), dog.getPhotoLink());
    }
};

class UpdateCommand : public Command {
    Service& service;
    Dog oldDog, newDog;
public:
    UpdateCommand(Service& s, const Dog& oldD, const Dog& newD)
        : service(s), oldDog(oldD), newDog(newD) {}
    void execute() override {
        service.updateDog(oldDog.getBreed(), oldDog.getName(),
                          newDog.getBreed(), newDog.getName(),
                          newDog.getAge(), newDog.getPhotoLink());
    }
    void undo() override {
        service.updateDog(newDog.getBreed(), newDog.getName(),
                          oldDog.getBreed(), oldDog.getName(),
                          oldDog.getAge(), oldDog.getPhotoLink());
    }
};