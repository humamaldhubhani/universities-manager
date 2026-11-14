#include<iostream>
#include <vector>

using namespace std;

class University;
class Faculty;
class Department;
class Course;
class Student;
class Person;
class Teacher;





class University {
public:
	int UniversityID;
	int static Universitycounter;//counter to automattically assign the ID
	string name;
	string location;
	string header_name;
	vector<Faculty*> faculties;

	University( string name, string location,string header_name);
	void get_all();
	void list_faculties();
	void addFaculty(Faculty* faculty);
	void removeFaculty(Faculty* faculty);

	
}ASU("Ar-rrashed","14th octoper, street","Humam");


class Faculty {
public:
	//====attributes======
	int facultyID;
	int static facultycounter;
	string name_faculty;
	string header_name;
	University* university;
	vector<Department*> departments;
	Faculty(string name_faculty, string header_name,University* u);
	void get_faculty_info();
	void list_departments();                                  
	void addDepartment(Department* department);
	void removeDepartment( Department* department);
	
};




class Person {
	protected://===========was public in the class diagram==================private information no one can have it============================
		string email;
		string address;
	public:
		string name;
};


class Student:public Person{		
		
	public:
		//======attributes====
		int studentID;
		int  static Studentcounter;//counter to automatically assign the ID
		string PhoneNumber;
		string major;
		Department* department;
		vector <Course*> coursesEnrolled;	
		//=====methods=========
		Student(string name, string email,string address,Department* department);	
		void registerCourse(Course* course);
		void dropCourse(Course* course);
		void ListStudentCourses();							
		void viewStudentGrades();//========================================did not make it yet====================================================================
		void GetStudentInfo();	
		bool CourseIshere(Course* course);	
	
};





class Department{
	public:
		//=========attributes=========
	int departmentID;
	int static DepartmentCounter;
	string name;
	Faculty* faculty;
	vector<Course*> DepartmentCourses;
	vector<Student*> DepartmentStudent; 
	vector<Teacher*> DepartmentTeachers;
	//=======methods================
	Department(string name,Faculty* faculty);
	void addStudent(Student* student);
	void removeStudent(Student* student);
	void addCourse(Course* course);
	void removeCourse(Course* course);
	void addTeacher(Teacher* teacher);
	void removeTeacher(Teacher* teacher);
	void assignTeacher(Course* course,Teacher* teacher);
	void displayDepartmentTeachers();
	void displayDepartmentStudent();
	void displayDepartmentCourse();
	bool StudentIShere(Student* student);
	bool CourseIshere(Course* course);
	
	
};



class Course{
	public:
		//=====attributes======
		int courseID;
		int static Coursecounter;
		int Student_number;
		string name;
		Teacher* teacher;
		vector <Student*> studentsEnrolled;
		//=========methods	
		Course(Department* department,string name);
		void enrollStudent(Student* student);
		void unenrollStudent(Student* student);		
		void ListStudentEnrolled();		
		Student* checkIDCourse(int id);
		void ShowCourseInfo(); 
		

};







class Teacher:public Person{
	public:
		//=====attributes=======
		int teacherID;
		int static Teachercounter;
		struct description{
			string qualification;
			int YearsOfExperince;
			
		}descripe;
		Department* department;
		vector <Course*> coursesTeaching;//this list will be fulled by department by (assignprofessortocourse) method
		//=====methods=========
		Teacher(string name ,string email , string address , string qulaifications ,int  YearsOfExperince,Department* department); //============it was a function and I make it Constructor=============================
		void ListcoursesTeaching();
		void ShowTeacherInfo();
	
};









 
















int main(){

	Faculty f1("Engineering","humam",&ASU);
	f1.get_faculty_info();
	Department d1("cyber",&f1);
Course c1(&d1,"data structue"),c2(&d1,"network");
Student s1("humam","humam@gmail","hadda street",&d1);
Student s2("Eyad","ghjk","fghjkl",&d1);

Teacher t1("Bilal","fghjkl","ghjkl","ghjk",7,&d1);
s1.registerCourse(&c1);
d1.assignTeacher(&c1,&t1);
s2.registerCourse(&c1);
d1.assignTeacher(&c2,&t1);









	
	return 0;
}

//====================University==========================================

int University::Universitycounter = 0;



University::University(string name, string location, string header_name) {

	this->name = name;
	this->location = location;
	this->header_name = header_name;
	UniversityID = ++Universitycounter;
}



void University::get_all() {
	cout << "UniversityID:" << UniversityID << endl;
	cout << "University Name :" << name << endl;
	cout << "University loation:" << location << endl;
	cout << "University Header name" << header_name << endl;
	
}


void University::list_faculties() {
	int i = 1;
	cout << "\t\tThe faculties of " << name << " are : " << endl;
	for (Faculty* faculty : faculties) {
		cout << i << " - faculty ID:" << faculty->facultyID << "\tFaculty name" << faculty->name_faculty << endl;
		i++;
	}

}

void University::addFaculty(Faculty* faculty) {
	faculties.push_back(faculty);

}


void University::removeFaculty(Faculty* faculty) {
	for (int i = 0; i < faculties.size(); i++) {
		if (faculties.at(i) == faculty) {
			faculties.erase(faculties.begin() + i);
			break;
		}
	}
}





//====================Faculty==========================================
int Faculty::facultycounter = 0;
Faculty::Faculty(string name_faculty, string header_name,University* u) {
	university=u;
	university->addFaculty(this);
	this->name_faculty=name_faculty; 
	this->header_name = header_name;
	facultyID=++facultycounter;
}

void Faculty::get_faculty_info(){                                        
	cout<<"University : "<<university->name<<endl;
	cout<<"Facutly ID: "<<facultyID<<endl;
	cout<<"Faculty Name : "<<name_faculty<<endl;
	cout<<"Header name  : "<<header_name<<endl;
	
}


void Faculty::list_departments() {
	for (Department* department : departments) {
		int i = 1;
		cout << i << "-" << "department Name" << department->name;
		i++;
	}
}



void Faculty::addDepartment(Department* department) {
	departments.push_back(department);

}



void Faculty::removeDepartment(Department* department) {
	for (int i = 0; i < departments.size(); i++) {
		if (departments.at(i) == department) {
			departments.erase(departments.begin() + i);
			break;
		}
	}
}





//====================Department==========================================


int Department::DepartmentCounter=0;

Department::Department(string name,Faculty* faculty){
	this->faculty=faculty;
	this->faculty->addDepartment(this);
	this->name=name;
	departmentID=++DepartmentCounter;
}

void Department::addStudent(Student* student){
	DepartmentStudent.push_back(student);
}

void Department::removeStudent(Student* student){
	bool found=false;
	for(int i=0;i<DepartmentStudent.size();i++){
		if(student==DepartmentStudent.at(i)){
			DepartmentStudent.erase(DepartmentStudent.begin()+i);
			found=false;
			break;
		}
	}
	if(found==false)
	cout<<student->name<<" is not in this department\n";
}

void Department::addCourse(Course* course){
	DepartmentCourses.push_back(course);
}

void Department::removeCourse(Course* course){
	bool found=false;
	for(int i=0;i<DepartmentCourses.size();i++){
		if(course==DepartmentCourses.at(i)){
			DepartmentCourses.erase(DepartmentCourses.begin()+i);
			found=true;
			break;
		}
	
	}
	if(found==false)
	cout<<course->name<<" is not within this department courses list\n";

}

void Department::addTeacher(Teacher* teacher){
	DepartmentTeachers.push_back(teacher);
}

void Department::removeTeacher(Teacher* teacher){
	for(int i=0;i<DepartmentTeachers.size();i++){
		if(DepartmentTeachers.at(i)==teacher){
			DepartmentTeachers.erase(DepartmentTeachers.begin()+i);
			cout<<"The teacher is removed successfully\n";
		}
		else
		cout<<"The teacher is not in this department\n";
	}
}

void Department::displayDepartmentStudent(){
	cout<<"\tStudent ID \t Student Name "<<endl<<endl;
		int i=1;
	for(Student* student : DepartmentStudent){
	
		cout<<i<<" - "<<"Student ID : "<<student->studentID<<"\t  Name : "<<student->name<<"\n";
		i++;
	}
		cout<<endl<<endl;
}

void Department::displayDepartmentCourse(){
	cout<<"\tCourse ID \t   Course Name"<<endl<<endl;
		int i=1;
	for(Course* course: DepartmentCourses){
	
		cout<<i<<" - "<<"Course ID : "<<course->courseID<<"\t Course Name : "<<course->name<<endl;
		i++;
	}
	cout<<endl<<endl;
}

void Department::displayDepartmentTeachers(){
	int i=1;
	cout<<"Here are the teachers in this department\n\n";
	cout<<"Teacher ID : "<<"\t Teacher Name : "<<endl;
	for(Teacher* teacher : DepartmentTeachers){
		cout<<i<<" - Teacher ID : "<<teacher->teacherID<<"\tTeacher Name : "<<teacher->name<<endl;
	}
}

bool Department::StudentIShere(Student* student){
	bool found=false;
	for(int i=0;i<DepartmentStudent.size();i++){
		if(student==DepartmentStudent.at(i)){
			 found=true;
			 break;	
		}
	}
	return found;
	
}

bool Department::CourseIshere(Course* course){
	bool found=false;
	for(int i=0;i<DepartmentCourses.size();i++){
		if(course=DepartmentCourses.at(i)){
			found=true;
			break;
		}
	}
	return found;
}

void Department::assignTeacher(Course* course,Teacher* teacher){

	course->teacher=teacher;
	teacher->coursesTeaching.push_back(course);
	cout<<"The teacher : "<<teacher->name<<" was successfuly assigned to "<<course->name<<endl;
}









//====================Course==========================================



int Course::Coursecounter=0;

Course::Course(Department* department,string name){
	
	department->addCourse(this);
	this->name=name;
	courseID=++Coursecounter;
	
}

void Course::ListStudentEnrolled(){
		int i=1;
		cout<<"Course name : "<<name<<"\tCourse ID : "<<courseID<<"\t  Student Enrolled : "<<Student_number<<endl<<endl<<endl;
	for(Student* student : studentsEnrolled){
	
		cout<<i<<"-"<<"Student Name : "<<student->name<<"\t\tStudent ID : "<<student->studentID<<endl<<endl;	
		i++;	
	}
	
}

void Course::enrollStudent(Student* student){

	Student_number++;
	studentsEnrolled.push_back(student);
	
}

void Course::unenrollStudent(Student* student){
	
	for(int i=0;i<studentsEnrolled.size();i++){
			if(student==studentsEnrolled.at(i)){	
	studentsEnrolled.erase(studentsEnrolled.begin()+i);
			}
		}	
		student->dropCourse(this);
		
		Student_number--;
	}
	
void Course::ShowCourseInfo(){
	cout<<"Course ID : "<<courseID<<endl;
	cout<<"Course Teacher: Dr."<<teacher->name<<endl;
	cout<<"Number of students registered in this Course : "<<studentsEnrolled.size()<<endl;
}












//====================Student==========================================
int Student::Studentcounter=0;

Student::Student(string name, string email,string address,Department* department){
	this->name=name;
	this->address=address;
	this->email=email;
//	this->department=department;
	major=department->name;
	department->addStudent(this);
	Studentcounter++;
	studentID=Studentcounter;
}

void Student::registerCourse(Course* course){	
		coursesEnrolled.push_back(course);		
		course->enrollStudent(this);

		cout<<"The course : "<<course->name<<" was added for you successfully"<<endl;
		

}

void Student::dropCourse(Course* course){
	
	
	if(department->StudentIShere(this)){
		if(department->CourseIshere(course)){
			if(this->CourseIshere(course)){
					for(int i=0;i<coursesEnrolled.size();i++){
						if(course==coursesEnrolled.at(i)){
							coursesEnrolled.erase(coursesEnrolled.begin()+i);
							course->unenrollStudent(this);
					}	
			}
			}else
			cout<<"You are not registered in this course\n";
		
		}else
		cout<<"This course is not within your department\n";
		}else
	cout<<"You are not added to your department !!\n please contact with your department\n";


}

void Student::ListStudentCourses(){
		cout<<" \t\t\t\t\t Hello "<<name<<","<<endl;
		cout<<"\t\t\t here are the courses your are registered in : "<<endl<<endl;
	if(!coursesEnrolled.empty()){
		int i=1;
		for(Course* course : coursesEnrolled){
			
			cout<<"\t\t\t\t"<<i<<" - "<<"Course name : "<<course->name<<endl;
			i++;
		}	
	}else
	cout<<"\n\n\n\t\t\t  "<<"Your are not registered in any course yet!!\n";
	
	
	
}

void Student::GetStudentInfo(){
	cout<<"Hello "<<name<<endl<<endl;
	cout<<"ID : "<<studentID<<endl;
	cout<<"Phone Number : "<<PhoneNumber<<endl;
	cout<<"Department : "<<major<<endl;
	cout<<"E-mail : "<<email<<endl;
	cout<<"Adress : "<<address<<endl;
}

bool Student::CourseIshere(Course* course){
	bool found=false;
	for(int i=0;i<coursesEnrolled.size();i++){
		if(course==coursesEnrolled.at(i)){
			found=true;
			break;
		}
	}
	return false;
}






//====================Teacher==========================================

int Teacher::Teachercounter=0;

Teacher::Teacher(string name ,string email , string address , string qulaifications ,int  YearsOfExperince, Department* department){
	
	descripe.qualification=qulaifications;
	descripe.YearsOfExperince=YearsOfExperince;
	this->department=department;
	department->addTeacher(this);
	this->name=name;
	this->email=email;
	this->address=address;
	Teachercounter++;
	teacherID=Teachercounter;
}



void Teacher::ShowTeacherInfo(){
	cout<<"ID : "<<teacherID<<endl;
	cout<<"Name : "<<name<<endl;
	cout<<"qualifications : "<<descripe.qualification<<endl;
	cout<<"Years of excperience : "<<descripe.YearsOfExperince<<endl;
	
}


void Teacher::ListcoursesTeaching(){

	cout<<"\n\n\t\t\t\t\t welcome Dr."<<name<<endl;
	
	if(coursesTeaching.size()!=0){
		int i=1;
		cout<<"\t\tHere are the courses your department assigned you to teach :\n"<<endl;
		for(Course* course : coursesTeaching){
			cout<<"\t\t"<<i<<" - Course name : "<<course->name<<"\t Course ID : "<<course->courseID<<"\t\tNumber of student : "<<course->Student_number<<endl;	
		i++;
		}
			
	}else
	cout<<"\n\n\t\t  Sorry Dr."<<name<<" it looks like your department didnot assign you to any course\n";
}














