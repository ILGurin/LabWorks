#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <fstream> 
#include <string>
#include <Windows.h> 
 
using namespace std; 
 
enum class ProductName { 
    PRODUCT_A, 
    PRODUCT_B, 
    PRODUCT_C 
}; 
 
struct Product { 
    ProductName name; 
    int quantity; 
    int factoryNumber; 
    float price; 
    bool hasDiscount : 1; 
    union { 
        float discount; 
        int weight; 
    }; 
}; 
 
vector<Product> products; 
 
const string dataFileName = "products.txt"; 
const string dataIndexName = "index.txt";
 
void ReadDataFromFile() { 
    ifstream inputFile(dataFileName); 
    if (!inputFile) { 
        cout << "Ошибка открытия файла." << endl; 
        return; 
    } 
 
    int size; 
    inputFile >> size; 
    products.resize(size); 
 
    for (int i = 0; i < size; ++i) { 
        int name; 
        inputFile >> name; 
        products[i].name = static_cast<ProductName>(name); 
 
        inputFile >> products[i].quantity; 
        inputFile >> products[i].factoryNumber; 
        inputFile >> products[i].price; 
 
        int hasDiscount; 
        inputFile >> hasDiscount; 
        products[i].hasDiscount = static_cast<bool>(hasDiscount); 
 
        if (products[i].hasDiscount) { 
            inputFile >> products[i].discount; 
        } 
        else { 
            inputFile >> products[i].weight; 
        } 
    } 
 
    inputFile.close(); 
} 
 
void WriteDataToFile() { 
    ofstream outputFile(dataFileName); 
    if (!outputFile) { 
        cout << "Ошибка открытия файла." << endl; 
        return; 
    } 
 
    int size = products.size(); 
    outputFile << size << endl; 
 
    for (int i = 0; i < size; ++i) { 
        outputFile << static_cast<int>(products[i].name) << endl; 
        outputFile << products[i].quantity << endl; 
        outputFile << products[i].factoryNumber << endl; 
        outputFile << products[i].price << endl; 
        outputFile << static_cast<int>(products[i].hasDiscount) << endl; 
 
        if (products[i].hasDiscount) { 
            outputFile << products[i].discount << endl; 
        } 
        else { 
            outputFile << products[i].weight << endl; 
        } 
    } 
 
    outputFile.close(); 
} 
 
void AddProduct() { 
    Product product; 
    int name; 
 
    cout << "Введите данные нового продукта:" << endl; 
    cout << "Название продукта (1 - Продукт A, 2 - Продукт B, 3 - Продукт C): "; 
    cin >> name; 
    product.name = static_cast<ProductName>(name - 1); 
 
    cout << "Количество: "; 
    cin >> product.quantity; 
 
    cout << "Номер цеха: "; 
    cin >> product.factoryNumber; 
 
    cout << "Цена: "; 
    cin >> product.price; 
 
 
    if (product.hasDiscount) { 
        cout << "Скидка: "; 
        cin >> product.discount; 
    } 
    else { 
        cout << "Вес: "; 
        cin >> product.weight; 
    } 
 
    products.push_back(product); 
 
    // Дописываем новую запись в файл 
    ofstream outputFile(dataFileName, ios::app); 
    if (!outputFile) { 
        cout << "Ошибка открытия файла." << endl; 
        return; 
    } 
 
    outputFile << static_cast<int>(product.name) << endl; 
    outputFile << product.quantity << endl; 
    outputFile << product.factoryNumber << endl; 
    outputFile << product.price << endl; 
    outputFile << static_cast<int>(product.hasDiscount) << endl; 
 
    if (product.hasDiscount) { 
        outputFile << product.discount << endl; 
    } 
    else { 
        outputFile << product.weight << endl; 
    } 
 
    outputFile.close(); 
} 
 
void ModifyProduct() { 
    int index; 
 
    cout << "Введите номер продукта, который хотите изменить: "; 
    cin >> index; 
 
    if (index >= 1 && index <= products.size()) { 
        Product& product = products[index - 1]; 
 
        cout << "Введите новые данные для продукта " << index << ":" << endl; 
        cout << "Название продукта (1 - Продукт A, 2 - Продукт B, 3 - Продукт C): "; 
        cin >> index; 
        product.name = static_cast<ProductName>(index - 1); 
 
        cout << "Количество: "; 
        cin >> product.quantity; 
 
        cout << "Номер цеха: "; 
        cin >> product.factoryNumber;

        cout << "Цена: "; 
        cin >> product.price; 
 
 
        if (product.hasDiscount) { 
            cout << "Скидка: "; 
            cin >> product.discount; 
        } 
        else { 
            cout << "Вес: "; 
            cin >> product.weight; 
        } 
 
        // Перезаписываем все данные в файл 
        WriteDataToFile(); 
 
        cout << "Данные для продукта с индексом " << index << " успешно изменены." << endl; 
    } 
    else { 
        cout << "Продукт с указанным номером не найден." << endl; 
    } 
} 
 
void DeleteProduct() { 
    int index; 
    cout << "Введите номер продукта, который хотите удалить: "; 
    cin >> index; 
 
    if (index >= 1 && index <= products.size()) { 
        products.erase(products.begin() + index - 1); 
 
        // Перезаписываем все данные в файл 
        WriteDataToFile(); 
 
        cout << "Продукт с индексом " << index << " успешно удален." << endl; 
    } 
    else { 
        cout << "Продукт с указанным номером не найден." << endl; 
    } 
} 

void Sort(){
    vector<int> indexs(products.size());
    for (int i = 0; i < products.size(); i++){
        indexs[i] = (i+1);
    }
    vector<int> quantiti(products.size());
    for (int i = 0; i < products.size(); i++){
        quantiti[i] = products[i].quantity;
    }
    int temp;
    for (int i = 0; i < products.size() - 1; i++) {
        for (int j = 0; j < products.size() - i - 1; j++) {
            if (quantiti[j] > quantiti[j + 1]) {
                temp = quantiti[j];
                quantiti[j] = quantiti[j + 1];
                quantiti[j + 1] = temp;

                temp = indexs[j];
                indexs[j] = indexs[j + 1];
                indexs[j + 1] = temp;
            }
        }
    }
    
    ofstream outputFile(dataIndexName); 
    if (!outputFile) { 
        cout << "Ошибка открытия файла." << endl; 
        return; 
    } 
    for (int i = 0; i < products.size(); i++){
        outputFile << indexs[i] << endl;
    }
    outputFile.close(); 
    cout << "Продукты отсортированы по количеству. Индексы сохранены в файле " << dataIndexName << endl;
}
 
void ShowProducts() { 
    cout << "Список продуктов:" << endl; 
    cout << "-----------------------------" << endl; 
    int index = 1; 
    for (const auto& product : products) { 
        cout << "Номер продукта: " << index << endl; 
        cout << "Название: "; 
 
        switch (product.name) { 
        case ProductName::PRODUCT_A: 
            cout << "Продукт A"; 
            break; 
        case ProductName::PRODUCT_B: 
            cout << "Продукт B"; 
            break; 
        case ProductName::PRODUCT_C: 
            cout << "Продукт C"; 
            break; 
        } 
 
        cout << endl; 
 
        cout << "Количество: " << product.quantity << endl; 
        cout << "Номер цеха: " << product.factoryNumber << endl; 
        cout << "Цена: " << product.price << endl; 
 
        if (product.hasDiscount) { 
            cout << "Скидка: " << product.discount << endl; 
        } 
        else { 
            cout << "Вес: " << product.weight << endl; 
        } 
 
        cout << "-----------------------------" << endl; 
        ++index; 
    } 
} 
 
int main() { 
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    ReadDataFromFile(); 
    int choice; 
 
    do { 
        cout << "1. Добавить продукт" << endl; 
        cout << "2. Изменить продукт" << endl; 
        cout << "3. Удалить продукт" << endl; 
        cout << "4. Показать список продуктов" << endl; 
        cout << "5. Сортировать список продуктов" << endl;
        cout << "0. Выход" << endl; 
 
        cout << "Выберите действие: "; 
        cin >> choice; 
 
        switch (choice) { 
        case 1: 
            AddProduct(); 
            break; 
        case 2: 
            ModifyProduct(); 
            break; 
        case 3: 
            DeleteProduct(); 
            break; 
        case 4: 
            ShowProducts(); 
            break; 
        case 5:
            Sort();
            break;
        case 0: 
            WriteDataToFile(); 
            break; 
        default: 
            cout << "Неверный выбор. Повторите попытку." << endl; 
            break; 
        } 
        cout << endl; 
    } while (choice != 0); 
    return 0; 
}
