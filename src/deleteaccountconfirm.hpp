#pragma once
#include <QDialog>

namespace Ui {
class DeleteAccountConfirm;
}

class DeleteAccountConfirm : public QDialog {
  Q_OBJECT

public:
  explicit DeleteAccountConfirm(QWidget *parent = nullptr);
  ~DeleteAccountConfirm();

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();

signals:
  void DeleteAccountConfirmed(bool isChecked);

private:
  Ui::DeleteAccountConfirm *ui;
};
