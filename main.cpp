#include <QApplication>
#include "MainWindow.h"
#include "Repository.h"
#include "Service.h"
#include "UserService.h"
#include "tests.h"
#include <QInputDialog>

int main(int argc, char* argv[]) {
    tests t;
    t.testAll();

    QApplication app(argc, argv);
    Repository repo("dogs.txt");
    Service service(repo);
    bool ok;
    QString type = QInputDialog::getItem(
        nullptr, "File type", "Choose adoption list type:",
        {"HTML", "CSV"}, 0, false, &ok
    );
    if (!ok) return 1;

    UserService userService(repo, type.toStdString());

    MainWindow window(service, userService);
    window.show();

    return app.exec();
}