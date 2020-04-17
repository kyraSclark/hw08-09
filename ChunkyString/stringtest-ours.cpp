/**
 * stringtest.cpp
 *
 * Purpose: Tests a ChunkyString for correctness.
 */

#include <signal.h>
#include <unistd.h>
#include <cstddef>
#include <cstdlib>

#include <cs70/testinglogger.hpp>

// These two lines are for homework 7. Comment out or delete
// for homeworks 8 & 9
#include <cs70/stringwrapper.hpp>
using TestingString = GenericString;

// These two lines are for homeworks 8 & 9. Comment out for homework 7.
// #include "chunkystring.hpp"
// using TestingString = ChunkyString;

/**
 * Assuming chunks are supposed to be at least an average of
 * 1/divisor full, checks for the lowest allowable utilization
 * for the input string
 *
 * The function does so by calculating the
 * lowest allowable utilization for a string the length of the
 * input string, including handling the edge cases of small strings.
 * Since checkUtilization is not a test on its own, but rather
 * a helper function to be used in other tests, it doesn't
 * create its own TestingLogger object. Instead, its affirms
 * will be associated with the TestingLogger of the calling
 * function.
 *
 */
void checkUtilization(const TestingString& test, size_t divisor) {
  double utilLimit = 0;

  if (test.size() > 0) {
    size_t chunks = 1;
    size_t size = test.size() - 1;
    divisor = TestingString::CHUNKSIZE / divisor;
    chunks += (size + divisor - 1) / divisor;
    utilLimit = static_cast<double>(size) /
                static_cast<double>(chunks * TestingString::CHUNKSIZE);
    affirm(test.utilization() >= utilLimit);
  }
}

// Testing functions start here -- you'll edit these for Homework 7!

/**
 * \brief tests ChunkyString constructor
 **/
bool constructorTest() {
  // Set up the TestingLogger object
  TestingLogger log("ChunkyString constructor");

  TestingString s;
  affirm(s.size() == 0);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

/**
 * \brief tests ChunkyString's begin() and end(),
 * as well as iterator incrementation, decrementation, and equality
 **/
bool beginEndIterEqualsTest() {
  TestingLogger log("begin, end, and iterator equality");

  TestingString s;

  TestingString::iterator iterBegin = s.end();
  TestingString::iterator iterEnd = s.begin();
  TestingString::iterator iter2 = s.begin();
  affirm(iterEnd == iterBegin);

  s.push_back('a');
  s.push_back('b');
  iterBegin = s.begin();
  iter2 = s.begin();
  iterEnd = s.end();
  affirm(iterBegin != iterEnd);

  ++iterBegin;
  affirm(iterBegin != iter2);

  --iterBegin;
  affirm(iterBegin == iter2);

  ++iterBegin;
  ++iter2;
  affirm(iterBegin == iter2);

  ++iterBegin;
  affirm(iterBegin != iter2);
  affirm(iterBegin == iterEnd);

  return log.summarize();
}

/**
 * \brief test the iterator's dereference
 */
bool iterDereferenceTest() {
  TestingLogger log("iterator's * and ->");

  TestingString s;
  s.push_back('a');
  s.push_back('b');

  TestingString::iterator iter = s.begin();
  affirm(*iter == 'a');
  ++iter;
  affirm(*iter == 'b');

  return log.summarize();
}

/**
 * \brief test push_back and size
 * \note tests string of length 13 so we use 2 chunks
 */
bool pushBackSizeTest() {
  TestingLogger log("push_back and size");

  TestingString s;
  affirm(s.size() == 0);
  s.push_back('a');
  affirm(s.size() == 1);
  s.push_back('b');
  affirm(s.size() == 2);
  s.push_back('c');
  affirm(s.size() == 3);
  s.push_back('d');
  affirm(s.size() == 4);
  s.push_back('e');
  affirm(s.size() == 5);
  s.push_back('f');
  affirm(s.size() == 6);
  s.push_back('g');
  affirm(s.size() == 7);
  s.push_back('h');
  affirm(s.size() == 8);
  s.push_back('i');
  affirm(s.size() == 9);
  s.push_back('j');
  affirm(s.size() == 10);
  s.push_back('k');
  affirm(s.size() == 11);
  s.push_back('l');
  affirm(s.size() == 12);
  s.push_back('z');
  affirm(s.size() == 13);

  TestingString::iterator iter = s.begin();
  affirm(*iter == 'a');
  ++iter;
  affirm(*iter == 'b');
  ++iter;
  affirm(*iter == 'c');
  ++iter;
  affirm(*iter == 'd');
  ++iter;
  affirm(*iter == 'e');
  ++iter;
  affirm(*iter == 'f');
  ++iter;
  affirm(*iter == 'g');
  ++iter;
  affirm(*iter == 'h');
  ++iter;
  affirm(*iter == 'i');
  ++iter;
  affirm(*iter == 'j');
  ++iter;
  affirm(*iter == 'k');
  ++iter;
  affirm(*iter == 'l');
  ++iter;
  affirm(*iter == 'z');

  return log.summarize();
}

/**
 * \brief tests ChunkyString equality
 */
bool equalityTest() {
  TestingLogger log("ChunkyString equality");

  TestingString s;
  TestingString t;
  affirm(s == t);

  s.push_back('a');
  affirm(s != t);

  t.push_back('a');
  affirm(s == t);

  s.push_back('b');
  affirm(s != t);

  t.push_back('c');
  affirm(s != t);

  TestingString u;
  u.push_back('a');
  u.push_back('b');
  u.push_back('d');
  u.push_back('e');
  u.push_back('f');
  u.push_back('g');
  u.push_back('h');
  u.push_back('i');
  u.push_back('j');
  u.push_back('k');
  u.push_back('l');
  u.push_back('z');

  s.push_back('d');
  s.push_back('e');
  s.push_back('f');
  s.push_back('g');
  s.push_back('h');
  s.push_back('i');
  s.push_back('j');
  s.push_back('k');
  s.push_back('l');
  s.push_back('z');

  affirm(u == s);

  return log.summarize();
}

/**
 * \brief tests insert()
 */
bool insertTest() {
  TestingLogger log("insert()");

  TestingString s;
  s.push_back('a');

  TestingString::iterator inserted = s.insert(s.begin(), 'b');
  affirm(s.size() == 2);
  TestingString::iterator iter = s.begin();
  affirm(*iter == 'b');
  affirm(iter == inserted);
  ++iter;
  affirm(*iter == 'a');

  inserted = s.insert(iter, 'c');
  affirm(s.size() == 3);
  iter = s.begin();
  affirm(*iter == 'b');
  ++iter;
  affirm(iter == inserted);
  affirm(*iter == 'c');
  ++iter;
  affirm(*iter == 'a');

  iter = s.insert(iter, 'd');
  iter = s.insert(iter, 'e');
  iter = s.insert(iter, 'f');
  iter = s.insert(iter, 'g');
  iter = s.insert(iter, 'h');
  iter = s.insert(iter, 'i');
  iter = s.insert(iter, 'j');
  iter = s.insert(iter, 'k');
  iter = s.insert(iter, 'l');
  iter = s.insert(iter, 'z');

  TestingString u;
  u.push_back('b');
  u.push_back('c');
  u.push_back('z');
  u.push_back('l');
  u.push_back('k');
  u.push_back('j');
  u.push_back('i');
  u.push_back('h');
  u.push_back('g');
  u.push_back('f');
  u.push_back('e');
  u.push_back('d');
  u.push_back('a');
  affirm(u == s);

  return log.summarize();
}

/**
 * \brief tests ChunkyString's operator<
 */
bool lessThan() {
  TestingLogger log("operator<");

  TestingString s;
  TestingString t;
  TestingString b;
  TestingString u;

  s.push_back('a');
  t.push_back('a');
  affirm(!(s < t));
  b.push_back('b');

  s.push_back('a');
  affirm(t < s);
  affirm(t < b);
  t.push_back('b');
  affirm(s < t);

  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');
  s.push_back('a');

  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('a');
  u.push_back('b');

  affirm(s < u);

  return log.summarize();
}

/**
 * \brief tests ChunkyString's += operator
 */
bool plusEqualsTest() {
  TestingLogger log("operator +=");

  TestingString s;
  TestingString t;
  s += s;
  affirm(s.size() == 0);
  s += t;
  affirm(s.size() == 0);
  s.push_back('a');
  t.push_back('b');

  TestingString expected;
  expected.push_back('a');
  expected.push_back('a');
  s += s;
  affirm(s == expected);
  s += t;
  expected.push_back('b');
  affirm(s == expected);

  return log.summarize();
}

//--------------------------------------------------
//           RUNNING THE TESTS
//--------------------------------------------------

// Called if the test runs too long.
static void timeout_handler(int) {
  write(STDERR_FILENO, "Timeout occurred!\n", 18);
  abort();
}

// Run tests
int main(int argc, char** argv) {
  // This line is for homework 7.
  // Comment it out for homework 8 and homework 9.
  GenericString::loadImplementation(argv[1]);

  // Initalize testing environment
  TestingLogger alltests{"All tests"};

  signal(SIGALRM, timeout_handler);  // Call this when the timer expires
  alarm(10);                         // set the timer at 10 seconds

  // Add calls to your tests here...
  affirm(constructorTest());
  affirm(beginEndIterEqualsTest());
  affirm(iterDereferenceTest());
  affirm(pushBackSizeTest());
  affirm(equalityTest());
  affirm(insertTest());
  affirm(lessThan());
  affirm(plusEqualsTest());

  if (alltests.summarize(true)) {
    return 0;  // Error code of 0 == Success!
  } else {
    return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
  }
}
