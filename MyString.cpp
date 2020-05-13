#include "MyString.h"
#include <cctype>

#define DEBUG

/*Construtors*/

MyString::MyString():
	m_lng(0),
	m_head(new char('\0'))
{
#ifdef DEBUG
	std::cout << "default constructor" << std::endl;
#endif 
}

MyString::MyString(const MyString &str):
	m_lng(str.length()),
	m_head(new char[length() + 1])
{
#ifdef DEBUG
	std::cout << "copy constructor: " << str << std::endl;
#endif
	std::memcpy(m_head, str.m_head, length() + 1);
}

MyString::MyString(const char* str):
	m_lng(strlen(str)),
	m_head(new char[length() + 1])
{
#ifdef DEBUG
	std::cout << "const char* constructor: " << str << std::endl;
#endif
	std::memcpy(m_head, str, length() + 1);
}

MyString::MyString(MyString&& rs) noexcept:
	m_lng(std::move(rs.m_lng)),
	m_head(std::move(rs.m_head))
{
#ifdef DEBUG
	std::cout << "move constructor" << std::endl;
#endif // DEBUG
	rs.m_head = nullptr;
}

MyString::~MyString() noexcept
{
#ifdef DEBUG
	if (m_head == nullptr)	std::cout << "destructor on stolen object" << std::endl;
	else					std::cout << "destructor on : " << m_head << " ln: " << length() << std::endl;
#endif
	delete[] m_head;
}

/*overloads*/

MyString& MyString::operator=(const MyString& other)
{
#ifdef DEBUG
	std::cout << "operator=&" << std::endl;
#endif
	if (this != &other) { 
		delete[] m_head;
		m_lng = other.length();
		m_head = new char[length() + 1];
		std::memcpy(m_head, other.m_head, length() + 1);
	}
	return *this;
}

MyString& MyString::operator=(MyString&& rother) noexcept
{
#ifdef DEBUG
	std::cout << "operator=&&" << std::endl;
#endif
	if (this != &rother) { 
		delete[] m_head;
		m_lng = std::move(rother.m_lng);
		m_head = std::move(rother.m_head);
		rother.m_lng = 0;
		rother.m_head = nullptr;
	}
	return *this;
}

char MyString::operator[](unsigned index) const throw(const char*)
{
#ifdef DEBUG
	std::cout << "char operator[] const" << std::endl;
#endif
	if (index < length()) return m_head[index];
	else throw "Invalid index";
}

char MyString::operator[](unsigned index) throw(const char*)
{
#ifdef DEBUG
	std::cout << "char& operator[]" << std::endl;
#endif
	if (index < length()) return m_head[index];
	else throw "Invalid Index";
}

MyString::operator long() const throw(const char*)
{
	long nb = 0;
	long dec = 1;
	for (int i = (int)length() - 1; i >= 0; --i) {
		if (m_head[i] < '0' || m_head[i] > '9') throw("Invalid number");
		else {
			nb += (m_head[i] - 48) * (dec);
			dec *= 10;
		}
	}
	return nb;
}

MyString& MyString::operator+=(const MyString& other)
{
	size_t totalLn = length() + other.length();
	char* tmp = new char[totalLn + 1];
	std::memcpy(tmp, m_head, length());
	std::memcpy(tmp + length(), other.m_head, other.length());
	tmp[totalLn] = '\0';
	delete[] m_head;
	m_head = tmp;
	m_lng = totalLn;
	return *this;
}

/*utilities*/

MyString& MyString::toupper()
{
	for (size_t i = 0; i < length(); ++i) m_head[i] = std::toupper(m_head[i]);
	return *this;
}

MyString& MyString::tolower()
{
	// (*this)[i] = std::tolower((*this)[i]); //2 fois le nombre d'appels operator[] bcp trop de call
	for (size_t i = 0; i < length(); ++i) m_head[i] = std::tolower(m_head[i]);
	return *this;
}

char MyString::get(unsigned i) const throw(const char*)
{
	return (*this)[--i];
}

size_t MyString::length() const noexcept
{
	return m_lng;
}

void MyString::display() const
{
	std::cout << *this << std::endl;
}

void MyString::swap(MyString& other)
{
	std::swap(m_head, other.m_head);
	std::swap(m_lng, other.m_lng);
}

MyString& MyString::pushback(char c)
{
	char* tmp = new char[length() + 2];
	std::memcpy(tmp, m_head, length());
	tmp[length()] = c;
	tmp[++m_lng] = '\0';
	delete[] m_head;
	m_head = tmp;
	return *this;
}

MyString& MyString::pushfront(char c)
{
	char* tmp = new char[length() + 2];
	std::memcpy(tmp + 1, m_head, length() + 1);
	tmp[0] = c;
	++m_lng;
	delete[] m_head;
	m_head = tmp;
	return *this;
}

char MyString::popback()
{
	char c = '\0';
	if(length()) 
	{
		char c = (*this)[(unsigned)length() - 1];
		char* tmp = new char[length()];
		--m_lng;
		std::memcpy(tmp, m_head, length());
		tmp[length()] = '\0';
		delete[] m_head;
		m_head = tmp;
	}
	return c;

}

char MyString::popfront()
{
	char c = '\0';
	if (length() > 0) {
		c = (*this)[0];
		char* tmp = new char[length()];
		std::memcpy(tmp, m_head + 1, length());
		--m_lng;
		delete[] m_head;
		m_head = tmp;
	}
	return c;
}

/*friends*/

std::ostream& operator<<(std::ostream& out, const MyString& s)
{
	return out << s.m_head;
}

std::istream& operator>>(std::istream& in, MyString& s)
{
	char * newstr = s.getcin(in);

	s = std::move(MyString(newstr));

	return in;
}

MyString operator+(const MyString& s1, const MyString& s2)
{
	MyString s = s1;
	s += s2;
	return s;
}

bool operator==(const MyString& s1, const MyString& s2) noexcept
{
	if (s1.length() != s2.length()) return false;
	for (size_t i = 0; i < s1.length(); ++i) {
		if (s1.m_head[i] != s2.m_head[i]) return false;
	}
	return true;
}

bool operator!=(const MyString& s1, const MyString& s2) noexcept
{
	return !(s1 == s2);
}

bool operator<(const MyString& s1, const MyString& s2) noexcept
{
	size_t i = 0;
	for (; i < s1.length() && i < s2.length(); ++i) {

		if (toupper(s1.m_head[i]) < toupper(s2.m_head[i])) return true;
		else {
			if (toupper(s1.m_head[i]) > toupper(s2.m_head[i])) return false;
		}

	}
	if (i != s2.length() && i == s1.length()) {
		return true;
	}
	return false;
}

bool operator>(const MyString& s1, const MyString& s2) noexcept
{
	return s2 < s1;
}

bool operator<=(const MyString& s1, const MyString& s2) noexcept
{
	return !(s1 > s2);
}

bool operator>=(const MyString& s1, const MyString& s2) noexcept
{
	return !(s2 > s1);
}

char* MyString::getcin(std::istream& in) const
{
	size_t capacity = 20;
	char* buffer = new char[capacity];
	unsigned i = 0;
	char c;
	scanf_s("%c", &c, 1);
	while (c != '\n') {

		buffer[i++] = c;

		if (i == capacity) {
			capacity *= 2;
			char* tmp = new char[capacity];
			std::memcpy(tmp, buffer, i);
			delete[] buffer;
			buffer = tmp;
		}

		scanf_s("%c", &c, 1);
	}

	buffer[i] = '\0';
	return buffer;
}