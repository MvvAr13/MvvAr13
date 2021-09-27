#include "MyString.h"

MyString::MyString()
{
	str = nullptr;
	length = 0;
}

MyString::MyString(const char* str)
{
	this->length = strlen(str);

	this->str = new char[length + 1];

	for (int i = 0; i < length; i++)
		this->str[i] = str[i];

	this->str[length] = '\0';
}

MyString::MyString(const MyString& other)
{
	this->length = other.length;

	for (int i = 0; i < this->length; i++)
		this->str[i] = other.str[i];
}

MyString::MyString(MyString&& other)
{
	this->length = other.length;
	this->str = other.str;
	other.str = nullptr;
}

MyString MyString::operator+(const MyString& other)
{
	MyString newStr;
	newStr.length = this->length + other.length;
	int i = 0;

	newStr.str = new char[newStr.length];

	for (; i < this->length; i++)
		newStr.str[i] = this->str[i];

	for (int j = 0; j < other.length; j++, i++)
		newStr.str[i] = other.str[j];
		
	return newStr;
}

MyString& MyString::operator=(const MyString& other)
{
	this->length = other.length;

	for (int i = 0; i < this->length; i++)
		this->str[i] = other.str[i];

	return *this;
}

char& MyString::operator[](const int index)
{
	return str[index];
}

bool MyString::operator==(const MyString& other)
{
	if (this->length != other.length)
		return false;

	for (int i = 0; i < this->length; i++)
		if (this->str[i] != other.str[i])
			return false;

	return true;
}

bool MyString::operator!=(const MyString& other)
{
	return !(this->operator==(other));
}

void MyString::reverse()
{
	char tmp;

	for (int i = 0; i < length/2; i++)
		if (i != (length - 1 - i))
		{
			tmp = str[length - 1 - i]; // символ с конца строки сохраняем во временную переменную
			str[length - 1 - i] = str[i];
			str[i] = tmp;
		}
}

int MyString::balanceBrackets()
{
	int countOpen = 0;
	int countClose = 0;

	for (int i = 0; i < length; i++){
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
			countOpen++;
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
			countClose++;
	}

	if (countOpen == countClose && countOpen > 0 && countClose > 0)
		return 1;
	else if (countOpen != countClose)
		return 0;
	else
		return -1;
}

int MyString::occurenceSubstring(const MyString& other)
{
	int position = 0;

	for (int i = 0, j = 0; i < this->length && j < other.length; i++)
	{
		if (this->str[i] == other.str[j]){
			//if(j == 0)
			position = i;
			j++;
		}
	}
	position -= other.length-1;
	return position;
}

void MyString::insert(const MyString& other, const int posInsert)
{
	char* buf = new char[this->length+1];
	int sizeBuf = this->length + 1;
	int i = 0;

	for (int i = 0; i < this->length; i++)
		buf[i] = this->str[i];
	buf[this->length] = '\0';

	this->str = new char[this->length + other.length + 1];
	this->length = this->length + other.length + 1;

	while (i != posInsert)
	{
		this->str[i] = buf[i];
		i++;
	}
	
	int tmpI = i;

	for (int j = 0; i < tmpI + other.length, j < other.length; i++, j++)
		this->str[i] = other.str[j];

	for (int j = posInsert; i < this->length, j < sizeBuf; i++, j++)
		this->str[i] = buf[j];
}

void MyString::cutString(MyString& tooCopy, const int lengthCopy, const int posFirstElem)
{
	tooCopy.str = new char[lengthCopy+1];
	tooCopy.length = lengthCopy;

	for (int i = posFirstElem-1, j = 0; i < this->length || j < tooCopy.length; i++, j++)
		tooCopy.str[j] = this->str[i];

	tooCopy.str[lengthCopy] = '\0';
}

std::ostream& operator<<(std::ostream& out, const MyString& other)
{
	out << other.str << std::endl;

	return out;
}

std::istream& operator>>(std::istream& in, MyString& other)
{
	std::cout << "Enter length line: ";
	in >> other.length;

	other.str = new char[other.length+1];

	std::cin.ignore();

	std::cout << "Enter your line: ";
	for (int i = 0; i < other.length; i++)
		std::cin.get(other.str[i]);


	other.str[other.length] = '\0';

	other.length = strlen(other.str);

	return in;
}