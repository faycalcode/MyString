#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>

class MyString{
	size_t m_lng; //nb of char
	char* m_head; //everytime i add  char i reallocate (no capacity)
	char* getcin(std::istream&) const; //get a char* from the std::cin
public:
	/*constructors & destructors*/
	MyString();
	MyString(const MyString&);
	MyString(const char*);
	MyString(MyString&&) noexcept;
	~MyString() noexcept;

	/*overloads*/
	MyString& operator=(const MyString&);
	MyString& operator=(MyString&&) noexcept;
	char operator[](unsigned) const; //for const MyString; 
	char operator[](unsigned);
	operator long() const;
	MyString& operator+=(const MyString&);

	/*utilities*/
	size_t length() const noexcept;
	MyString& toupper();
	MyString& tolower();
	char get(unsigned) const; //from 1 to length()
	void display() const;
	void swap(MyString&);
	MyString& pushback(char);
	MyString& pushfront(char);
	char popback(); //return '\0' when MyString is empty
	char popfront(); //return '\0' when MyString is empty

	/*friends*/
	friend std::ostream& operator<<(std::ostream&, const MyString&);
	friend std::istream& operator>>(std::istream&, MyString&);
	friend MyString operator+(const MyString&, const MyString&);
	friend bool operator==(const MyString&, const MyString&) noexcept;
	friend bool operator!=(const MyString&, const MyString&) noexcept; 
	friend bool operator<(const MyString&, const MyString&) noexcept;
	friend bool operator>(const MyString&, const MyString&) noexcept;
	friend bool operator<=(const MyString&, const MyString&) noexcept;
	friend bool operator>=(const MyString&, const MyString&) noexcept;
};

#endif // MYSTRING_H