#include <QApplication>
#include <mainwindow.hpp>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowTitle("Wallet Manager");
  w.display();
  return a.exec();
}
