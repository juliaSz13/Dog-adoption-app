#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Service.h"
#include"Command.h"
#include<stack>

class AdminWindow : public QWidget {
    Q_OBJECT
public:
    AdminWindow(Service& service, QWidget* parent = nullptr);
private:
    Service& service;
    QTableWidget* table;
    QLineEdit* breedEdit;
    QLineEdit* nameEdit;
    QSpinBox*  ageSpin;
    QLineEdit* photoEdit;
    QPushButton* addBtn;
    QPushButton* removeBtn;
    QPushButton* updateBtn;
    QPushButton* undoBtn;
    QPushButton* redoBtn;

    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

    void populateTable();
    void onAdd();
    void onRemove();
    void onUpdate();
    void onUndo();
    void onRedo();
    void executeCommand(std::unique_ptr<Command> cmd);
    signals:
    void dogsChanged();
};