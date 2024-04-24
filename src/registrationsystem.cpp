#include <registrationsystem.hpp>
#include <ui_registrationsystem.h>

RegistrationSystem::RegistrationSystem(QWidget *parent)
    : QDialog(parent), ui(new Ui::RegistrationSystem) {
  ui->setupUi(this);
}

RegistrationSystem::~RegistrationSystem() { delete ui; }

QString RegistrationSystem::getName() { return m_userName; }

QString RegistrationSystem::getPass() { return m_userPass; }

bool RegistrationSystem::checkPass() {
  return (m_userPass == m_confirmation && m_userPass != "" && m_userName != "");
}

void RegistrationSystem::on_RegButton_clicked() {
  emit register_button_clicked2();
}

void RegistrationSystem::on_lineName_textEdited(const QString &arg1) {
  m_userName = arg1;
}

void RegistrationSystem::on_linePassword_textEdited(const QString &arg1) {
  m_userPass = arg1;
}

void RegistrationSystem::on_linePassword_2_textEdited(const QString &arg1) {
  m_confirmation = arg1;
}

void RegistrationSystem::on_RegButton_2_clicked() {
  ui->lineName->clear();
  ui->linePassword->clear();
  ui->linePassword_2->clear();
  emit login_button_clicked2();
}
