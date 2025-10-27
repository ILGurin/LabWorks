package by.lab_2.controller;

import java.util.Collections;
import java.util.LinkedList;
import java.util.List;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.server.ResponseStatusException;
import reactor.core.publisher.Flux;

@RestController
public class MainController {
    private final int maxNumberOfElements = 10000000;
    private List<Integer> numbers = new LinkedList<>();

    public MainController() {
        for (int i = 1; i < maxNumberOfElements + 1; i++) {
            numbers.add(i);
        }
    }

    @GetMapping("/reverse/{numberOfElements}")
    public Flux<Integer> index(@PathVariable Integer numberOfElements) {
        if (numberOfElements > maxNumberOfElements) {
            throw new ResponseStatusException(HttpStatus.BAD_REQUEST, "Number of elements exceeds the maximum");
        }
        return Flux.fromIterable(numbers)
                .take(numberOfElements)
                .collectList()
                .flatMapMany(list -> {
                    Collections.reverse(list);
                    return Flux.fromIterable(list);
                });
    }
}
