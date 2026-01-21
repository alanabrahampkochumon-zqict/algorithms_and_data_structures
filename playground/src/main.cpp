#include <functional>
#include <iostream>

#include <InsertionSort.h>

// Function Declarations

template<typename T>
void getInput(const int& limit, std::vector<T>& result);

template<typename T>
void printVector(const std::vector<T>& vec);

static void printMainMenu();
static void printSortingMenu();
static void startApplication();




// Struct and Classes

struct MenuItem
{
	std::string label;
	std::function<void()> action;

	
};

static std::ostream& operator<<(std::ostream& os, const MenuItem& item)
{
	os << item.label;
	return os;
}


// Global Variables

MenuItem mainMenuItems[] = {
	{"1. Sorting", printSortingMenu}
};

MenuItem sortingMenuItems[2] = {
	// {"1. Sorting", Algorithms::InsertionSort::sort<int>}
};


// Function Definitions

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
	std::cout << " ------------------------------------\n\n";
	std::cout << "Select an option from the list\n";

	bool running = true;

	for (auto& item: mainMenuItems)
	{
		std::cout << item << "\n";
	}
	while (running)
	{
		unsigned char option;
		std::cin >> option;

		if (option && option > 0 && option <= std::size(mainMenuItems))
			mainMenuItems[option].action();
	}
}

static void printSortingMenu()
{
	std::cout << " ------------------------------------\n";
	std::cout << "|        Sorting Algorithms          |\n";
	std::cout << " ------------------------------------\n\n";
	std::cout << "Select an option from the list\n";
	std::cout << "1. Insertion Sort\n";
	std::cout << "999. Go Back\n";
}



static void startApplication(bool& running)
{

	while (running)
	{
		printMainMenu();
		printSortingMenu();
		running = false;
	}
}

static void printHeader()
{
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "|        Welcome to CPP Algorithm Playground          |\n";
	std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n\n";
}

int main()
{
	printHeader();

	bool running = true;

	startApplication(running);
}
