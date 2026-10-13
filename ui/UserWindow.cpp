#include "UserWindow.h"
#include <QMessageBox>
#include <QGroupBox>
#include <QHeaderView>
#include"AdoptionModelTable.h"
#include <cstdlib>

UserWindow::UserWindow(UserService& us, QWidget* parent)
    : QWidget(parent), userService(us)
{
    setWindowTitle("User Mode");
    setMinimumSize(500, 400);

    //--- Dog display area ---
    breedLabel = new QLabel("Breed: ");
    nameLabel  = new QLabel("Name: ");
    ageLabel   = new QLabel("Age: ");
    photoLabel = new QLabel("Photo: ");

    auto* dogGroup = new QGroupBox("Current Dog");
    auto* dogLayout = new QVBoxLayout(dogGroup);
    dogLayout->addWidget(breedLabel);
    dogLayout->addWidget(nameLabel);
    dogLayout->addWidget(ageLabel);
    dogLayout->addWidget(photoLabel);

    // --- Browse buttons ---
    nextBtn  = new QPushButton("Next");
    adoptBtn = new QPushButton("Adopt");

    auto* browseLayout = new QHBoxLayout();
    browseLayout->addWidget(nextBtn);
    browseLayout->addWidget(adoptBtn);

    // --- Filter area ---
    breedFilter = new QLineEdit();
    breedFilter->setPlaceholderText("Breed (leave empty for all)");
    ageFilter = new QSpinBox();
    ageFilter->setRange(1, 30);
    ageFilter->setValue(30);

    filterBtn  = new QPushButton("Filter");
    showAllBtn = new QPushButton("Show All");

    auto* filterLayout = new QHBoxLayout();
    filterLayout->addWidget(new QLabel("Breed:"));
    filterLayout->addWidget(breedFilter);
    filterLayout->addWidget(new QLabel("Max age:"));
    filterLayout->addWidget(ageFilter);
    filterLayout->addWidget(filterBtn);
    filterLayout->addWidget(showAllBtn);

    // --- Adoption list button ---
    adoptionListBtn = new QPushButton("Open Adoption List");
    viewAdoptionListBtn = new QPushButton("View Adoption List");

    // --- Main layout ---
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(dogGroup);
    mainLayout->addLayout(browseLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(adoptionListBtn);
    mainLayout->addWidget(viewAdoptionListBtn);

    // --- Connections ---
    connect(nextBtn,         &QPushButton::clicked, this, &UserWindow::onNext);
    connect(adoptBtn,        &QPushButton::clicked, this, &UserWindow::onAdopt);
    connect(filterBtn,       &QPushButton::clicked, this, &UserWindow::onFilter);
    connect(showAllBtn,      &QPushButton::clicked, this, &UserWindow::onShowAll);
    connect(adoptionListBtn, &QPushButton::clicked, this, &UserWindow::onShowAdoptionList);
    connect(viewAdoptionListBtn, &QPushButton::clicked, this, &UserWindow::onViewAdoptionList);

    // load all dogs at start
    onShowAll();
}

void UserWindow::showCurrentDog() {
    if (currentDogs.empty()) {
        breedLabel->setText("Breed: -");
        nameLabel->setText("Name: -");
        ageLabel->setText("Age: -");
        photoLabel->setText("Photo: -");
        return;
    }
    int idx = currentIndex % currentDogs.size();
    Dog d = currentDogs[idx];
    breedLabel->setText("Breed: " + QString::fromStdString(d.getBreed()));
    nameLabel->setText("Name: "  + QString::fromStdString(d.getName()));
    ageLabel->setText("Age: "    + QString::number(d.getAge()));
    photoLabel->setText("Photo: "+ QString::fromStdString(d.getPhotoLink()));

    std::string cmd = "open \"" + d.getPhotoLink() + "\"";
    system(cmd.c_str());
}

void UserWindow::onNext() {
    if (currentDogs.empty()) return;
    currentIndex++;
    showCurrentDog();
}

void UserWindow::onAdopt() {
    if (currentDogs.empty()) {
        QMessageBox::information(this, "Info", "No dogs to adopt.");
        return;
    }
    int idx = currentIndex % currentDogs.size();
    Dog d = currentDogs[idx];
    userService.adoptDog(d);
    currentDogs.erase(currentDogs.begin() + idx);
    if (currentIndex >= (int)currentDogs.size() && currentIndex > 0)
        currentIndex--;
    QMessageBox::information(this, "Adopted!", 
        QString::fromStdString(d.getName()) + " was added to the adoption list!");
    showCurrentDog();

    if (adoptionModel && adoptionWindow && adoptionWindow->isVisible()) {
        delete adoptionModel;
        adoptionModel = new AdoptionTableModel(userService.getAdoptionList(), adoptionWindow);
        adoptionView->setModel(adoptionModel);
    }
}

void UserWindow::onFilter() {
    std::string breed = breedFilter->text().toStdString();
    int maxAge = ageFilter->value();
    currentDogs = userService.filterDogs(breed, maxAge);
    currentIndex = 0;
    if (currentDogs.empty())
        QMessageBox::information(this, "No results", "No dogs match the filter.");
    showCurrentDog();
}

void UserWindow::onShowAll() {
    currentDogs = userService.filterDogs("", 9999);
    currentIndex = 0;
    showCurrentDog();
}

void UserWindow::onShowAdoptionList() {
    userService.openAdoptionList();

}
void UserWindow::onViewAdoptionList() {
    if (!adoptionWindow) {
        adoptionWindow = new QWidget(nullptr);
        adoptionWindow->setWindowTitle("Adoption List");
        adoptionWindow->setMinimumSize(500, 300);

        adoptionModel = new AdoptionTableModel(userService.getAdoptionList(), adoptionWindow);

        adoptionView = new QTableView(adoptionWindow);
        adoptionView->setModel(adoptionModel);
        adoptionView->horizontalHeader()->setStretchLastSection(true);
        adoptionView->setSelectionBehavior(QAbstractItemView::SelectRows);
        adoptionView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        adoptionView->setStyleSheet(
            "QTableView { background-color: #c0392b; color: white; }"
            "QTableView::item:selected { background-color: #922b21; }"
            "QHeaderView::section { background-color: #922b21; color: white; font-weight: bold; }"
        );
        auto* layout = new QVBoxLayout(adoptionWindow);
        layout->addWidget(adoptionView);
    }
    adoptionWindow->show();
    //adoptionWindow->raise();
}
void UserWindow::populateTable() {
    currentDogs = userService.filterDogs("", 9999);
    currentIndex = 0;
    showCurrentDog();
}
