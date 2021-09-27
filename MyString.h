#pragma once
#include <iostream>

class MyString
{
public:
	//конструкторы, инициализация, оптимизация
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other);

	//деструктор, освобождает память
	~MyString() { delete[] str; }

	//перегрузка нужных в работе и использовании операторов
	MyString operator+(const MyString& other);

	MyString& operator=(const MyString & other);

	char& operator[](const int index);

	bool operator==(const MyString& other);

	bool operator!=(const MyString& other);

	friend std::ostream& operator<<(std::ostream& out, const MyString& other);

	friend std::istream& operator>>(std::istream& in, MyString& other);

	//фонкция возвращает длину строки
	int lenStr() { return length; }

	//функция "разворачивания" строки
	void reverse();

	//баланс скобок
	int balanceBrackets(); 

	//поиск подстроки, возвращение позиции начала подстроки
	int occurenceSubstring(const MyString& other);

	//вставка подсроки в основную строку оп конкретному индексу
	void insert(const MyString& other, const int posInsert);

	//запись в объект подстроки, определённой длины, начиная с конкретног оместа
	void cutString(MyString& tooCopy, const int lengthCopy, const int posFirstElem);

private:
	char* str;//сама строка
	int length;//длина этой строки
};

