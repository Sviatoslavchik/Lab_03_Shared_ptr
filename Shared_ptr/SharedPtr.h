#pragma once
#include <atomic>
#include <iostream>
#include "counter.h"
using namespace std;

template <typename T>

class SharedPtr 
{
	counter* count; // Счетчик на количество обьектов, на который сс-ся количество обьектов
	T* data; // Какие-то данные шаблона Т
public:
	SharedPtr() 
	{
		this->data = nullptr;
		this->count = nullptr;
	}
	SharedPtr(T* ptr) 
	{
		cout << "Helo";
		this->data = ptr;
		this->count = new counter(1);
	}
	SharedPtr(const SharedPtr& r) // Конструктор копирования
	{
		cout << "Helo1";
		this->data = r.data;
		this->count = r.count;
		count->increase();
	}
	SharedPtr(SharedPtr&& r) // Конструктор перемещения
	{
		cout << "Helo2";
		this->data = r.data;
		this->count = r.count;
		count->increase();
		r.data = nullptr;
		r.count = nullptr;
	}
	~SharedPtr() 
	{
		if (*this) // Если есть еще обьекты ссылки
		{
			count->decrease();
		}
		if (!count) // Если нет обьектов
		{
			cout << "kfkfk";
			delete data;
			delete count;
		}
	}
	// Перегрузка оператора =
	auto operator = (const SharedPtr & r)->SharedPtr<T> & 
	{
		if (!count) 
		{
			delete data;
			delete count;
		}
		data = r.data;
		count = r.count;
		if (*this) 
		{
			count->increase();
		}
		return *this;
	}
	auto operator = (SharedPtr && r)->SharedPtr & 
	{
		if (!count) 
		{
			delete data;
			delete count;
		}
		data = r.data;
		count = r.count;
		r.data = nullptr;
		r.count = nullptr;
		return *this;

	}

	// Проверяет, указывает ли указатель на объект
	operator bool() const 
	{
		return !(data == nullptr);
	}
	auto operator*() const->T & // Перегрузка оператора указателя
	{
		if (!*this) 
		{
			throw logic_error("Attempt to get value of nullptr");
		}
		return *data;
	}
	auto operator->() const->T* // Оператор взятия значения
	{
		return data; 
	}
	auto get()->T* { // Get
		return data;
	}
	void reset() 
	{ // Сбросить
		if (!*this) return;
		count->decrease();
		if (count == nullptr) 
		{
			delete count;
			delete data;
		}
		count = nullptr;
		data = nullptr;
	}
	void reset(T* ptr)
	{
		if (*this) 
		{
			count->decrease();
			if (*count == 0) 
			{
				delete count;
				delete data;
			}
		}
		count = new counter(1);
		data = ptr;
	}
	void swap(SharedPtr& r) 
	{ // Поменять местами
		if (data == r.data) return;
		auto buf = r;
		r = *this;
		*this = buf;
	}
	// Возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
	auto use_count() const->size_t 
	{
		if (!*this) return 0;
		return static_cast<size_t>(count->get());
	}
};