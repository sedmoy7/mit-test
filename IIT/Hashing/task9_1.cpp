#include <iostream>
//#include <time.h>
//#include <stdlib.h>
//#include <stdio.h>
#include <vector>
#include <string>
//#include <map>
#include <fstream>
//#include <cmath>
//#include <queue>
//#include <math.h>
//#include <iomanip>
//#include <cctype>
//#include <iterator>
//#include <numeric>
//#include <functional>
//#include <fstream>
//#include <process.h>
//#include <typeinfo>
//#include "verylong.h"

//using namespace std;

struct Date
{
	int d, m, y;

	bool operator >(Date x)
	{
		if (y > x.y) return true;
		else if (y == x.y && m > x.m) return true;
		else if (y == x.y && m == x.m && d > x.d) return true;
		return false;
	}

	bool operator == (Date x)
	{
		if (y == x.y && m == x.m && d == x.d) return true;
		return false;
	}
};

struct people
{
	std::string surname;
	std::string pos;
	Date date_ob;
	int xp;
	int sal;

	bool operator == (people x)
	{
		if (surname.compare(x.surname) == 0 && date_ob == x.date_ob && pos.compare(x.pos) == 0) return true;
		return false;
	}
};

Date str_to_date(std::string str) {
	Date temp;
	std::string str1 = str.substr(0, 2);
	const char* sd = str1.c_str();
	int dd = atoi(sd);
	temp.d = dd;

	str1 = str.substr(3, 2);
	sd = str1.c_str();
	int mm = atoi(sd);
	temp.m = mm;

	str1 = str.substr(6, 4);
	sd = str1.c_str();
	dd = atoi(sd);
	temp.y = dd;

	return temp;
}

void print(people x)
{
	std::cout << x.surname << " " << x.pos << " " << x.date_ob.d << "." << x.date_ob.m << "." << x.date_ob.y << " " << x.xp << " " << x.sal << std::endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
struct list
{
	people inf;
	list* next;
	list* prev;
};

void push(list*& h, list*& t, people x)
{
	list* r = new list;
	r->inf = x;
	r->next = NULL;
	if (!h && !t)
	{
		r->prev = NULL;
		h = r;
	}
	else
	{
		t->next = r;
		r->prev = t;
	}
	t = r;
}


void print(list* h, list* t)
{
	list* p = h;
	while (p)
	{
		//std::cout << "\n";
		print(p->inf);
		p = p->next;
	}
}


list* find(list* h, list* t, people x)
{
	list* p = h;
	while (p)
	{
		if (p->inf == x) break;
		p = p->next;
	}
	return p;
}

void insert_after(list*& h, list*& t, list* r, people y)
{
	list* p = new list;
	p->inf = y;
	if (r == t)
	{
		p->next = NULL;
		p->prev = r;
		r->next = p;
		t = p;
	}
	else
	{
		r->next->prev = p;
		p->next = r->next;
		p->prev = r;
		r->next = p;
	}
}

void del_node(list*& h, list*& t, list* r)
{
	if (r == h && r == t)
	{
		h = t = NULL;
	}
	else if (r == h)
	{
		h = h->next;
		h->prev = NULL;
	}
	else if (r == t)
	{
		t = t->prev;
		t->next = NULL;
	}
	else
	{
		r->next->prev = r->prev;
		r->prev->next = r->next;
	}
	delete r;
}

const int N = 20;
const int alpha = 2;
const int M = 10;

int main() {
	int k, tmp;

	std::vector<std::pair<list*, list*>> hash;
	hash.resize(M);
	for (int i = 0; i < M; i++)
	{
		hash[i].first = NULL;
		hash[i].second = NULL;
	}

	std::vector<people> a;
	people temp;
	std::string tmp_dt;
	std::ifstream fin;
	fin.open("in_file.txt");
	while (!fin.eof())
	{
		fin >> temp.surname;
		fin >> temp.pos;
		fin >> tmp_dt;
		temp.date_ob = str_to_date(tmp_dt);
		fin >> temp.xp;
		fin >> temp.sal;
		a.push_back(temp);
		//print(temp);
	}

	for (int i = 0; i < N; i++)
	{
		k = a[i].date_ob.d % M;
		push(hash[k].first, hash[k].second, a[i]);
	}

	std::cout << "\nEnter the day of birth of human that you want to find and delete: ";
	std::cin >> tmp;
	k = tmp % M;

	/*
	std::cout << "\nEnter information about human that you want to find and delete: ";
	std::cin >> temp.surname;
	std::cin >> temp.pos;
	std::cin >> tmp_dt;
	temp.date_ob = str_to_date(tmp_dt);
	std::cin >> temp.xp;
	std::cin >> temp.sal;
	k = temp.date_ob.d % M;
	*/

	//std::cout << hash[k].first->inf.surname;

	list* p = hash[k].first;

	print(hash[k].first, hash[k].second);

	while (p)
	{
		if(p->inf.date_ob.d == tmp)
		//if (p->inf == temp)
		{
			std::cout << "\nResult: ";
			print(p->inf);
			del_node(hash[k].first, hash[k].second, p);
			print(hash[k].first, hash[k].second);
			break;
		}
		p = p->next;
	}

    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.