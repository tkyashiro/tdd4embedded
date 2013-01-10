#include "CppUTest/CommandLineTestRunner.h"

#include <stdio.h>
#include <string.h>

TEST_GROUP(sprintf){
	char output[100];
	const char *expected;

	void setup(){
		memset( output, 0xaa, sizeof(output) );
		expected = "";
	}

	void expect( const char* s ){
		expected = s;
	}

	void given( int charsWritten ){
		LONGS_EQUAL( strlen( expected ), charsWritten );
		STRCMP_EQUAL(expected, output);
		BYTES_EQUAL( 0xaa, output[strlen(expected)+1] );
	}
};

//TEST(sprintf, NoFormatOperations)
//{
//	char output[5] = "";
//
//	LONGS_EQUAL(3, sprintf(output, "hey"));
//	STRCMP_EQUAL("hey", output );
//}

TEST(sprintf, NoFormatOperations)
{
	expect("hey");
	given(sprintf(output, "hey"));
}

TEST(sprintf, InsertString)
{
	expect("Hello World\n");
	given(sprintf(output, "Hello %s\n", "World"));
}

int main( int argc, char **argv )
{
	return RUN_ALL_TESTS(argc, argv);
}

