#pragma once

#include <compare>
#include <optional>
#include <string>
#include <unordered_set>
#include <random>

#include "Person.hpp"
#include "Utils.hpp"

class Account {

public:
  Account(const Person* const owner, std::string& password);

  auto get_owner() const -> const Person*;
  auto get_balance() const -> double;
  auto get_account_number() const -> std::string;
  auto get_status() const -> bool;

  auto get_CVV2(std::string& owner_fingerprint) const -> std::string;
  auto get_password(std::string& owner_fingerprint) const -> std::string;
  auto get_exp_date(std::string& owner_fingerprint) const -> std::string;

  auto set_password(std::string& password, std::string& owner_fingerprint) -> bool;

  auto operator<=>(const Account& other) const -> std::strong_ordering;

  void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
  auto generate_unique_account_number() const -> std::string;
  auto authentication(const std::string& owner_fingerprint) const -> bool;

private:
  const Person* owner_;
  const std::string CVV2_;
  std::string password_;
  std::string exp_date_; // TODO: set this 
  const std::string account_number_;

  double balance_ = 0.0;
  bool account_status_ = true;

  static std::unordered_set<std::string> used_account_numbers;
};
