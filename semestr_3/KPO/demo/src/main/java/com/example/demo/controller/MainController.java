package com.example.demo.controller;

import com.example.demo.Repository.EmployeeRepository;
import com.example.demo.Repository.UserRepository;
import com.example.demo.Service.EmployeeService;
import com.example.demo.domain.Employee;
import com.example.demo.domain.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
public class MainController {
    @Autowired
    private UserRepository userRepository;

    @Autowired
    private EmployeeRepository employeeRepository;

    @Autowired
    private EmployeeService employeeService;

    @GetMapping("/main")
    public String main(Model model){
        List<User> users = userRepository.findAll();
        model.addAttribute("users", users);

        List<Employee> employees = employeeRepository.findAll();
        model.addAttribute("employees", employees);

        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        String currentPrincipalName = authentication.getName();
        model.addAttribute("currentPrincipalName", currentPrincipalName);

        return "main";
    }


    @PostMapping("/main")
    public String add(@RequestParam String surname,
                      @RequestParam String name,
                      @RequestParam String patronymic,
                      @RequestParam String dataOfBirth,
                      @RequestParam String departmentName,
                      @RequestParam String position,
                      @RequestParam String startDate,
                      Model model){

        employeeService.addEmployee(surname, name, patronymic, dataOfBirth, departmentName, position, startDate);

        List<Employee> employees = employeeService.findAll();
        model.addAttribute("employees", employees);

        return "main";
    }
}
