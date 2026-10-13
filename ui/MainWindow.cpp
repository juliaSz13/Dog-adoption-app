#include "MainWindow.h"
#include "AdminWindow.h"
#include "UserWindow.h"

MainWindow::MainWindow(Service& s, UserService& us, QWidget* parent)
    : QWidget(parent), service(s), userService(us)
{
    ui.setupUi(this);

    auto* adminWin = new AdminWindow(service, nullptr);
    auto* userWin  = new UserWindow(userService, nullptr);

    connect(adminWin, &AdminWindow::dogsChanged, userWin, &UserWindow::populateTable);

    connect(ui.adminBtn, &QPushButton::clicked, this, [adminWin]() {
        adminWin->show();
        adminWin->raise();
    });

    connect(ui.userBtn, &QPushButton::clicked, this, [userWin]() {
        userWin->show();
        userWin->raise();
    });
}