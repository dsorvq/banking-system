#include <gtest/gtest.h>
#include <regex>

#include "Account.hpp"
#include "Person.hpp"

class PersonTest : public ::testing::Test {
   protected:
	std::string valid_name = "John Doe";
	size_t valid_age = 30;
	std::string valid_gender = "Male";
	std::string valid_fingerprint = "Valid Fingerprint";
	size_t valid_socioeconomic_rank = 5;
	bool valid_is_alive = true;

	size_t hash_fingerprint(const std::string& fingerprint) {
		return std::hash<std::string>{}(fingerprint);
	}

	Person create_valid_person() {
		return Person(valid_name,
                  valid_age,
                  valid_gender,
                  valid_fingerprint,
                  valid_socioeconomic_rank,
                  valid_is_alive);
	}
};

TEST_F(PersonTest, Person_GetName) {
  Person person = create_valid_person();
  EXPECT_EQ(person.get_name(), valid_name) << "Failed at get_name(): Expected " << valid_name << ", got " << person.get_name();
}

TEST_F(PersonTest, Person_GetAge) {
  Person person = create_valid_person();
  EXPECT_EQ(person.get_age(), valid_age) << "Failed at get_age(): Expected " << valid_age << ", got " << person.get_age();
}

TEST_F(PersonTest, Person_GetGender) {
  Person person = create_valid_person();
  EXPECT_EQ(person.get_gender(), valid_gender) << "Failed at get_gender(): Expected " << valid_gender << ", got " << person.get_gender();
}

TEST_F(PersonTest, Person_GetHashedFingerprint) {
  Person person = create_valid_person();
	EXPECT_EQ(person.get_hashed_fingerprint(), hash_fingerprint(valid_fingerprint)) << "Failed at get_hashed_fingerprint(): Expected non-zero";
}

TEST_F(PersonTest, Person_GetSocioeconomicRank) {
  Person person = create_valid_person();
  EXPECT_EQ(person.get_socioeconomic_rank(), valid_socioeconomic_rank) 
    << "Failed at get_socioeconomic_rank(): Expected " 
    << valid_socioeconomic_rank << ", got " << person.get_socioeconomic_rank();
}

TEST_F(PersonTest, Person_GetIsAlive) {
  Person person = create_valid_person();
  EXPECT_EQ(person.get_is_alive(), valid_is_alive) 
    << "Failed at get_is_alive(): Expected " 
    << std::boolalpha << valid_is_alive << ", got " << std::boolalpha << person.get_is_alive();
}

TEST_F(PersonTest, Person_ConstructorGenderValidation) {
  std::string invalid_gender = "Other";
  EXPECT_ANY_THROW(
    { Person person(valid_name, valid_age, invalid_gender, valid_fingerprint, valid_socioeconomic_rank, valid_is_alive); }
    ) << "Constructor should throw std::invalid_argument for gender: " << invalid_gender;
}

TEST_F(PersonTest, Person_SocioeconomicRankValidation) {
  size_t invalid_rank_high = 11;
  size_t invalid_rank_low = 0;
  EXPECT_ANY_THROW(
    { Person person(valid_name, valid_age, valid_gender, valid_fingerprint, invalid_rank_high, valid_is_alive); }
    ) << "Constructor should throw std::exception for socioeconomic rank: " << invalid_rank_high;

  EXPECT_ANY_THROW(
    { Person person(valid_name, valid_age, valid_gender, valid_fingerprint, invalid_rank_low, valid_is_alive); }
    ) << "Constructor should throw std::exception for socioeconomic rank: " << invalid_rank_low;
}

TEST_F(PersonTest, Person_SetAge) {
  Person person = create_valid_person();
  size_t new_age = 35;

  EXPECT_TRUE(person.set_age(new_age)) << "Failed to set a valid age.";
  EXPECT_EQ(person.get_age(), new_age) << "get_age() did not return the expected new age after set_age().";
}

TEST_F(PersonTest, Person_SetSocioeconomicRank) {
  Person person = create_valid_person();
  size_t new_rank = 8;

  EXPECT_TRUE(person.set_socioeconomic_rank(new_rank)) << "Failed to set a valid socioeconomic rank.";
  EXPECT_EQ(person.get_socioeconomic_rank(), new_rank) << "get_socioeconomic_rank() did not return the expected new rank after set_socioeconomic_rank().";

  size_t invalid_rank = 15; 
  EXPECT_ANY_THROW(person.set_socioeconomic_rank(invalid_rank)) << "set_socioeconomic_rank() should return false for invalid rank value: " << invalid_rank;
}

TEST_F(PersonTest, Person_SetIsAlive) {
  Person person = create_valid_person();
  bool new_state = false;

  EXPECT_TRUE(person.set_is_alive(new_state)) << "Failed to set a new state for is_alive.";
  EXPECT_EQ(person.get_is_alive(), new_state) << "get_is_alive() did not return the expected new state after set_is_alive().";
}

TEST_F(PersonTest, Person_SpaceshipOperatorComparison) {
  std::string name1 = "Alice";
  size_t age1 = 30;
  std::string gender1 = "Female";
  std::string fingerprint1 = "fingerprint1";
  size_t socioeconomic_rank1 = 5;
  bool is_alive1 = true;

  std::string name2 = "Bob";
  size_t age2 = 25;
  std::string gender2 = "Male";
  std::string fingerprint2 = "fingerprint2";
  size_t socioeconomic_rank2 = 7;
  bool isAlive2 = false;

  Person person1(name1, age1, gender1, fingerprint1, socioeconomic_rank1, is_alive1);
  Person person2(name2, age2, gender2, fingerprint2, socioeconomic_rank2, isAlive2);

  EXPECT_TRUE((person1 <=> person2) == std::strong_ordering::less) << "person1 should be considered less than person2 based on hashed fingerprints.";
  EXPECT_TRUE((person2 <=> person1) == std::strong_ordering::greater) << "person2 should be considered greater than person1 based on hashed fingerprints.";
  EXPECT_TRUE((person1 <=> person1) == std::strong_ordering::equal) << "A person should be equal to themselves when comparing hashed fingerprints.";
}

TEST_F(PersonTest, Person_GetInfoFileOutput) {
  Person person = create_valid_person();
  std::string filename = "test_person_info.txt";
  person.get_info(filename);

  std::ifstream file(filename);
  EXPECT_TRUE(file.good()) << "File " << filename << " was not created.";

  std::string line;
  getline(file, line);
  EXPECT_FALSE(line.empty()) << "The file " << filename << " is empty, but expected to contain person information.";

  file.close();

  std::remove(filename.c_str());
}

/**************************************/
/* Account Tests */

class AccountTest : public ::testing::Test {
protected:
  std::string person_name = "John Doe";
  size_t person_age = 30;
  std::string person_gender = "Male";
  std::string person_fingerprint = "validFingerprint";
  size_t socioeconomic_rank = 5;
  bool is_alive = true;

  std::string bank_fingerprint = "bankFingerprint";

  std::string account_password = "password123";

  Person* person;

  void SetUp() override {
    person = new Person(person_name, person_age, person_gender, person_fingerprint, socioeconomic_rank, is_alive);
  }

  void TearDown() override {
    delete person;
  }

  Account create_valid_account() {
    return Account(person, account_password);
  }
};

TEST_F(AccountTest, Account_ConstructorAndOwnerGetter) {
  Account account = create_valid_account();

  EXPECT_EQ(account.get_owner(), person) << "Account owner does not match the expected person object.";
}

TEST_F(AccountTest, Account_GetBalanceInitialization) {
  Account account = create_valid_account();

  EXPECT_EQ(account.get_balance(), 0.0) << "Initial account balance is not correctly zero-initialized.";
}

TEST_F(AccountTest, Account_GetStatusInitialization) {
  Account account = create_valid_account();

  EXPECT_TRUE(account.get_status()) << "Initial account status is not true as expected for a clean starting state.";
}

TEST_F(AccountTest, Account_AccountNumberFormatAndUniqueness) {
  auto account = create_valid_account();

  auto account_number = account.get_account_number();
  EXPECT_EQ(account_number.length(), 16) << "Account number should be a 16-digit number.";
  EXPECT_TRUE(std::all_of(account_number.begin(), account_number.end(), ::isdigit)) << "Account number should only contain digits.";

  auto another_account = create_valid_account();
  auto another_account_number = another_account.get_account_number();
  EXPECT_NE(account_number, another_account_number) << "Account numbers for different accounts must be unique.";
}

TEST_F(AccountTest, Account_GetCVV2WithAuthentication) {
  Account account = create_valid_account();
  std::string correct_fingerprint = person_fingerprint;
  std::string incorrect_fingerprint = "invalidFingerprint";

  EXPECT_NO_THROW({
    std::string cvv2 = account.get_CVV2(correct_fingerprint);
    EXPECT_EQ(cvv2.length(), 4) << "CVV2 should be a 4-digit number.";
    EXPECT_TRUE(std::all_of(cvv2.begin(), cvv2.end(), ::isdigit)) << "CVV2 should only contain digits.";
  });

  EXPECT_ANY_THROW({
    account.get_CVV2(incorrect_fingerprint);
  }) << "Accessing CVV2 with an incorrect fingerprint should throw an error.";
}

TEST_F(AccountTest, Account_GetPasswordWithAuthentication) {
  Account account = create_valid_account();
  std::string correct_fingerprint = person_fingerprint;
  std::string expected_password = account_password;
  std::string incorrect_fingerprint = "invalidFingerprint";

  EXPECT_NO_THROW({
      auto password = account.get_password(correct_fingerprint);
      EXPECT_EQ(password, expected_password) << "Password does not match the expected value.";
  });

  EXPECT_ANY_THROW({
      account.get_password(incorrect_fingerprint);
  }) << "Accessing password with an incorrect fingerprint should throw an error.";
}

TEST_F(AccountTest, Account_GetExpDateWithAuthentication) {
  Account account = create_valid_account();
  std::string correct_fingerprint = person_fingerprint;
  std::string incorrect_fingerprint = "invalidFingerprint";

  std::regex exp_date_pattern(R"(\d{2}-\d{2})");

  EXPECT_NO_THROW({
    auto expDate = account.get_exp_date(correct_fingerprint);
    bool matches = std::regex_match(expDate, exp_date_pattern);
    EXPECT_TRUE(matches) << "Expiration date " << expDate << " does not match the expected format 'YY-MM'.";
  });

  EXPECT_ANY_THROW({
    account.get_exp_date(incorrect_fingerprint);
  }) << "Accessing expiration date with an incorrect fingerprint should throw an error.";
}
