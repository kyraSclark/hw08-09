/*********************************************************************
 * ChunkyList: class.
 *********************************************************************
 *
 * Implementation for the ChunkyList class
 *
 */

#include <iostream>
#include <stdexcept>
#include <cassert>
#include <string>

/*********************************************************************
 * Chunk implementation
 *********************************************************************/
// template <typename ELEMENT>
// ChunkyList<ELEMENT>::Chunk::Chunk() {
//     // Note: Not implemented yet
// }

// template <typename ELEMENT>
// ChunkyList<ELEMENT>::Chunk::Chunk(const Chunk& other) {
//     // Note: Not implemented yet
// }


// TODO(students): 
// If you decide to add additional constructors or 
// member functions for your Chunk class (not required), 
// implement them here

/*********************************************************************
 * ChunkyList<ELEMENT> implementation
 *********************************************************************/

template <typename ELEMENT>
ChunkyList<ELEMENT>::ChunkyList() : size_{0}{
    ChunkyList::Chunk first;
    chunks_.push_back(first);
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::begin() {
    ChunkyList<ELEMENT>::iterator iter = Iterator<false>(chunks_.begin(), 0);
    if (size() == 0) {
        return iter;
    } else {
        // Return the first chunk with stuff in it
        while (iter.iter_ -> length_ == 0) {
            ++iter;
        }
    }
    return iter;
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::end() {
    return Iterator<false>(chunks_.end(), 0);
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::const_iterator
                                ChunkyList<ELEMENT>::begin() const {
    ChunkyList<ELEMENT>::iterator iter = Iterator<true>(chunks_.begin(), 0);
    if (size() == 0) {
        return iter;
    } else {
        // Return the first chunk with stuff in it
        while (iter.iter_ -> length_ == 0) {
            ++iter;
        }
    }
    return iter;
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::const_iterator ChunkyList<ELEMENT>::end() const {
    return Iterator<true>(chunks_.end(), 0);
}

template <typename ELEMENT>
void ChunkyList<ELEMENT>::push_back(ELEMENT c) {
    ChunkyList<ELEMENT>::iterator iter = end();
    --iter;

    if ((size() / size(chunks_) >= CHUNKSIZE / 2) ||
        (iter.iter_ -> length_ == CHUNKSIZE) ) {
        // Parameterized chunk that takes the length
        // add the char to the chunk
        // add the chunk to chunks_
        ChunkyList<ELEMENT>::Chunk newChunk;
        chunks_.push_back(newChunk);
    } else {
        *(iter.iter_)[iter.elementIndex_ + 1];
        ++(iter.iter_ -> length_);
    }   
    ++size_;
}

template <typename ELEMENT>
size_t ChunkyList<ELEMENT>::size() const {
    return size_;
}

template <typename ELEMENT>
bool ChunkyList<ELEMENT>::operator==(const ChunkyList<ELEMENT>& rhs) const {
    // Note: Not implemented yet
    return true;
}

template <typename ELEMENT>
bool ChunkyList<ELEMENT>::operator!=(const ChunkyList<ELEMENT>& rhs) const {
    // Note: Not implemented yet
    return false;
}

template <typename ELEMENT>
std::ostream& ChunkyList<ELEMENT>::print(std::ostream& out) const {
    // Note: Not implemented yet
    return out;
}

template <typename ELEMENT>
ChunkyList<ELEMENT>& ChunkyList<ELEMENT>::operator+=(
                          const ChunkyList<ELEMENT>& rhs) {
    // Note: Not implemented yet
    return *this;
}

template <typename ELEMENT>
bool ChunkyList<ELEMENT>::operator<(const ChunkyList<ELEMENT>& rhs) const {
    // Note: Not implemented yet
    return true;
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator
         ChunkyList<ELEMENT>::insert(iterator iter, ELEMENT c) {
    // Note: Not implemented yet
    return Iterator<false>();
}


template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator
    ChunkyList<ELEMENT>::erase(iterator iter) {
    // Note: Not implemented yet
    return Iterator<false>();
}

template <typename ELEMENT>
double ChunkyList<ELEMENT>::utilization() const {
    return static_cast<double>(size()) / (chunks_.size() * CHUNKSIZE);
}

/* Here's a free function that you can use for debugging.
 * If you have a test of a ChunkyList  that fails,
 * it is often useful to add debugging output to the test code, e.g.,
 * std::cerr << "Before: " << s << std::endl;
 * s.push_back('*');
 * std::cerr << "After: " << s << std::endl;
 * 
 * But sometimes bugs occur only when a chunk is full, or becomes
 * empty, or has exactly 2 chars, and normal printing (by design)
 * just shows the characters, not the chunk structure, making
 * these bugs hard to diagnose.
 * 
 * The solution in such cases is to call the dump method, e.g.,
 *         s.dump("Before: ");
 *         s.push_back('*');
 *         s.dump("After: ");
 *
 *  Then you can tell whether the ChunkyString "abc" is really
 *         |3:abc|         -- 3 chars in one chunk
 *         |2:ab|1:c|      -- 2 chars in 1st chunk, 1 char in 2nd
 *         |1:a|1:b|1:c|   -- 1 char in each of 3 chunks
 *  or whether the problem is that s is just corrumpted, e.g.,
 *         |2:ab|0:|0:|1:c|   -- some empty chunks in the middle
 *         |3:abc|-9:|        -- a chunk with negative length_ !?
 *
 *  Alternatively, rather than adding output to the tests, you might
 *     (temporarily!) add debugging output to your member functions.
 *     For example, if you think there's a problem in operator+=
 *     you can change the code for that member function to:
 *
 *          ChunkyList<ELEMENT>& operator+=(const ChunkyList<ELEMENT>& right_side) {
 *              dump("Left side before append: ");
 *              right_side.dump("Right side before append: ");
 *              ...code to do the append...
 *              dump("Left side after append : ");
 *              return *this;
 *          }
 */

template <typename ELEMENT>
void ChunkyList<ELEMENT>::dump(const std::string& label) const {
    // Print the label so that we know where this output came from
    std::cerr << label << " ";

    // Handle empty-list case specially
    if (chunks_.size() == 0) {
        std::cerr << "(no chunks)\n";
        return;
    }

    // print size and contents of each chunk.
    std::cerr << "|";
    for (const Chunk& chunk : chunks_) {
        std::cerr << chunk.length_ << ":";
        for (size_t i = 0; i < chunk.length_; ++i) {
            std::cerr << chunk.chars_[i];
        }
        std::cerr << "|";
      }
    std::cerr << "\n";
}

// TODO(students): Add any other constructors or member functions
// for your ChunkyList class here.


/*********************************************************************
 * ChunkyString::Iterator class.
 *********************************************************************
 *
 * Implementation for the templated ChunkyString iterator
 *
 */


// template <typename ELEMENT>
// template <bool is_const>
// ChunkyList<ELEMENT>::template Iterator<is_const>::Iterator() {
    
// }

template <typename ELEMENT>
template<bool is_const>
ChunkyList<ELEMENT>::Iterator<is_const>::Iterator(const Iterator<false>& i) {
    iter_ = i.iter_;
    elementIndex_ = i.elementIndex_;
}

template <typename ELEMENT>
template<bool is_const>
ChunkyList<ELEMENT>::Iterator<is_const>::Iterator(chunk_iter_t iter,
                                           std::size_t elementIndex) : iter_{iter}, elementIndex_{elementIndex} {
}

template <typename ELEMENT>
template<bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>&
                  ChunkyList<ELEMENT>::Iterator<is_const>::operator++() {
    ++elementIndex_;
    while (iter_ != chunks_.end()) {
        if (elementIndex_ == iter_ -> length_) {
            elementIndex_ = 0;
            ++iter_;
        } else {
            return *this;
        }
    }
    return *this;
}

template <typename ELEMENT>
template<bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>&
         ChunkyList<ELEMENT>::Iterator<is_const>::operator--() {
    if (elementIndex_ == 0) {
        --iter_;
        while (iter_ -> length_ == 0 && iter_ != chunks_.begin()) {
            --iter_;
        }
        if (iter_ == chunks_.begin()) {
            elementIndex_ = 0;
        } else {
            elementIndex_ = iter_ -> length_ - 1;
        }
    } else {
        --elementIndex_;
    }

    return *this;
}

template <typename ELEMENT>
template<bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>::reference
    ChunkyList<ELEMENT>::Iterator<is_const>::operator*() const {

    ChunkyList<ELEMENT>::Chunk currentChunk = *iter_;
    Iterator<is_const>::reference currentEl = currentChunk.elements_[elementIndex_];
    return currentEl;
}

template <typename ELEMENT>
template<bool is_const>
bool ChunkyList<ELEMENT>::Iterator<is_const>::operator==(
                                             const Iterator& rhs) const {
  return (iter_ == rhs.iter_ && elementIndex_ == rhs.elementIndex_);
}

template <typename ELEMENT>
template<bool is_const>
bool ChunkyList<ELEMENT>::Iterator<is_const>::operator!=(
                                              const Iterator& rhs) const {
    return !(*this == rhs);
}

// TODO(students): Add any other constructors or member functions
// for your Iterator class here.
