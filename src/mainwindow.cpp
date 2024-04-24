#include <./ui_mainwindow.h>
#include <QDateTime>
#include <QDebug>
#include <QListView>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <mainwindow.hpp>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  user_counter = 0;
  ui_auth.setWindowTitle("Authorization");
  ui_reg.setWindowTitle("Registration");

  connect(&ui_auth, SIGNAL(login_button_clicked()), this,
          SLOT(authorizeUser()));
  connect(&ui_auth, SIGNAL(destroyed()), this, SLOT(show()));
  connect(&ui_auth, SIGNAL(register_button_clicked()), this,
          SLOT(registerWindowShow()));
  connect(&ui_reg, SIGNAL(register_button_clicked2()), this,
          SLOT(registerUser()));
  connect(&ui_reg, SIGNAL(destroyed()), &ui_auth, SLOT(show()));
  connect(&ui_reg, SIGNAL(login_button_clicked2()), this,
          SLOT(loginWindowShow()));
  connect(add_account, &AddAccount::signalAccount, this,
          &MainWindow::addAccount);
  connect(dialog, &Dialog::add_button_clicked, this,
          &MainWindow::AddTransaction);
  connect(delete_account, &DeleteAccountConfirm::DeleteAccountConfirmed, this,
          &MainWindow::DeleteAccount);
  connectDB();

  request = "CREATE TABLE userlist ( "
            "number INTEGER PRIMARY KEY NOT NULL,"
            "name TEXT, "
            "pass TEXT); ";
  query = new QSqlQuery(db);
  query->exec(request);

  accounts_model = new QSqlTableModel(this, db);
  transaction_model = new QSqlTableModel(this, db);
  ui->setupUi(this);
}
MainWindow::~MainWindow() {
  db.removeDatabase("authorisationDB");
  delete ui;
}

void MainWindow::display() { ui_auth.show(); }
void MainWindow::on_AddTransactionButton_clicked() {
  dialog->setModal(true);
  request = "SELECT name FROM %1";
  request = request.arg(accounts_table_name);
  query->exec(request);
  dialog->ClearAccChoose();
  while (query->next()) {
    QString name = query->value(0).toString();
    dialog->AddAccoutTo(name);
    dialog->AddAccoutFrom(name);
  }
  dialog->exec();
}

void MainWindow::on_AddAccountButton_clicked() {
  add_account->setModal(true);
  add_account->exec();
}

void MainWindow::registerUser() {
  if (ui_reg.checkPass()) {
    QSqlQuery query;
    QSqlRecord rec;
    request = "SELECT COUNT(*) "
              "FROM userlist;";
    query.exec(request);
    query.next();
    rec = query.record();

    user_counter = rec.value(0).toInt();
    m_username = ui_reg.getName();
    m_userpass = ui_reg.getPass();

    request = " SELECT * "
              " FROM userlist "
              " WHERE name = '%1'";
    request = request.arg(m_username);
    query.exec(request);

    if (!query.next()) {
      ++user_counter;
      request = "INSERT INTO userlist(number, name, pass)"
                "VALUES(%1, '%2', '%3');";
      request = request.arg(user_counter).arg(m_username).arg(m_userpass);
      query.exec(request);

      CreateUsersDB();

      accounts_model->setTable(accounts_table_name);
      ui->AccountsTable->setModel(accounts_model);

      transaction_model->setTable(transactions_table_name);
      ui->TransactionsTable->setModel(transaction_model);

      UpdateModels();
      ui_reg.hide();
      ui_auth.show();
    } else {
      qDebug() << "User with this name already exist";
    }
  } else {
    qDebug() << "Confirm password coorectly";
  }
}

void MainWindow::authorizeUser() {
  m_username = ui_auth.getLogin();
  m_userpass = ui_auth.getPass();
  QString username = "";
  QString userpass = "";

  request = " SELECT * "
            " FROM userlist "
            " WHERE name = '%1'";
  request = request.arg(m_username);
  QSqlQuery query;
  QSqlRecord rec;
  query.exec(request);
  rec = query.record();
  if (query.next()) {
    user_counter = query.value(rec.indexOf("number")).toInt();
    username = query.value(rec.indexOf("name")).toString();
    userpass = query.value(rec.indexOf("pass")).toString();
  }
  if (m_username != username || m_userpass != userpass) {
    qDebug() << "Password missmatch";
  } else if (username == "" || userpass == "") {
    qDebug() << "Uncorrect Login or password";
  } else {
    ui_auth.close();
    ui_reg.close();

    accounts_table_name = QString("%1%2").arg(m_username).arg("Accounts");
    transactions_table_name =
        QString("%1%2").arg(m_username).arg("Transactions");

    accounts_model->setTable(accounts_table_name);
    ui->AccountsTable->setModel(accounts_model);

    ui->AccountsTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Fixed);
    ui->AccountsTable->setColumnWidth(0, 150);
    ui->AccountsTable->setColumnWidth(1, 100);
    ui->AccountsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->AccountsTable->horizontalHeader()->setStretchLastSection(true);

    transaction_model->setTable(transactions_table_name);
    ui->TransactionsTable->setModel(transaction_model);
    transaction_model->setSort(0, Qt::DescendingOrder);

    ui->TransactionsTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Fixed);
    ui->TransactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TransactionsTable->hideColumn(5);
    ui->TransactionsTable->hideColumn(6);
    ui->TransactionsTable->hideColumn(7);
    ui->TransactionsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->TransactionsTable->horizontalHeader()->setStretchLastSection(true);

    UpdateModels();
    this->show();
  }
}

void MainWindow::registerWindowShow() {
  ui_auth.hide();
  ui_reg.show();
}
void MainWindow::loginWindowShow() {
  ui_auth.show();
  ui_reg.hide();
}

void MainWindow::CreateUsersDB() {
  request = "CREATE TABLE %1 ( "
            "name TEXT, "
            "currency TEXT, "
            "balance TEXT); ";
  accounts_table_name = QString("%1%2").arg(m_username).arg("Accounts");
  request = request.arg(accounts_table_name);
  query->exec(request);

  request = "CREATE TABLE %1 ( "
            "date TEXT,"
            "type TEXT, "
            "sum TEXT, "
            "currency TEXT, "
            "description TEXT, "
            "AccountTo TEXT, "
            "AccountFrom TEXT, "
            "Category TEXT); ";
  transactions_table_name = QString("%1%2").arg(m_username).arg("Transactions");
  request = request.arg(transactions_table_name);
  query->exec(request);
}

void MainWindow::addAccount(QString name, Currency curr, QString balance) {
  request = " SELECT * "
            " FROM %1 "
            " WHERE name = '%2'";
  request = request.arg(accounts_table_name).arg(name);
  query->exec(request);
  if (!query->next()) {
    request = "INSERT INTO %1(name, currency, balance)"
              "VALUES('%2', '%3', '%4');";
    request = request.arg(accounts_table_name)
                  .arg(name)
                  .arg(CurrencyToString(curr))
                  .arg(balance);
    query->exec(request);
    UpdateModels();
  } else {
    qDebug() << "Account with this name already exist";
  }
}

void MainWindow::DeleteAccount(bool isChecked) {
  if (isChecked) {
    QString name =
        accounts_model->data(accounts_model->index(account_row, 0)).toString();
    QModelIndexList matchingIndexes = transaction_model->match(
        transaction_model->index(0, transaction_model->fieldIndex("AccountTo")),
        Qt::DisplayRole, name, -1, Qt::MatchExactly);
    for (const QModelIndex &modelIndex : matchingIndexes) {
      DeleteTransaction(modelIndex.row());
    }

    matchingIndexes = transaction_model->match(
        transaction_model->index(0,
                                 transaction_model->fieldIndex("AccountFrom")),
        Qt::DisplayRole, name, -1, Qt::MatchExactly);
    for (const QModelIndex &modelIndex : matchingIndexes) {
      qDebug() << modelIndex.row();
      DeleteTransaction(modelIndex.row());
    }
  }
  accounts_model->removeRow(account_row);
  UpdateModels();
}

void MainWindow::AddTransaction(QString type, QString account_to,
                                QString account_from, QString currency,
                                QString description, QString sum,
                                QString category, QDate date) {
  request = "INSERT INTO %1(date, type, sum, currency, description, AccountTo, "
            "AccountFrom, Category)"
            "VALUES('%2', '%3', '%4', '%5', '%6', '%7', '%8', '%9');";
  request = request.arg(transactions_table_name)
                .arg(date.toString("yyyy-MM-dd"))
                .arg(type)
                .arg(sum)
                .arg(currency)
                .arg(description)
                .arg(account_to)
                .arg(account_from)
                .arg(category);
  query->exec(request);
  if (type == "Expense") {
    DepositAccount(account_to, sum, StringToCurrency(currency), "-");
  } else if (type == "Income") {
    DepositAccount(account_to, sum, StringToCurrency(currency), "+");
  } else {
    DepositAccount(account_from, sum, StringToCurrency(currency), "-");
    DepositAccount(account_to, sum, StringToCurrency(currency), "+");
  }
  UpdateModels();
}

void MainWindow::DeleteTransaction(int rowid) {
  QSqlRecord record = transaction_model->record(rowid);
  QString type = record.value(1).toString();
  QString AccountTo = record.value(5).toString();
  QString sum = record.value(2).toString();
  Currency currency = StringToCurrency(record.value(3).toString());
  if (type == "Expense") {
    DepositAccount(AccountTo, sum, currency, "+");
  } else if (type == "Income") {
    DepositAccount(AccountTo, sum, currency, "-");
  } else {
    QString AccountFrom = record.value(6).toString();
    DepositAccount(AccountFrom, sum, currency, "+");
    DepositAccount(AccountTo, sum, currency, "-");
  }
  transaction_model->removeRow(rowid);
  UpdateModels();
}

void MainWindow::DepositAccount(QString name, QString sum, Currency currency,
                                QString type) {
  request = "SELECT balance, currency FROM %1 WHERE name = '%2'";
  request = request.arg(accounts_table_name).arg(name);
  query->exec(request);
  query->next();
  double currentBalance = query->value(0).toDouble();
  Currency RealCurrency = StringToCurrency(query->value(1).toString());
  if (type == "+") {
    currentBalance +=
        money_system.TransferCurrency(currency, RealCurrency, sum.toDouble());
  } else {
    currentBalance -=
        money_system.TransferCurrency(currency, RealCurrency, sum.toDouble());
  }
  request = "UPDATE %1 SET balance = '%2' WHERE name = '%3'";
  request = request.arg(accounts_table_name).arg(currentBalance).arg(name);
  query->exec(request);
}

void MainWindow::connectDB() {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("./authorisationDB");
  db.open();
}

void MainWindow::on_DeleteTransactionButton_clicked() {
  DeleteTransaction(transaction_row);
}
void MainWindow::on_TransactionsTable_clicked(const QModelIndex &index) {
  transaction_row = index.row();
}
void MainWindow::on_AccountsTable_clicked(const QModelIndex &index) {
  account_row = index.row();
}
void MainWindow::on_DeleteAccoButton_clicked() { delete_account->show(); }

void MainWindow::UpdateModels() {
  accounts_model->select();
  transaction_model->select();
}
