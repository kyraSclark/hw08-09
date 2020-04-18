/*********************************************************************
 * ChunkyList: class.
 *********************************************************************
 *
 * Implementation for the ChunkyList class
 *
 */

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

/*********************************************************************
 * Chunk implementation
 *********************************************************************/

template <typename ELEMENT>
ChunkyList<ELEMENT>::Chunk::Chunk() : length_{0} {}

// template <typename ELEMENT>
// ChunkyList<ELEMENT>::Chunk::Chunk(const Chunk& other) {
//     // Note: Not implemented yet
// }

/*********************************************************************
 * ChunkyList<ELEMENT> implementation
 *********************************************************************/

template <typename ELEMENT>
ChunkyList<ELEMENT>::ChunkyList() : size_{0} {}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::begin() {
  return Iterator<false>(chunks_.begin(), 0);
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::end() {
  return Iterator<false>(chunks_.end(), 0);
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::const_iterator ChunkyList<ELEMENT>::begin()
    const {
  return Iterator<true>(chunks_.begin(), 0);
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::const_iterator ChunkyList<ELEMENT>::end() const {
  return Iterator<true>(chunks_.end(), 0);
}

template <typename ELEMENT>
void ChunkyList<ELEMENT>::push_back(ELEMENT c) {
  // if the ChunkyList is empty, we need to add a new chunk
  if (size() == 0) {
    ChunkyList<ELEMENT>::Chunk newChunk;
    newChunk.elements_[0] = c;
    ++newChunk.length_;
    chunks_.push_back(newChunk);
  } else {
    ChunkyList<ELEMENT>::iterator iter = end();
    --iter;

    // keep proper utilization by creating new chunks when necessary
    if ((size() / chunks_.size() >= CHUNKSIZE / 2) ||
        (iter.iter_->length_ == CHUNKSIZE)) {
      ChunkyList<ELEMENT>::Chunk newChunk;
      newChunk.elements_[0] = c;
      ++newChunk.length_;
      chunks_.push_back(newChunk);
    } else {
      iter.iter_->elements_[iter.elementIndex_ + 1] = c;
      ++(iter.iter_->length_);
    }
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
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::insert(
    iterator iter, ELEMENT c) {
  // Note: Not implemented yet
  return Iterator<false>();
}

template <typename ELEMENT>
typename ChunkyList<ELEMENT>::iterator ChunkyList<ELEMENT>::erase(
    iterator iter) {
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
 *          ChunkyList<ELEMENT>& operator+=(const ChunkyList<ELEMENT>&
 * right_side) { dump("Left side before append: "); right_side.dump("Right side
 * before append: ");
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
      std::cerr << chunk.elements_[i];
    }
    std::cerr << "|";
  }
  std::cerr << "\n";
}


/*********************************************************************
 * ChunkyString::Iterator class.
 *********************************************************************
 *
 * Implementation for the templated ChunkyString iterator
 *
 */

template <typename ELEMENT>
template <bool is_const>
ChunkyList<ELEMENT>::template Iterator<is_const>::Iterator()
    : elementIndex_{0} {
}

template <typename ELEMENT>
template <bool is_const>
ChunkyList<ELEMENT>::Iterator<is_const>::Iterator(const Iterator<false>& i) {
  iter_ = i.iter_;
  elementIndex_ = i.elementIndex_;
}

template <typename ELEMENT>
template <bool is_const>
ChunkyList<ELEMENT>::Iterator<is_const>::Iterator(chunk_iter_t iter,
                                                  std::size_t elementIndex)
    : iter_{iter}, elementIndex_{elementIndex} {}

template <typename ELEMENT>
template <bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>&
ChunkyList<ELEMENT>::Iterator<is_const>::operator++() {
  ++elementIndex_;
  if (elementIndex_ == iter_->length_) {
    elementIndex_ = 0;
    ++iter_;
  }
  return *this;
}

template <typename ELEMENT>
template <bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>&
ChunkyList<ELEMENT>::Iterator<is_const>::operator--() {
  if (elementIndex_ == 0) {
    --iter_;
    elementIndex_ = iter_->length_ - 1;
  } else {
    --elementIndex_;
  }

  return *this;
}

template <typename ELEMENT>
template <bool is_const>
typename ChunkyList<ELEMENT>::template Iterator<is_const>::reference
    ChunkyList<ELEMENT>::Iterator<is_const>::operator*() const {
  ChunkyList<ELEMENT>::Iterator<is_const>::reference currentEl =
      (*iter_).elements_[elementIndex_];
  return currentEl;
}

template <typename ELEMENT>
template <bool is_const>
bool ChunkyList<ELEMENT>::Iterator<is_const>::operator==(
    const Iterator& rhs) const {
  return (iter_ == rhs.iter_ && elementIndex_ == rhs.elementIndex_);
}

template <typename ELEMENT>
template <bool is_const>
bool ChunkyList<ELEMENT>::Iterator<is_const>::operator!=(
    const Iterator& rhs) const {
  return !(*this == rhs);
}
