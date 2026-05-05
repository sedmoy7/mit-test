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

const int N = 20;
const int M = 25;
const int c1 = 1;
const int c2 = 3;

//Основная — квадратичное хеширование, вспомогательная — метод деления по стажу
int main() {
	int k, tmp;

	std::vector<people> hash;
	hash.resize(M);

	for (int i = 0; i < M; i++)
	{
		hash[i].xp = -100;
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

	int j, p;
	for (int i = 0; i < N; i++)
	{
		k = a[i].xp % M;
		j = 0;
		for (int iterat = 0; iterat < M; iterat++) 
		{
			p = (k + c1 * j + c2 * j * j) % M;
			if (hash[p].xp == -100)
			{
				hash[p] = a[i];
				break;
			}
			else { j++; }
		}
	}

	std::cout << "Hash table:\n";
	for (int i = 0; i < M; i++)
	{
		std::cout << i << ": ";
		if (hash[i].xp == -100)
		{
			std::cout << "NULL\n";
		}
		else
		{
			std::cout << hash[i].xp << "\n";
		}
	}

	j = 0;
	std::cout << "\nEnter the experience of human that you want to find: ";
	std::cin >> tmp;
	k = tmp % M;
	std::cout << "\nResult:\n";
	while(hash[p].xp!=-100)
	{
		p = (k + c1 * j + c2 * j * j) % M;
		if (hash[p].xp == tmp)
		{
			print(hash[p]);
			//break;
			j++;
		}
		else { j++; }
	}
	
	/*
	std::cout << "\nEnter information about human that you want to find: ";
	std::cin >> temp.surname;
	std::cin >> temp.pos;
	std::cin >> tmp_dt;
	temp.date_ob = str_to_date(tmp_dt);
	std::cin >> temp.xp;
	std::cin >> temp.sal;
	k = temp.xp % M;

	while (hash[p].xp != -100)
	{
		p = (k + c1 * j + c2 * j * j) % M;
		if (hash[p].xp == temp.xp)
		{
			std::cout << "\nResult:\n";
			print(hash[p]);
			break;
		}
		else { j++; }
	}
	*/
	
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