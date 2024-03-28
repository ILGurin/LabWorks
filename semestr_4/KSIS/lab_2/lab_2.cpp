#include <iostream> 

int main() {
    char text[100];
    std::cout << "Enter text: ";
    std::cin.getline(text, 100);

    bool condition_met = true;

    __asm {
        lea esi, text  // Загрузка адреса строки в регистр esi 
        mov ecx, 0     // Обнуление счетчика 

        loop_start:
        mov al, [esi + ecx]  // Загрузка символа из памяти в регистр al 
            test al, al          // Проверка, является ли символ нулевым-терминатором строки 
            jz end_loop          // Если символ нулевой-терминатор, завершаем цикл z

            cmp al, 'A'          // Сравниваем символ с 'A' 
            jl not_upper         // Если меньше 'A', переходим к следующему символу 
            cmp al, 'Z'          // Сравниваем символ с 'Z' 
            jg not_upper         // Если больше 'Z', переходим к следующему символу 

            sub al, 'A'          // Вычисляем разность между текущим символом и 'A' 
            mov bl, 'Z'          // Загружаем символ 'Z' в регистр bl 
            sub bl, al           // Вычитаем разность из 'Z', чтобы получить симметричный символ 
            mov[esi + ecx], bl   // Обновляем символ в строке 

            not_upper :
        inc ecx              // Увеличиваем счетчик 
            jmp loop_start       // Переходим к следующей итерации цикла 

            end_loop :            // Метка окончания цикла 
    }

    if (condition_met) {
        std::cout << "Condition met. Proceed with further processing." << std::endl;
    }
    else {
        std::cout << "Condition not met. Check the text for compliance." << std::endl;
    }

    std::cout << "Text after processing: " << text << std::endl;

    return 0;
}