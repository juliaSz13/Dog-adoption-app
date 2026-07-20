#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include "UserService.h"
#include "Dog.h"
#include <QTableWidget>
#include"AdoptionModelTable.h"

class UserWindow : public QWidget {
    Q_OBJECT
public:
    UserWindow(UserService& userService, QWidget* parent = nullptr);
private:
    UserService& userService;

    // current dog list being browsed
    std::vector<Dog> currentDogs;
    int currentIndex = 0;

    // display labels
    QLabel* breedLabel;
    QLabel* nameLabel;
    QLabel* ageLabel;
    QLabel* photoLabel;

    // filter inputs
    QLineEdit* breedFilter;
    QSpinBox*  ageFilter;

    // buttons
    QPushButton* nextBtn;
    QPushButton* adoptBtn;
    QPushButton* filterBtn;
    QPushButton* showAllBtn;
    QPushButton* adoptionListBtn;
    QPushButton* viewAdoptionListBtn;

    QTableView* adoptionView = nullptr;
    AdoptionTableModel* adoptionModel = nullptr;
    QWidget* adoptionWindow = nullptr;

    void showCurrentDog();
    void onNext();
    void onAdopt();
    void onFilter();
    void onShowAll();
    void onShowAdoptionList();
    void onViewAdoptionList();
public slots:
void populateTable();
};