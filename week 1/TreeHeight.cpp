#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <sstream>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
	int key;
	Node *parent;
	std::vector<Node *> children;

	Node() {
		this->parent = NULL;
	}

	void setParent(Node *theParent) {
		parent = theParent;
		parent->children.push_back(this);     //  children.push_back(parent);
		
	}
};


int main_with_large_stack_space() {
	std::ios_base::sync_with_stdio(0);
	int n, root;

	//// custom input variables \\\\\

	char choice;
	int max_files;
	std::string text, fileName, relativePath;
	std::cout << "'y' for custom input and any othe key for already savedfiles :   ";
	std::cin >> choice;
	if (choice == 'y')
		max_files = 1;
	else
		max_files = 24;
	for (int ii = 1; ii <= max_files; ii++)
	{
		std::vector<Node> nodes;
		if (choice != 'y')
		{

			if (ii < 10)
				fileName = "0" + std::to_string(ii);
			else
				fileName = std::to_string(ii);
			relativePath = "../../tests/" + fileName;
			std::ifstream sampleFile;
			sampleFile.open(relativePath);

			if (sampleFile.is_open())
			{
				getline(sampleFile, text);

				n = std::stoi(text);
				nodes.resize(n);

				int parent_index, child_index = 0;
				getline(sampleFile, text);					// inputs are the parents against the index (input position)
				std::stringstream  lineStream(text);
				while (lineStream >> parent_index)
				{
					if (parent_index >= 0)
						nodes[child_index].setParent(&nodes[parent_index]);
					else
						root = child_index;
					nodes[child_index].key = child_index;
					child_index++;
				}
				sampleFile.close();
			}
			else
			{
				std::cout << "can't open required file" << std::endl;
			}
		}
		else
		{
			std::cin >> n;;
			nodes.resize(n);
			for (int child_index = 0; child_index < n; child_index++) {
				int parent_index;
				std::cin >> parent_index;  // inputs are the parents against the index (input position)
				if (parent_index >= 0)
					nodes[child_index].setParent(&nodes[parent_index]);
				else
					root = child_index;
				nodes[child_index].key = child_index;
			}
		}





		//// Replace this code with a faster implementation
		//int maxHeight = 0;
		//for (int leaf_index = 0; leaf_index < n; leaf_index++) {
		//	int height = 0;
		//	for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
		//		height++;
		//	maxHeight = std::max(maxHeight, height);
		//}

		/*
		////////////////////////////MSM Code///////////////////////////
		*/
		int height = 0, firstNodeKey = 0;
		bool isLevelClear = false;
		std::queue <Node> myQueue;
		myQueue.push(nodes[root]);
		firstNodeKey = root;
		while (!myQueue.empty())
		{
			Node currentNode = myQueue.front();
			myQueue.pop();
			if (currentNode.key == firstNodeKey)
			{
				height++;
				isLevelClear = true;
			}
			if (currentNode.children.size() != 0)
			{
				for (int i = 0; i < currentNode.children.size(); i++)
					myQueue.push(nodes[currentNode.children[i]->key]);
				if (isLevelClear)
				{
					firstNodeKey = currentNode.children[0]->key;
					isLevelClear = false;
				}		
			}	
		}

		if (choice == 'y')
			std::cout << height<< std::endl;
		else
		{
			std::ifstream checkFile;
			relativePath += ".a";
			checkFile.open(relativePath);

			if (checkFile.is_open())
			{
				getline(checkFile, text);
				if ((height) == stoi(text)) {
					std::cout << "File : " << fileName << " Ans = " << height << " is true" << std::endl;
				}
				else
				{
					std::cout << "File : " << fileName << " Ans = " << height << " is False. Actual Ans is " << text << std::endl;
				}
				checkFile.close();
			}
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
	// Allow larger stack space
	const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
	struct rlimit rl;
	int result;

	result = getrlimit(RLIMIT_STACK, &rl);
	if (result == 0)
	{
		if (rl.rlim_cur < kStackSize)
		{
			rl.rlim_cur = kStackSize;
			result = setrlimit(RLIMIT_STACK, &rl);
			if (result != 0)
			{
				std::cerr << "setrlimit returned result = " << result << std::endl;
			}
		}
	}

#endif
	return main_with_large_stack_space();
}
