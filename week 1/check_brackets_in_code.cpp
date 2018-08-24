#include <iostream>
#include <fstream>
#include <stack>
#include <string>

struct Bracket {
	Bracket(char type, int position) : type(type), position(position)
	{

	}

	bool Matchc(char c) {
		if (type == '[' && c == ']')
			return true;
		if (type == '{' && c == '}')
			return true;
		if (type == '(' && c == ')')
			return true;
		return false;
	}

	char type;
	int position;
};

int main() {
	char choice;
	int max_files;
	std::string text, fileName, relativePath;
	std::cout << "'y' for custom input and any othe key for already savedfiles :   ";
	std::cin >> choice;
	if (choice == 'y')
		max_files = 1;
	else
		max_files = 54;
	for (int i = 1; i <= max_files; i++)
	{
		if (choice != 'y')
		{

			if (i < 10)
			{
				fileName = "0" + std::to_string(i);
			}
			else
			fileName = std::to_string(i);
			relativePath = "../../tests/" + fileName;
			std::ifstream sampleFile;
			sampleFile.open(relativePath);

			if (sampleFile.is_open())
			{
				getline(sampleFile, text);
				sampleFile.close();
			}
			else
			{
				std::cout << "can't open required file" << std::endl;
			
			}
		}
		else
		{
			getline(std::cin, text);
			getline(std::cin, text);
		}

		std::string ans = "Success";
		std::stack <Bracket> opening_brackets_stack;
		for (int position = 0; position < text.length(); ++position) {
			char next = text[position];
			Bracket toAdd = Bracket(next, position);

			if (next == '(' || next == '[' || next == '{') {

				opening_brackets_stack.push(toAdd);

			}

			if (next == ')' || next == ']' || next == '}') { 

				if (opening_brackets_stack.empty())
				{
					ans = std::to_string(position + 1);
					break;
				}
				Bracket toRemove = Bracket(next, position);
				toRemove = opening_brackets_stack.top();
				if (!toRemove.Matchc(next))
				{
					ans = std::to_string(position + 1);
					break;
				}
				opening_brackets_stack.pop();
			}
		}
		if (opening_brackets_stack.size() != 0 && ans == "Success")
		{
			Bracket temp = opening_brackets_stack.top();
			ans = std::to_string(temp.position + 1);
		}
		if(choice=='y')
			std::cout << ans << std::endl;
		else
		{
			std::ifstream checkFile;
			relativePath += ".a";
			checkFile.open(relativePath);

			if (checkFile.is_open())
			{
				getline(checkFile, text);
				if (ans == text) {
					std::cout << "File : " << fileName << " Ans = " << ans << " is true" << std::endl;
				}
				else
				{
					std::cout << "File : " << fileName << " Ans = " << ans << " is False. Actual Ans is " << text << std::endl;
				}
				checkFile.close();
			}
		}
	}
}
