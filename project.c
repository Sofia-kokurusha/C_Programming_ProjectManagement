#include <stdio.h>
#include <string.h>
// Student structure
struct Student {
    int id;
    char name[50];
    char program[50];
    float gpa;
};

// Professor structure
struct Professor {
    int id;
    char name[50];
    char department[50];
    struct Student supervised_student[10];
};

void sort_students_gpa(struct Student students[25]){
    for(int i = 0; i<25; i++){
        for(int k = i+1; k<25; k++){
            if(students[i].id != 0 && students[k].id != 0 && students[i].gpa < students[k].gpa){
                struct Student temp = students[i];
                students[i] = students[k];
                students[k] = temp;
            }
        }
    }
    printf("Students sorted by GPA (highest to lowest): \n");
}

void sort_students_program(struct Student students[25]){
    for(int i = 0; i<25; i++){
        for(int k = i+1; k<25; k++){
            if(students[i].id!= 0 && students[k].id != 0 &&
                strcmp(students[i].program, students[k].program)>0){
                    struct Student temp = students[i];
                    students[i] = students[k];
                    students[k] = temp;
                }
        }
    }
    printf("Students sorted by Academic Program Name (A-Z): \n");
}

// Add a new student 
void add_student(struct Student s[25], int nb){
    
    printf("Enter name of a student:\n");
    fflush(stdin);
    fgets(s[nb].name,sizeof(s[nb].name),stdin);
    
    int valid = 0;
    while(!valid){
        printf("Enter student id:\n");
        scanf("%d", &s[nb].id);
        if(s[nb].id>0)
            valid = 1;
        else
            printf("Invalid ID. Please try again.\n");
    }

    printf("Enter program name student is enrolled in:\n");
    fflush(stdin);
    fgets(s[nb].program,sizeof(s[nb].program),stdin);

    int valid_gpa = 0;
    while(!valid_gpa){
        printf("Enter GPA of a student:\n");
        scanf("%f", &s[nb].gpa);
        if(s[nb].gpa > 0.0 && s[nb].gpa < 4.1)
            valid_gpa = 1;
        else
            printf("Invalid GPA. Please try again.\n");
    }
}

// Add a new professor 
void add_professor(struct Professor p[25], int nb){
    printf("Enter name of a professor:\n");
    fflush(stdin);
    fgets(p[nb].name,sizeof(p[nb].name),stdin);

    int valid = 0;
    while(!valid){
        printf("Enter professor id:\n");
        scanf("%d", &p[nb].id);
        if(p[nb].id>0)
            valid = 1;
        else
            printf("Professor ID must be positive.\n");
        
    }

    printf("Enter department name:\n");
    fflush(stdin);
    fgets(p[nb].department,sizeof(p[nb].department),stdin);
}

// Display full list of students 
void display_students(struct Student students[25]){
    for (int i=0;i<25;i++){
        if(students[i].id){
            printf("----------\n");
            printf("Name: %s\n Student ID: %d\n Program: %s\n GPA: %f \n",
                students[i].name,
                students[i].id,
                students[i].program,
                students[i].gpa);
        }
    }
    printf("---------\n");
}

// Display full list of professors 
void display_professors(struct Professor professors[25]){
    for (int i=0; i<25;i++){
        if(professors[i].id){
            printf("-----------\n");
            printf("Name: %s\n Professor ID: %d\n Department: %s\n",
                professors[i].name,
                professors[i].id,
                professors[i].department);
        }
    }
    printf("---------\n");
}

void display_supervised(struct Professor professors[25],int unique_id){
    for (int i = 0;i<25;i++){
        
        if(professors[i].id == unique_id){
            printf("Professor %s with an ID %d supervises: \n",
                professors[i].name,
                professors[i].id
            );
        
            for(int j = 0; j< 10; j++){
                if (professors[i].supervised_student[j].id != 0){
                    printf("- Student: %s (ID: %d, GPA: %f)", 
                        professors[i].supervised_student[j].name,
                        professors[i].supervised_student[j].id,
                        professors[i].supervised_student[j].gpa
                    );
                }
            }
            return;
        }

    }
    printf("Professor with ID %d not found.\n",unique_id);
}

void search_student(struct Student students[25], int student_id){
    for(int i = 0; i<25; i++){
        if(student_id == students[i].id){
        printf("Student found: %s, ID: %d, GPA: %f, Program: %s \n", 
            students[i].name, students[i].id, students[i].gpa, students[i].program);
            return;
        }
    }
    printf("Student with ID %d not found.\n", student_id);
}

void modify_student(struct Student students[25]){
    printf("---- Do you want to modify a student record?---- \n");

    int valid = 0;
    int st_id = -1;
    while(!valid){
        printf("Enter Student id:\n");
        scanf("%d", &st_id);
        if(st_id>0)
            valid = 1;
        else
            printf("Invalid ID. Please try again.\n");
    }
    for(int i = 0; i<25; i++){
        if(students[i].id == st_id){
            printf("Student found: %s ID: %d, GPA: %f, Program: %s \n",
                students[i].name,students[i].id,students[i].gpa, students[i].program);
            
            int choice;
            printf("What do you want to modify?\n");
            printf("1. Name\n 2. Program\n 3. GPA\n Enter your choice:\n");
            scanf("%d", &choice);
            getchar();

            switch (choice){
                case 1:
                    printf("Enter new name:\n");
                    fflush(stdin);
                    fgets(students[i].name,sizeof(students[i].name),stdin);
                    break;
                
                case 2:
                    printf("Enter new program:\n");
                    fflush(stdin);
                    fgets(students[i].program,sizeof(students[i].program),stdin);
                    break;
                
                case 3:
                    printf("Enter new GPA:\n");
                    float new_gpa;
                    scanf("%f",&new_gpa);
                    if(new_gpa > 0.0 && new_gpa < 4.1){
                        students[i].gpa = new_gpa;
                    } else {
                        printf("Invalid GPA. Please try again. \n");
                    }
                    break;
                default:
                    printf("Invalid choice.\n");
            }
            printf("Student record updated successfully.\n");
            return;
        }
    }

    printf("Student with ID %d not found.\n", st_id);
    
}

void delete_student(struct Student students[25]){
    printf("---- Do you want to delete a student record?---- \n");

    int valid = 0;
    int st_id = -1;
    while(!valid){
        printf("Enter Student id:\n");
        scanf("%d", &st_id);
        if(st_id>0)
            valid = 1;
        else
            printf("Invalid ID. Please try again.\n");
    }
    for(int i = 0; i<25; i++){
        if(students[i].id == st_id){
            printf("Student found: %s ID: %d, GPA: %f, Program: %s \n",
                students[i].name,students[i].id,students[i].gpa, students[i].program);

            int choice;
            printf("Please confirm that you want to delete a student record.\n");
            printf("1. Yes, I confirm\n 2. No, I don't confirm\n Enter your choice:\n");
            scanf("%d", &choice);
            getchar();

            switch (choice) {
                case 1:
                students[i].id = 0;
                students[i].gpa = 0;
                strcpy(students[i].name, "");
                strcpy(students[i].program, "");

                printf("Student record deleted successfully.\n");
                break;

                case 2:
                    printf("Deletion canceled.\n");
                    break;
            
                default:
                    printf("Invalid choice.\n");
            }
            return;
        }
    }
    printf("Student with ID %d not found.\n", st_id);
}

void assign_student(struct Professor professors[25],struct Student students[25],int student_id, int professor_id){
    int student_index = -1;
    for(int j = 0; j<25; j++){
        if(students[j].id == student_id){
            student_index = j;
            break;
        }
    }
    if(student_index == -1){
        printf("Student ID not found.\n");
        return;
    }
    int professor_index = -1;
    for(int k = 0; k<25;k++){
        if(professors[k].id == professor_id){
            professor_index=k;
            break;
        }
    }
    if(professor_index == -1){
        printf("Professor ID not found.\n");
        return;
    }

    int assigned = 0;
    for(int i = 0; i< 10; i++){
        if(professors[professor_index].supervised_student[i].id == 0){
            professors[professor_index].supervised_student[i] = students[student_index];

            printf("Student %s is assigned to Professor %s \n", 
                students[student_index].name,
                professors[professor_index].name);
            assigned = 1;
            break;
        }
    }
    if(!assigned){
        printf("Professor %s already supervises 10 students.\n",professors[professor_index].name);
    }
}

int main(){
    struct Student students[25]={0};
    struct Professor professors[25]={0};
    int nbstudents=0;
    int nbprofs = 0;

    int menuchoice = 0;

    do {
        printf("\n -------------- MENU -------------- \n");
        printf("1. Add Student\n");
        printf("2. Add Professor\n");
        printf("3. Display All Students\n");
        printf("4. Display All Professors\n");
        printf("5. Assign Student to Professor\n");
        printf("6. Display Students Supervised by a Professor \n");
        printf("7. Search Student by ID\n");
        printf("8. Modify Student Record\n");
        printf("9. Delete Student Record\n");
        printf("10. Sort Students by GPA\n");
        printf("11. Sort Students by Academic Program\n");
        printf("0. Exit\n");
        scanf("%d",&menuchoice);
        getchar();

        switch(menuchoice){
            case 1:
                if (nbstudents<25){
                    add_student(students,nbstudents);
                    nbstudents++;
                }
                else {
                    printf("Student list is full.\n");
                }
                break;

            case 2:
                if (nbprofs<25){
                    add_professor(professors,nbprofs);
                    nbprofs++;
                }
                else {
                    printf("Professor list is full.\n");
                }
                break;
            
            case 3:
                display_students(students);
                break;
            
            case 4:
                display_professors(professors);
                break;
            
            case 5:{
                int st_id, prof_id;
                printf("Enter Student ID to be supervised: \n");
                scanf("%d",&st_id);
                printf("Enter Professor ID to assign: \n");
                scanf("%d",&prof_id);
                assign_student(professors,students,st_id,prof_id);
                break;
            }
            case 6: {
                int prof_id;
                printf("Enter Professor ID to view supervised students: \n");
                scanf("%d",&prof_id);
                display_supervised(professors,prof_id);
                break;
            }
            case 7:{
                int st_id;
                printf("Enter Student ID to search: \n");
                scanf("%d",&st_id);
                search_student(students,st_id);
                break;
            }   
            case 8:
                modify_student(students);
                break;
            
            case 9:
                delete_student(students);
                break;

            case 10:
                sort_students_gpa(students);
                break;

            case 11:
                sort_students_program(students);
                break;

            case 0:
                printf("Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please try again. \n");
        }
    } while (menuchoice !=0);
    return 0;
}
