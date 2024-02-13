#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#include "labs_array_maker.h"
#include "labs_sort_runner.h"
#include "labs_sorting_functors.h"
#include "labs_utility_func.h"

//Функция для печати массивов
std::ostream& operator<<(std::ostream& os, const std::vector<int>& arr) {
	for (int num : arr) {
		os << num << " ";
	}
	return os;
}

Settings start_program() {
	Settings settings;

	// Предлагаем пользователю выбрать режим работы
	std::cout << "Select the program mode:\n";
	std::cout << "0 - Debug mode\n";
	std::cout << "1 - Presentation mode\n";
	std::cout << "Enter 0 or 1: ";

	// Безопасный ввод для выбора режима
	while (!(std::cin >> settings.mode) || (settings.mode != 0 && settings.mode != 1)) {
		if (std::cin.fail()) {
			std::cin.clear(); // Очищаем флаг ошибки
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Игнорируем неверные вводы

			// Проверяем на команду выхода
			std::cout << "Invalid input. Enter 999 to exit or try again: ";
			int exitCommand;
			std::cin >> exitCommand;
			if (exitCommand == 999) return settings;
		}
		std::cout << "Enter 0 or 1: ";
	}

	// Если выбран презентационный режим
	if (settings.mode == 1) {
		std::cout << "\nEnter the number of iterations: ";
		while (!(std::cin >> settings.iterations) || settings.iterations < 1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid input. Enter 999 to exit or try again: ";
			int exitCommand;
			std::cin >> exitCommand;
			if (exitCommand == 999) return settings;

			std::cout << "Enter a positive number for the number of iterations: ";
		}

		std::cout << "Enter the step value: ";
		while (!(std::cin >> settings.step) || settings.step < 1) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			std::cout << "Invalid input. Enter 999 to exit or try again: ";
			int exitCommand;
			std::cin >> exitCommand;
			if (exitCommand == 999) return settings;

			std::cout << "Enter a positive number for the step: ";
		}
	}

	return settings;
}

std::vector<int64_t> get_tablerow_data(int arr_size) {
	std::vector<int64_t> tablerow_data;
	tablerow_data.reserve(10);
	for (int i = 0; i < 10; ++i) {
		tablerow_data.emplace_back(-1);
	}

	tablerow_data[0] = arr_size;

	ArrayMaker am(arr_size);

	// Получаем данные по сортировкам прямого выбора
	SelectionSortFunctor ss1;
	SortRunner selection_sort_desc(am.desc_array, &ss1);
	tablerow_data[1] = selection_sort_desc.get_cm();
	SortRunner selection_sort_asc(am.asc_array, &ss1);
	tablerow_data[2] = selection_sort_asc.get_cm();
	SortRunner selection_sort_rand(am.rand_array, &ss1);
	tablerow_data[3] = selection_sort_rand.get_cm();

	// Получаем данные по сортировкам Шелла
	ShellSortFunctor ss2;
	SortRunner shell_sort_desc(am.desc_array, &ss2);
	tablerow_data[4] = shell_sort_desc.get_cm();
	SortRunner shell_sort_asc(am.asc_array, &ss2);
	tablerow_data[5] = shell_sort_asc.get_cm();
	SortRunner shell_sort_rand(am.rand_array, &ss2);
	tablerow_data[6] = shell_sort_rand.get_cm();

	// Получаем данные по сортировкам пирамиды
	HeapSortFunctor ss3;
	SortRunner heap_sort_desc(am.desc_array, &ss3);
	tablerow_data[7] = heap_sort_desc.get_cm();
	SortRunner heap_sort_asc(am.asc_array, &ss3);
	tablerow_data[8] = heap_sort_asc.get_cm();
	SortRunner heap_sort_rand(am.rand_array, &ss3);
	tablerow_data[9] = heap_sort_rand.get_cm();

	return tablerow_data;
}