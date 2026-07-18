#include <iostream>

#include <vector>

#include <string>

#include <limits>

using namespace std;

struct Department

{
	
    int id;
    
    string name;
    
    string facultyOffice;
    
};

struct Programme

{
	
    int deptId;
    
    string name;
    
};

struct Teacher

{
	
    string name;
    
    string subject;
    
    int deptId;
    
};

struct Student

{
	
    string name;
    
    int rollNumber;
    
    int deptId;
    
    int progIndex;
    
};

struct Admin

{
	
    string name;
    
};

vector <Department> departments;

vector <Programme> programmes;

vector <Teacher> teachers;

vector <Student> students;

vector <Admin> admins;

int totalClassrooms = 0;

bool isDeptIdValid (int id)

{
	
    for (const auto & dept : departments) if (dept.id == id) return true;
    
    return false;
    
}

int getDeptIndex(int id)

{
	
    for (int i = 0; i < departments.size(); i++)
    
        if (departments[i].id == id) return i;
        
    return -1;
    
}

int getValidatedInt (string prompt)

{
	
    int value;
    
    while (true)
	
	{
		
        cout << prompt;
        
        if (cin >> value)
		
		{
			
            cin.ignore (numeric_limits<streamsize>::max(), '\n');
            
            return value;
            
        }
		
		else
		
		{
			
            cout << "\nInvalid input! Please enter a number.\n";
            
            cin.clear();
            
            cin.ignore (numeric_limits<streamsize>::max(), '\n');
            
        }
        
    }
    
}

string getLine (string prompt)

{
	
    string input;
    
    cout << prompt;
    
    getline (cin, input);
    
    return input;
    
}

void addDepartment ()

{
	
    Department dept;
    
    dept.id = getValidatedInt ("\nEnter Department ID: ");
    
    dept.name = getLine ("\nEnter Department Name: ");
    
    dept.facultyOffice = getLine ("\nEnter Faculty Office Name: ");
    
    departments.push_back (dept);
    
    cout << "\nDepartment added!\n";
    
}

void addProgramme ()

{
	
    if (departments.empty()) { cout << "\nAdd a department first.\n"; return; }
    
    int deptId = getValidatedInt("\nEnter Department ID to add programme to: ");
    
    if (!isDeptIdValid(deptId)) { cout << "\nInvalid Department ID!\n"; return; }
    
    Programme prog;
    
    prog.deptId = deptId;
    
    prog.name = getLine ("\nEnter Programme Name: ");
    
    programmes.push_back (prog);
    
    cout << "\nProgramme added!\n";
    
}

void addTeacher ()

{
	
    if (departments.empty()) { cout << "\nAdd a department first.\n"; return; }
    
    int deptId = getValidatedInt ("\nEnter Department ID for Teacher: ");
    
    if (!isDeptIdValid(deptId)) { cout << "\nInvalid Department ID!\n"; return; }
    
    Teacher t;
    
    t.deptId = deptId;
    
    t.name = getLine("\nEnter Teacher Name: ");
    
    t.subject = getLine("\nEnter Subject: ");
    
    teachers.push_back(t);
    
    cout << "\nTeacher added!\n";
    
}

void addStudent ()

{
	
    if (departments.empty() || programmes.empty()) { cout << "\nAdd departments and programmes first.\n"; return; }
    
    int deptId = getValidatedInt ("\nEnter Department ID for Student: ");
    
    if (!isDeptIdValid(deptId)) { cout << "\nInvalid Department ID!\n"; return; }
    

    cout << "\nProgrammes in this Department:\n";
    
    vector <int> indices;
    
    for (int i = 0; i < programmes.size(); i++)
	
	{
		
        if (programmes[i].deptId == deptId)
		
		{
			
            cout << indices.size() << ". " << programmes[i].name << "\n";
            
            indices.push_back(i);
            
        }
        
    }
    
    if (indices.empty()) { cout << "\nNo programmes in this department.\n"; return; }

    int progChoice = getValidatedInt("\nChoose programme index: ");
    
    if (progChoice < 0 || progChoice >= indices.size()) { cout << "\nInvalid programme choice.\n"; return; }

    Student s;
    
    s.deptId = deptId;
    
    s.progIndex = indices [progChoice];
    
    s.name = getLine ("\nEnter Student Name: ");

    s.rollNumber = getValidatedInt ("\nEnter Roll Number: ");
    
    students.push_back (s);
    
    cout << "\nStudent added!\n";
    
}

void addAdmin ()

{
	
    Admin a;
    
    a.name = getLine ("\nEnter Admin Name: ");
    
    admins.push_back (a);
    
    cout << "\nAdmin added!\n";
    
}

void setClassrooms ()

{
	
    totalClassrooms = getValidatedInt ("\nEnter Total Classrooms: ");
    
    cout << "\nClassrooms updated!\n";
    
}

void editDepartment ()

{
	
    if (departments.empty()) { cout << "\nNo departments to edit.\n"; return; }
    
    for (const auto& d : departments)
    
        cout << d.id << ". " << d.name << " | " << d.facultyOffice << "\n";
        
    int id = getValidatedInt ("\nEnter Department ID to edit: ");
    
    int index = getDeptIndex (id);
    
    if (index == -1) { cout << "\nDepartment not found!\n"; return; }
    
    departments [index].name = getLine ("\nEnter new Department Name: ");
    
    departments [index].facultyOffice = getLine ("\nEnter new Faculty Office: ");
    
    cout << "\nDepartment updated!\n";
    
}

void editProgramme ()

{
	
    if (programmes.empty()) { cout << "\nNo programmes to edit.\n"; return; }
    
    for (int i=0;i<programmes.size();i++)
    
        cout << i << ". " << programmes [i].name << " (Dept ID: " << programmes [i].deptId << ")\n";
        
    int choice = getValidatedInt("\nEnter index of programme to edit: ");
    
    if (choice < 0 || choice >= programmes.size()) { cout << "\nInvalid choice.\n"; return;}
    
    programmes [choice].name = getLine ("\nEnter new Programme Name: ");
    
    cout << "\nProgramme updated!\n";
    
}

void editTeacher ()

{
	
    if (teachers.empty()) { cout << "\nNo teachers to edit.\n"; return; }
    
    for (int i=0;i<teachers.size();i++)
    
        cout << i << ". " << teachers [i].name << " | " << teachers [i].subject << " | Dept ID: " << teachers [i].deptId << "\n";
        
    int choice = getValidatedInt ("\nEnter index of teacher to edit: ");
    
    if (choice < 0 || choice >= teachers.size()) { cout << "\nInvalid choice.\n"; return;}
    
    teachers [choice].name = getLine ("\nEnter new Teacher Name: ");
    
    teachers [choice].subject = getLine ("\nEnter new Subject: ");
    
    teachers [choice].deptId = getValidatedInt ("\nEnter new Department ID: ");
    
    cout << "\nTeacher updated!\n";
    
}

void editStudent ()

{
	
    if (students.empty()) { cout << "\nNo students to edit.\n"; return; }
    
    for (int i=0;i<students.size();i++)
    
        cout << i << ". " << students [i].name << " | Roll: " << students [i].rollNumber << " | Dept ID: " << students [i].deptId
        
            << " | Programme: " << programmes [students[i].progIndex].name << "\n";
            
    int choice = getValidatedInt("\nEnter index of student to edit: ");
    
    if (choice < 0 || choice >= students.size()) { cout << "\nInvalid choice.\n"; return;}
    
    students [choice].name = getLine ("\nEnter new Student Name: ");
    
    students [choice].rollNumber = getValidatedInt ("\nEnter new Roll Number: ");
    
    students [choice].deptId = getValidatedInt ("\nEnter new Department ID: ");
    
    students [choice].progIndex = getValidatedInt ("\nEnter new Programme Index: ");
    
    cout << "\nStudent updated!\n";
    
}

void editAdmin ()

{
	
    if (admins.empty()) { cout << "\nNo admins to edit.\n"; return; }
    
    for (int i=0;i<admins.size();i++) cout << i << ". " << admins [i].name << "\n";
    
    int choice = getValidatedInt ("\nEnter index of admin to edit: ");
    
    if (choice < 0 || choice >= admins.size()) { cout << "\nInvalid choice.\n"; return;}
    
    admins [choice].name = getLine ("\nEnter new Admin Name: ");
    
    cout << "\nAdmin updated!\n";
    
}

void deleteDepartment ()

{
	
    if (departments.empty()) { cout << "\nNo departments to delete.\n"; return; }
    
    for (const auto& d: departments) cout << d.id << ". " << d.name << " | " << d.facultyOffice << "\n";
    
    int id = getValidatedInt ("\nEnter Department ID to delete: ");
    
    int index = getDeptIndex (id);
    
    if (index==-1) { cout << "\nDepartment not found!\n"; return; }
    
    for (int i=programmes.size()-1;i>=0;i--) if (programmes[i].deptId==id) programmes.erase(programmes.begin()+i);
    
    for (int i=students.size()-1;i>=0;i--) if (students[i].deptId==id) students.erase(students.begin()+i);
    
    departments.erase(departments.begin()+index);
    
    cout << "\nDepartment deleted!\n";
    
}

void deleteProgramme ()

{
	
    if (programmes.empty()) { cout << "\nNo programmes to delete.\n"; return; }
    
    for (int i=0;i<programmes.size();i++)
    
        cout << i << ". " << programmes[i].name << " (Dept ID: " << programmes[i].deptId << ")\n";
        
    int choice = getValidatedInt ("\nEnter index of programme to delete: ");
    
    if (choice<0 || choice>=programmes.size()) { cout << "\nInvalid choice.\n"; return; }
    
    for (int i=students.size()-1;i>=0;i--)
    
    {
    	
        if (students[i].progIndex==choice)
        
            students.erase(students.begin()+i);
            
        else if (students[i].progIndex>choice)
        
            students[i].progIndex--;
            
    }
    
    programmes.erase(programmes.begin()+choice);
    
    cout << "\nProgramme deleted!\n";
    
}

void deleteTeacher ()

{
	
    if (teachers.empty()) { cout << "\nNo teachers to delete.\n"; return; }
    
    for (int i=0;i<teachers.size();i++)
    
        cout << i << ". " << teachers[i].name << " | " << teachers[i].subject << " | Dept ID: " << teachers[i].deptId << "\n";
        
    int choice=getValidatedInt ("\nEnter index of teacher to delete: ");
    
    if (choice<0 || choice>=teachers.size()) { cout << "\nInvalid choice.\n"; return;}
    
    teachers.erase(teachers.begin()+choice);
    
    cout << "\nTeacher deleted!\n";
    
}

void deleteStudent ()

{
	
    if (students.empty()) { cout << "\nNo students to delete.\n"; return; }
    
    for (int i=0;i<students.size();i++)
    
        cout << i << ". " << students[i].name << " | Roll: " << students[i].rollNumber << " | Dept ID: " << students[i].deptId
        
            << " | Programme: " << programmes[students[i].progIndex].name << "\n";
            
    int choice = getValidatedInt ("\nEnter index of student to delete: ");
    
    if (choice<0 || choice>=students.size()) { cout << "\nInvalid choice.\n"; return; }
    
    students.erase (students.begin()+choice);
    
    cout << "\nStudent deleted!\n";
    
}

void deleteAdmin ()

{
	
    if (admins.empty()) { cout << "\nNo admins to delete.\n"; return; }
    
    for (int i=0;i<admins.size();i++) cout << i << ". " << admins[i].name << "\n";
    
    int choice=getValidatedInt ("\nEnter index of admin to delete: ");
    
    if (choice<0 || choice>=admins.size()) { cout << "Invalid choice.\n"; return;}
    
    admins.erase(admins.begin()+choice);
    
    cout << "\nAdmin deleted!\n";
    
}

void showDepartments ()

{
	
    if (departments.empty()){ cout << "\nNo departments.\n"; return;}
    
    cout << "\nDepartments:\n";
    
    for (const auto& d: departments)
    
        cout << d.id << ". " << d.name << " | Faculty Office: " << d.facultyOffice << "\n";
        
}

void showProgrammes ()

{
	
    if (programmes.empty()){ cout << "\nNo programmes.\n"; return;}
    
    cout << "\nProgrammes:\n";
    
    for (int i=0;i<programmes.size();i++)
    
        cout << i << ". " << programmes[i].name << " (Dept ID: " << programmes[i].deptId << ")\n";
        
}

void showTeachers ()

{
	
    if (teachers.empty()) { cout << "\nNo teachers.\n"; return;}
    
    cout << "\nTeachers:\n";
    
    for (int i=0;i<teachers.size();i++)
    
        cout << i << ". " << teachers[i].name << " | Subject: " << teachers[i].subject << " | Dept ID: " << teachers[i].deptId << "\n";
        
}

void showStudents ()

{
	
    if (students.empty()) { cout<<"\nNo students.\n"; return;}
    
    cout << "\nStudents:\n";
    
    for (int i=0;i<students.size();i++)
    
        cout << i << ". " << students[i].name << " | Roll: " << students[i].rollNumber << " | Dept ID: " << students[i].deptId
        
            << " | Programme: " << programmes[students[i].progIndex].name << "\n";
            
}

void showAdmins ()

{
	
    if (admins.empty()) { cout<<"\nNo admins.\n"; return;}
    
    cout<<"\nAdmins:\n";
    
    for (int i=0;i<admins.size();i++) cout << i << ". " << admins[i].name << "\n";
    
}

void showClassrooms ()

{
	
    cout << "\nTotal Classrooms: " << totalClassrooms << "\n";
    
}

int main ()

{
	
    while (true)
	
	{
        
        cout << "===================================\n";
        
        cout << "|                                 |\n";
        
        cout << "|     Campus Management System    |\n";
        
        cout << "|                                 |\n";
        
        cout << "===================================\n";
        
        cout << "\n0. Exit" << endl;
        
        cout << "\n1. Add Department" << endl;
        
        cout << "\n2. Show Departments" << endl;
        
        cout << "\n3. Edit Department" << endl;
        
        cout << "\n4. Delete Department" << endl;
        
        cout << "\n5. Add Programme" << endl;
        
        cout << "\n6. Show Programmes" << endl;
        
        cout << "\n7. Edit Programmes" << endl;
        
        cout << "\n8. Delete Programme" << endl;
        
        cout << "\n9. Add Teacher" << endl;
        
        cout << "\n10. Show Teachers" << endl;
        
        cout << "\n11. Edit Teacher" << endl;
        
        cout << "\n12. Delete Teacher" << endl;
        
        cout << "\n13. Add Student" << endl;
        
        cout << "\n14. Show Students" << endl;
        
        cout << "\n15. Edit Student" << endl;
        
        cout << "\n16. Delete Student" << endl;
        
        cout << "\n17. Add Admin" << endl;
        
        cout << "\n18. Show Admins" << endl;
        
        cout << "\n19. Edit Admin" << endl;
        
        cout << "\n20. Delete Admin" << endl;
        
        cout << "\n21. Set Classrooms" << endl;
        
        cout << "\n22. Show Classrooms" << endl;
        
        int choice = getValidatedInt ("\nEnter choice: ");
        
        switch (choice)
		
		{
			
            case 1:
			
			addDepartment ();
			
			break;
            
            case 2:
			
			showDepartments (); 
			
			break;
            
            case 3:
			
			editDepartment ();
			
			break;
            
            case 4:
			
			deleteDepartment ();
			
			break;
            
            case 5:
			
			addProgramme ();
			
			break;
            
            case 6:
			
			showProgrammes ();
			
			break;
            
            case 7:
			
			editProgramme ();
			
			break;
            
            case 8:
			
			deleteProgramme ();
			
			break;
            
            case 9:
			
			addTeacher ();
			
			break;
            
            case 10:
			
			showTeachers ();
			
			break;
            
            case 11:
			
			editTeacher ();
			
			break;
            
            case 12:
			
			deleteTeacher ();
			
			break;
            
            case 13:
			
			addStudent ();
			
			break;
            
            case 14:
			
			showStudents ();
			
			break;
            
            case 15:
			
			editStudent ();
			
			break;
            
            case 16:
			
			deleteStudent ();
			
			break;
            
            case 17:
			
			addAdmin ();
			
			break;
            
            case 18:
			
			showAdmins ();
			
			break;
            
            case 19:
			
			editAdmin ();
			
			break;
            
            case 20:
			
			deleteAdmin ();
			
			break;
            
            case 21:
			
			setClassrooms ();
			
			break;
            
            case 22:
			
			showClassrooms ();
			
			break;
            
            case 0:
			
			cout<<"\nExited.\n"; 
			
			return 0;
			
            default:
			
			cout<<"\nInvalid choice!\n";
            
        }
        
    }
    
}