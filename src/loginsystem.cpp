#include <loginsystem.hpp>
#include <ui_loginsystem.h>

LoginSystem::LoginSystem(QWidget *parent)
    : QDialog(parent), ui(new Ui::LoginSystem) {
  ui->setupUi(this);
}

LoginSystem::~LoginSystem() { delete ui; }

QString LoginSystem::getLogin() { return m_username; }

QString LoginSystem::getPass() { return m_userpass; }

void LoginSystem::on_LoginButton_clicked() { emit login_button_clicked(); }

void LoginSystem::on_RegButton_clicked() {
  ui->lineName->clear();
  ui->linePassword->clear();
  emit register_button_clicked();
}

void LoginSystem::on_lineName_textEdited(const QString &arg1) {
  m_username = arg1;
}

void LoginSystem::on_linePassword_textEdited(const QString &arg1) {
  m_userpass = arg1;
}
