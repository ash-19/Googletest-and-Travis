#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <vector>
#include <map>
#include "Students.h"

// TODO: stub test cases, then fill them

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

//  Tests addUser() with valid string name and
//  invalid ID (negative int). Tests if names and ids were indeed
//  added to the map with a call to nameExists() and idForName().
//
//  ID should not be -1. But is -1. Therefore, type of id used
//  is int and not unsigned int.
TEST(AddUser, NegativeID) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", -1);

        ASSERT_THROW(studentsDB->idForName("Squirtel"), std::out_of_range);
        delete studentsDB;
}

//  Tests addUser() by calling idForName() for a name that's
//  not in the DB.
//
//  Expected out_of_range
TEST(AddUser, NameNotInRecords) {
        Students* studentsDB = new Students();
        studentsDB->addUser("Pikachu", 1);

        EXPECT_TRUE (studentsDB->nameExists("Pikachu"));
        EXPECT_EQ (4294967295, studentsDB->idForName("Pikachu")) <<
                "-1 ID as an unsigned should be 4294967295. Type is signed int.";
        delete studentsDB;
}

//  Tests addUser() for duplicates names. Both names should
//  be in the map but with different ids.
TEST(AddUser, DuplicateName) {
        Students* studentsDB = new Students();

        //TODO: implement. MAP ONLY ALLOWS UNIQUE KEYS..

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

        //TODO: test in runtime what outputs and then decide the behavior
        EXPECT_EQ("", studentsDB->phoneForName("Pikachu"));
        EXPECT_EQ("801585-1726", studentsDB->phoneForName("Squirtel"));

        delete studentsDB;
}

//  Tests addPhoneNumber() for duplicate users. Should have different
//  ids and different phone numbers.
TEST(AddPhoneNumber, DuplicateUser) {
        Students* studentsDB = new Students();

        //TODO: implement

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

//  Tests addPhoneNumber() with invalid grade (incorrect format)
//  and valid id.
TEST(AddGrade, InvalidGrade) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests addGrades() for duplicate users. Should have different ids,
//  phones, grades.
TEST(AddGrade, DuplicateUsers) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests numberOfNames() added with valid parameters. Checks
//  the number of users in map with call to numberOfNames().
TEST(NumberOfNames, ValidParameters) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests numberOfNames() after adding some names and then removing
//  some names.
TEST(NumberOfNames, AddAndDelete) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests numberOfNames() after adding some names duplicate users.
//  Should count all duplicate users.
TEST(NumberOfNames, DuplicateUsers) {
        Students* studentsDB = new Students();

        //TODO: implement

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
        delete studentsDB;
}

//  Tests removeStudent() trying to remove a student from an
//  empty map.
TEST(RemoveStudent, ExceptionEmptyMap) {
        Students* studentsDB = new Students();
        EXPECT_EQ (0, studentsDB->numberOfNames());
        studentsDB->removeStudent("David");
        EXPECT_EQ (0, studentsDB->numberOfNames());

        delete studentsDB;
}

//  Tests removeStudent() trying to remove a student not in the
//  map. Should throw out_of_range exception
TEST(RemoveStudent, ExceptionNoName) {
        Students* studentsDB = new Students();
    
        ASSERT_THROW(studentsDB->removeStudent("David"), std::out_of_range);

        delete studentsDB;
}

//  Tests if the id was also removed after removing a student from
//  the map.
TEST(RemoveStudent, IdRemoved) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests if the phoneNumber was also removed after removing a student from
//  the map.
TEST(RemoveStudent, PhoneRemoved) {
        Students* studentsDB = new Students();
    
        //TODO: implement

        delete studentsDB;
}

//  Tests if the grade was also removed after removing a student from
//  the map.
TEST(RemoveStudent, GradeRemoved) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests numberOfNames() after deleting one of the duplicate users.
//  Check if both removed? If they were, that's bad!!!
TEST(RemoveStudent, DuplicateUsers) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests fullRecord() with valid parameters. Checks if the
//  ids, phones, grades were indeed added.
TEST(FullRecord, ValidParameters) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests fullRecord() with missing id, then missing grade,
//  then missing name, then with missing phone.
TEST(FullRecord, MissingParameters) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests fullRecord() with duplicate names. Check both the names
//  have correct and different ids, phones, grades assigned.
TEST(FullRecord, DuplicateNames) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests removing a student added using fullRecord().
TEST(FullRecord, RemoveStudent) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests some students by using AddName() (with other required ad***),
//  and some with fullRecord(). See if the list sizes, distinctiveness of
//  the students, etc holds.
TEST(FullRecord, DifferentWaysToAdd) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests removeList() with valid parameters.
TEST(RemoveList, ValidParameters) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests removeList() where users were added using FullRecord().
TEST(RemoveList, FullRecordAdds) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

//  Tests removeList() where users were added using FullRecord() and
//  AddUser().
TEST(RemoveList, MixedAdds) {
        Students* studentsDB = new Students();

        //TODO: implement

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
        EXPECT_EQ (false, studentsDB->nameExists("David"));
        ASSERT_THROW(studentsDB->idForName("David"), std::out_of_range);
        ASSERT_THROW(studentsDB->gradeForName("David"), std::out_of_range);
        ASSERT_THROW(studentsDB->phoneForName("David"), std::out_of_range);
    
        delete studentsDB;
}

//  Tests clearAll() when more than one Student objects are made.
TEST(ClearAll, MultipleObjects) {
        Students* studentsDB = new Students();
    
        std::vector<int> names = {"David", "Sam", "Frank"};
    
        studentsDB->addUser(names[0], 1);
        studentsDB->addGrade(1, 'C');
        studentsDB->addPhoneNumbers(1, "123-124-1234");
    
        studentsDB->addUser(names[1], 2);
        studentsDB->addGrade(2, 'B');
        studentsDB->addPhoneNumbers(2, "123-124-1234");
    
        studentsDB->addUser(names[2], 3);
        studentsDB->addGrade(3, 'A');
        studentsDB->addPhoneNumbers(3, "123-124-1234");
    
        EXPECT_EQ (1, studentsDB->numberOfNames());
        
        studentsDB->clearAll();
        
        EXPECT_EQ (0, studentsDB->numberOfNames());
    
        // Test each name
        for(std::vector<int>::size_type i = 0; i != names.size(); i++) {
            EXPECT_EQ (false, studentsDB->nameExists(names[i]));
            ASSERT_THROW(studentsDB->idForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->gradeForName(names[i]), std::out_of_range);
            ASSERT_THROW(studentsDB->phoneForName(names[i]), std::out_of_range);
        }

        delete studentsDB;
}

//  Tests clearAll() when one object is referencing to other Student
//  object. Both cleared?
TEST(ClearAll, ReferenceObjects) {
        Students* studentsDB = new Students();

        //TODO: implement

        delete studentsDB;
}

// Tests gradeForName() when the name is not in the records
// Should throw out_of_range exception
TEST(GradeForName, InvalidName) {
        Students* studentsDB = new Students();
        studentsDB->addUser("David", 1);
    
        ASSERT_THROW(studentsDB->gradeForName("Nick"), std::out_of_range);
    
        delete studentsDB;
}

// Tests gradeForName() when no grade is associated with the name
// Should throw out_of_range exception
TEST(GradeForName, InvalidGrade) {
    Students* studentsDB = new Students();
    studentsDB->addUser("David", 1);
    
    ASSERT_THROW(studentsDB->gradeForName("David"), std::out_of_range);
    
    delete studentsDB;
}
