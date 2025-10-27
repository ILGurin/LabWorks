package by.brstu;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.model.Filters;
import org.bson.Document;
import org.bson.conversions.Bson;
import tools.jackson.databind.ObjectMapper;

import java.util.ArrayList;
import java.util.List;

public class StudentService {
    private final ObjectMapper mapper = new ObjectMapper();
    private final MongoCollection<Document> nestedStudentsCollection;
    private final MongoCollection<Document> referenceStudentsCollection;
    private final MongoCollection<Document> examsCollection;

    public StudentService(MongoCollection<Document> nestedStudentsCollection,
                          MongoCollection<Document> referenceStudentsCollection,
                          MongoCollection<Document> examsCollection) {
        this.nestedStudentsCollection = nestedStudentsCollection;
        this.referenceStudentsCollection = referenceStudentsCollection;
        this.examsCollection = examsCollection;
    }

    // Работа со вложенными документами
    public void insertStudentsWithNestedExams() {
        nestedStudentsCollection.deleteMany(new Document());

        Document exam1 = new Document("subject", "Mathematics")
                .append("date", "2024-05-10")
                .append("grade", "5")
                .append("type", "exam");

        Document exam2 = new Document("subject", "Physics")
                .append("date", "2024-06-15")
                .append("grade", "4")
                .append("type", "test");

        List<Document> exams = new ArrayList<>();
        exams.add(exam1);
        exams.add(exam2);

        Document student1 = new Document("studentId", "1")
                .append("name", "Ivan Ivanov")
                .append("year_of_birth", "2000")
                .append("group", "PO-10")
                .append("exams", exams);

        Document student2 = new Document("studentId", "2")
                .append("name", "Petr Petrov")
                .append("year_of_birth", "2010")
                .append("group", "PO-11");

        nestedStudentsCollection.insertOne(student1);
        nestedStudentsCollection.insertOne(student2);
    }

    public void printStudentsWithNestedExams() {
        System.out.println("Students with nested exams:");
        for (Document doc : nestedStudentsCollection.find()) {
            System.out.println(doc.toJson());
        }
        System.out.println("+++ Filter by Physics exam +++");

        for (Document doc : nestedStudentsCollection.find(
                Filters.elemMatch("exams", Filters.and(
                        Filters.eq("subject", "Physics"),
                        Filters.eq("type", "test")
                )))) {
            System.out.println(doc.toJson());
        }
    }

    public void printStudentsByYearAndGroupNested(String yearOfBirth, String group) {
        Bson filter = Filters.and(
                Filters.eq("year_of_birth", yearOfBirth),
                Filters.eq("group", group)
        );
        FindIterable<Document> results = nestedStudentsCollection.find(filter);

        System.out.println("Students born in " + yearOfBirth + " and group " + group + ":");
        for (Document doc : results) {
            System.out.println(doc.toJson());
        }
    }

    // Работа с внешними ссылками
    public void insertStudentsWithExternalExams() {
        referenceStudentsCollection.deleteMany(new Document());
        examsCollection.deleteMany(new Document());

        Document student = new Document("studentId", "1")
                .append("year_of_birth", "2000")
                .append("name", "Ivan Ivanov")
                .append("group", "B-124");

        referenceStudentsCollection.insertOne(student);

        Document exam1 = new Document("studentId", "1")
                .append("subject", "History")
                .append("date", "2024-05-20")
                .append("grade", "5")
                .append("type", "exam");

        Document exam2 = new Document("studentId", "1")
                .append("subject", "Literature")
                .append("date", "2024-06-10")
                .append("grade", "3")
                .append("type", "test");

        examsCollection.insertMany(List.of(exam1, exam2));
    }

    public void printStudentsWithExternalExams() {
        System.out.println("===== Students with external links to exams =====");
        for (Document student : referenceStudentsCollection.find()) {
            System.out.println("Student: " + student.toJson());

            List<Document> exams = examsCollection.find(Filters.eq("studentId", student.getString("studentId"))).into(new ArrayList<>());
            if (exams.isEmpty()) {
                System.out.println("Exams not found");
            } else {
                System.out.println("Student exams:");
                for (Document exam : exams) {
                    System.out.println(exam.toJson());
                }
            }
        }
    }

    public void printStudentsByYearAndGroupReference(String yearOfBirth, String group) {
        // Фильтр по году рождения и группе
        FindIterable<Document> students = referenceStudentsCollection.find(
                Filters.and(
                        Filters.eq("year_of_birth", yearOfBirth),
                        Filters.eq("group", group)
                )
        );

        System.out.println("Students with year of born" + yearOfBirth + " and group " + group + ":");
        for (Document student : students) {
            System.out.println("Student: " + student.toJson());
            String studentId = student.getString("studentId");

            List<Document> exams = examsCollection.find(Filters.eq("studentId", studentId))
                    .into(new ArrayList<>());

            if (exams.isEmpty()) {
                System.out.println("Exams not found");
            } else {
                System.out.println("Student's exams:");
                for (Document exam : exams) {
                    System.out.println("  " + exam.toJson());
                }
            }
            System.out.println("-----");
        }
    }
}
