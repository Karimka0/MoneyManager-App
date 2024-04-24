#include <MoneySystem.hpp>

double MoneySystem::TransferCurrency(Currency from, Currency to, double sum) {
  if (from == to) {
    return sum;
  }
  sum *= (ToRub[CurrencyToString(from)] / ToRub[CurrencyToString(to)]);
  return round(sum * 100) / 100;
}

QString CurrencyToString(Currency currency) {
  switch (currency) {
  case Currency::RUB:
    return "RUB";
  case Currency::KZT:
    return "KZT";
  case Currency::USD:
    return "USD";
  case Currency::EUR:
    return "EUR";
  }
}

Currency StringToCurrency(QString currency) {
  if (currency == "RUB")
    return Currency::RUB;
  else if (currency == "KZT")
    return Currency::KZT;
  else if (currency == "USD")
    return Currency::USD;
  else
    return Currency::EUR;
}
