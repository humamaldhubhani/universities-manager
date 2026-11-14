<div align="center">

<img src="docs/logo.svg" alt="Universities Manager logo" width="130"/>

# Universities Manager

**An object-oriented model of a university, from campus down to the classroom, written in C++.**

![C++](https://img.shields.io/badge/C%2B%2B-11-00599C?logo=cplusplus&logoColor=white)
![Course](https://img.shields.io/badge/Course-Object%20Oriented%20Programming-5B47E0)
![Year](https://img.shields.io/badge/Year-2-FFC857)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)

</div>

---

## Overview

Universities Manager is my **Object Oriented Programming** final project (2nd year, Cyber Security, Ar-Rasheed University). The goal was to design a class diagram for a real-world domain **first**, then implement it faithfully in C++.

The model covers seven classes and the relationships between them:
**University → Faculty → Department → Course**, with **Student** and **Teacher** both inheriting from **Person**.

## Class diagram

```mermaid
classDiagram
    direction LR
    class Person {
        #string email
        #string address
        +string name
    }
    class Student {
        +int studentID
        +string major
        +registerCourse(Course*)
        +dropCourse(Course*)
        +ListStudentCourses()
        +GetStudentInfo()
    }
    class Teacher {
        +int teacherID
        +description descripe
        +ListcoursesTeaching()
        +ShowTeacherInfo()
    }
    class University {
        +int UniversityID
        +string name
        +string location
        +addFaculty(Faculty*)
        +removeFaculty(Faculty*)
        +list_faculties()
    }
    class Faculty {
        +int facultyID
        +string name_faculty
        +addDepartment(Department*)
        +removeDepartment(Department*)
    }
    class Department {
        +int departmentID
        +addStudent(Student*)
        +addCourse(Course*)
        +addTeacher(Teacher*)
        +assignTeacher(Course*, Teacher*)
    }
    class Course {
        +int courseID
        +string name
        +enrollStudent(Student*)
        +unenrollStudent(Student*)
        +ListStudentEnrolled()
    }

    Person <|-- Student
    Person <|-- Teacher
    University "1" o-- "*" Faculty
    Faculty "1" o-- "*" Department
    Department "1" o-- "*" Course
    Department "1" o-- "*" Student
    Department "1" o-- "*" Teacher
    Course "*" -- "*" Student : enrolled
    Course "*" -- "1" Teacher : teaches
```

The original UML diagram submitted with the project is in [`docs/uml-class-diagram.pdf`](docs/uml-class-diagram.pdf), and the full write-up is in [`docs/documentation.docx`](docs/documentation.docx).

## OOP concepts applied

| Concept | Where |
|---|---|
| **Encapsulation** | `Person` keeps `email` and `address` `protected`. I changed this from public in the diagram, since private data shouldn't be exposed |
| **Inheritance** | `Student` and `Teacher` extend `Person` |
| **Composition / aggregation** | Each level holds a `vector<T*>` of the level below it |
| **Static members** | `static` counters assign unique, auto-incrementing IDs per class |
| **Bidirectional links** | Enrolling a student updates both `Student::coursesEnrolled` and `Course::studentsEnrolled` |
| **Forward declarations** | Let mutually-referencing classes compile in a single file |

## Run it

```bash
g++ -std=c++11 UniversitiesManager.cpp -o universities-manager
./universities-manager
```

`main()` builds a small demo world: one faculty, a *cyber* department, two courses, two students and a teacher. It then registers students and assigns the teacher, printing each step.

## What I'd do differently today

This is a 2nd-year project, kept as submitted. Looking back:

- `viewStudentGrades()` was planned but never implemented.
- Raw pointers everywhere. Today I'd use references or `std::shared_ptr`/`weak_ptr` for the back-links.
- Everything lives in one file. Splitting it into a header and source file per class would make it easier to maintain.
- No interactive menu. The demo scenario is hard-coded in `main()`.

## Author

**Humam Al-Dhubhani** · [GitHub](https://github.com/humamaldhubhani)

<sub>Released under the [MIT License](LICENSE).</sub>
