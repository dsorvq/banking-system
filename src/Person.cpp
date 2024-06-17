#include "Person.hpp"

Person::Person(std::string &name,
               size_t age,
               std::string &gender,
               std::string &fingerprint,
               size_t socioeconomic_rank, 
               bool is_alive) 
  : name_{name}
  , age_{age}
  , gender_{gender}
  , hashed_fingerprint_ {hash_fingerprint(fingerprint)}
  , socioeconomic_rank_{socioeconomic_rank}
  , is_alive_{is_alive}
{
  if (!(gender_ == "Female" or gender_ == "Male")) {
    throw std::invalid_argument("gender must be Female or Male");
  }
  if (!(1 <= socioeconomic_rank_ and socioeconomic_rank <= 10)) {
    throw std::invalid_argument("socioeconomic rank must be between 1 and 10");
  }
}
 
auto Person::get_name() const -> std::string {
  return name_;
}

auto Person::get_age() const -> size_t {
  return age_;
}

auto Person::get_gender() const -> std::string {
  return gender_;
}

auto Person::get_hashed_fingerprint() const -> size_t {
  return hashed_fingerprint_; 
}

auto Person::get_socioeconomic_rank() const -> size_t {
  return socioeconomic_rank_;
}

auto Person::get_is_alive() const -> bool {
  return is_alive_;
}


auto Person::set_age(size_t age) -> bool {
  age_ = age;
  return true;
}

auto Person::set_socioeconomic_rank(size_t rank) -> bool {
  if (1 <= rank and rank <= 10) {
    socioeconomic_rank_ = rank;
    return true;
  }

  throw std::invalid_argument("socioeconomic rank must be between 1 and 10");
}

auto Person::set_is_alive(bool is_alive) -> bool {
  is_alive_ = is_alive;
  return true;
}

auto Person::operator<=>(const Person &other) const -> std::strong_ordering {
  return hashed_fingerprint_ <=> other.hashed_fingerprint_;
}

auto Person::get_info(std::optional<std::string> file_name) const -> void {
  if (file_name) {
    std::ofstream file(*file_name);
    if (file.is_open()) {
      print_info(file);
      file.close();
    } else {
      std::cerr << "Failed to open file: " << *file_name << std::endl;
    }
  } else {
    print_info(std::cout);
  }
}

auto Person::print_info(std::ostream& os) const -> void {
  os
    << name_ << "\n"
    << age_ << "\n"
    << gender_ << "\n"
    << hashed_fingerprint_ << "\n"
    << socioeconomic_rank_ << "\n"
    << is_alive_ << "\n";
}
