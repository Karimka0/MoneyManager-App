#include <dialog.hpp>
#include <ui_dialog.h>

Dialog::Dialog(QWidget *parent) : QDialog(parent), ui(new Ui::Dialog) {
  ui->setupUi(this);
  QRegularExpression regExp("^\\d{0,12}([\\.,]\\d{1,2})?$");
  QRegularExpressionValidator *validator =
      new QRegularExpressionValidator(regExp);
  ui->SumData->setValidator(validator);
  this->setWindowTitle("Transaction data");
}

Dialog::~Dialog() { delete ui; }

void Dialog::on_TypeChoose_activated(int index) {
  if (index == 0) {
    ui->Category->setText("Category:");
    ui->ExpenseChoose->show();
    ui->IncomeChoose->hide();
    ui->AccountFromChoose->hide();

  } else if (index == 1) {
    ui->Category->setText("Category:");
    ui->IncomeChoose->show();
    ui->ExpenseChoose->hide();
    ui->AccountFromChoose->hide();

  } else if (index == 2) {
    ui->Category->setText("From wallet:");
    ui->AccountFromChoose->show();
    ui->ExpenseChoose->hide();
    ui->IncomeChoose->hide();
  }
}

void Dialog::AddAccoutTo(QString name) { ui->AccountToChoose->addItem(name); }

void Dialog::AddAccoutFrom(QString name) {
  ui->AccountFromChoose->addItem(name);
}

void Dialog::ClearAccChoose() {
  ui->AccountToChoose->clear();
  ui->AccountFromChoose->clear();
}

void Dialog::on_pushButton_clicked() {
  QString description = " ";
  QString category = " ";
  if (ui->TypeChoose->currentText() == "Expense") {
    description = "for " + ui->ExpenseChoose->currentText() + " from " +
                  ui->AccountToChoose->currentText() + "s";
    category = ui->ExpenseChoose->currentText();
  } else if (ui->TypeChoose->currentText() == "Income") {
    description = ui->IncomeChoose->currentText() + " on " +
                  ui->AccountToChoose->currentText();
    category = ui->IncomeChoose->currentText();
  } else {
    description = "from " + ui->AccountFromChoose->currentText() + " to " +
                  ui->AccountToChoose->currentText();
  }

  emit add_button_clicked(
      ui->TypeChoose->currentText(), ui->AccountToChoose->currentText(),
      ui->AccountFromChoose->currentText(), ui->CurrencyChoose->currentText(),
      description, ui->SumData->text(), category, ui->dateEdit->date());
  ui->SumData->clear();
  close();
}
