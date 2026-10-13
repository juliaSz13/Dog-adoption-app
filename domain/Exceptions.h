//
// Created by Szep Julia-Maria on 13.04.2026.
//

#ifndef A6_7_JULIASZ13_EXCEPTIONS_H
#define A6_7_JULIASZ13_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class DogException : public std::runtime_error {
public:
    DogException(const std::string& msg) : std::runtime_error(msg) {}
};

class ValidationException : public DogException {
public:
    ValidationException(const std::string& msg) : DogException(msg) {}
};

class RepositoryException : public DogException {
public:
    RepositoryException(const std::string& msg) : DogException(msg) {}
};
#endif //A6_7_JULIASZ13_EXCEPTIONS_H