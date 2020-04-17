/**
 * \file chunkystring.hpp
 *
 * \authors CS 70 given code
 *
 * \brief Declares the ChunkyString class.
 */

#ifndef CHUNKYSTRING_HPP_INCLUDED
#define CHUNKYSTRING_HPP_INCLUDED 1

#include <cstddef>
#include <string>

bool my_compare(char c1, char c2) {
  return std::char_traits<char>::lt(c1, c2);  
}

#include "chunkylist.hpp"

using ChunkyString = ChunkyList<char>;


#endif  //  CHUNKYSTRING_HPP_INCLUDED
