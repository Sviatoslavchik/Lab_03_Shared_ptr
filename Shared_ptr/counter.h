#pragma once
#include <atomic>
#include <iostream>
using namespace std;

class counter
{
	atomic <unsigned int> count; // Для счетчика ссылок используйте переменную класса std::atomic_uint. 
public:
	counter() // Конструктор для инициализации
	{
		this->count = 1;
	}
	explicit counter(unsigned int c) // Конструктор для класса счетчика
	{
		this->count = c;
	}
	~counter() = default; // Деструктор
	void increase() { count++; }
	void decrease() { count--; }
	int get() const 
	{
		return static_cast <int> (count); // Привести к типу int
	}
};
