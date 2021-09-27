#pragma once
#include <iostream>

class MyString
{
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other);

	~MyString() { delete[] str; }

	MyString operator+(const MyString& other);

	MyString& operator=(const MyString & other);

	char& operator[](const int index);

	bool operator==(const MyString& other);

	bool operator!=(const MyString& other);

	friend std::ostream& operator<<(std::ostream& out, const MyString& other);

	friend std::istream& operator>>(std::istream& in, MyString& other);

	int lenStr() { return length; }

	void reverse();

	// прототип функции проверки баланса парных скобок
	int balanceBrackets(); 

	int occurenceSubstring(const MyString& other);

	void insert(const MyString& other, const int posInsert);

	void cutString(MyString& tooCopy, const int lengthCopy, const int posFirstElem);

private:
	char* str;
	int length;
};

