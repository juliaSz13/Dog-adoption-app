#include "AdminWindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include<QShortcut>

AdminWindow::AdminWindow(Service& s, QWidget* parent)
    : QWidget(parent), service(s)
{
    setWindowTitle("Admin Panel");
    setMinimumSize(700, 500);

    // --- Table ---
    table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({"Breed", "Name", "Age", "Photo"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // --- Input fields ---
    breedEdit = new QLineEdit();
    breedEdit->setPlaceholderText("Breed");
    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Name");
    ageSpin = new QSpinBox();
    ageSpin->setRange(0, 30);
    photoEdit = new QLineEdit();
    photoEdit->setPlaceholderText("Photo URL");

    addBtn    = new QPushButton("Add");
    removeBtn = new QPushButton("Remove selected");
    updateBtn = new QPushButton("Update selected");
    undoBtn   = new QPushButton("Undo");
    redoBtn   = new QPushButton("Redo");

    auto* formLayout = new QHBoxLayout();
    formLayout->addWidget(new QLabel("Breed:"));
    formLayout->addWidget(breedEdit);
    formLayout->addWidget(new QLabel("Name:"));
    formLayout->addWidget(nameEdit);
    formLayout->addWidget(new QLabel("Age:"));
    formLayout->addWidget(ageSpin);
    formLayout->addWidget(new QLabel("Photo:"));
    formLayout->addWidget(photoEdit);

    auto* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(addBtn);
    btnLayout->addWidget(removeBtn);
    btnLayout->addWidget(updateBtn);
    btnLayout->addWidget(undoBtn);
    btnLayout->addWidget(redoBtn);

    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(btnLayout);

    connect(addBtn,    &QPushButton::clicked, this, &AdminWindow::onAdd);
    connect(removeBtn, &QPushButton::clicked, this, &AdminWindow::onRemove);
    connect(updateBtn, &QPushButton::clicked, this, &AdminWindow::onUpdate);
    connect(undoBtn,   &QPushButton::clicked, this, &AdminWindow::onUndo);
    connect(redoBtn,   &QPushButton::clicked, this, &AdminWindow::onRedo);
    auto* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), this);
    auto* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), this);
    connect(undoShortcut, &QShortcut::activated, this, &AdminWindow::onUndo);
    connect(redoShortcut, &QShortcut::activated, this, &AdminWindow::onRedo);

    populateTable();
}

void AdminWindow::populateTable() {
    table->setRowCount(0);
    for (const Dog& d : service.listAllDogs()) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getBreed())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(d.getName())));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(d.getAge())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getPhotoLink())));
    }

}
void AdminWindow::executeCommand(std::unique_ptr<Command> cmd) {
    try {
        cmd->execute();
        undoStack.push(std::move(cmd));
        while (!redoStack.empty()) redoStack.pop();
        populateTable();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    emit dogsChanged();
}
void AdminWindow::onAdd() {
    auto cmd = std::make_unique<AddCommand>(service,
        Dog(breedEdit->text().toStdString(),
            nameEdit->text().toStdString(),
            ageSpin->value(),
            photoEdit->text().toStdString()));
    executeCommand(std::move(cmd));
}

void AdminWindow::onRemove() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this, "Error", "Select a row first."); return; }
    std::string breed = table->item(row, 0)->text().toStdString();
    std::string name  = table->item(row, 1)->text().toStdString();
    int age           = table->item(row, 2)->text().toInt();
    std::string photo = table->item(row, 3)->text().toStdString();
    auto cmd = std::make_unique<RemoveCommand>(service, Dog(breed, name, age, photo));
    executeCommand(std::move(cmd));
}

void AdminWindow::onUpdate() {
    int row = table->currentRow();
    if (row < 0) { QMessageBox::warning(this, "Error", "Select a row to update."); return; }
    std::string oldBreed = table->item(row, 0)->text().toStdString();
    std::string oldName  = table->item(row, 1)->text().toStdString();
    int oldAge           = table->item(row, 2)->text().toInt();
    std::string oldPhoto = table->item(row, 3)->text().toStdString();

    std::string newBreed = breedEdit->text().isEmpty() ? oldBreed : breedEdit->text().toStdString();
    std::string newName  = nameEdit->text().isEmpty()  ? oldName  : nameEdit->text().toStdString();
    int newAge           = ageSpin->value() == 0       ? oldAge   : ageSpin->value();
    std::string newPhoto = photoEdit->text().isEmpty() ? oldPhoto : photoEdit->text().toStdString();

    auto cmd = std::make_unique<UpdateCommand>(service,
        Dog(oldBreed, oldName, oldAge, oldPhoto),
        Dog(newBreed, newName, newAge, newPhoto));
    executeCommand(std::move(cmd));
}

void AdminWindow::onUndo() {
    if (undoStack.empty()) { QMessageBox::information(this, "Undo", "Nothing to undo."); return; }
    auto cmd = std::move(undoStack.top());
    undoStack.pop();
    try {
        cmd->undo();
        redoStack.push(std::move(cmd));
        populateTable();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    emit dogsChanged();
}

void AdminWindow::onRedo() {
    if (redoStack.empty()) { QMessageBox::information(this, "Redo", "Nothing to redo."); return; }
    auto cmd = std::move(redoStack.top());
    redoStack.pop();
    try {
        cmd->execute();
        undoStack.push(std::move(cmd));
        populateTable();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    emit dogsChanged();
}