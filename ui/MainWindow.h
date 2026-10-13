#pragma once
#include <QWidget>
#include "ui_MainWindow.h"
#include "Service.h"
#include "UserService.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    MainWindow(Service& service, UserService& userService, QWidget* parent = nullptr);
private:
    Ui::MainWindow ui;
    Service& service;
    UserService& userService;
};