#include <iostream>

#include <InsertionSort.h>

template <typename T>
void getInput(const int& limit, std::vector<T>& result)
{
	for (int i = 0; i < result.size(); i++)
	{
		std::cin >> result[i];
	}
}

template <typename T>
void printVector(const std::vector<T>& vec)
{
	std::cout << "< ";
	for (size_t i = 0, size = vec.size(); i < size; i++)
	{
		const char delimiter = (i < size - 1) ? ',' : ' ';
		std::cout << vec[i] << delimiter;
	}
	std::cout << " >" << "\n";
}

static void printMainMenu()
{
	std::cout << " ------------------------------------\n";
	std::cout << "|            Algorithms              |\n";
	std::cout << " ------------------------------------\n\n\n";
	std::cout << "Select an option from the list\n";
	std::cout << "1. Sorting\n";
}

static void printSortingMenu()
{
	std::cout << " ------------------------------------\n";
	std::cout << "|        Sorting Algorithms          |\n";
	std::cout << " ------------------------------------\n\n\n";
	std::cout << "Select an option from the list\n";
	std::cout << "1. Insertion Sort\n";
	std::cout << "999. Go Back\n";
}

int main()
{
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "|        Welcome to CPP Algorithm Playground          |\n";
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n";
	
	bool running = true;

	while (running)
	{
		printMainMenu();
		printSortingMenu();
		running = false;
	}
}
