#include <iostream>
#include <string>

using namespace std;

class Person{
private:
    string name;
    int age;
    int gender;
public:
    //Конструктор без параметров
    Person(){ 

    }

    //Конструктор с параметрами
    Person(string name, int age, int gender){ 
        this->name = name;
        this->age = age;
        this->gender = gender;
        cout << "constructor " << this << endl;
        
    }

    //Конструктор копирования
    Person(const Person& other){ 
        this->name = other.name;
        this->age = other.age;
        this->gender = other.gender;
    }


    //Геттеры
    string GetName(){
        return name;
    }

    int GetAge(){
        return age;
    }

    int GetGender(){
        return gender;
    }

    //Сеттеры
    void SetName(string Name){
        this->name = name;
    }

    void SetAge(int age){
        this->age = age;
    }

    void SetGender(int gender){
        this->gender = gender;
    }

    void SetAll(string name, int age, int gender){
        this->name = name;
        this->age = age;
        this->gender = gender;
    }

    void Print(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: ";
        gender == 1 ? cout << gender << " (men)" << endl : cout << gender << " (women)" << endl;
    }

    //Деструктор
    ~Person(){
        cout << "destructor " << this << endl;
    }
};

int main(){
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    Person ILYA("Ilya", 18, 1);
    Person NAME("name", 20, 0);
    Person NAME1("namee", 25, 1);
    NAME.~Person();
    Person NAME2("name", 22, 0);
    Person *p_ILYA = &ILYA;
    p_ILYA->Print();
    ILYA.Print();
    return 0;
}