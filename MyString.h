#ifndef MYSTRING_H
#define MYSTRING_H
#pragma warning( disable : 4290 )

#include <iostream>

class MyString{
	size_t m_lng; //nb of char
	char* m_head; //everytime i add  char i reallocate (no capacity)
	char* getcin(std::istream&) const throw(std::bad_alloc); //get a char* from the std::cin
public:
	/*constructors & destructors*/
	MyString() throw(std::bad_alloc);
	MyString(const MyString&) throw(std::bad_alloc);
	MyString(const char*) throw(std::bad_alloc);
	MyString(MyString&&) noexcept;
	~MyString();

	/*overloads*/
	MyString& operator=(const MyString&) throw(std::bad_alloc);
	MyString& operator=(MyString&&) noexcept;
	char operator[](unsigned) const throw(const char*); //for const MyString; 
	char operator[](unsigned) throw(const char*);
	operator long() const throw(const char*);
	MyString& operator+=(const MyString&) throw(std::bad_alloc);

	/*utilities*/
	size_t length() const noexcept;
	MyString& toupper();
	MyString& tolower();
	char get(unsigned) const throw(const char*); //from 1 to length()
	void display() const;
	void swap(MyString&);
	MyString& pushback(char) throw(std::bad_alloc);
	MyString& pushfront(char) throw(std::bad_alloc);
	char popback() throw(std::bad_alloc); //return '\0' when MyString is empty
	char popfront() throw(std::bad_alloc); //return '\0' when MyString is empty

	/*friends*/
	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&) throw (std::bad_alloc);
	friend MyString operator+(const MyString&, const MyString&) throw(std::bad_alloc);
	friend bool operator==(const MyString&, const MyString&) noexcept; //didnt test all comparisons bellow
	friend bool operator!=(const MyString&, const MyString&) noexcept; 
	friend bool operator<(const MyString&, const MyString&) noexcept;
	friend bool operator>(const MyString&, const MyString&) noexcept;
	friend bool operator<=(const MyString&, const MyString&) noexcept;
	friend bool operator>=(const MyString&, const MyString&) noexcept;
};

#endif // MYSTRING_H