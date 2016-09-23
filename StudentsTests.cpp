// CS 3505, A4 - Testing and Travis
// Snehashish Mishra and Nick Porter
// Provides tests for the Students class

#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <map>
#include "Students.h"

//  Tests addUser() with valid string name and valid
//  unsigned int ID. Tests if names and ids were indeed
//  added to the map with a call to nameExists() and idForName().
//
//  All tests should pass.
TEST(AddUser, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 2);
        studentsDB->addUser("Charmander", 3);
        EXPECT_TRUE (studentsDB->nameExists("Pikachu"));
        EXPECT_TRUE (studentsDB->nameExists("Balbasaur"));
        EXPECT_TRUE (studentsDB->nameExists("Charmander"));

        EXPECT_EQ (1, studentsDB->idForName("Pikachu"));
        EXPECT_EQ (2, studentsDB->idForName("Balbasaur"));
        EXPECT_EQ (3, studentsDB->idForName("Charmander"));

        EXPECT_FALSE(studentsDB->nameExists("Squirtel"));
        delete studentsDB;
}

//  Tests addUser() by calling idForName() for a name that's
//  not in the DB.
//
//  Expected out_of_range
TEST(AddUser, NameNotInRecords) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);

        ASSERT_THROW(studentsDB->idForName("Squirtel"), std::out_of_range);
        delete studentsDB;
}

//  Tests addUser() with valid string name and
//  invalid ID (negative int). Tests if names and ids were indeed
//  added to the map with a call to nameExists() and idForName().
//
//  ID should not be -1. But is -1. Therefore, type of id used
//  is int and not unsigned int.
TEST(AddUser, NegativeID) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);

        EXPECT_TRUE (studentsDB->nameExists("Pikachu"));
        EXPECT_EQ (4294967295, studentsDB->idForName("Pikachu")) <<
                "-1 ID as an unsigned should be 4294967295. Type is signed int.";
        delete studentsDB;
}

//  The DB design should allow for duplicate names (since people have 
//  same names in real world), when id's are different.
TEST(AddUser, DuplicateNames) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Pikachu", 2);
        
        if(studentsDB->numberOfNames() == 1) {
                FAIL();
        }

        delete studentsDB;
}

//  Tests addPhoneNumber() with valid id number and valid
//  phone no. Tests if phone nos. were indeed
//  added to the map with a call to phoneForName().
//
//  All tests should pass.
TEST(AddPhoneNumber, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Squirtel", 2);
        studentsDB->addPhoneNumbers(1, "000-000-0000");
        studentsDB->addPhoneNumbers(2, "000-000-0001");
        
        EXPECT_EQ ("000-000-0000", studentsDB->phoneForName("Pikachu"));
        EXPECT_EQ ("000-000-0001", studentsDB->phoneForName("Squirtel"));

        delete studentsDB;
}

//  Tests addPhoneNumber() by calling phoneForName on a student 
//  without phone number.
//  Expected out_of_range exception.
TEST(AddPhoneNumber, NoPhoneForName) {
        Students* studentsDB = new Students();
        studentsDB->addUser("David", 1);
        studentsDB->addPhoneNumbers(2, "000-000-0000");

        ASSERT_THROW(studentsDB->phoneForName("David"), std::out_of_range);
        
        delete studentsDB;
}

//  Tests addPhoneNumber() by calling phoneForName on a student 
//  not in the DB.
//  Expected out_of_range exception.
TEST(AddPhoneNumber, NoNameInDB) {
        Students* studentsDB = new Students();
        studentsDB->addUser("David", 1);
        studentsDB->addPhoneNumbers(2, "000-000-0000");
        
        ASSERT_THROW(studentsDB->phoneForName("Pikachu"), std::out_of_range);
        
        delete studentsDB;
}

//  Tests addPhoneNumber() with invalid phone number (empty string)
//  and valid id.
TEST(AddPhoneNumber, InvalidPhoneNumber) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Squirtel", 2);

        // empty phone number, invalid format
        studentsDB->addPhoneNumbers(1, "");
        studentsDB->addPhoneNumbers(2, "801585-1726");

        // Should adhere to the phone number format ###-###-####
        if(studentsDB->phoneForName("Pikachu") == "" ) {
                FAIL() << "Incorrect Phone number format - Empty string";
        }
        if(studentsDB->phoneForName("Squirtel") == "801585-1726") {
                FAIL() << "Incorrect phone number format - ######-####";
        }

        delete studentsDB;
}

//  Tests addPhoneNumber() for students with same id.
TEST(AddPhoneNumber, NamesWithSameID) {
        Students* studentsDB = new Students();

        studentsDB->addUser("David", 1);
        studentsDB->addUser("Pikachu", 1);

        studentsDB->addPhoneNumbers(1, "100-100-1000");
        studentsDB->addPhoneNumbers(1, "100-100-1002");
        EXPECT_EQ("100-100-1002", studentsDB->phoneForName("Pikachu"));

        if(studentsDB->phoneForName("David") == "100-100-1002") {
                FAIL() << "Replaced the phone number of different user";
        }

        delete studentsDB;
}

//  Tests addGrade() with valid id number and valid
//  grade. Tests if grades were indeed
//  added to the map with a call to gradeForName().
//
//  All tests should pass.
TEST(AddGrade, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("David", 1);
        studentsDB->addGrade(1, 'C');
        EXPECT_EQ ('C', studentsDB->gradeForName("David"));

        delete studentsDB;
}

//  Tests addGrade() for a user not in DB.
TEST(AddGrade, NoNameInDB) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(2, 'A');
        
        ASSERT_THROW(studentsDB->gradeForName("Squirtel"), std::out_of_range);

        delete studentsDB;
}

//  Tests addGrade() for a user without a grade
TEST(AddGrade, NoGradeForName) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        
        ASSERT_THROW(studentsDB->gradeForName("Pikachu"), std::out_of_range);

        delete studentsDB;
}

//  Tests addGrades() for users with same id.
TEST(AddGrade, NamesWithSameID) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 1);
        
        studentsDB->addGrade(1, 'A');
        EXPECT_EQ('A', studentsDB->gradeForName("Pikachu"));
        if(studentsDB->gradeForName("Balbasaur") == 'A') {
                FAIL();
        }
        
        delete studentsDB;
}

//  Tests numberOfNames() added with valid parameters. Checks
//  the number of users in map with call to numberOfNames().
TEST(NumberOfNames, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 2);
        studentsDB->addUser("Squirtel", 3);
        studentsDB->addUser("Charmander", 4);

        size_t s = 4;
        EXPECT_EQ(s, studentsDB->numberOfNames());

        delete studentsDB;
}

//  Tests numberOfNames() after adding some names and then removing
//  some names.
TEST(NumberOfNames, AddAndDelete) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 2);
        studentsDB->addUser("Squirtel", 3);
        studentsDB->addUser("Charmander", 4);
        size_t s = 4;
        EXPECT_EQ(s, studentsDB->numberOfNames());
        
        studentsDB->removeStudent("Pikachu");
        s = 3;
        EXPECT_EQ(s, studentsDB->numberOfNames());

        studentsDB->removeStudent("Squirtel");
        studentsDB->removeStudent("Charmander");
        s = 1;
        EXPECT_EQ(s, studentsDB->numberOfNames());

        delete studentsDB;
}

//  Tests numberOfNames() after adding some names duplicate users.
//  Should not count all duplicate users due to names being keys
TEST(NumberOfNames, DuplicateUsers) {
        Students* studentsDB = new Students();

        studentsDB->addUser("David", 1);
        studentsDB->addUser("David", 2);
        studentsDB->addUser("David", 3);
        if( studentsDB->numberOfNames() == 1) {
                FAIL() << "Threr are 3 distinct students with different id's. But only 1 in DB.";
        }

        delete studentsDB;
}


//  Tests removeStudent() added with valid parameters. Checks
//  the number of users in map with call to numberOfNames().
TEST(RemoveStudent, ValidParameters) {
        Students* studentsDB = new Students();
        studentsDB->addUser("David", 1);
        EXPECT_EQ (1, studentsDB->numberOfNames());
        studentsDB->removeStudent("David");
        EXPECT_EQ (0, studentsDB->numberOfNames());

        EXPECT_FALSE(studentsDB->nameExists("David"));
        delete studentsDB;
}

//  Tests removeStudent() trying to remove a name from an
//  empty map.
TEST(RemoveStudent, ExceptionEmptyMap) {
        Students* studentsDB = new Students();
        EXPECT_EQ (0, studentsDB->numberOfNames());
        ASSERT_THROW(studentsDB->removeStudent(""), std::out_of_range);

        delete studentsDB;
}

//  Tests removeStudent() trying to remove a student not in the
//  map. Should throw out_of_range exception
TEST(RemoveStudent, ExceptionNoName) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Nick", 1);
        ASSERT_THROW(studentsDB->removeStudent("David"), std::out_of_range);

        delete studentsDB;
}

//  Tests if all the info was also removed after removing a student from
//  the map.
TEST(RemoveStudent, PhoneRemovedOrNot) {
        Students* studentsDB = new Students();
    
        // Add name with id 1, its phone and then remove it
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addPhoneNumbers(1, "000-000-0000");
        studentsDB->removeStudent("Pikachu");
        EXPECT_FALSE(studentsDB->nameExists("Pikachu"));

        // Try to get info for the just removed student
        ASSERT_THROW(studentsDB->phoneForName("Pikachu"), std::out_of_range);

        delete studentsDB;
}

//  Tests if the grade was also removed after removing a student from
//  the map.
TEST(RemoveStudent, GradeRemovedOrNot) {
        Students* studentsDB = new Students();
        
        // Add name with id 1, its grade and then remove it
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(1, 'A');
        studentsDB->removeStudent("Pikachu");
        EXPECT_FALSE(studentsDB->nameExists("Pikachu"));

        ASSERT_THROW(studentsDB->gradeForName("Pikachu"), std::out_of_range);

        delete studentsDB;
}

//  Tests if the id was also removed after removing a student from
//  the map.
TEST(RemoveStudent, IDRemovedOrNot) {
        Students* studentsDB = new Students();
        
        // Add name with id 1, its grade and then remove it
        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(1, 'A');
        studentsDB->removeStudent("Pikachu");
        EXPECT_FALSE(studentsDB->nameExists("Pikachu"));

        ASSERT_THROW(studentsDB->idForName("Pikachu"), std::out_of_range);

        delete studentsDB;
}

//  Tests fullRecord() for a name not in DB.
TEST(FullRecord, NameNotInDB) {
        Students* studentsDB = new Students();
        unsigned int id;
        char grade;
        std::string phone;

        EXPECT_FALSE( studentsDB->fullRecord("Pikachu", id, phone, grade));

        delete studentsDB;
}

//  Tests fullRecord() for a name in DB.
TEST(FullRecord, NameInDB) {
        Students* studentsDB = new Students();
        unsigned int id;
        char grade;
        std::string phone;

        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(1, 'A');
        studentsDB->addPhoneNumbers(1, "000-000-0000");

        EXPECT_TRUE( studentsDB->fullRecord("Pikachu", id, phone, grade));

        delete studentsDB;
}

//  Tests fullRecord() with valid parameters. Checks if the
//  ids, phones, grades were indeed assigned to ref parameters 
//  correctly.
TEST(FullRecord, OneStudentDetails) {
        Students* studentsDB = new Students();
        unsigned int id;
        char grade;
        std::string phone;

        EXPECT_FALSE( studentsDB->fullRecord("Pikachu", id, phone, grade));

        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(1, 'A');
        studentsDB->addPhoneNumbers(1, "000-000-0000");
         
        EXPECT_TRUE( studentsDB->fullRecord("Pikachu", id, phone, grade));

        EXPECT_EQ(1, id) << "Assigning the grade to id";
        EXPECT_EQ('A', grade) << "Assigning some random char to grade";
        EXPECT_EQ("000-000-0000", phone);
        
        delete studentsDB;
}

//  Tests fullRecord() with valid parameters for 2 students. 
//  Checks if the ids, phones, grades were indeed assigned to 
//  ref parameters correctly.
TEST(FullRecord, TwoStudentsDetails) {
        Students* studentsDB = new Students();
        unsigned int id;
        char grade;
        std::string phone;

        studentsDB->addUser("Pikachu", 1);
        studentsDB->addUser("Balbasaur", 2);

        EXPECT_FALSE( studentsDB->fullRecord("Pikachu", id, phone, grade));
        EXPECT_FALSE( studentsDB->fullRecord("Balbasaur", id, phone, grade));

        studentsDB->addUser("Pikachu", 1);
        studentsDB->addGrade(1, 'A');
        studentsDB->addPhoneNumbers(1, "000-000-0000");

        studentsDB->addUser("Balbasaur", 2);
        studentsDB->addGrade(2, 'B');
        studentsDB->addPhoneNumbers(2, "000-000-0001");
         
        EXPECT_TRUE( studentsDB->fullRecord("Pikachu", id, phone, grade));

        EXPECT_EQ(1, id) << "Assigning the grade to id" ;
        EXPECT_EQ('A', grade) << "Assigning some random char to grade";
        EXPECT_EQ("000-000-0000", phone);

        EXPECT_TRUE( studentsDB->fullRecord("Balbasaur", id, phone, grade));

        EXPECT_EQ(2, id) << "Assigning the grade to id" ;
        EXPECT_EQ('B', grade) << "Assigning some random char to grade";
        EXPECT_EQ("000-000-0001", phone);
        
        delete studentsDB;
}

//  Tests removeList() where all names passed are in DB
TEST(RemoveList, AllNamesInDB) {
        Students* studentsDB = new Students();
        std::vector<std::string> names = {"David", "Sam", "Frank"};
    
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            studentsDB->addUser(names[i], i + 1);
            studentsDB->addGrade(i + 1, 'C');
            studentsDB->addPhoneNumbers(i + 1, "333-333-3333");
        }
        EXPECT_EQ(3, studentsDB->numberOfNames());
        studentsDB->removeList(names);
        EXPECT_EQ(0, studentsDB->numberOfNames());
    
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            EXPECT_FALSE(studentsDB->nameExists(names[i]));
            ASSERT_THROW(studentsDB->idForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->phoneForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->gradeForName(names[i]), std::out_of_range);
        }
    
        delete studentsDB;
}

//  Tests removeList() where some names passed are not in DB
TEST(RemoveList, SomeNamesNotInDB) {
        Students* studentsDB = new Students();

        std::vector<std::string> names = {"David", "Sam", "Frank"};
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            studentsDB->addUser(names[i], i + 1);
            studentsDB->addGrade(i + 1, 'C');
            studentsDB->addPhoneNumbers(i + 1, "333-333-3333");
        }
    
        names = {"David", "Sam", "Frank", "Luke"}; // Luke not in the DB
        EXPECT_EQ(3, studentsDB->removeList(names));
    
        delete studentsDB;
}

//  Tests removeList() where a name was already deleted before calling removeList
TEST(RemoveList, DeletedName) {
        Students* studentsDB = new Students();
    
        std::vector<std::string> names = {"David", "Sam", "Frank"};
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            studentsDB->addUser(names[i], i + 1);
            studentsDB->addGrade(i + 1, 'C');
            studentsDB->addPhoneNumbers(i + 1, "333-333-3333");
        }
        studentsDB->removeStudent("Sam");
        names = {"Sam"};
        EXPECT_EQ(0, studentsDB->removeList(names));
    
        delete studentsDB;
}

//  Tests clearAll() on one Student object
TEST(ClearAll, OneObject) {
        Students* studentsDB = new Students();

        studentsDB->addUser("David", 1);
        studentsDB->addGrade(1, 'C');
        studentsDB->addPhoneNumbers(1, "123-124-1234");
        EXPECT_EQ (1, studentsDB->numberOfNames());
    
        studentsDB->clearAll();
    
        EXPECT_EQ (0, studentsDB->numberOfNames());
        EXPECT_FALSE (studentsDB->nameExists("David"));
        
        if(studentsDB->idForName("David") == 1) {
                FAIL();
        }
        if( studentsDB->gradeForName("David") == 'C') {
                FAIL();
        }
        if(studentsDB->phoneForName("David") == "123-124-1234") {
                FAIL();
        }
    
        delete studentsDB;
}

//  Tests clearAll() when more than one Student objects are made.
TEST(ClearAll, MultipleObjects) {
        Students* studentsDB = new Students();
    
        std::vector<std::string> names = {"David", "Sam", "Frank"};
    
        studentsDB->addUser(names[0], 1);
        studentsDB->addGrade(1, 'C');
        studentsDB->addPhoneNumbers(1, "123-124-1234");
    
        studentsDB->addUser(names[1], 2);
        studentsDB->addGrade(2, 'B');
        studentsDB->addPhoneNumbers(2, "123-124-1234");
    
        studentsDB->addUser(names[2], 3);
        studentsDB->addGrade(3, 'A');
        studentsDB->addPhoneNumbers(3, "123-124-1234");
    
        EXPECT_EQ (3, studentsDB->numberOfNames());
        
        studentsDB->clearAll();
        
        EXPECT_EQ (0, studentsDB->numberOfNames());
    
        // Test each name
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            EXPECT_FALSE (studentsDB->nameExists(names[i]));
        }

        if( studentsDB->idForName("David") == 1) {
                FAIL();
        }
        if( studentsDB->gradeForName("Sam") == 'B') {
                FAIL();
        }
        if( studentsDB->phoneForName("Frank") == "123-124-1234") {
                FAIL();
        }

        delete studentsDB;
}

//  Tests clearAll() when one object is referencing to other Student
//  object. Both cleared?
TEST(ClearAll, ReferenceObjects) {
        Students* studentsDB = new Students();
        Students* studentsDB1 = studentsDB;

        std::vector<std::string> names = {"David", "Sam", "Frank"};
    
        studentsDB->addUser(names[0], 1);
        studentsDB->addGrade(1, 'C');
        studentsDB->addPhoneNumbers(1, "123-124-1234");
    
        studentsDB->addUser(names[1], 2);
        studentsDB->addGrade(2, 'B');
        studentsDB->addPhoneNumbers(2, "123-124-1234");
    
        studentsDB->addUser(names[2], 3);
        studentsDB->addGrade(3, 'A');
        studentsDB->addPhoneNumbers(3, "123-124-1234");
    
        EXPECT_EQ (3, studentsDB->numberOfNames());
        EXPECT_EQ (3, studentsDB1->numberOfNames());
        studentsDB->clearAll();
        
        EXPECT_EQ (0, studentsDB->numberOfNames());
        EXPECT_EQ (0, studentsDB1->numberOfNames());
        // Test each name
        for(std::vector<std::string>::size_type i = 0; i != names.size(); i++) {
            EXPECT_FALSE (studentsDB->nameExists(names[i]));
            ASSERT_THROW(studentsDB->idForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->gradeForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->phoneForName(names[i]), std::out_of_range);

            EXPECT_FALSE (studentsDB1->nameExists(names[i]));
            ASSERT_THROW(studentsDB1->idForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB1->gradeForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB1->phoneForName(names[i]), std::out_of_range);
        }

        delete studentsDB;
}