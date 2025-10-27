package by.brstu;

import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

public class Main {

    public static void main(String[] args) {
        MongoDatabase database = MongoConnection.getDatabase();

/*        // Working with nested documents
        MongoCollection<Document> studentNestedCollection = database.getCollection("students_nested");
        insertStudentsWithNestedExams(studentNestedCollection);
        printStudentsWithNestedExams(studentNestedCollection);

        // Working with external links
        MongoCollection<Document> studentsReferenceCollection = database.getCollection("students_reference");
        MongoCollection<Document> examsCollection = database.getCollection("exams");
        insertStudentsWithExternalExams(studentsReferenceCollection, examsCollection);
        printStudentsWithExternalExams(studentsReferenceCollection, examsCollection);*/

        MongoCollection<Document> nestedStudentsCollection = database.getCollection("students_nested");
        MongoCollection<Document> referenceStudentsCollection = database.getCollection("students_reference");
        MongoCollection<Document> examsCollection = database.getCollection("exams");

        StudentService studentService = new StudentService(nestedStudentsCollection, referenceStudentsCollection, examsCollection);

        studentService.insertStudentsWithNestedExams();
        studentService.printStudentsWithNestedExams();
        studentService.printStudentsByYearAndGroupNested("2000", "PO-10");

        System.out.println("===================================");
        System.out.println("===================================");
        System.out.println("===================================");

        studentService.insertStudentsWithExternalExams();
        studentService.printStudentsWithExternalExams();
        studentService.printStudentsByYearAndGroupReference("2000", "B-124");
    }
}