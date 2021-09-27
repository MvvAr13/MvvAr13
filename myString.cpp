#include "MyString.h"

//инициализация данных стартовыми значениями
MyString::MyString()
{
	str = nullptr;
	length = 0;
}

//конструктор с параметрами, в параметр передаётся строка.
//длина высчитывается автоматически
MyString::MyString(const char* str)
{
	//находим длину переданой строки
	this->length = strlen(str);

	//выделения памяти под строку
	this->str = new char[length + 1];

	//поэлементное заполнение строки класса
	for (int i = 0; i < length; i++)
		this->str[i] = str[i];

	//в конец добавляем нуль терминатор, для корректной работы с строкой
	this->str[length] = '\0';
}

//констуктор копии, нужен для адекватного копирования объектов
//без него в объект, в который копируем, присваевается ссылка на копируемый объект
//при выхода с области видимости одного из них полезут ошибки и возможна утечка данных
MyString::MyString(const MyString& other)
{
	//копирование длины строки
	this->length = other.length;

	//поэлементное копирование из одной строки в другую
	for (int i = 0; i < this->length; i++)
		this->str[i] = other.str[i];
}

//конструктор перемещения
//нужен для оптимизации программы
//в особенности операции конкантенации
MyString::MyString(MyString&& other)
{
	this->length = other.length;
	this->str = other.str;
	other.str = nullptr;
}

//перегрузка оператора сложения
//нужно для возможности сложения(конкатенации) двух строк
MyString MyString::operator+(const MyString& other)
{
	//создание нового объекта, который будет хранить результат
	MyString newStr;
	//присваеваем длину, что равна суме конкатерирующих строк
	newStr.length = this->length + other.length;
	int i = 0;//индекс итераций по массиву, используется в нескольких циклах
	
	//выделяем новый размер для строки
	//размер выделяемой памяти на 1 больше, из-за нуль-терминатора в конце каждой строки
	newStr.str = new char[newStr.length+1];
	
	//поэлементно копируем элементы из текущего объекта в новый
	for (; i < this->length; i++)
		newStr.str[i] = this->str[i];

	//к масиву созданному после выполнения предыдущей операции
	//добавляем строку объекта переданного в функцыю
	for (int j = 0; j < other.length; j++, i++)
		newStr.str[i] = other.str[j];
	
	//нуль-терминатор в конце строки, для видимости того, где она заканчивается
	newStr.str[newStr.length] = '\0';
	//возвращение полученого массива
	return newStr;
}

//оператор присвоения
//реализован для возможности операции конкатенации и присваивания одной строки в другую
MyString& MyString::operator=(const MyString& other)
{
	//копируем длину 
	this->length = other.length;
	
	delete[] this->str;
	
	//выделяем новый размер памяти, перед чем не забывая удалить старый массив
	this->str = new char[this->length + 1];

	//поэлементное копирование в только что созданный новый массив
	for (int i = 0; i < this->length; i++)
		this->str[i] = other.str[i];

	//в конце добавляем нуль-терминатор
	this->str[this->length] = '\0';

	return *this;
}

//перегруженный оператор индексации элементов массива
//для возможности работы с конкретным элементом массива
char& MyString::operator[](const int index)
{
	return str[index];
}

//перегруженный оператор равенства
//используется при сравнении двух строк
bool MyString::operator==(const MyString& other)
{
	//если длина строк не равна возврааем false
	if (this->length != other.length)
		return false;
	
	//если длина их совпадает сравниваем строки(поэлементно)
	//если хоть одна пара символов разная возвращаем false
	for (int i = 0; i < this->length; i++)
		if (this->str[i] != other.str[i])
			return false;
	//если строки равны возвращаем true
	return true;
}


//перегруженный оператор неравенства
//вызывает сравнение на равенство и инвертирует его результат
bool MyString::operator!=(const MyString& other)
{
	return !(this->operator==(other));
}

//функция разворачивания строки
//начало строки меняется местами с концом и тд.
void MyString::reverse()
{
	//временная переменная использующаяся при перестановке местами
	char tmp;

	for (int i = 0; i < length/2; i++)
		//если итератор не перешёл половину массива
		if (i != (length - 1 - i))
		{
			//меняем первый и последний лемент местами
			tmp = str[length - 1 - i]; // символ с конца строки сохраняем во временную переменную
			str[length - 1 - i] = str[i];
			str[i] = tmp;
		}
}

//проверка баланся скобочек в сторке, учитываются все кроме угловых
//возвращаем 1 если баланс соблюдён
//0 если баланс не соблюдён
//-1 если скобок вообще нету
int MyString::balanceBrackets()
{
	int countOpen = 0;//счётчик всех открытых скобок
	int countClose = 0;//счётчик всех закрытых скобок

	for (int i = 0; i < length; i++){
		//если скобка была открыта, счётчик открытых скобок увеличиваем на 1
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
			countOpen++;
		//или же если скобка была закрыта увеличиваем соответствующий счётчик на 1
		else if (str[i] == ')' || str[i] == ']' || str[i] == '}')
			countClose++;
	}
	
	//проверяем на то соблюдён баланс или нет
	if (countOpen == countClose && countOpen > 0 && countClose > 0)
		return 1;
	else if (countOpen != countClose)
		return 0;
	else
		return -1;
}

//поиск позиции первого елемента подстроки в основной строке
int MyString::occurenceSubstring(const MyString& other)
{
	int position = 0;

	for (int i = 0, j = 0; i < this->length && j < other.length; i++)
	{
		//если символ основной строки равен символу подстроки
		//записываем символ символа основной строки
		//и увеличиваем итератор подстроки на 1
		if (this->str[i] == other.str[j]){
			//if(j == 0)
			position = i;
			j++;
		}
	}
	//на выходе получили номер последнего символа подстроки
	//для получения позиции первого елемента нужно 
	//отнять от позиции длину подстроки
	position -= other.length-1;
	return position;
}

//вставка подстроки в основную строку(по конкретному индексу)
void MyString::insert(const MyString& other, const int posInsert)
{
	//временный массив(далее буффер), для сохранения данных
	char* buf = new char[this->length+1];
	//размер буффера
	int sizeBuf = this->length + 1;
	int i = 0;//внешний счётчик

	//поэлементно копируем основной массив в буфер
	for (int i = 0; i < this->length; i++)
		buf[i] = this->str[i];
	buf[this->length] = '\0';

	//удаляем предыдущий массив, для избежания переполнения памяти
	delete[] this->str;

	//определяем новую длину строки
	this->length = this->length + other.length;
	//выделяем память на эту строку с учётом нуль-терминатора
	this->str = new char[this->length + 1];

	//пока итератор не равен позиции вставляемой строки
	//переписываем массив
	while (i != posInsert)
	{
		this->str[i] = buf[i];
		i++;
	}
	
	int tmpI = i;//переменная для хранения текущего значения итератора
	
	//записываем саму подстроку
	for (int j = 0; i < tmpI + other.length, j < other.length; i++, j++)
		this->str[i] = other.str[j];

	//в конец записываем оставшуюся часть основного массива
	for (int j = posInsert; i < this->length, j < sizeBuf; i++, j++)
		this->str[i] = buf[j];

	//добавления нуль-терминатора не нужно, поскольку он уже был добавлен в предыдущей строке
	delete[] buf;
}

//функция для копирования подстроки длиной в N с позиции k в новую строку
void MyString::cutString(MyString& tooCopy, const int lengthCopy, const int posFirstElem)
{
	//выделяем строку размером равным размеру подстроки
	tooCopy.str = new char[lengthCopy+1];
	//записываем длину
	tooCopy.length = lengthCopy;

	//записываем саму подстроку до тех пор пока строка не будет переписана
	//или если основной массив закончится
	for (int i = posFirstElem-1, j = 0; i < this->length || j < tooCopy.length; i++, j++)
		tooCopy.str[j] = this->str[i];

	//в конец добавляем нуль-терминатор
	tooCopy.str[lengthCopy] = '\0';
}

//перегрузка оператора вывода
//для удобства работы с объектами
std::ostream& operator<<(std::ostream& out, const MyString& other)
{
	out << other.str << std::endl;

	return out;
}

//перегрузка оператора ввода
//также для удобства работы со строкой
std::istream& operator>>(std::istream& in, MyString& other)
{
	//вводим длину строки
	std::cout << "Enter length line: ";
	in >> other.length;

	//выделяем память под саму строку
	other.str = new char[other.length+1];

	//игнорируем заблудший ендлайн, для корректного воода
	std::cin.ignore();

	//вводим саму строку
	std::cout << "Enter your line: ";
	for (int i = 0; i < other.length; i++)
		std::cin.get(other.str[i]);

	//в конец строки записываем нуль-терминатор
	other.str[other.length] = '\0';
	
	return in;
}
