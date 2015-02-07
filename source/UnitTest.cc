

//#include "../googleTest/fused-src/gtest/gtest.h"
#include "gtest/gtest.h"
#include "DBFile.h"


/*
*This method is used for writing test cases for creating DBFile.
*/
TEST(CreateTest, TestCases){

DBFile f;
//checks for a null file path.
EXPECT_EQ(0, f.Create(NULL, heap, NULL));
//checks for a correct file type.c
EXPECT_EQ(0, f.Create("./bin/nation.bin", sorted, NULL));
//checks for a correct file path passed.
cout << "Please make sure you have loaded the nation table for this test case to pass."<<endl;
EXPECT_EQ(1, f.Create("./bin/nation.bin", heap, NULL));
EXPECT_EQ(0, f.Create("./bin/nation.incorrect", heap, NULL));


}

