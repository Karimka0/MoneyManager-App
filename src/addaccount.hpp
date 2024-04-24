#pragma once
#include <MoneySystem.hpp>
#include <QDialog>

namespace Ui {
class AddAccount;
}

class AddAccount : public QDialog {
  Q_OBJECT

public:
  explicit AddAccount(QWidget *parent = nullptr);
  ~AddAccount();

private:
  Ui::AddAccount *ui;

signals:
  void signalAccount(QString name, Currency curr, QString sum);

private slots:
  void on_pushButton_clicked();
};
