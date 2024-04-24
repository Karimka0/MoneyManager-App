#pragma once
#include <QString>
#include <map>

enum class Currency { RUB, KZT, USD, EUR };

QString CurrencyToString(Currency currency);
Currency StringToCurrency(QString currency);

class MoneySystem {
  std::map<QString, double> ToRub = {
      {"RUB", 1.0}, {"USD", 93.33}, {"EUR", 99.59}, {"KZT", 0.21}};

public:
  double TransferCurrency(Currency from, Currency to, double sum);
};
