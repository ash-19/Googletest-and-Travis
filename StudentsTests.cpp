#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <map>
#include "Students.h"

// TODO: stub test cases, then fill them

//  Include call to addUser() in the interface
//  with valid string name and valid unsigned int ID.
//  Tests if names were indeed added to the map with a
//  call to nameExists().
TEST(AddUser, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 2);
        studentsDB->addUser("Charmander", 3);
        EXPECT_TRUE (studentsDB->nameExists("Pikachu"));
        EXPECT_TRUE (studentsDB->nameExists("Balbasaur"));
        EXPECT_TRUE (studentsDB->nameExists("Charmander"));
        EXPECT_FALSE(studentsDB->nameExists("Squirtel"));
}
