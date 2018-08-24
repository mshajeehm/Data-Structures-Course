#include <iostream>
#include <queue>
#include <vector>
#include <deque>
#include <string>
#include <fstream>
#include <sstream>



std::string text, fileName, relativePath;

struct Request {
	Request(int arrival_time, int process_time) :
		arrival_time(arrival_time),
		process_time(process_time)
	{}

	int arrival_time;
	int process_time;
};

struct Response {
	Response(bool dropped, int start_time) :
		dropped(dropped),
		start_time(start_time)
	{}

	bool dropped;
	int start_time;
};

class Buffer {
public:
	Buffer(int size) :
		size_(size),
		finish_time_()
	{}

	Response Process(const Request &request) {
		// write your code here

		while (!finishTimes.empty())  //first of all clear all the elements that should have been processed by the arrival of this request till the time list is empty
		{
			if (request.arrival_time >= finishTimes.back())
				finishTimes.pop_back();
			else
				break;
		}
		if (finishTimes.size() == size_) //if buffer is already full, return -1
		{
			return Response(true, -1);
		}
		if (finishTimes.empty())  //will reach here only if the buffer is not full and items therefore can be added in it. So if it is empty we add with processtime+arrivaltime
		{
				thisPacketResponse = Response(false, request.arrival_time);
				finishTimes.push_front(request.process_time + request.arrival_time);
				return thisPacketResponse;			
		}

		thisPacketResponse = Response(false, finishTimes.front());  //otherwise we add it with processtime+finishtime of earlier packet
		finishTimes.push_front(request.process_time + finishTimes.front());
		

	}
private:
	int size_;
	std::queue <int> finish_time_;
	std::deque<int> finishTimes;
	Response thisPacketResponse = Response(false, 0);
};

std::vector <Request> ReadRequests() {
	std::vector <Request> requests;
	int count;
	std::cin >> count;
	for (int i = 0; i < count; ++i) {
		int arrival_time, process_time;
		std::cin >> arrival_time >> process_time;
		requests.push_back(Request(arrival_time, process_time));
	}
	return requests;
}



std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
	std::vector <Response> responses;
	for (int i = 0; i < requests.size(); ++i)
		responses.push_back(buffer->Process(requests[i]));
	return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
	for (int i = 0; i < responses.size(); ++i)
		std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

void PrintFileResponses(const std::vector <Response> &responses) {

	std::ifstream checkFile;
	relativePath += ".a";
	checkFile.open(relativePath);

	for (int i = 0; i < responses.size(); ++i)
	{

		int ans = (responses[i].dropped ? -1 : responses[i].start_time);
		if (checkFile.is_open())
		{
			getline(checkFile, text);
			if (ans == stoi(text)) {
				//std::cout << "File : " << fileName << "   Line Number  " << i << " Ans = " << ans << " is true" << std::endl;
			}
			else
			{
				std::cout << "File : " << fileName << "   Line Number  " << i << " Ans = " << ans << " is False. Actual Ans is " << text << std::endl;
			}
		}
	}
	checkFile.close();
}


int main() {
	int size;

	/////////////////////////////
	char choice;
	int max_files;
	
	std::cout << "'y' for custom input and any othe key for already savedfiles :   ";
	std::cin >> choice;
	if (choice == 'y')
		max_files = 1;
	else
		max_files = 22;
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
				int temp1 = 0, temp2 = 0, count = 0;
				getline(sampleFile, text);
				std::stringstream  lineStream(text);
				while (lineStream >> temp1)
				{
					temp2 == 0 ? size = temp1 : count = temp1;
					temp2++;
				}
				std::vector <Request> requests;
				for (int i = 0; i < count; ++i) {
					int arrival_time = 0, process_time = 0; temp2 = 0;
					getline(sampleFile, text);
					std::stringstream  lineStream(text);
					while (lineStream >> temp1)
					{
						temp2 == 0 ? arrival_time = temp1 : process_time = temp1;
						temp2++;
					}
					requests.push_back(Request(arrival_time, process_time));
				}
				sampleFile.close();
				Buffer buffer(size);
				std::vector <Response> responses = ProcessRequests(requests, &buffer);

				PrintFileResponses(responses);

			}
			else
			{
				std::cout << "can't open required file" << std::endl;

			}
		}
		else
		{
			getline(std::cin, text);
			std::cin >> size;
			std::vector <Request> requests = ReadRequests();

			Buffer buffer(size);
			std::vector <Response> responses = ProcessRequests(requests, &buffer);

			PrintResponses(responses);
		}
	}
	return 0;
}
