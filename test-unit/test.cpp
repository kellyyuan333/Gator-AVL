// #include "../src/main.cpp"
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
// #define private public

// using namespace std;
// /*
// 	To check output (At the Project1 directory):
// 		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
// */

// TEST_CASE("BST Insert", "[flag]")
// {
// 	AVLTree tree1;   // Create a Tree object 
// 	tree1.insert("A11y", "45679999");
// 	tree1.insert("Kelly", "123");
// 	tree1.insert("Bobby", "abc12345");
// 	tree1.insert("Dylan M", "34534");
// 	tree1.insert("123", "33334412");
// 	vector<string> actualOutput = tree1.printInorder();
// 	vector<string> expectedOutput = {};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// }

// TEST_CASE("Edge Cases", "[flag]")
// {
// 	AVLTree tree2;	
// 	ostringstream oss; //https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
// 	tree2.remove("12345678", oss);
// 	tree2.removeInorder(0, oss);
// 	tree2.searchName("Lia", oss);
// 	REQUIRE(oss.str() == "unsuccessful\nunsuccessful\nunsuccessful\n");
// }

// TEST_CASE("Rotation", "[flag]")
// {
// 	AVLTree tree3; //right rotation
// 	tree3.insert("a", "99999999");
// 	tree3.insert("b", "55555555");
// 	tree3.insert("c", "11111111");
// 	vector<string> actualOutput = tree3.printPostorder();
// 	vector<string> expectedOutput = {"c", "a", "b"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree4; //left rotation
// 	tree4.insert("a", "11111111");
// 	tree4.insert("b", "55555555");
// 	tree4.insert("c", "99999999");
// 	actualOutput = tree4.printPostorder();
// 	expectedOutput = {"a", "c", "b"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree5; //right-left rotation
// 	tree5.insert("a", "11111111");
// 	tree5.insert("b", "55555555");
// 	tree5.insert("c", "33333333");
// 	actualOutput = tree5.printPostorder();
// 	expectedOutput = {"a", "b", "c"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree6; //left-right rotation
// 	tree6.insert("a", "99999999");
// 	tree6.insert("b", "55555555");
// 	tree6.insert("c", "77777777");
// 	actualOutput = tree6.printPostorder();
// 	expectedOutput = {"b", "a", "c"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// }

// TEST_CASE("Deletion", "[flag]")
// {
// 	AVLTree tree7; //no children
// 	tree7.insert("Bob", "12345678");
// 	tree7.remove("12345678");
// 	vector<string> actualOutput = tree7.printPostorder();
// 	vector<string> expectedOutput = {};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree8; //one child
// 	tree8.insert("Bob", "12345678");
// 	tree8.insert("biggerBob", "23456789");
// 	tree8.remove("12345678");
// 	actualOutput = tree8.printPostorder();
// 	expectedOutput = {"biggerBob"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// 	AVLTree tree9; //two children
// 	tree9.insert("Bob", "12345678");
// 	tree9.insert("biggerBob", "23456789");
// 	tree9.insert("smallerBob", "01234567");
// 	tree9.remove("12345678");
// 	actualOutput = tree9.printPostorder();
// 	expectedOutput = {"smallerBob", "biggerBob"};
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	REQUIRE(actualOutput == expectedOutput);
// }

// TEST_CASE("Insert Large", "[flag]")
// {
//     AVLTree tree10;
//     vector<string> expectedOutput, actualOutput;
//     for(int i = 0; i < 100; i++)
//     {
//         int randomInput = 10000000 + (rand() % 99999999);
//         if (count(expectedOutput.begin(), expectedOutput.end(), to_string(randomInput)) == 0)
//         {
//             expectedOutput.push_back(to_string(randomInput));
//             tree10.insert("hi", to_string(randomInput));
//         }
//     }
//     actualOutput = tree10.printIdsInorder();
//     REQUIRE(expectedOutput.size() == actualOutput.size());
//     sort(expectedOutput.begin(), expectedOutput.end());
//     REQUIRE(expectedOutput == actualOutput);
// 	for(int j = 0; j < 10; j++)
// 	{
// 		int randomIndex = rand() % (99 - j);
// 		tree10.removeInorder(randomIndex);
// 		expectedOutput.erase(expectedOutput.begin() + randomIndex);
// 	}
// 	actualOutput = tree10.printIdsInorder();
// 	REQUIRE(expectedOutput.size() == actualOutput.size());
// 	sort(expectedOutput.begin(), expectedOutput.end());
//     REQUIRE(expectedOutput == actualOutput);
// }