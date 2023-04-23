#include <iostream> 
#include <vector> 
#include <algorithm> 

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


// Массив структур для хранения информации о продукции 
std::vector<Product> products;

// Функция для добавления продукта в массив 
void addProduct(ProductName name, int quantity, int factoryNumber, float price, bool hasDiscount, float discount) {
    Product product;
    product.name = name;
    product.quantity = quantity;
    product.factoryNumber = factoryNumber;
    product.price = price;
    product.hasDiscount = hasDiscount;
    product.discount = discount;
    products.push_back(product);
    std::cout << "Продукт успешно добавлен.\n";
}

// Функция для вывода содержимого массива на экран 
void viewProducts() {
    std::cout << "Список продуктов:\n";
    for (const Product& product : products) {
        std::cout << "Наименование: ";
        switch (product.name) {
        case ProductName::PRODUCT_A:
            std::cout << "Продукт A";
            break;
        case ProductName::PRODUCT_B:
            std::cout << "Продукт B";
            break;
        case ProductName::PRODUCT_C:
            std::cout << "Продукт C";
            break;
        }
        std::cout << "\nКоличество: " << product.quantity
            << "\nНомер цеха: " << product.factoryNumber 
            << "\nЦена без скидки: "  << product.price 
            << "\nНаличие скидки: "<< product.hasDiscount 
            << "\nСкидка: " << product.discount << "\n\n";
    }
}

// Функция для сортировки массива по одному полю 
void sortProductsByField(int field) {
    switch (field) {
    case 1:
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.name < b.name;
            });
        std::cout << "Массив продуктов отсортирован по наименованию.\n";
        break;
    case 2:
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.quantity < b.quantity;
            });
        std::cout << "Массив продуктов отсортирован по количеству.\n";
        break;
    case 3:
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.factoryNumber < b.factoryNumber;
            });
        std::cout << "Массив продуктов отсортирован по номеру цеха.\n";
        break;
    case 4:
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.price < b.price;
        });
        std::cout << "Массив отсортирован по цене.\n";
        break;
    case 5:
        std::sort(products.begin(), products.end(), [](const Product& a, const Product& b) {
            return a.discount < b.discount;
            });
        std::cout << "Массив отсортирован по величине скидки. \n";
        break;

    default:
        std::cout << "Некорректный выбор поля для сортировки.\n";
        break;
    }
}

// Функция для удаления записи по заданному значению поля 
void deleteProductByFactoryNumber(int factoryNumber) {
    for (auto it = products.begin(); it != products.end();) {
        if (it->factoryNumber == factoryNumber) {
            it = products.erase(it);
        }
        else {
            ++it;
        }
    }
    std::cout << "Продукты с номером цеха " << factoryNumber << " успешно удалены.\n";
}

// Функция для обновления количества продуктов по заданному номеру цеха 
void updateProductQuantityByFactoryNumber(int factoryNumber, int newQuantity, float newPrice, bool discount, float discountt) {
    for (Product& product : products) {
        if (product.factoryNumber == factoryNumber) {
            product.quantity = newQuantity;
            product.price = newPrice;
            product.hasDiscount = discount;
            product.discount = discountt;
            std::cout << "Значения о продуктах в цехе " << factoryNumber << " успешно обновлены.\n";
            return;
        }
    }
    std::cout << "Продукты с номером цеха " << factoryNumber << " не найдены.\n";
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // Добавление продуктов 
    addProduct(ProductName::PRODUCT_A, 100, 1, 500.4, true, 10);
    addProduct(ProductName::PRODUCT_B, 200, 2, 250.4, false, 30);
    addProduct(ProductName::PRODUCT_C, 150, 1, 23, true, 20);

    viewProducts();
    updateProductQuantityByFactoryNumber(1, 120, 400, true, 20);
    deleteProductByFactoryNumber(2);
    viewProducts();
    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить продукт\n";
        std::cout << "2. Вывести список продуктов\n";
        std::cout << "3. Отсортировать продукты\n";
        std::cout << "4. Обновить количество продуктов\n";
        std::cout << "5. Удалить продукт\n";
        std::cout << "6. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int productChoice;
            int quantity;
            int factoryNumber;
            int price;
            bool hasDiscount;
            float discount;
            std::cout << "Выберите наименование продукта (1 - Продукт A, 2 - Продукт B, 3 - Продукт C): ";
            std::cin >> productChoice;
            std::cout << "Введите количество продукта: ";
            std::cin >> quantity;
            std::cout << "Введите номер цеха: ";
            std::cin >> factoryNumber;
            std::cout << "Введите новую цену: ";
            std::cin >> price;
            std::cout << "Есть ли скидка (true, false)";
            std::cin >> hasDiscount;
            std::cout << "Введите процент скидки: ";
            std::cin >> discount;

            addProduct(static_cast<ProductName>(productChoice - 1), quantity, factoryNumber, price, hasDiscount, discount);
            break;
        }
        case 2: {
            viewProducts();
            break;
        }
        case 3: {
            int field;
            std::cout << "Выберите поле для сортировки (1 - наименование, 2 - количество, 3 - номер цеха, 4 - цена, 5 - скидка): ";
            std::cin >> field;
            sortProductsByField(field);
            break;
        }
        case 4: {
            int factoryNumber;
            int newQuantity;
            float newPrice;
            bool discount;
            float discountt;
            std::cout << "Введите номер цеха: ";
            std::cin >> factoryNumber;
            std::cout << "Введите новое количество продукта: ";
            std::cin >> newQuantity;
            std::cout << "Введите новую цену: ";
            std::cin >> newPrice;
            std::cout << "Есть ли скидка (true, false)";
            std::cin >> discount;
            std::cout << "Введите процент скидки: ";
            std::cin >> discountt;


            updateProductQuantityByFactoryNumber(factoryNumber, newQuantity, newPrice, discount, discountt);
            break;
        }
        case 5: {
            int factoryNumber;
            std::cout << "Введите номер цеха: ";
            std::cin >> factoryNumber;
            deleteProductByFactoryNumber(factoryNumber);
            break;
        }
        case 6: {
            std::cout << "Выход...\n";
            break;
        }
        default: {
            std::cout << "Некорректный выбор. Попробуйте снова.\n;";
            break;
        }
        }
    } while (choice != 6);

    return 0;
}