#include "Account.hpp"

std::unordered_set<std::string> Account::used_account_numbers;

Account::Account(const Person* const owner, std::string& password)
  : owner_{owner}
  , CVV2_{generate_random_digits_string(4)}
  , password_{password}
  , exp_date_{"12-34"} // TODO: change this to proper init
  , account_number_{generate_unique_account_number()}
  , balance_{0.0}
  , account_status_{true}
{ }

auto Account::get_owner() const -> const Person* {
  return owner_;
}

auto Account::get_balance() const -> double {
  return balance_;
}

auto Account::get_account_number() const -> std::string {
  return account_number_;
}

auto Account::get_status() const -> bool {
  return account_status_;
}

auto Account::get_CVV2(std::string& owner_fingerprint) const -> std::string {
  try {
    authentication(owner_fingerprint); // throws on a mismatch
    return CVV2_;  
  } catch (const std::invalid_argument& e) {
    throw e;
  }
}

auto Account::get_password(std::string& owner_fingerprint) const -> std::string {
  try {
    authentication(owner_fingerprint); // throws on a mismatch
    return password_;  
  } catch (const std::invalid_argument& e) {
    throw e;
  }
}

auto Account::get_exp_date(std::string& owner_fingerprint) const -> std::string {
  try {
    authentication(owner_fingerprint); // throws on a mismatch
    return exp_date_;  
  } catch (const std::invalid_argument& e) {
    throw e;
  }
}

auto Account::set_password(std::string& password, std::string& owner_fingerprint) -> bool {
  try {
    authentication(owner_fingerprint); // throws on a mismatch
    password_ = password;  
  } catch (const std::invalid_argument& e) {
    throw e;
  }

  return true;
}

auto Account::operator<=>(const Account& other) const -> std::strong_ordering {
  return account_number_ <=> other.account_number_;
}

auto Account::generate_unique_account_number() const -> std::string {
  std::string account_number;
  do {
    account_number = generate_random_digits_string(16);
  } while (used_account_numbers.contains(account_number));

  used_account_numbers.insert(account_number);
  return account_number;
}

auto Account::authentication(const std::string& owner_fingerprint) const -> bool {
  auto is_correct = hash_fingerprint(owner_fingerprint) == owner_->get_hashed_fingerprint();
  if (!is_correct) {
    throw std::invalid_argument("Fingerprints are not matching");
  }
  return true;
}
