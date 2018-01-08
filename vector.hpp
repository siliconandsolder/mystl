#pragma once
#include <initializer_list>

template<typename T>
class MyVector 
{
private: 
	template<typename T>
	class MyVector_Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef T value_t;
		typedef value_t* pointer;
		typedef value_t& reference;
		typedef std::ptrdiff_t difference_type;
	private:
		typedef MyVector_Iterator<value_t> iterator;

		pointer data;
	public:
		MyVector_Iterator<value_t>() : data(nullptr) {}
		MyVector_Iterator<value_t>(pointer pos) : data(pos) {}
		MyVector_Iterator<value_t>(const iterator& other) : data(other.data) {}
		~MyVector_Iterator<value_t>() {}

		iterator& operator=(iterator iter) { data = iter.data; return *this; }
		iterator& operator=(pointer pos) { data = pos; return *this; }
		iterator  operator++(int) { return data++; }
		iterator& operator++() { ++data; return *this; }
		iterator  operator--(int) { return data--; }
		iterator& operator--() { --data; return *this; }
		reference operator* () { return *data; }
		pointer   operator->() { return data; }
		iterator  operator+ (difference_type v) { return data + v; }
		iterator  operator- (difference_type v) { return data - v; }
		difference_type  operator+ (iterator other) { return data + other.data; }
		difference_type  operator- (iterator other) { return data - other.data; }
		iterator& operator+= (difference_type v) { data += v; return *this; }
		iterator& operator-= (difference_type v) { data -= v; return *this; }
		bool	  operator< (const iterator& other) { return (data - other.data) < 0; }
		bool	  operator> (const iterator& other) { return (data - other.data) > 0; }
		bool      operator==(const iterator& rhs) const { return data == rhs.data; }
		bool      operator!=(const iterator& rhs) const { return data != rhs.data; }
		bool	  operator<=(const iterator& other) const { return (data == other.data) || (data < other.data); }
		bool	  operator>=(const iterator& other) const { return (data == other.data) || (data > other.data); }
	};

	template<typename T>
	class MyVector_Const_Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef T value_t;
		typedef value_t* pointer;
		typedef value_t& reference;
		typedef std::ptrdiff_t difference_type;
	private:
		typedef MyVector_Const_Iterator<value_t> const_iterator;
		typedef MyVector_Iterator<value_t> iterator;

		pointer data;
	public:
		MyVector_Const_Iterator<value_t>() : data(nullptr) {}
		MyVector_Const_Iterator<value_t>(pointer pos) : data(pos) {}
		MyVector_Const_Iterator<value_t>(const const_iterator& other) : data(other.data) {}
		MyVector_Const_Iterator<value_t>(MyVector_Iterator<value_t> iter) : data(iter.operator->()) {}
		~MyVector_Const_Iterator<value_t>() {}

		const_iterator& operator=(const_iterator con) { data = con.data; return *this; }
		const_iterator& operator=(pointer pos) { data = pos; return *this; }
		const_iterator  operator++(int) { return data++; }
		const_iterator& operator++() { ++data; return *this; }
		const_iterator  operator--(int) { return data--; }
		const_iterator& operator--() { --data; return *this; }
		const reference operator* () { return *data; }
		const pointer   operator->() { return data; }
		const_iterator  operator+ (difference_type v) { return data + v; }
		const_iterator  operator- (difference_type v) { return data - v; }
		difference_type  operator+ (const_iterator other) { return data + other.data; }
		difference_type  operator- (const_iterator other) { return data - other.data; }
		const_iterator& operator+= (difference_type v) { data += v; return *this; }
		const_iterator& operator-= (difference_type v) { data -= v; return *this; }
		bool	  operator< (const const_iterator& other) const { return (data - other.data) < 0; }
		bool	  operator> (const const_iterator& other) const { return (data - other.data) > 0; }
		bool      operator==(const const_iterator& rhs) const { return data == rhs.data; }
		bool      operator!=(const const_iterator& rhs) const { return data != rhs.data; }
		bool	  operator<= (const const_iterator& other) const { return (data == other.data) || (data < other.data); }
		bool	  operator>= (const const_iterator& other) const { return (data == other.data) || (data > other.data); }
	};
public:
	typedef T value_t;
	typedef value_t& reference;
	typedef size_t size_type;
	typedef value_t* pointer;
	typedef const value_t* const_pointer;
	typedef MyVector_Iterator<value_t> iterator;
	typedef MyVector_Const_Iterator<value_t> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
private:
	size_type vecSize;
	size_type vecCap;
	pointer elements;
	iterator begPtr, endPtr;
public:
	MyVector<value_t>(): vecSize(0), vecCap(0), elements(nullptr) { begPtr = endPtr = elements; }
	MyVector<value_t>(size_type cap) : vecSize(0), vecCap(cap) 
	{ 
		elements = new value_t[vecCap]; 
		iterator temp(elements);
		begPtr = endPtr = temp;
	}
	~MyVector<value_t>() { if (elements) delete[] elements; }
	
	// capacity functions
	bool		empty() const { return vecSize == 0; }
	size_type	size() const { return vecSize; }
	size_type	capacity() const { return vecCap; }
	void		shrink_to_fit();
	void		resize(size_type n);
	void		resize(size_type n, value_t const& val);

	// element access
	reference	operator[](size_type index);
	reference	at(size_type index);
	value_t		front();
	value_t		back();
	pointer		data() noexcept;

	// modifiers
	void assign(iterator first, iterator last);
	void assign(size_type n, const value_t& val);
	void assign(std::initializer_list<value_t> list);
	void push_back(const value_t& val);
	void pop_back();
	iterator insert(const_iterator position, const value_t& val);
	iterator insert(const_iterator position, size_type n, const value_t& val);
	iterator insert(const_iterator position, const_iterator first, const_iterator last);
	iterator insert(const_iterator position, value_t&& val);
	iterator insert(const_iterator position, std::initializer_list<value_t> il);
	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);
	void swap(MyVector& v);
	void clear();

	// iterators
	iterator begin() { return begPtr; }
	iterator end() { return endPtr; }
	const_iterator cbegin() { return const_iterator(begPtr); }
	const_iterator cend() { return const_iterator(endPtr); }
	reverse_iterator rbegin() { return endPtr; }
	reverse_iterator rend() { return begPtr; }
	const_reverse_iterator crbegin() { return const_reverse_iterator(rbegin()); }
	const_reverse_iterator crend() { return const_reverse_iterator(rend()); }

private:
	void resizeVector(size_type newSize);
	void rebuildVector();
};

/**
@name:		shrink_to_fit
@purpose:	Shrinks the cap of the vector to match the size of the vector
@param:		void
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::shrink_to_fit()
{
	vecCap = vecSize;
	resizeVector(vecCap);
	return;
}

/**
@name:		resize
@purpose:	resizes the vector to a specified size
@param:		size_type
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::resize(size_type n)
{
	if (n > vecCap) 
	{
		resizeVector(n);
		for (size_t i = vecSize; i < n; ++i)
		{
			value_t v{};
			push_back(v);
		}
		vecSize = n;
	}
	else if (n > vecSize && n <= vecCap) 
	{
		for (size_t i = vecSize; i < n; ++i)
		{
			value_t v{};
			push_back(v);
		}
		vecSize = n;
	}
	else if (n < vecSize)
	{
		vecSize = n;
		rebuildVector();
	}
	return;
}

/**
@name:		resize
@purpose:	resizes a vector to a specified size, fills any empty spaces with a specified value
@param:		size_type, const& value_t 
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::resize(size_type n, value_t const & val)
{
	if (n > vecCap) 
	{
		resizeVector(n);
		for (size_type i = vecSize; i < n; ++i)
			push_back(val);
		vecSize = n;
	}
	else if(n > vecSize && n <= vecCap)
	{
		for (size_type i = vecSize; i < n; ++i)
			push_back(val);
		vecSize = n;
	}
	else if (n < vecSize)
	{
		vecSize = n;
		rebuildVector();
	}
	// nothing else to be done, n can only be the size of vecSize
	return;
}

/**
@name:		operator[]
@purpose:	returns a reference to the value at the specified index
@param:		size_type
@return:	reference
*/
template<typename value_t>
typename MyVector<value_t>::reference MyVector<value_t>::operator[](size_type index)
{
	if (index < 0 || index > vecSize - 1)
		throw out_of_range("Out of scope");
	return elements[index];
}

/**
@name:		at
@purpose:	returns a reference to the value at the specified index
@param:		size_type
@return:	reference
*/
template<typename value_t>
typename MyVector<value_t>::reference MyVector<value_t>::at(size_type index)
{
	if (index < 0 || index > vecSize - 1)
		throw out_of_range("Out of scope");
	return elements[index];
}

/**
@name:		front
@purpose:	returns the first element in the vector
@param:		void
@return:	value_t
*/
template<typename value_t>
value_t MyVector<value_t>::front()
{
	return elements[0];
}

/**
@name:		back
@purpose:	returns the last element in the vector
@param:		void
@return:	value_t
*/
template<typename value_t>
value_t MyVector<value_t>::back()
{
	return elements[vecSize - 1];
}

template<typename value_t>
typename MyVector<value_t>::pointer MyVector<value_t>::data() noexcept
{
	return elements;
}

/**
@name:		assign
@purpose:	emptys the vector, then fills it with all values between first and last
@param:		iterator, iterator
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::assign(iterator first, iterator last)
{
	clear();
	for (iterator it = first; it < last; ++it)
		push_back(*it);	
}

/**
@name:		assign
@purpose:	emptys the vector, then assigns the value of val to each element
@param:		size_type, const value_t&
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::assign(size_type n, const value_t & val)
{
	clear();
	for (size_type i = 0; i < n; ++i)
		push_back(val);
}

/**
@name:		assign
@purpose:	emptys the vector, then fills it with th evalues in list
@param:		std::initializer_list
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::assign(std::initializer_list<value_t> list)
{
	clear();
	for (auto x : list)
		push_back(x);
}

/**
@name:		push_back
@purpose:	adds a value to the end of the vector
@param:		const value_t&
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::push_back(const value_t & val)
{
	++vecSize;
	if (!elements)		// if vector has not been initialised
	{
		elements = new value_t[1];
		vecCap = vecSize;
		begPtr = endPtr = elements;
	}
	if (vecSize > vecCap)
		resizeVector(vecCap * 2);
	elements[vecSize - 1] = val;
	++endPtr;
	return;
}

/**
@name:		pop_back
@purpose:	removes the last element in the vector
@param:		void
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::pop_back()
{
	if (vecSize > 0) 
	{
		value_t val{};
		elements[vecSize - 1] = val;
		--vecSize;
		--endPtr;
	}
	return;
}

/**
@name:		insert
@purpose:	inserts a value at a certain position in the vector
@param:		const_iterator, const value_t&
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::insert(const_iterator position, const value_t & val)
{
	if (begPtr == endPtr)	// elements is not initialised
		return begPtr;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;
	
	if (diff > (endPtr - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");
	
	temp += diff;
	*temp = val;
	return temp;
}

/**
@name:		insert
@purpose:	inserts a value a set number of times starting at a certain position in the vector
@param:		const_iterator, size_type, const value_t&
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::insert(const_iterator position, size_type n, const value_t & val)
{
	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;
	
	if (diff > (endPtr - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	while (i < n)
	{
		if (vecSize == 0)
		{
			resizeVector(1);
			temp = begPtr;
		}
		else
		{
			resizeVector(vecCap * 2);
			temp = begPtr + diff + i;
		}
			
		if (temp == endPtr)  // if we've hit the end of the vector
		{
			++vecSize;
			++endPtr;
		}
		*temp = val;
		++temp;
		++i;		
	}
	return ret;
}

/**
@name:		insert
@purpose:	inserts all values between first and last starting at a certain position in the vector
@param:		const_iterator, const_iterator, const_iterator
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::insert(const_iterator position, const_iterator first, const_iterator last)
{
	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;
	
	if (diff > (endPtr - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	for (const_iterator it = first; it != last; ++it, ++temp, ++i)
	{
		if (vecSize == 0)
		{
			resizeVector(1);
			temp = begPtr;
		}
		else
		{
			resizeVector(vecCap * 2);
			temp = begPtr + diff + i;
		}

		if (temp == endPtr)  // if we've hit the end of the vector
		{
			++vecSize;
			++endPtr;
		}
		*temp = *it;
	}
	return ret;
}

/**
@name:		insert
@purpose:	inserts a value at a certain position in the vector. The variable holding the value is moved into the vector.
@param:		const_iterator, value_t&&
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::insert(const_iterator position, value_t && val)
{
	if (begPtr == endPtr)
		return begPtr;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;

	if (diff > (endPtr - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");
	
	temp += diff;
	*temp = val;
	return temp;
}

/**
@name:		insert
@purpose:	inserts all values between in the initialization list starting at a certain position in the vector
@param:		const_iterator, std::initializer_list
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::insert(const_iterator position, std::initializer_list<value_t> il)
{	
	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;

	if ((diff > (endPtr - 1) - temp) && vecSize > 0)
		throw out_of_range("Const Iterator references non-existent position in vector.");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	for (auto x : il)
	{
		if (vecSize == vecCap) // sometimes endPtr is not the real end; vector may have deleted element
		{
			if (vecSize == 0)
			{
				resizeVector(1);
				temp = begPtr;
			}
			else
			{
				resizeVector(vecCap * 2);
				temp = begPtr + diff + i;
			}
		}

		if (temp == endPtr)  // if we've hit the end of the vector
		{
			++vecSize;
			++endPtr;
		}
		*temp = x;
		++temp;
		++i;
	}
	return ret;
}

/**
@name:		erase
@purpose:	erases the element at a certain position in the vector
@param:		const_iterator
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::erase(const_iterator position)
{
	if (begPtr == endPtr)
		return begPtr;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;

	if (diff > (endPtr - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector.");

	temp += diff;

	for (temp += 1; temp != endPtr; ++temp)
		*(temp - 1) = *temp;

	--vecSize;
	rebuildVector();
	iterator ret = begin() + diff;
	return ret;
}

/**
@name:		erase
@purpose:	erases all elements between first and last
@param:		const_iterator, const_iterator
@return:	void
*/
template<typename value_t>
typename MyVector<value_t>::iterator MyVector<value_t>::erase(const_iterator first, const_iterator last)
{
	if (begPtr == endPtr)
		return begPtr;

	iterator itFirst = begin();
	std::ptrdiff_t diffOne = first - itFirst;
	
	if (diffOne > (endPtr - 1) - itFirst)
		throw out_of_range("Const Iterator references non-existent position in vector.");
	itFirst += diffOne;

	iterator itLast = itFirst;
	std::ptrdiff_t diffTwo = last - itLast;

	if (diffTwo > (endPtr - 1) - itLast)
		throw out_of_range("Const Iterator references non-existent position in vector.");
	itLast += diffTwo;

	std::ptrdiff_t deleteRange = diffTwo + 1;	// have to account for first iterator (eg. deleting elements 0-3 is 4 elements)

	for(iterator it = itLast + 1; it < endPtr; ++it)	// move all elements ahead of the deleted elements to the left
		*(it - deleteRange) = *it;

	vecSize -= deleteRange;
	rebuildVector();
	iterator ret = begPtr + diffOne;
	return ret;
}

/**
@name:		swap
@purpose:	swaps the member variables between two vectors
@param:		MyVector&
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::swap(MyVector<value_t>& v)
{
	MyVector<value_t> temp = this;
	this = v;
	v = temp;
}

/**
@name:		clear
@purpose:	empties the vector
@param:		void
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::clear()
{
	vecSize = 0;
	vecCap = 0;
	delete[] elements;
	elements = nullptr;
	iterator temp(elements);
	begPtr = endPtr = temp;
}

/**
@name:		resizeVector
@purpose:	resizes the vector based on the desired capacity
@param:		size_type
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::resizeVector(size_type newCap)
{
	pointer newElements = new value_t[newCap];
	
	pointer newElCopy = newElements;
	for (iterator beg = begPtr; beg != endPtr; ++beg, ++newElCopy)	// copy everything from old element container to new element container
		*newElCopy = *beg;
	
	delete[] elements;
	elements = newElements;
	vecCap = newCap;
	begPtr = elements;
	endPtr = elements + vecSize;
	return;
}

/**
@name:		rebuildVector
@purpose:	destroys all elements beyond the size of the vector, but below the cap.
@param:		size_type
@return:	void
*/
template<typename value_t>
void MyVector<value_t>::rebuildVector()
{
	pointer remElements = new value_t[vecSize];
	pointer curElements = elements;
	size_t i = 0;
	// put all of the elements into an array
	for (curElements; i < vecSize; ++i, ++curElements)
		remElements[i] = *curElements;

	delete[] elements;
	elements = new value_t[vecCap];
	// put all of the elements back into the array
	for (i = 0; i < vecSize; ++i)
		elements[i] = remElements[i];

	begPtr = elements;
	endPtr = elements + vecSize;
	delete[] remElements;
}
