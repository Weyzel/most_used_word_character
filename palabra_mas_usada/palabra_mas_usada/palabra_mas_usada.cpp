#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <map>
#include <sstream>
#include <cctype>

void search_word();
void most_repeated_words();
void characters_repeat();
void choose_option();

int main() {
	choose_option();
	return 0;
}
void choose_option() {
	int option = 0;
	while (option != 4) {
	std::cout << "What would you like to do: ";
	std::cout << "\n1. Search how many times a word is repeated.";
	std::cout << "\n2. Search the most repeated words.";
	std::cout << "\n3. Search how many times each character repeats itself.";
	std::cout << "\n4. End program.\n\n";
	std::cin >> option;
	std::cout << std::endl;
	
		switch (option) {
		case 1: {
			search_word();
			std::cout << std::endl;
			break;
		}
		case 2: {
			most_repeated_words();
			std::cout << std::endl;
			break;
		}
		case 3: {
			characters_repeat();
			std::cout << std::endl;
			break;
		}
		case 4: {
			break;
		}
		}
	}
}
void search_word() {
	std::string word;
	int count = 0;
	std::cout << "Enter the word you want to search: \n";
	std::cin >> word;
	std::cout << std::endl;
	std::ifstream file("complete_works_shakespeare.txt");

	auto start = std::chrono::high_resolution_clock::now();
	if (!file.is_open()) {
		std::cout << "File was not opened!\n\n";
	}
	if (file.is_open()) {
		std::string line;
		while(!file.eof()){
			getline(file, line);
			auto pos = line.find(word, 0);
			while (pos != std::string::npos) {
				count++;
				pos = line.find(word, pos + 1);
			}
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

	std::cout << "\nThe word '" << word << "' appears " << count << " times in the file.\n" <<  "It took for the programm " << duration << " miliseconds to look trough the file!\n\n";
	file.close();
}
void most_repeated_words() {
	std::ifstream file("complete_works_shakespeare.txt");;
	std::map<std::string, int> mymap;

	std::cout << "Here are the most repeated words of the file: \n\n";
	if (!file.is_open()) {
		std::cout << "File was not opened!\n\n";
	}

	auto start = std::chrono::high_resolution_clock::now();
	if (file.is_open()) {
		std::string word;
		std::string line;
		while (!file.eof()) {
			while (getline(file, line)) {
				std::istringstream iss(line);
				while (iss >> word) {
					mymap[word]++;
				}
			}
		}
	}
	for (const auto& pair : mymap) {
		if (pair.second > 5000) {
			std::cout << pair.first << ": " << pair.second << std::endl;
		}
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

	std::cout << "\n\nThe program took: " << duration << " seconds to execute!\n\n";

	file.close();
}
void characters_repeat() {
	std::string file_name;
	std::cout << "Enter the name of the file with .txt: \n";
	std::cin >> file_name;
	std::ifstream file(file_name);
	if (!file.is_open()) {
		std::cout << "File was not open correctly!\n\n";
	}
	std::map<char, int> mymap;
	auto start = std::chrono::high_resolution_clock::now();
	if (file.is_open()) {
		char c;
		bool flag = true;
		while (!file.eof()) {
			while (file.get(c)) {
				if (std::isalpha(static_cast<unsigned char>(c))){
					mymap[c]++;
				}
				if (flag == true && c == 'Z') {
					// code to execute once
					std::cout << std::endl;
					flag = false;
				}
			}
		}
	}
	for(const auto& c : mymap){
		std::cout << c.first << ": " << c.second << std::endl;
	}
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	std::cout << "\nIt took to the program " << duration << " seconds to execute!";

	file.close();
}