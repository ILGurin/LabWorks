package com.example.demo.controller;

import com.example.demo.Repository.EmployeeRepository;
import com.example.demo.Service.EmployeeService;
import com.example.demo.domain.Employee;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.Authentication;
import org.springframework.security.core.context.SecurityContextHolder;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

@Controller
@RequestMapping("/main")
@PreAuthorize("hasAuthority('ADMIN')")
public class EmployyeController {
    @Autowired
    private EmployeeRepository employeeRepository;

    @Autowired
    private EmployeeService employeeService;

    @GetMapping("{employee}")
    public String employeeEditForm(@PathVariable Employee employee, Model model){
        model.addAttribute("employee", employee);

        Authentication authentication = SecurityContextHolder.getContext().getAuthentication();
        String currentPrincipalName = authentication.getName();
        model.addAttribute("currentPrincipalName", currentPrincipalName);
        return "employeeEdit";
    }

    @PostMapping("/save")
    public String employeeSave(
            @RequestParam("name") String name,
            @RequestParam("surname") String surname,
            @RequestParam("patronymic") String patronymic,
            @RequestParam("dataOfBirth") String dataOfBirth,
            @RequestParam("departmentName") String departmentName,
            @RequestParam("position") String position,
            @RequestParam("startDate") String startDate,
            @RequestParam("employeeId") Employee employee
    ){
        employeeService.saveEmployee(employee, name, surname, patronymic, dataOfBirth, departmentName, position, startDate);
        return "redirect:/main";
    }

    @PostMapping("/{employee}/remove")
    public String delete(@RequestParam("employeeId") Employee employee){
        employeeService.deleteEmployee(employee.getId());
        return "redirect:/main";
    }
}
