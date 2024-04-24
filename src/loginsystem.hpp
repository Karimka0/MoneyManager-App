#pragma once
#include <QDialog>

namespace Ui {
class LoginSystem;
}

class LoginSystem : public QDialog {
  Q_OBJECT

public:
  explicit LoginSystem(QWidget *parent = nullptr);
  ~LoginSystem();

  QString getLogin();
  QString getPass();

signals:
  void login_button_clicked();
  void register_button_clicked();

private slots:
  void on_LoginButton_clicked();

  void on_RegButton_clicked();

  void on_lineName_textEdited(const QString &arg1);

  void on_linePassword_textEdited(const QString &arg1);

private:
  Ui::LoginSystem *ui;
  QString m_username;
  QString m_userpass;
};
