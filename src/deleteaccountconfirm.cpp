#include <deleteaccountconfirm.hpp>
#include <ui_deleteaccountconfirm.h>

DeleteAccountConfirm::DeleteAccountConfirm(QWidget *parent)
    : QDialog(parent), ui(new Ui::DeleteAccountConfirm) {
  ui->setupUi(this);
}

DeleteAccountConfirm::~DeleteAccountConfirm() { delete ui; }

void DeleteAccountConfirm::on_pushButton_clicked() {
  emit DeleteAccountConfirmed(ui->DeleteTransactionsCheck->isChecked());
  close();
}

void DeleteAccountConfirm::on_pushButton_2_clicked() { close(); }
