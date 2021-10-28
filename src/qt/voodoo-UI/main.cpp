#include "voodoUI.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QMainWindow *MainWindow = new QMainWindow;


  Ui::MainWindow ui;

  ui.setupUi(MainWindow);

  MainWindow->show();


  return app.exec();// this runs the main event loop and sees to it that cleanup is done
}
