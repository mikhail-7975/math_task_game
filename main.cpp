#include <iostream>
#include <string>
#include <vector>
#include <time.h>


class Task {
public:
	Task(size_t maxNumber); 
	int first_number, second_number, result, index_of_aritmetic_operation;
	std::vector<char> arithmetic_operation = { '+', '-', 'x', '/' };
	bool check_answer(int users_answer);
	void show();
};

Task::Task(size_t maxNumber) {
	first_number = 1 + rand() % maxNumber;
	second_number = 1 + rand() % maxNumber;
	index_of_aritmetic_operation = 1 + rand() % 4;
	switch (arithmetic_operation[index_of_aritmetic_operation]) {
	case '+':
		result = first_number + second_number;
		break;
	case '-':
		result = first_number - second_number;
		break;

	case 'x':
		result = first_number * second_number;
		break;

	case '/':
		result = first_number / second_number; 
		break;
	}
}

bool Task::check_answer(int users_answer) {
	return (users_answer == result);
}

void Task::show() {
	std::cout << first_number << arithmetic_operation[index_of_aritmetic_operation] << second_number << " = ";
}

int main() {
	size_t correct_answer_count = 0;
	size_t incorrect_answer_count = 0;
	size_t task_count = 0;
	size_t max_number_of_task = 4;
	size_t max_number = 10;
	time_t begin_time;
	time_t end_time;
	time(&begin_time);
	while (1) {
		Task task(max_number);
		task.show();
		std::string answer;
		std::getline(std::cin, answer);
		while(!task.check_answer(std::stoi(answer))) {
			incorrect_answer_count++;
			std::cout << "What?" << std::endl;
			std::getline(std::cin, answer);
		}
		correct_answer_count++;
		std::cout << "Right!" << std::endl;
		if (correct_answer_count % max_number_of_task == 0) break;
		//task_count++;
	}
	time(&end_time);
	int t;
	std::cout << (end_time - begin_time) / correct_answer_count << " sec for 1 task" << std::endl;
	system("pause");
}