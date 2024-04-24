#pragma once
#include <QDebug>
#include <QMainWindow>
#include <QSqlTableModel>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <addaccount.hpp>
#include <deleteaccountconfirm.hpp>
#include <dialog.hpp>
#include <loginsystem.hpp>
#include <registrationsystem.hpp>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void display();
  void connectDB();

private slots:

  void authorizeUser();
  void registerWindowShow();
  void loginWindowShow();
  void registerUser();
  void CreateUsersDB();
  void on_DeleteTransactionButton_clicked();
  void on_TransactionsTable_clicked(const QModelIndex &index);
  void on_AddAccountButton_clicked();
  void on_AddTransactionButton_clicked();
  void on_DeleteAccoButton_clicked();
  void on_AccountsTable_clicked(const QModelIndex &index);

private:
  Ui::MainWindow *ui;
  Dialog *dialog = new Dialog();
  AddAccount *add_account = new AddAccount();
  DeleteAccountConfirm *delete_account = new DeleteAccountConfirm();
  QSqlTableModel *accounts_model;
  QSqlTableModel *transaction_model;
  LoginSystem ui_auth;
  RegistrationSystem ui_reg;
  MoneySystem money_system;
  QSqlQuery *query;
  QSqlDatabase db;

  QString m_username;
  QString m_userpass;
  QString request;
  QString accounts_table_name;
  QString transactions_table_name;

  int user_counter;
  int transaction_row;
  int account_row;

  void UpdateModels();
  // template <typename... Args> void DoRequest(QString request, Args... args);
  // void ProcessArgs(QString &request);
  // template <typename T, typename... Args>
  // void ProcessArgs(QString &request, T arg, Args... args);

public slots:

  void addAccount(QString name, Currency curr, QString sum);
  void DeleteAccount(bool isChecked);
  void AddTransaction(QString type, QString account_to, QString account_from,
                      QString currency, QString description, QString sum,
                      QString category, QDate date);
  void DeleteTransaction(int rowid);
  void DepositAccount(QString name, QString sum, Currency currency,
                      QString type);
};
