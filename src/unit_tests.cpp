#include <gtest/gtest.h>

#include "Person.hpp"

class PersonTest : public ::testing::Test {
   protected:
	std::string valid_name = "John Doe";
	size_t valid_age = 30;
	std::string valid_gender = "Male";
	std::string valid_fingerprint = "Valid Fingerprint";
	size_t valid_socioeconomicRank = 5;
	bool valid_is_alive = true;

	size_t hash_fingerprint(const std::string& fingerprint) {
		return std::hash<std::string>{}(fingerprint);
	}

	Person createValidPerson() {
		return Person(valid_name,
                  valid_age,
                  valid_gender,
                  valid_fingerprint,
                  valid_socioeconomicRank,
                  valid_is_alive);
	}
};

TEST_F(PersonTest, Person_GetName) {
  Person person = createValidPerson();
  EXPECT_EQ(person.get_name(), valid_name) << "Failed at get_name(): Expected " << valid_name << ", got " << person.get_name();
}

TEST_F(PersonTest, Person_GetAge) {
  Person person = createValidPerson();
  EXPECT_EQ(person.get_age(), valid_age) << "Failed at get_age(): Expected " << valid_age << ", got " << person.get_age();
}

TEST_F(PersonTest, Person_GetGender) {
  Person person = createValidPerson();
  EXPECT_EQ(person.get_gender(), valid_gender) << "Failed at get_gender(): Expected " << valid_gender << ", got " << person.get_gender();
}
