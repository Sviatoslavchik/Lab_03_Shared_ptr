#include "SharedPtr.h"
#include "counter.h"
#include <iostream>
using namespace std;
template< class T > class shared_ptr;

int main() 
{
	cout << "With library " << endl;
	int* ap = new int(5); 
	 

	std::shared_ptr<int> sh1(ap);
	std::shared_ptr<int> sh2(sh1);
	std::shared_ptr<int> sh3(sh2);
	std::shared_ptr<int> sh4(sh3);
	sh3.reset();
	sh4.reset();

	// constructor with object
	{
		std::shared_ptr<int> sh5(sh1);
		std::cout << sh1.use_count() << '\n';
		std::cout << sh5.use_count() << '\n';
	}
	std::cout << sh2.use_count() << '\n';

	cout << endl << "With my class ptr " << endl;
	int* a = new int(5);
	SharedPtr<int> P1(a);
	SharedPtr<int> P2(P1);
	SharedPtr<int> P3(P2);
	SharedPtr<int> P4(P3);
	P3.reset(); // Сбросили
	P4.reset(); // Сбросили подсчет
	{
		SharedPtr<int> P5(P1);
		cout << P1.use_count() << endl;
	}
	cout << P2.use_count();
	cout << endl;
	system("pause");
	return 0;
}

int main()
{

}