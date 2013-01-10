SUBDIRS = stdio LedDriver

check_PROGRAMS = test
test_SOURCES=test.cpp test_marubatsu.cpp.cpp ../src/marubatsu.cpp
test_CXXFLAGS = -I /home/e11062/SAGYOU/cpputest-master/include/ -I ../src/
test_LDFLAGS = -L /home/e11062/SAGYOU/cpputest-master/lib
test_LDADD = -lCppUTest

XFAIL_TESTS = 
AUTOMAKE_OPTIONS = color-tests

TESTS = test

