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

		pointer data_;
	public:
		MyVector_Iterator<value_t>() : data_(nullptr) {}
		MyVector_Iterator<value_t>(pointer pos) : data_(pos) {}
		MyVector_Iterator<value_t>(const iterator& other) : data_(other.data_) {}
		~MyVector_Iterator<value_t>() {}

		iterator& operator=(iterator iter) { data_ = iter.data_; return *this; }
		iterator& operator=(pointer pos) { data_ = pos; return *this; }
		iterator  operator++(int) { iterator temp(data_++); return temp; }
		iterator& operator++() { ++data_; return *this; }
		iterator  operator--(int) { iterator temp(data_--); return temp; }
		iterator& operator--() { --data_; return *this; }
		reference operator* () { return *data_; }
		pointer   operator->() { return data_; }
		iterator  operator+ (difference_type v) { return data_ + v; }
		iterator  operator- (difference_type v) { return data_ - v; }
		difference_type  operator+ (iterator other) { return data_ + other.data_; }
		difference_type  operator- (iterator other) { return data_ - other.data_; }
		iterator& operator+= (difference_type v) { data_ += v; return *this; }
		iterator& operator-= (difference_type v) { data_ -= v; return *this; }
		bool	  operator< (const iterator& other) { return (data_ - other.data_) < 0; }
		bool	  operator> (const iterator& other) { return (data_ - other.data_) > 0; }
		bool      operator==(const iterator& rhs) const { return data_ == rhs.data_; }
		bool      operator!=(const iterator& rhs) const { return data_ != rhs.data_; }
		bool	  operator<=(const iterator& other) const { return (data_ == other.data_) || (data_ < other.data_); }
		bool	  operator>=(const iterator& other) const { return (data_ == other.data_) || (data_ > other.data_); }
	};

	template<typename T>
	class MyVector_Const_Iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef T value_t;
		typedef value_t* pointer;
		typedef value_t const * const_pointer;
		typedef value_t& reference;
		typedef value_type const& const_reference;
		typedef std::ptrdiff_t difference_type;
	private:
		typedef MyVector_Const_Iterator<value_t> const_iterator;
		typedef MyVector_Iterator<value_t> iterator;

		pointer data_;
	public:
		MyVector_Const_Iterator<value_t>() : data_(nullptr) {}
		MyVector_Const_Iterator<value_t>(pointer pos) : data_(pos) {}
		MyVector_Const_Iterator<value_t>(const const_iterator& other) : data_(other.data_) {}
		MyVector_Const_Iterator<value_t>(MyVector_Iterator<value_t> iter) : data_(iter.operator->()) {}
		~MyVector_Const_Iterator<value_t>() {}

		const_iterator& operator=(const_iterator con) { data_ = con.data_; return *this; }
		const_iterator& operator=(pointer pos) { data_ = pos; return *this; }
		const_iterator  operator++(int) { const_iterator temp(data_++); return temp; }
		const_iterator& operator++() { ++data_; return *this; }
		const_iterator  operator--(int) { const_iterator temp(data_--); return temp; }
		const_iterator& operator--() { --data_; return *this; }
		const_reference operator* () const { return *data_; }
		const_pointer   operator->() const { return data_; }
		const_iterator  operator+ (difference_type v) { return data_ + v; }
		const_iterator  operator- (difference_type v) { return data_ - v; }
		difference_type  operator+ (const_iterator other) { return data_ + other.data_; }
		difference_type  operator- (const_iterator other) { return data_ - other.data_; }
		const_iterator& operator+= (difference_type v) { data_ += v; return *this; }
		const_iterator& operator-= (difference_type v) { data_ -= v; return *this; }
		bool	  operator< (const const_iterator& other) const { return (data_ - other.data_) < 0; }
		bool	  operator> (const const_iterator& other) const { return (data_ - other.data_) > 0; }
		bool      operator==(const const_iterator& rhs) const { return data_ == rhs.data_; }
		bool      operator!=(const const_iterator& rhs) const { return data_ != rhs.data_; }
		bool	  operator<= (const const_iterator& other) const { return (data_ == other.data_) || (data_ < other.data_); }
		bool	  operator>= (const const_iterator& other) const { return (data_ == other.data_) || (data_ > other.data_); }
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
	size_type vecSize_;
	size_type vecCap_;
	pointer elements_;
	iterator begPtr_, endPtr_;
public:
	MyVector<value_t>(): vecSize_(0), vecCap_(0), elements_(nullptr) { begPtr_ = endPtr_ = elements_; }
	MyVector<value_t>(size_type cap) : vecSize_(0), vecCap_(cap) 
	{ 
		elements_ = new value_t[vecCap_]; 
		iterator temp(elements_);
		begPtr_ = endPtr_ = temp;
	}
	~MyVector<value_t>() { if (elements_) delete[] elements_; }
	
	// capacity functions
	bool		empty() const { return vecSize_ == 0; }
	size_type	size() const { return vecSize_; }
	size_type	capacity() const { return vecCap_; }
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
	iterator begin() { return begPtr_; }
	iterator end() { return endPtr_; }
	const_iterator cbegin() { return const_iterator(begPtr_); }
	const_iterator cend() { return const_iterator(endPtr_); }
	reverse_iterator rbegin() { return endPtr_; }
	reverse_iterator rend() { return begPtr_; }
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
	vecCap_ = vecSize_;
	resizeVector(vecCap_);
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
	if (n > vecCap_) 
	{
		resizeVector(n);
		for (size_t i = vecSize_; i < n; ++i)
		{
			value_t v{};
			push_back(v);
		}
		vecSize_ = n;
	}
	else if (n > vecSize_ && n <= vecCap_) 
	{
		for (size_t i = vecSize_; i < n; ++i)
		{
			value_t v{};
			push_back(v);
		}
		vecSize_ = n;
	}
	else if (n < vecSize_)
	{
		vecSize_ = n;
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
	if (n > vecCap_) 
	{
		resizeVector(n);
		for (size_type i = vecSize_; i < n; ++i)
			push_back(val);
		vecSize_ = n;
	}
	else if(n > vecSize_ && n <= vecCap_)
	{
		for (size_type i = vecSize_; i < n; ++i)
			push_back(val);
		vecSize_ = n;
	}
	else if (n < vecSize_)
	{
		vecSize_ = n;
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
	if (index < 0 || index > vecSize_ - 1)
		throw out_of_range("Out of scope");
	return elements_[index];
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
	if (index < 0 || index > vecSize_ - 1)
		throw out_of_range("Out of scope");
	return elements_[index];
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
	return elements_[0];
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
	return elements_[vecSize_ - 1];
}

template<typename value_t>
typename MyVector<value_t>::pointer MyVector<value_t>::data() noexcept
{
	return elements_;
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
	++vecSize_;
	if (!elements_)		// if vector has not been initialised
	{
		elements_ = new value_t[1];
		vecCap_ = vecSize_;
		begPtr_ = endPtr_ = elements_;
	}
	if (vecSize_ > vecCap_)
		resizeVector(vecCap_ * 2);
	elements_[vecSize_ - 1] = val;
	++endPtr_;
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
	if (vecSize_ > 0) 
	{
		value_t val{};
		elements_[vecSize_ - 1] = val;
		--vecSize_;
		--endPtr_;
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
	if (begPtr_ == endPtr_)	// elements is not initialised
		return begPtr_;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;
	
	if (diff > (endPtr_ - 1) - temp)
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
	
	if (diff > (endPtr_ - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	while (i < n)
	{
		if (vecSize_ == 0)
		{
			resizeVector(1);
			temp = begPtr_;
		}
		else
		{
			resizeVector(vecCap_ * 2);
			temp = begPtr_ + diff + i;
		}
			
		if (temp == endPtr_)  // if we've hit the end of the vector
		{
			++vecSize_;
			++endPtr_;
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
	
	if (diff > (endPtr_ - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector. Try push_back().");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	for (const_iterator it = first; it != last; ++it, ++temp, ++i)
	{
		if (vecSize_ == 0)
		{
			resizeVector(1);
			temp = begPtr_;
		}
		else
		{
			resizeVector(vecCap_ * 2);
			temp = begPtr_ + diff + i;
		}

		if (temp == endPtr_)  // if we've hit the end of the vector
		{
			++vecSize_;
			++endPtr_;
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
	if (begPtr_ == endPtr_)
		return begPtr_;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;

	if (diff > (endPtr_ - 1) - temp)
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

	if ((diff > (endPtr_ - 1) - temp) && vecSize_ > 0)
		throw out_of_range("Const Iterator references non-existent position in vector.");

	temp += diff;
	iterator ret = temp;
	size_type i = 0;
	for (auto x : il)
	{
		if (vecSize_ == vecCap_) // sometimes endPtr is not the real end; vector may have deleted element
		{
			if (vecSize_ == 0)
			{
				resizeVector(1);
				temp = begPtr_;
			}
			else
			{
				resizeVector(vecCap_ * 2);
				temp = begPtr_ + diff + i;
			}
		}

		if (temp == endPtr_)  // if we've hit the end of the vector
		{
			++vecSize_;
			++endPtr_;
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
	if (begPtr_ == endPtr_)
		return begPtr_;

	iterator temp = begin();
	std::ptrdiff_t diff = position - temp;

	if (diff > (endPtr_ - 1) - temp)
		throw out_of_range("Const Iterator references non-existent position in vector.");

	temp += diff;

	for (temp += 1; temp != endPtr_; ++temp)
		*(temp - 1) = *temp;

	--vecSize_;
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
	if (begPtr_ == endPtr_)
		return begPtr_;

	iterator itFirst = begin();
	std::ptrdiff_t diffOne = first - itFirst;
	
	if (diffOne > (endPtr_ - 1) - itFirst)
		throw out_of_range("Const Iterator references non-existent position in vector.");
	itFirst += diffOne;

	iterator itLast = itFirst;
	std::ptrdiff_t diffTwo = last - itLast;

	if (diffTwo > (endPtr_ - 1) - itLast)
		throw out_of_range("Const Iterator references non-existent position in vector.");
	itLast += diffTwo;

	std::ptrdiff_t deleteRange = diffTwo + 1;	// have to account for first iterator (eg. deleting elements 0-3 is 4 elements)

	for(iterator it = itLast + 1; it < endPtr_; ++it)	// move all elements ahead of the deleted elements to the left
		*(it - deleteRange) = *it;

	vecSize_ -= deleteRange;
	rebuildVector();
	iterator ret = begPtr_ + diffOne;
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
	vecSize_ = 0;
	vecCap_ = 0;
	delete[] elements_;
	elements_ = nullptr;
	iterator temp(elements_);
	begPtr_ = endPtr_ = temp;
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
	for (iterator beg = begPtr_; beg != endPtr_; ++beg, ++newElCopy)	// copy everything from old element container to new element container
		*newElCopy = *beg;
	
	delete[] elements_;
	elements_ = newElements;
	vecCap_ = newCap;
	begPtr_ = elements_;
	endPtr_ = elements_ + vecSize_;
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
	pointer remElements = new value_t[vecSize_];
	pointer curElements = elements_;
	size_t i = 0;
	// put all of the elements into an array
	for (curElements; i < vecSize_; ++i, ++curElements)
		remElements[i] = *curElements;

	delete[] elements_;
	elements_ = new value_t[vecCap_];
	// put all of the elements back into the array
	for (i = 0; i < vecSize_; ++i)
		elements_[i] = remElements[i];

	begPtr_ = elements_;
	endPtr_ = elements_ + vecSize_;
	delete[] remElements;
}
