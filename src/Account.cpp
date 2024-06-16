#include "Account.hpp"

Account::Account(const Person* const owner, const Bank* const bank, std::string& password)
  : owner_{owner}
  , bank_{bank}
  , password_{password}
  , account_number_{generate_unique_account_number()}
  , balance_{0}
  , account_status_{false}
{
   
}

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
    std::string number;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, 9);

    for (int i = 0; i < 16; ++i) {
      number += std::to_string(distribution(generator));
    }
  } while (used_account_numbers.contains(account_number));

  used_account_numbers.insert(account_number);
  return account_number;
}

auto Account::authentication(const std::string& owner_fingerprint) const -> bool {
  auto is_correct = std::hash<std::string>{}(owner_fingerprint) == owner_->get_hashed_fingerprint();
  if (!is_correct) {
    throw std::invalid_argument("Fingerprints are not matching");
  }
  return true;
}
