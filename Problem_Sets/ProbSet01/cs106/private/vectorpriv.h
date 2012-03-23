/*
 * File: vecpriv.h
 * ---------------
 * This file contains the private section of the vector.h interface.
 */

private:

/*
 * Implementation notes: Vector data structure
 * -------------------------------------------
 * The elements of the Vector are stored in a dynamic array of
 * the specified element type.  If the space in the array is ever
 * exhausted, the implementation doubles the array capacity.
 */

/* Constants */

   static const int INITIAL_CAPACITY = 100;

/* Instance variables */

   ValueType *elements;  /* A dynamic array of the elements   */
   int capacity;         /* The allocated size of the array   */
   int count;            /* The number of elements in use     */

/* Private methods */

   void expandCapacity();

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return vectors by value
 * and assign from one vector to another. The entire contents of
 * the vector, including all elements, are copied. Each vector
 * element is copied from the original vector to the copy using
 * assignment (operator=). Making copies is generally avoided
 * because of the expense and thus, vectors are typically passed
 * by reference, however, when a copy is needed, these operations
 * are supported.
 */

   void copyInternalData(const Vector & vec) {
      elements = new ValueType[vec.count];
      for (int i = 0; i < vec.count; i++) {
         elements[i] = vec.elements[i];
      }
      count = vec.count;
      capacity = vec.count;
   }

public:

   Vector & operator,(const ValueType & value) {
      this->add(value);
      return *this;
   }

   Vector & operator=(const Vector & rhs) {
      if (this != &rhs) {
         delete[] elements;
         copyInternalData(rhs);
      }
      return *this;
   }

   Vector(const Vector & rhs) {
      copyInternalData(rhs);
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator :
      public std::iterator<std::random_access_iterator_tag, ValueType> {

   private:
      const Vector *vp;
      int index;

   public:

      iterator() {
         this->vp = NULL;
      }

      iterator(const iterator & it) {
         this->vp = it.vp;
         this->index = it.index;
      }

      iterator(const Vector *vp, int index) {
         this->vp = vp;
         this->index = index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      iterator & operator--() {
         index--;
         return *this;
      }

      iterator operator--(int) {
         iterator copy(*this);
         operator--();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return vp == rhs.vp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      bool operator<(const iterator & rhs) {
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index < rhs.index;
      }

      bool operator<=(const iterator & rhs) {
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index <= rhs.index;
      }

      bool operator>(const iterator & rhs) {
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index > rhs.index;
      }

      bool operator>=(const iterator & rhs) {
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index >= rhs.index;
      }

      iterator operator+(const int & rhs) {
         return iterator(vp, index + rhs);
      }

      iterator operator-(const int & rhs) {
         return iterator(vp, index - rhs);
      }

      int operator-(const iterator & rhs) {
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index - rhs.index;
      }

      ValueType & operator*() {
         return vp->elements[index];
      }

      ValueType & operator[](int k) {
         return vp->elements[index + k];
      }

   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, count);
   }
