#include "tests.h"
#include <cassert>
#include <stdexcept>
#include <iostream>
#include <cstdio>

void tests::testDog() {
    Dog d("Labrador", "Rex", 3, "http://example.com");
    assert(d.getBreed() == "Labrador");
    assert(d.getName() == "Rex");
    assert(d.getAge() == 3);
    assert(d.getPhotoLink() == "http://example.com");

    d.setAge(5);
    assert(d.getAge() == 5);
    d.setBreed("Poodle");
    assert(d.getBreed() == "Poodle");
    d.setName("Max");
    assert(d.getName() == "Max");
    d.setPhotoLink("http://example2.com");
    assert(d.getPhotoLink() == "http://example2.com");

    Dog d2("Poodle", "Max", 10, "http://other.com");
    assert(d == d2);
}

void tests::testRepository() {
    std::remove("test.txt");
    Repository repo("test.txt");
    assert(repo.exists("Labrador", "Rex") == false);
    assert(repo.listAllDogs().size() == 0);
    repo.addDog(Dog("Labrador", "Rex", 3, "http://example.com"));
    assert(repo.exists("Labrador", "Rex") == true);
    assert(repo.listAllDogs().size() == 1);
    repo.addDog(Dog("Poodle", "Max", 5, "http://example.com"));
    assert(repo.listAllDogs().size() == 2);
    assert(repo.exists("Poodle", "Max") == true);
    assert(repo.exists("Husky", "Lup") == false);
    repo.updateDog("Labrador", "Rex", Dog("Labrador", "Rex", 7, "http://new.com"));
    assert(repo.listAllDogs()[0].getAge() == 7);
    assert(repo.listAllDogs()[0].getPhotoLink() == "http://new.com");

    repo.updateDog("Inexistent", "Nimeni", Dog("a", "b", 1, "http://x.com"));

    repo.removeDog("Labrador", "Rex");
    assert(repo.exists("Labrador", "Rex") == false);
    assert(repo.listAllDogs().size() == 1);

    repo.removeDog("Inexistent", "Nimeni");
    assert(repo.listAllDogs().size() == 1);
}

void tests::testService() {
    std::remove("test.txt");
    Repository repo("test.txt");
    Service service(repo);

    service.addDog("Labrador", "Rex", 3, "http://example.com");
    assert(service.listAllDogs().size() == 1);

    try { service.addDog("Labrador", "Rex", 3, "url"); assert(false); } catch (...) { assert(true); }
    try { service.addDog("Lab", "Buddy", -1, "url"); assert(false); } catch (...) { assert(true); }

    service.removeDog("Labrador", "Rex");
    assert(service.listAllDogs().size() == 0);

    try { service.removeDog("Labrador", "Rex"); assert(false); } catch (...) { assert(true); }

    service.addDog("Poodle", "Max", 2, "http://poodle.com");

    service.updateDog("Poodle", "Max", "Beagle", "Charlie", 5, "http://beagle.com");
    Dog d = service.listAllDogs()[0];
    assert(d.getBreed() == "Beagle");
    assert(d.getName() == "Charlie");
    assert(d.getAge() == 5);
    service.updateDog("Beagle", "Charlie", "same", "Maximus", 10, "same");
    d = service.listAllDogs()[0];
    assert(d.getBreed() == "Beagle");
    assert(d.getName() == "Maximus");
    assert(d.getAge() == 10);
    assert(d.getPhotoLink() == "http://beagle.com");
    service.updateDog("Beagle", "Maximus", "same", "same", -1, "http://newphoto.com");
    d = service.listAllDogs()[0];
    assert(d.getAge() == 10);
    assert(d.getPhotoLink() == "http://newphoto.com");
    try {
        service.updateDog("Non", "Existent", "same", "same", 5, "url");
        assert(false);
    } catch (std::runtime_error&) { assert(true); }

    try {
        service.updateDog("Beagle", "Maximus", "same", "", 5, "url");
        assert(false);
    } catch (std::runtime_error&) { assert(true); }

    assert(service.listAllDogs().size() == 1);
}

void tests::testUserService() {
    std::remove("test.txt");
    std::remove("test_adoption.csv");
    std::remove("test_adoption.html");

    Repository repo("test.txt");
    repo.addDog(Dog("Labrador", "Rex", 3, "http://example.com"));
    repo.addDog(Dog("Labrador", "Max", 1, "http://example.com"));
    repo.addDog(Dog("Poodle", "Bella", 5, "http://example.com"));
    repo.addDog(Dog("Husky", "Luna", 2, "http://example.com"));

    UserService usCSV(repo, "CSV", "test_adoption");
    usCSV.adoptDog(Dog("Labrador", "Rex", 3, "http://example.com"));
    assert(usCSV.getAdoptionList().size() == 1);
    assert(usCSV.isAdopted("Labrador", "Rex") == true);

    UserService usHTML(repo, "HTML", "test_adoption");
    usHTML.adoptDog(Dog("Labrador", "Max", 1, "http://example.com"));
    assert(usHTML.getAdoptionList().size() == 1);
    assert(usHTML.isAdopted("Labrador", "Max") == true);

    std::cout << "testUserService PASSED\n";
}

void tests::testAll() {
    testDog();
    testRepository();
    testService();
    testUserService();
    std::cout << "ALL TESTS PASSED\n" << std::endl;
}