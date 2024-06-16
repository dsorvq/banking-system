#pragma once

#include <compare>  
#include <optional>
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>

class Person {
public:
  Person(std::string &name,
         size_t age,
         std::string &gender,
         std::string &fingerprint,
         size_t socioeconomic_rank, 
         bool is_alive);

  auto get_name() const -> std::string;
  auto get_age() const -> size_t;
  auto get_gender() const -> std::string;
  auto get_hashed_fingerprint() const -> size_t;
  auto get_socioeconomic_rank() const -> size_t;
  auto get_is_alive() const -> bool;

  auto set_age(size_t age) -> bool;
  auto set_socioeconomic_rank(size_t rank) -> bool;
  auto set_is_alive(bool is_alive) -> bool;

  std::strong_ordering operator<=>(const Person &other) const;

  auto get_info(std::optional<std::string> file_name = std::nullopt) const -> void;
  auto print_info(std::ostream& os) const -> void;

private:
  const std::string name_;
  size_t age_;
  const std::string gender_;
  const size_t hashed_fingerprint_;
  size_t socioeconomic_rank_;
  bool is_alive_;
};
