#pragma once
#include <atomic>
#include <iostream>
using namespace std;

class counter
{
	atomic <unsigned int> count; // ��� �������� ������ ����������� ���������� ������ std::atomic_uint. 
public:
	counter() // ����������� ��� �������������
	{
		this->count = 1;
	}
	explicit counter(unsigned int c) // ����������� ��� ������ ��������
	{
		this->count = c;
	}
	~counter() = default; // ����������
	void increase() { count++; }
	void decrease() { count--; }
	int get() const 
	{
		return static_cast <int> (count); // �������� � ���� int
	}
};
