/**
 * \file chunkylist.hpp
 *
 * \authors CS 70 given code, with additions by ... your aliases here ...
 *
 * \brief Declares the ChunkyList class.
 */

#ifndef CHUNKYLIST_HPP_INCLUDED
#define CHUNKYLIST_HPP_INCLUDED 1

#include <cstddef>
#include <list>
#include <iostream>
#include <string>

/**
 * ChunkyList class
 * Efficiently represents lists where insert and erase are
 * constant-time operations.
 *
 * This class is comparable to a linked-list of ELEMENTs,
 * but more space efficient.
 *
 * reverse_iterator and const_reverse_iterator aren't
 * supported. Other than that, we use the STL container type declarations
 * such that STL functions are compatible with ChunkyString.
 */
template <typename ELEMENT>
class ChunkyList {
 private:
    // Forward declaration of Iterator
    template <bool is_const>
    class Iterator;

    template <bool is_const>
    friend class Iterator;
    
 public:
    static const int CHUNKSIZE = 12;

    // Standard STL container type definitions
    using value_type      = ELEMENT;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using iterator        = Iterator<false>;
    using const_iterator  = Iterator<true>;
    // reverse_iterator and const_reverse_iterator aren't supported

    /**
     * Default constructor
     * Note: constant time
     */
    ChunkyList();
    ~ChunkyList() = default;
    ChunkyList(const ChunkyList& other) = default;
    ChunkyList& operator=(const ChunkyList& other) = default;

    /**
    * \brief Returns an iterator to the first character in the ChunkyString.
    * \return a iterator to the first char in the ChunkyString
    */
    iterator begin();

   /**
    * \brief Returns an iterator to one past the last chunk in the ChunkyString.
    * \return a iterator to "one past the end"
    */
    iterator end();

    /**
    * \brief Returns an iterator to the first character in the ChunkyString.
    * \return a const_iterator to the first char in the ChunkyString
    */
    const_iterator begin() const;

    /**
    * \brief Returns an iterator to one past the last chunk in the ChunkyString.
    * \return a const_iterator to "one past the end"
    */
    const_iterator end() const;

    /**
     * \brief inserts a character at the end of the ChunkyString.
     * \param c the element to be inserted
     * \details invalidates all iterators
     */
    void push_back(ELEMENT c);

    // Standard string ops: size, concatenation, (in)equality, comparison, print

    /**
     * \brief returns the size of the ChunkyList
     * \returns size_
     */
    size_t size() const; 
    bool operator==(const ChunkyList<ELEMENT>& rhs) const;
    bool operator!=(const ChunkyList<ELEMENT>& rhs) const;
    std::ostream& print(std::ostream& out) const;      ///< String printing

    /**
     * String concatenation
     * Warning: invalidates all iterators
     */
    ChunkyList<ELEMENT>& operator+=(const ChunkyList<ELEMENT>& rhs);

    /**
     * List comparison is lexicographic, which means:
     *    + Two lists `s1` and `s2` are compared element by element.
     *    + The first elements that aren't equal determine the order. If the
     *      element value from `s1` is smaller than the corresponding one from
     *      `s2`, then `s1` < `s2`, and vice-versa.
     *    + If `s1` is a prefix of `s2`, then `s1` < `s2`, and vice-versa.
     *    + If `s1` and `s2` have exactly the same elements, then neither is
     *      less than the other.
     *    + An empty list is less than any other list, except the empty list.
     * See: http://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
     */
    bool operator<(const ChunkyList<ELEMENT>& rhs) const;


    /**
     * Insert a character before the character at i.
     * (What makes ChunkyList special is its ability to insert and
     * erase elements quickly while remaining space efficient.)
     *
     * Returns an iterator pointing to the newly inserted character.
     *
     * Note: constant time
     *
     * Warning: invalidates all iterators except the returned iterator
     */
    iterator insert(iterator i, ELEMENT c);

    /**
     * Erase a character at i
     * (What makes ChunkyList special is its ability to insert and
     *   erase elements quickly while remaining space efficient.)
     *
     * Returns an iterator pointing to the character after the one
     *   that was deleted.
     *
     * Note: constant time
     *
     * Warning: invalidates all iterators except the returned iterator
     *
     * Warning: erasing from an empty string is undefined behavior
     */
    iterator erase(iterator i);

    /**
     * Average capacity of each chunk, as a percentage
     * This function computes the fraction of the ChunkyList's element
     * cells that are in use. 
     * 
     * For reasonably sized lists (i.e., those with more than one or two 
     * elements), utilization should never fall to near one element per 
     * chunk; otherwise the data structure would be wasting too much space.
     *
     * The utilization for an empty list is undefined (i.e., any value is
     * acceptable).
     * 
     * Note: constant time
     */
    double utilization() const;

    /* A free function you can use for debugging. See chunkylist-private for
     * an explanation of how it works. This function isn't part of the 
     * "official" interface for a ChunkyList, but we think it will make
     * your debugging process easier! 
     */
    void dump(const std::string& label) const;

 private:
    // NOTE: You can choose to change Chunk to be a struct rather than a class
    class Chunk {
     public:
        Chunk() = default;
        /**
         * \brief Constructs a chunk with a starting length
         * \param length the desired length
         */
        Chunk(size_t length);
        Chunk(const Chunk& other) = default;
        ~Chunk() = default;
        Chunk& operator=(const Chunk& other) = default;

     private:
        size_t length_;
        ELEMENT elements_[CHUNKSIZE];
        friend class ChunkyList<ELEMENT>;
       
        template <bool is_const>
        friend class Iterator;
    };

    /**
     * Iterator Class
     *
     * For most implementations, the synthesized copy constructor, 
     * destructor, and assignment operator are okay.
     * If your implementation requires a custom implementation of 
     * one of these, you can provide it. 
     *
     * The typedefs and the member functions are such that
     * the iterator works properly with STL functions (e.g., copy).
     *
     * Since this is a bidirectional_iterator, `operator--`
     * is provided and meaningful for all iterators except for
     * ChunkyList::begin() and default constructed iterators.
     *
     *  Note:  The design of the templated iterator was inspired by these
     *           two sources:
     *  www.drdobbs.com/the-standard-librarian-defining-iterato/184401331
     *  www.sj-vs.net/c-implementing-const_iterator-and-non-const-
     *      iterator-without-code-duplication
     */
    template <bool is_const>
    class Iterator {
     public:
        // Default constructor
        // Iterator();

        ////////////////////////////////////////////
        /////Delete after implementing all functions
        ////////////////////////////////////////////
        Iterator() = default;

        // Convert a non-const iterator to a const-iterator, if necessary
        Iterator(const Iterator<false>& i);

        ~Iterator() = default;
        Iterator& operator=(const Iterator& other) = default;

        // Make Iterator STL-friendly with these typedefs:
        using difference_type   = ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = ELEMENT;
        using const_reference   = const value_type&;

        using reference = typename std::conditional<is_const,
                                                    const value_type&,
                                                    value_type&>::type;

        using pointer = typename std::conditional<is_const,
                                                  const value_type*,
                                                  value_type*>::type;

        /**
         *  The `chunk_iter_t` type below might be helpful for some 
         *  implementations. If your implementation ever needs to declare
         *  a variable whose type is an iterator for a chunk list, you 
         *  should use `chunk_iter_t` for the type name. 
         */
        using chunk_iter_t =  typename std::conditional<is_const,
                              typename std::list<Chunk>::const_iterator,
                              typename std::list<Chunk>::iterator>::type;

        // Operations
        /**
         * \brief ChunkyList iterator increment to the next char
         * \returns a reference to the incremented iterator
         */
        Iterator& operator++();
        
        /**
         * \brief ChunkyList iterator decrement to previous char
         * \returns a reference to decremented iterator
         */
        Iterator& operator--();

        /**
         * \brief ChunkyList iterator dereference of the current char
         * \returns a reference of the current character
         */
        reference operator*() const;

        /**
         * \brief ChunkyList iterator equality check
         * \param rhs the other Iterator we want to check
         * \returns a boolean if the Iterators have the same elementIndex and chunk iterator
         */
        bool operator==(const Iterator& rhs) const;

        /**
         * \brief ChunkyList iterator inequality check
         * \param rhs the other Iterator we want to check
         * \returns a boolean if the Iterators do not have the same elementIndex or chunk iterator
         */
        bool operator!=(const Iterator& rhs) const;

     private:
        friend class ChunkyList<ELEMENT>;

        /**
         * \brief Iterator parameterized constructor
         * \param iter a list iterator for chunks_
         * \param elementIndex the current index in the chunk
         */
        Iterator(chunk_iter_t iter, std::size_t elementIndex);

        chunk_iter_t iter_;
        std::size_t elementIndex_;
    };
    
    // ChunkyString data members
    size_t size_;              // Length of the string
    std::list<Chunk> chunks_;  // Linked list of chunks
};

/**
 * Print operator: displays a ChunkyList on the given stream
 * 
 *   This "global function" makes it possible for ChunkyList users to write 
 *   `cout << s` (where `s` is a ChunkyList). The implementation of this
 *   function just calls ChunkyList's `print` member function.
 */
template <typename ELEMENT>
inline std::ostream& operator<<(std::ostream& out,
                                const ChunkyList<ELEMENT>& chunkylist) {
    return chunkylist.print(out);
}

#include "chunkylist-private.hpp"

#endif  // CHUNKYLIST_HPP_INCLUDED
