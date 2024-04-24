#pragma once
#include <QDialog>

namespace Ui {
class RegistrationSystem;
}

class RegistrationSystem : public QDialog {
  Q_OBJECT

public:
  explicit RegistrationSystem(QWidget *parent = nullptr);
  ~RegistrationSystem();

  QString getName();
  QString getPass();
  bool checkPass();

signals:
  void register_button_clicked2();
  void login_button_clicked2();

private slots:
  void on_RegButton_clicked();

  void on_lineName_textEdited(const QString &arg1);

  void on_linePassword_textEdited(const QString &arg1);

  void on_linePassword_2_textEdited(const QString &arg1);

  void on_RegButton_2_clicked();

private:
  Ui::RegistrationSystem *ui;

  QString m_userName;
  QString m_userPass;
  QString m_confirmation;
};
