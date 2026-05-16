#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

const int P = 10;

int get_digit(int num, int pos, int max_digits)
{
	std::string num_str = std::to_string(std::abs(num));

	while (num_str.length() < max_digits)
	{
		num_str = "0" + num_str;
	}

    if (num < 0 && pos == 0) 
    {
        return 0; 
    }

    int actual_pos = pos;
    if (num < 0) actual_pos = pos - 1;
    if (actual_pos >= 0 && actual_pos < num_str.length()) 
	{
        return num_str[actual_pos] - '0';
    }

    return 0;
}

void MSD_sort(std::vector<int>& arr, int left, int right, int pos, int max_digits)
{
    if (left >= right || pos >= max_digits) 
	{
        return;
    }

    std::vector<std::vector<int>> b(P);

    for (int i = left; i <= right; i++) 
    {
        int digit = get_digit(arr[i], pos, max_digits);
        b[digit].push_back(arr[i]);
    }

    int index = left;
    for (int i = 0; i < P; i++) 
	{
        for (int val : b[i]) {
            arr[index++] = val;
        }
    }

    index = left;
    for (int i = 0; i < P; i++) 
    {
        if (!b[i].empty()) 
		{
            int b_start = index;
            int b_end = index + b[i].size() - 1;
            MSD_sort(arr, b_start, b_end, pos + 1, max_digits);
            index += b[i].size();
        }
    }
}

void sort(std::vector<int>& arr, int N)
{
    int max_el = arr[0];
    int min_el = arr[0];
    for (int i = 0; i < N; i++)
    {
        if (arr[i] < min_el) min_el = arr[i];
        if (arr[i] > max_el) max_el = arr[i];
    }

    int max_digits, temp, temp1;

    temp = std::abs(max_el);
    temp1 = std::abs(min_el);
    std::string temp_str = std::to_string(temp);
    std::string temp_str1 = std::to_string(temp1);

    if (temp_str.length() >= temp_str1.length())
    {
        max_digits = temp_str.length();
    }
    else
    {
        max_digits = temp_str1.length();
    }

    if (min_el < 0)
    {
        std::vector<int> negatives, positives;
        for (int i = 0; i < N; i++)
        {
            if (arr[i] < 0) negatives.push_back(arr[i]);
            else positives.push_back(arr[i]);
        }

        if (!negatives.empty())
        {
            std::vector<int> abs_negatives;
            for (int i = 0; i < negatives.size(); i++)
            {
                abs_negatives.push_back(std::abs(negatives[i]));
            }

            MSD_sort(abs_negatives, 0, abs_negatives.size() - 1, 0, max_digits);

            negatives.clear();
            for (int i = abs_negatives.size() - 1; i >= 0; i--)
            {
                negatives.push_back(-abs_negatives[i]);
            }
        }

        if (!positives.empty())
        {
            MSD_sort(positives, 0, positives.size() - 1, 0, max_digits);
        }

        arr.clear();
        arr.insert(arr.end(), negatives.begin(), negatives.end());
        arr.insert(arr.end(), positives.begin(), positives.end());
    }
    else 
    {
        MSD_sort(arr, 0, arr.size() - 1, 0, max_digits);
    }
}

//task - MSD
int main() 
{
    int N, temp, temp1;
    std::vector<int> arr;
    std::cout << "Enter N: "; std::cin >> N;
    std::cout << "Enter N elements: ";
    for (int i = 0; i < N; i++)
    {
        std::cin >> temp;
        arr.push_back(temp);
    }
    
    sort(arr, N);

    std::cout << "\nResult: ";
    for (int i = 0; i < N; i++)
    {
        std::cout << arr[i] << " ";
    }

    return 0;
}
