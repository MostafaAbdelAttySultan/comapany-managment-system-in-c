#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// ******validation , date modification , sort , search after delete and printing ********//

typedef struct
{
  int y;
  int m;
  int d;
}date;
typedef struct
{
  char lName[15], fName[15],address[30],pNum[12], email[40],Id[10],salary[6];
  date bdate;
}employee;
employee empolyees[100];
int employees_count = 0;
void read_data(char path[]){
   FILE* fp = fopen(path, "r");
    int row = 0, column ;
    if (fp) {
        char line[1024]; // a string to hold lines and separate them
         // to konw where we are and to navigate
        while (fgets(line, 1024,fp)) {
            column = 0;
            char* value = strtok(line, ", ");    // Splitting the data making pointer to hold data

            while (value) { // to know if the previous line returned or not

                if(column == 0)
                    strcpy(empolyees[row].Id,value);
                if(column == 1)
                    strcpy(empolyees[row].lName,value);
                if(column == 2)
                    strcpy(empolyees[row].fName,value);
                if(column == 3)
                    strcpy(empolyees[row].salary,value);
                if(column == 4)
                    read_date(value,row);
                if(column == 5)
                    strcpy(empolyees[row].address,value);
                if(column == 6)
                    strcpy(empolyees[row].pNum,value);
                if(column == 7)
                    strcpy(empolyees[row].email,value);
                value = strtok(NULL,", ");
                column ++;
                //printf("\n%d\n",column);
            }
                row++;
            //printf("\n");
            }
    }else
          printf("Can't open file\n");

  fclose(fp);// Close the file
  employees_count = row;
}
void read_date(char s[],int r){
    char* d = strtok(s,"-");
    int counter = 0;
    while(d){
        if (counter == 0)
            empolyees[r].bdate.d = atoi(d);
        if (counter == 1)
            empolyees[r].bdate.m = atoi(d);
        if (counter == 2)
            empolyees[r].bdate.y = atoi(d);
        counter ++;
        d = strtok(NULL,"-");
    }
}
void print_employee(int i){

    printf("\nID:%s\t LastName:%s \tFirstName:%s\tSalary:%s\tDate:%d/%d/%d\t",empolyees[i].Id,empolyees[i].lName,empolyees[i].fName,empolyees[i].salary,empolyees[i].bdate.d,empolyees[i].bdate.m,empolyees[i].bdate.y);
    printf("Address:%s\tphone-number:%s\temail:%s\n",empolyees[i].address,empolyees[i].pNum,empolyees[i].email);
}
void search(){
    char target[30];
    int flag = 0;
    printf("\n====================\nEntering search function\n");
    printf("Please Enter the last name of employee you want to search:");
    scanf("%s",&target);
    for(int i = 0;i<employees_count;i++){
        if(!strcasecmp(empolyees[i].lName,target)){
            print_employee(i);
            flag ++ ;
        }//printf("%d",flag);
    }
    if(!flag)
        printf("NO match\nWe did not found an employee with last name: %s",target);



}
void add(){
    printf("\n=========================\nAdding a new employee\nEnter ID:\n>>");
    scanf("%s",&empolyees[employees_count].Id);//check if id is reapeated
    printf("Enter last Name:\n>>");
    scanf("%s",&empolyees[employees_count].lName);
    printf("Enter first Name:\n>>");
    scanf("%s",&empolyees[employees_count].fName);
    printf("Enter salary:\n>>");
    scanf("%s",&empolyees[employees_count].salary);//check is num
    printf("Enter birth Date:\nday>>");
    scanf("%d",&empolyees[employees_count].bdate.d);
    printf("month>>");
    scanf("%d",&empolyees[employees_count].bdate.m);
    printf("year>>");
    scanf("%d",&empolyees[employees_count].bdate.y);
    printf("Enter address:\n>>");
    scanf("%s",&empolyees[employees_count].address);
    printf("Enter phone number:\n>>");
    scanf("%s",&empolyees[employees_count].pNum);//check the first 2 intials and lenght
    getchar();
    printf("Enter email:\n>>");
    scanf("%s",&empolyees[employees_count].email);//check for @ and .
    print_employee(employees_count);

    employees_count++;
}
void delete_employee(){
    char fn[30];
    char ln[30];
    int i;
    printf("\n===============\nDeleting employees\nEnter the last name of employee you want to delete:\n>>");
    scanf("%s",&ln);
    printf("Enter first name you want to delete\n>>");
    scanf("%s",&fn);
    for( i = 0;i<employees_count;i++)
        if(!(strcasecmp(empolyees[i].lName,ln) && strcasecmp(empolyees[i].fName,fn))){
            strcpy(empolyees[i].Id,"0");
            //print_employee(i);
        }
    print_sorted();
}
void modify(){
    char id[10],NEW[100];
    int i ,target_index,option;
    printf("===============\n Modifying employees Data\nEnter ID of the employee you want to modify\n>>");
    scanf("%s",&id);
    for(i =0;i<employees_count;i++)
        if(!strcmp(empolyees[i].Id,id))
            break;
    printf("Enter the number for the value you want to change for employee %d\n1:firstName\n2:LastNAme\n3:salary\n4:birthdate\n5:address\n6:Phonenumber\n7:Email\n>>",i+1);
    scanf("%d",&option);
    printf("\nEnter New Value:\n>>");
    scanf("%s",&NEW);
    switch(option){
        case (1):
            strcpy(empolyees[i].fName,NEW);
            break;
        case (2):
            strcpy(empolyees[i].lName,NEW);
            break;
        case (3):
            strcpy(empolyees[i].salary,NEW);
            break;
        case (4):
            //read_date()
            break;
        case (5):
            strcpy(empolyees[i].address,NEW);
            break;
        case (6):
            strcpy(empolyees[i].pNum,NEW);
            break;
        case (7):
            strcpy(empolyees[i].email,NEW);
            break;
        default:
            printf("You did NOT enter a ");
            break;


        }
        print_sorted();
}
void save(){
    FILE* fp = fopen("employeesDB.txt",w);
    fprintf(fp,"%s,%s,%s,%s,%d-%d-%d,%s,%s,%s\n",empolyees[i].Id,empolyees[i].lName,empolyees[i].fName,empolyees[i].salary,empolyees[i].date.d,empolyees[i].date.m,empolyees[i].date.y,empolyees[i].address,empolyees[i].pNum,empolyees[i].email);
    fprintf(EOF);
}

void print_sorted(){
    for(int i =0;i<employees_count;i++)
        if(strcmp(empolyees[i].Id,"0"))
            print_employee(i);
}
int main ()
{
    read_data("employeesDB.txt");
    //printf("%d",employees_count);
    //print_employee(2);
    int restart,option;
    printf("\n\t\tWelcome");
    while(1){
        printf("\nEnter the number of the function you want\n1:Search\n2:Add\n3:Delete\n4:Modify\n5:Print sorted\n6:Save\n7:Quit\n>>");
        scanf("%d",&option);
        switch(option){
        case (1):
            search();
            break;
        case (2):
            add();
            break;
        case (3):
            delete_employee();
            break;
        case (4):
            modify();
            break;
        case (5):
            printf("YAYYYYYY");
            break;
        case (6):
            save();
            break;
        case (7):
            printf("YAYYYYYY");
            break;
        default:

            break;


        }
    }

  return 0;
}
