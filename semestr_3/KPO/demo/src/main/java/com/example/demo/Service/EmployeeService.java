package com.example.demo.Service;

import com.example.demo.Repository.EmployeeRepository;
import com.example.demo.domain.Employee;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;


@Service
public class EmployeeService{
    @Autowired
    private EmployeeRepository employeeRepository;

    public void saveEmployee(Employee employee,
                             String name,
                             String surname,
                             String patronymic,
                             String dataOfBirth,
                             String departmentName,
                             String position,
                             String startDate) {
        employee.setName(name);
        employee.setSurname(surname);
        employee.setPatronymic(patronymic);
        employee.setDataOfBirth(dataOfBirth);
        employee.setDepartmentName(departmentName);
        employee.setPosition(position);
        employee.setStartDate(startDate);
        employeeRepository.save(employee);
    }

    public boolean deleteEmployee(Long id){
        if((employeeRepository.findById(id)) != null){
            employeeRepository.deleteById(id);
        }else{
            return false;
        }
        return true;
    }

    public boolean addEmployee(String surname, String name, String patronymic, String dataOfBirth, String departmentName, String position, String startDate){
        Employee employeeFromDb = employeeRepository.findBySurname(surname);

        if(employeeFromDb != null){
            return false;
        }
        Employee employee = new Employee(surname, name, patronymic, dataOfBirth, departmentName, position, startDate);
        employeeRepository.save(employee);
        return true;
    }

    public List<Employee> findAll(){ return employeeRepository.findAll(); }
}
