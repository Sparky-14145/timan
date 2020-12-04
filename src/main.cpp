#include <cstdio>
#include <ctime>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <fstream>

#include "task.h"
#include "timeman.h"

std::priority_queue<task> q;

void init()
{
	task tas;

	std::fstream in;
	in.open("list.txt", std::ios_base::in);
	if (!in)
	{
		in.setstate(std::ios_base::goodbit);
		in.open("list.txt", std::ios_base::in | std::ios_base::out);
	}
	while (in >> tas)
	{
		q.push(tas);
	}

	in.close();

	std::cout << "System is ready.\n";
}

int main()
{
	init();
	std::string command;
	task tas;

	while (1)
	{
		std::cout << "> ";
		std::cin >> command;
		if (command == "exit")
			break;
		else if (command == "add")
		{
			std::cout << "Please write down the task:\nname level deadline(year month day)\n";
			std::cin >> tas;
			q.push(tas);
		}
		else if (command == "check")
		{
			if (q.empty())
				std::cout << "You have no task.\n";
			else
			{
				tas = q.top();
				tas.printTo(std::cout);
				std::string c;
				std::cout << "\nsolved? ([y],n)\n";
				std::cin >> c;
				if (c == "y")
					q.pop();
			}
		}
		else if (command == "list")
		{
			std::ifstream fin("list.txt");
			while (fin >> tas)
			{
				tas.printTo(std::cout);
			}
			fin.close();
		}
		else
		{
			std::cout << "Unknown command. Check your input!" << std::endl;
			continue;
		}
	}

	std::ofstream out("list.txt");
	while (!q.empty())
	{
		tas = q.top();
		out << tas << '\n';
		q.pop();
	}

}
