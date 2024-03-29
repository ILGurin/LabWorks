package com.example.demo.controller;

import com.example.demo.Service.UserService;
import com.example.demo.domain.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;

@Controller
public class RegistrationController {
    @Autowired
    private UserService userService;

    @GetMapping("/registration")
    public String registration(Model model){
        return "registration";
    }

    @PostMapping("/registration")
    public String addUser(User user, Model model){
        if(!userService.addUser(user)){
            model.addAttribute("message", "User exists");
            return "registration";
        }

        return "redirect:/login";
    }
}
