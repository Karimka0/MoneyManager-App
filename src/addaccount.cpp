#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <addaccount.hpp>
#include <ui_addaccount.h>

AddAccount::AddAccount(QWidget *parent)
    : QDialog(parent), ui(new Ui::AddAccount) {
  ui->setupUi(this);
  QRegularExpression regExp("^\\d{0,12}([\\.,]\\d{1,2})?$");
  QRegularExpressionValidator *validator =
      new QRegularExpressionValidator(regExp);
  ui->InitSum->setValidator(validator);
  this->setWindowTitle("Account data");
}

AddAccount::~AddAccount() { delete ui; }

void AddAccount::on_pushButton_clicked() {
  emit signalAccount(ui->Name->text(), Currency(ui->comboBox->currentIndex()),
                     ui->InitSum->text());
  ui->Name->clear();
  ui->InitSum->clear();
  this->close();
}
