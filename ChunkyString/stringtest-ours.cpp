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
//#include <cs70/stringwrapper.hpp>
//using TestingString = GenericString;

// These two lines are for homeworks 8 & 9. Comment out for homework 7.
#include "chunkystring.hpp"
using TestingString = ChunkyString;

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

////////////////////////
/// Kyra's Tests
///////////////////////

/////////////////////////////////////
//// Iterator Member function Tests
////////////////////////////////////

// equalityTest() for Iterators
bool equalityTest2() {
  // Set up the TestingLogger object
  TestingLogger log("Equality and Inequality test");

  TestingString s;
  s.push_back('a');
  s.push_back('b');
  s.push_back('c');
  s.push_back('d');
  s.push_back('e');

  TestingString::iterator iterator1 = s.begin();

  for (TestingString::iterator it2 = s.begin(); it2 != s.end(); ++it2) {
    affirm(iterator1 == it2);
    affirm(!(iterator1 != it2));
    ++iterator1;
    affirm(!(iterator1 == it2));
    affirm(iterator1 != it2);
  }
  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// incrementDecrementTest() for Iterators
bool incrementDecrementTest() {
  // Set up the TestingLogger object
  TestingLogger log("preIncrement and preDecrement test");

  TestingString s;

  s.push_back('a');
  TestingString::iterator iterator1 = s.begin();
  ++iterator1;
  affirm(iterator1 == s.end());
  --iterator1;
  affirm(*iterator1 == 'a');
  affirm(iterator1 == s.begin());

  TestingString s2;
  s2.push_back('a');
  s2.push_back('b');
  TestingString::iterator iterator2 = s2.begin();
  ++iterator2;
  ++iterator2;
  --iterator2;
  affirm(*iterator2 == 'b');
  --iterator2;
  affirm(*iterator2 == 'a');

  TestingString::iterator iterator3 = s.end();
  --iterator3;
  affirm(iterator3 == s.begin());

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// dereferenceTest() for Iterators

bool dereferenceTest() {
  // Set up the TestingLogger object
  TestingLogger log("Iterator Dereference test");
  char letters[] = {'t', 'h', 'e', 'q', 'u', 'i', 'c', 'k', 'b', 'r', 'o'
  , 'w', 'n', 'f', 'o', 'x', 'j', 'u', 'm', 'p', 'e', 'd', 't', 'h'
  , 'e', 'l', 'a', 'z', 'y', 'd', 'o', 'g', '4', '2'};
  TestingString s;
  for (char x : letters) {
    s.push_back(x);
  }
  size_t i = 0;
  for (TestingString::iterator it = s.begin(); it != s.end(); ++it) {
    affirm(letters[i] == *it);
    // Affirming twice so that we make sure * is const
    affirm(letters[i] == *it);
    ++i;
  }
  TestingString::iterator iterator2 = s.begin();
  affirm(*iterator2 == 't');
  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// beginTest() for Iterators
bool beginTest() {
  // Set up the TestingLogger object
  TestingLogger log("Begin test");

  TestingString s;
  TestingString r;

  s.push_back('a');

  TestingString::iterator s_it1 = s.begin();
  TestingString::iterator s_it2 = s.begin();
  TestingString::iterator s_it3 = s.end();

  TestingString::iterator r_it1 = r.begin();
  TestingString::iterator r_it2 = r.begin();
  TestingString::iterator r_it3 = r.end();

  affirm(r_it1 == r_it2);
  // affirm(r_it1 == r_it3);
  affirm(s_it1 == s_it2);
  affirm(s_it1 != s_it3);

  s.push_back('b');

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// endTest() for Iterators
bool endTest() {
  // Set up the TestingLogger object
  TestingLogger log("End test");

  TestingString s;

  TestingString::iterator it1 = s.begin();
  TestingString::iterator it2 = s.end();

  affirm(it1 == it2);

  // If problems occur in testing, begin might be invalidated?

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}


/////////////////////////////////////////
//// ChunkyString Member function Tests
////////////////////////////////////////

// pushBackTest() for ChunkyString
bool pushBackTest() {
  // Set up the TestingLogger object
  TestingLogger log("push_back test");

  TestingString s;
  TestingString r;

  s.push_back('a');
  affirm(s.size() == 1);
  affirm(s != r);

  r.push_back('a');
  affirm(s == r);
  affirm(r.size() == 1);

  s.push_back('a');
  r.push_back('b');
  affirm(r.size() == 2);
  affirm(s.size() == 2);
  affirm(r != s);

  for (size_t i = 0; i < 50; ++i) {
    s.push_back('a');
  }
  affirm(s.size() == 52);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// constructorTest() for ChunkyString
bool constructorTest2() {
  // Set up the TestingLogger object
  TestingLogger log("constructor test");

  TestingString s;
  affirm(s.size() == 0);

  TestingString r;
  affirm(r == s);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// sizeTest() for ChunkyString
bool sizeTest() {
  // Set up the TestingLogger object
  TestingLogger log("Size test");

  TestingString s;

  size_t count = 0;
  affirm(s.size() == count);

  for (size_t i = 0; i < 100; ++i) {
    s.push_back('j');
    ++count;
    affirm(s.size() == count);
  }

  for (TestingString::iterator it2 = s.begin();
                it2 != s.end(); it2 = s.erase(it2)) {
    affirm(s.size() == count);
    --count;
  }


  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// operatorEqTest() for ChunkyString
bool operatorEqTest() {
  // Set up the TestingLogger object
  TestingLogger log("Operator= and operator!= test");

  TestingString s;
  TestingString r;

  // check that two default strings are the same
  // we include all of these to ensure symmetry
  affirm(r == s);
  affirm(!(r != s));
  affirm(s == r);
  affirm(!(s != r));

  s.push_back('a');
  s.push_back('l');
  s.push_back('p');
  s.push_back('h');
  s.push_back('a');

  r.push_back('b');
  r.push_back('e');
  r.push_back('t');
  r.push_back('a');

  // Affirm two strings of different size are different
  affirm(r != s);
  affirm(!(r == s));
  affirm(s != r);
  affirm(!(s == r));


  r.push_back('a');
  r.push_back('l');
  r.push_back('p');
  r.push_back('h');
  r.push_back('a');

  s.push_back('b');
  s.push_back('e');
  s.push_back('t');
  s.push_back('a');

  // Affirm two strings of the same size but rearranged
  //  letters are diferent
  affirm(r != s);
  affirm(!(r == s));
  affirm(s != r);
  affirm(!(s == r));

  TestingString t;
  t.push_back('a');
  t.push_back('l');
  t.push_back('p');
  t.push_back('h');
  t.push_back('a');

  t.push_back('b');
  t.push_back('e');
  t.push_back('t');
  t.push_back('a');

  // Affirm equality holds for equal strings
  affirm(t == s);
  affirm(!(t != s));
  affirm(s == t);
  affirm(!(s != t));

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// operatorLessTest() for ChunkyString
bool operatorLessTest() {
  // Set up the TestingLogger object
  TestingLogger log("operator< test");

  TestingString s;
  TestingString r;

  s.push_back('a');

  affirm(r < s);
  affirm(!(s < r));

  r.push_back('a');

  affirm(!(r < s));
  affirm(!(s < r));

  s.push_back('a');
  r.push_back('b');

  affirm(s < r);

  TestingString q;

  q.push_back('a');
  affirm(q < s);
  affirm(q < r);

  TestingString t;

  t.push_back('b');
  affirm(r < t);
  affirm(s < t);
  affirm(q < t);

  t.push_back('a');
  affirm(r < t);
  affirm(s < t);
  affirm(q < t);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// appendTest() for operator+= in ChunkyString
bool appendTest() {
  // Set up the TestingLogger object
  TestingLogger log("Operator+= test");

  TestingString s;
  TestingString r;

  r.push_back('a');
  r.push_back('l');
  r.push_back('p');
  r.push_back('h');
  r.push_back('a');

  s.push_back('b');
  s.push_back('e');
  s.push_back('t');
  s.push_back('a');

  TestingString s1;
  TestingString r1;

  r1.push_back('a');
  r1.push_back('l');
  r1.push_back('p');
  r1.push_back('h');
  r1.push_back('a');

  s1.push_back('b');
  s1.push_back('e');
  s1.push_back('t');
  s1.push_back('a');

  TestingString t;
  t.push_back('a');
  t.push_back('l');
  t.push_back('p');
  t.push_back('h');
  t.push_back('a');

  t.push_back('b');
  t.push_back('e');
  t.push_back('t');
  t.push_back('a');

  TestingString t1;
  t1.push_back('b');
  t1.push_back('e');
  t1.push_back('t');
  t1.push_back('a');

  t1.push_back('a');
  t1.push_back('l');
  t1.push_back('p');
  t1.push_back('h');
  t1.push_back('a');

  size_t sizeR = r.size();
  size_t sizeS = s.size();
  r += s;
  affirm(r == t);
  affirm(s == s1);
  affirm(r.size() == sizeR + sizeS);

  s += r1;
  affirm(s == t1);
  affirm(r.size() == (sizeR + sizeS));

  TestingString r2;

  r2.push_back('a');
  r2.push_back('l');
  r2.push_back('p');
  r2.push_back('h');
  r2.push_back('a');

  TestingString empty;
  r1 += empty;
  affirm(r2 == r1);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
  return log.summarize();
}

// insertTest() for ChunkyString
bool insertTest2() {
  // Set up the TestingLogger object
  TestingLogger log("insert test");

  TestingString s;
  TestingString r;

  s.push_back('a');
  s.push_back('b');

  r.push_back('a');
  r.push_back('c');
  r.push_back('b');

  TestingString::iterator it1 = s.begin();
  ++it1;

  TestingString::iterator it2 = s.insert(it1, 'c');

  affirm(*it2 == 'c');
  affirm(s.size() == 3);
  affirm(s == r);

  // Print a summary of the all the affirmations and return true
  // if they were all successful.
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
  // GenericString::loadImplementation(argv[1]);

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
  //affirm(insertTest());
  affirm(lessThan());
  affirm(plusEqualsTest());

  // Kyra's Tests
  affirm(equalityTest2());
  affirm(incrementDecrementTest());
  affirm(dereferenceTest());
  affirm(beginTest());
  affirm(endTest());
  affirm(pushBackTest());
  affirm(constructorTest2());
  //affirm(sizeTest());
  affirm(operatorEqTest());
  affirm(operatorLessTest());
  affirm(appendTest());
  //affirm(insertTest2());

  if (alltests.summarize(true)) {
    return 0;  // Error code of 0 == Success!
  } else {
    return 2;  // Arbitrarily chosen exit code of 2 means tests failed.
  }
}
