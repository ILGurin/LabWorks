#include <iostream>
#include <cstring>
#include <string>
#include <chrono>

constexpr int MAX_LENGTH = 100;
constexpr int RESULT_LENGTH = 256;

int main() {
	setlocale(LC_ALL, "ru");
	char str[100];
	std::cout << "Введите текст: ";
	std::cin.getline(str, 100);
	char* str1 = new char[MAX_LENGTH];
	char* str2 = new char[MAX_LENGTH];
	char* result = new char[RESULT_LENGTH];

	size_t len = strlen(str);
	size_t half_len = len / 2;
	size_t second_half_len = len - half_len; // Сохраняем размер второй половины строки

	// Копирование первой половины строки в str1
	strncpy_s(str1, MAX_LENGTH, str, half_len);
	str1[half_len] = '\0'; // Добавляем завершающий нуль-символ

	// Копирование второй половины строки в str2
	strncpy_s(str2, MAX_LENGTH, str + half_len, second_half_len);
	str2[second_half_len] = '\0'; // Добавляем завершающий нуль-символ

	auto start = std::chrono::high_resolution_clock::now(); // Засекаем начало времени

	__asm {
		mov esi, str1  // Загрузка адреса первой половины строки в регистр esi
		mov edi, result  // Загрузка адреса результата в регистр edi
		mov ecx, half_len  // Инициализация счетчика для первой половины

		// Цикл для переворачивания первой половины строки
		reverse_first :
		mov al, [esi + ecx - 1]  // Загрузка символа из первой половины строки в обратном порядке
			mov[edi], al  // Запись символа в результат
			inc edi  // Увеличение указателя на результат
			loop reverse_first  // Повторяем цикл до завершения переворачивания

			mov esi, str2  // Загрузка адреса второй половины строки в регистр esi
			mov ecx, second_half_len  // Инициализация счетчика для второй половины

			// Цикл для переворачивания второй половины строки и записи ее в результат
			reverse_second :
		mov al, [esi + ecx - 1]  // Загрузка символа из второй половины строки в обратном порядке
			mov[edi], al  // Запись символа в результат
			inc edi  // Увеличение указателя на результат
			loop reverse_second  // Повторяем цикл до завершения переворачивания и записи

			mov byte ptr[edi], 0  // Добавляем завершающий нуль-символ к результату
	}

	auto end = std::chrono::high_resolution_clock::now(); // Засекаем конец времени

	// Рассчитываем время выполнения
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

	std::cout << "Time taken by assembly code: " << duration << " miliseconds" << std::endl;

	std::cout << "Reverse string: " << result << std::endl;
	delete[] str1;
	delete[] str2;
	delete[] result;
	return 0;
}