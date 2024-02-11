package com.example.demo.Service;

import com.example.demo.Repository.UserRepository;
import com.example.demo.domain.Role;
import com.example.demo.domain.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.core.userdetails.UserDetails;
import org.springframework.security.core.userdetails.UserDetailsService;
import org.springframework.security.core.userdetails.UsernameNotFoundException;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.stereotype.Service;

import java.util.*;
import java.util.stream.Collectors;

@Service
public class UserService implements UserDetailsService {
    @Autowired
    private UserRepository userRepository;

    @Autowired
    private PasswordEncoder passwordEncoder;


    @Override
    public UserDetails loadUserByUsername(String username) throws UsernameNotFoundException {
        return userRepository.findByUsername(username);
    }

    public boolean addUser(User user){ //возвращает true если пользователь добавлен, false если нет
        User userFromDb = userRepository.findByUsername(user.getUsername());

        if(userFromDb != null){
            return false;
        }

        user.setActive(true);
        user.setRoles(Collections.singleton(Role.USER)); //Создаёт сет с одним единственным значением
        user.setPassword(passwordEncoder.encode(user.getPassword()));
        userRepository.save(user);

        return true;
    }

    public boolean deleteUser(Long id){
        Optional<User> user = userRepository.findById(id);
        if(user != null){
            userRepository.deleteById(id);
        }else{
            return false;
        }
        return true;
    }

    public List<User> findAll() {
        return userRepository.findAll();
    }

    public void saveUser(User user, String username, Map<String, String> form) {
        user.setUsername(username);

        //Переводим строки из enum'а в строковый вид
        Set<String> roles = Arrays.stream(Role.values())//берем все существующие в приложении роли
                .map(Role::name)//преобразуем массив этих ролей в стрим (java stream api), где получаем имена ролей и полученый список имён складываем в set
                .collect(Collectors.toSet());

        user.getRoles().clear(); //очищаем коллекцию от установленных ролей

        for (String key : form.keySet()) {
            if(roles.contains(key)){
                user.getRoles().add(Role.valueOf(key));
            }
        }
        userRepository.save(user);
    }
}
