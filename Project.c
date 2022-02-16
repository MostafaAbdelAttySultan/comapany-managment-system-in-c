#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// Without data bases or OOP as it was not mentioned 
// add validations to modify
// ****** sort , search after delete and printing & add check in the quit to ask for saving or not //////// validation names AND DATE MODIFICATION change saving path
typedef struct
{
  int y;
  int m;
  int d;
}date;
typedef struct
{
  char lName[15], fName[15],address[30],pNum[12], email[40],Id[10],salary[12];
  date bdate;
}employee;

// Global variables
employee employees[100];
int employees_count = 0,saveflag = 0,i;
char path[100] = "Company.txt", strd[5],strm[5],stry[5];

//reading functions
void read_data(){ // reading the data from the CSV file in the bath (global variable)
   FILE* fp = fopen(path, "r");
    int row = 0, column ;
    if (fp) {
        char line[1024]; // a string to hold lines and separate them
         // to konw where we are and to navigate
        while (fgets(line, 1024,fp)) {
            column = 0;
            char* value = strtok(line, ",-\n");    // Splitting the data making pointer to hold data

            while (value) { // to know if the previous line returned or not

                if(column == 0)
                    strcpy(employees[row].Id,value);
                if(column == 1)
                    strcpy(employees[row].lName,value);
                if(column == 2)
                    strcpy(employees[row].fName,value);
                if(column == 3)
                    strcpy(employees[row].salary,value);
                if(column == 4)
                    employees[row].bdate.d= atoi(value);
                if(column == 5)
                    employees[row].bdate.m= atoi(value);
                if(column == 6)
                    employees[row].bdate.y= atoi(value);
                if(column == 7)
                    strcpy(employees[row].address,value);
                if(column == 8)
                    strcpy(employees[row].pNum,value);
                if(column == 9)
                    strcpy(employees[row].email,value);
                value = strtok(NULL,",-\n");
                column ++;
            }
                row++;
            }
            printf("\t      +========+\n\t     Reading Done\n\t      +========+\n");
    }else
          printf("\a\nXXXXXX\tCan't open file\tXXXXXX\n");

  fclose(fp);// Close the file
  employees_count = row;
}
void read_date(char s[],int r){// DID NOT WORK WELL RESULTED IN BREAK IM THE WHILE
    char* d = strtok(s,"-");
    int counter = 0;
    while(d){
        if (counter == 0)
            employees[r].bdate.d = atoi(d);
        if (counter == 1)
            employees[r].bdate.m = atoi(d);
        if (counter == 2)
            employees[r].bdate.y = atoi(d);
        counter ++;
        d = strtok(NULL,"-");
    }
}

// working functions
void search(){ //prints the input it wants to search employees by last name
    char target[30];
    int flag = 0;
    printf("\n====================\nEntering search function\n");
    printf("Please Enter the last name of employee you want to search:");
    getchar();
    gets(target);
    while(!Svalidation(target,1)){
        printf("\aXXXXXX Wrong input please enter a valid name XXXXX\n");

        gets(target);
    }
    for( i = 0;i<employees_count;i++){
        if(!strcasecmp(employees[i].lName,target)){
            printf("\t+++=======+++\nWe found the employee on index %d and here is the data \n",i+1);
            print_employee(i);
            flag ++ ;
        }//printf("%d",flag);
    }
    if(!flag)
        printf("\aXXXX\tNO match\tXXXX\nWe did not found an employee with last name: %s\n",target);



}
void add(){ // adding new employee
    int i, flag = 1;
    printf("\n=========================\nAdding a new employee\nEnter ID:\n>>");
    scanf("%s",&employees[employees_count].Id);//check if id is wrong
    while(!Svalidation(employees[employees_count].Id,2)){
                printf("\aXXXXXX Wrong input please a id XXXXXX\n");
                scanf("%s",&employees[employees_count].Id);
            }
    while(flag){//to know if id repeated or 0
        flag = 0;
        for(i = 0;i<employees_count;i++)
            if(!strcmp(employees[employees_count].Id,employees[i].Id) || !strcmp(employees[employees_count].Id,"0"))
                flag =1;

        if (flag){
            printf("\n\aSorry we can not add This ID it is repeated or 0\nReenter the id\n>>");
            scanf("%s",&employees[employees_count].Id);
        }
        }
    // Asking user for data
    printf("Enter last Name:\n>>");
    getchar();
    gets(employees[employees_count].lName);
    while(!Svalidation(employees[employees_count].lName,1)){
        printf("\aXXXXXX Wrong input please enter a valid name XXXXX\n");
        getchar();
        gets(employees[employees_count].lName);
    }
    printf("Enter first Name:\n>>");
    gets(employees[employees_count].fName);
    while(!Svalidation(employees[employees_count].fName,1)){
        printf("\aXXXXXX Wrong input please enter a valid name XXXXX\n");
        getchar();
        gets(employees[employees_count].fName);
    }
    printf("Enter salary:\n>>");
    scanf("%s",&employees[employees_count].salary);//check is num
    while(!Svalidation(employees[employees_count].salary,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&employees[employees_count].salary);
    }
    printf("Enter birth Date:\nday>>");
    //scanf("%d",&employees[employees_count].bdate.d); // infinate loop when a letter is entered
    scanf("%s",&strd);
    while(!Svalidation(strd,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&strd);
    }
    employees[employees_count].bdate.d = atoi(strd);

    while(!Nvalidation(employees[employees_count].bdate.d,1)){
        printf("\aXXXXXX Wrong input please reenter the day correctly XXXXX\n");
        scanf("%d",&employees[employees_count].bdate.d);
    }
    printf("month>>");

    scanf("%s",&strm);
    while(!Svalidation(strm,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&strm);
    }
    employees[employees_count].bdate.m = atoi(strm);
    while(!Nvalidation(employees[employees_count].bdate.m,2)){
        printf("\aXXXXXX Wrong input please reenter the month correctly XXXXX\n");
        scanf("%d",&employees[employees_count].bdate.m);
    }
    printf("year>>");

    scanf("%s",&stry);
    while(!Svalidation(stry,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&stry);
    }
    employees[employees_count].bdate.y = atoi(stry);
    while(!Nvalidation(employees[employees_count].bdate.y,3)){
        printf("\aXXXXXX Wrong input please reenter the year correctly XXXXX\n");
        scanf("%d",&employees[employees_count].bdate.y);
    }
    printf("Enter address:\n>>");
    getchar();
    gets(employees[employees_count].address);
    printf("Enter phone number:\n>>");
    scanf("%s",&employees[employees_count].pNum);//check the first 2 intials and lenght
    while(!Svalidation(employees[employees_count].pNum,3)){
        printf("\aXXXXXX Wrong input please reenter phone number XXXXXX\n");
        scanf("%s",&employees[employees_count].pNum);
    }
    getchar();
    printf("Enter email:\n>>");
    scanf("%s",&employees[employees_count].email);//check for @ and .
    while(!Svalidation(employees[employees_count].email,5)){
        printf("\aXXXXXX Wrong input please reenter the email XXXXX\n");
        scanf("%s",&employees[employees_count].email);
    }
    // done saving and printing operation done
    printf("\t+++=======+++\nAdding employee done ");
    print_employee(employees_count);

    employees_count++;
    saveflag = 1;
}
void delete_employee(){ //delete employee with his last and first name
    char fn[30];
    char ln[30];
    int i;
    //name of the function
    printf("\n===============\nDeleting employees\nEnter the last name of employee you want to delete:\n>>");
    //take last name and first name + validate if they are valid names
    getchar();
    gets(ln);
    while(!Svalidation(ln,1)){
        printf("\aXXXXXX Wrong input please enter a valid name XXXXX\n");
        getchar();
        gets(ln);
    }
    printf("Enter first name you want to delete\n>>");
    getchar();
    gets(fn);
    while(!Svalidation(fn,1)){
        printf("\aXXXXXX Wrong input please enter a valid name XXXXX\n");
        getchar();
        gets(fn);
    }
    // check if employee exists and name id as 0 to neglect
    for( i = 0;i<employees_count;i++)
        if(!(strcasecmp(employees[i].lName,ln) || strcasecmp(employees[i].fName,fn))){
            strcpy(employees[i].Id,"0");
            printf("\n*************** DELETING employee Done **************\n");
            break;
        }
    // if not found  print the wrong message
    if(i == employees_count)
        printf("\a\nXXXXXXXXXXX\t NO MATCH please retry\t XXXXXXXXXX");
    //print_sorted();
    saveflag = 1;
}
void modify(){ // modify the data of specific employee
    char id[10],NEW[100],bd[5],bm[5],by[8];
    int i ,target_index,option,d,m,y,flag = 0;
    printf("===============\n Modifying employees Data\nEnter ID of the employee you want to modify\n>>");
    // getting the id
    scanf("%s",&id);
    while(!Svalidation(id,2)){
                printf("\aXXXXXX Wrong input please id as number XXXXXX\n");
                scanf("%s",&id);
            }
    // validate if id is found in the data
    while(1){
        for(i=0;i<employees_count;i++)
            if(!strcmp(employees[i].Id,id))
                break;
        if(i == employees_count){
            printf("XXXXX \a\temployee does NOT exist or wrong id\tXXXXX\n");
            scanf("%s",&id);
        }else
            break;

    }
    if(flag)
        printf("\aXXXXXXXX\temployee does NOT exist XXXXX");

    // get the value then validate in the switch
    printf("Enter the number for the value you want to change for employee %d\n1:firstName\n2:LastNAme\n3:salary\n4:birthdate\n5:address\n6:Phonenumber\n7:Email\n>>",i+1);
    scanf("%d",&option);
    printf("\nEnter New Value:\n>>");
    if(option==4){
    printf("Day: ");
    scanf("%s",&bd);
    while(!Svalidation(bd,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&bd);
    }
    d = atoi(bd);
    printf("Month: ");
    scanf("%s",&bm);
    while(!Svalidation(bm,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&bm);
    }
    m = atoi(bm);
    printf("year: ");
    scanf("%s",&by);
    while(!Svalidation(by,2)){
        printf("\aXXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&by);
    }
    y = atoi(by);
    }
    else{
    getchar();
    gets(NEW);
    }
    // to change and validate
    switch(option){
        case (1):
            while(!Svalidation(NEW,1)){
                printf("\aXXXXXX Wrong input please a valid name XXXXXX\n");
                getchar();
                gets(NEW);
            }
            strcpy(employees[i].fName,NEW);
            break;
        case (2):
            while(!Svalidation(NEW,1)){
                printf("\aXXXXXX Wrong input please a valid name XXXXXX\n");
                getchar();
                gets(NEW);
            }
            strcpy(employees[i].lName,NEW);
            break;
        case (3):
            while(!Svalidation(NEW,2)){
                printf("\aXXXXXX Wrong input please a salary XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].salary,NEW);
            break;
        case (4):
            while(!Nvalidation(d,1)){
              printf("\aXXXXXX Wrong input please a valid day date XXXXXX\n");
              scanf("%d",&d);
            } employees[i].bdate.d=d;
            while(!Nvalidation(m,2)){
              printf("\aXXXXXX Wrong input please a valid month date XXXXXX\n");
              scanf("%d",&m);
            } employees[i].bdate.m=m;
            while(!Nvalidation(y,3)){
              printf("\aXXXXXX Wrong input please a valid year date XXXXXX\n");
              scanf("%d",&y);
            } employees[i].bdate.y=y;
            break;
        case (5):
            while(!Svalidation(NEW,4)){
                printf("\aXXXXXX Wrong input please a valid address XXXXXX\n");
                getchar();
                gets(NEW);
            }
            strcpy(employees[i].address,NEW);
            break;
        case (6):
            while(!Svalidation(NEW,3)){
                printf("\aXXXXXX Wrong input please a valid phone number XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].pNum,NEW);
            break;
        case (7):
            while(!Svalidation(NEW,5)){
                printf("\aXXXXXX Wrong input please a valid email XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].email,NEW);
            break;
        default:
            printf("\aYou did NOT enter a valid input ");
            break;

        }
        printf("Modifying.....\n\tDONE ");
        saveflag = 1;
}
void sort (){ // sorting according to Bdate / last name / salary
 int option,i,j;
  employee temp1;
          printf("===============\n Enter the sorting way \n1:Date of birth \n2:Last name \n3:Salary \n>>");
            scanf("%d",&option);
            // get the option he want to sort by
        switch(option){//using bubble sort to sort data according to each option
 case(1):

         for (i=0;i<employees_count-1;i++)
         {  for (j=0;j<employees_count-1-i;j++)
            {
              if (employees[j].bdate.y>employees[j+1].bdate.y)
              {
                 temp1=employees[j];
                 employees[j]=employees[j+1];
                 employees[j+1]=temp1;
              }
             else if (employees[j].bdate.y==employees[j+1].bdate.y)
              {
                 if (employees[j].bdate.m>employees[j+1].bdate.m)
                 {
                    temp1=employees[j];
                    employees[j]=employees[j+1];
                    employees[j+1]=temp1;
                 }
                 else if (employees[j].bdate.m==employees[j+1].bdate.m)
                 {
                     if (employees[j].bdate.d>employees[j+1].bdate.d)
                     {
                       temp1=employees[j];
                       employees[j]=employees[j+1];
                       employees[j+1]=temp1;
                     }

                 }
             }

             }
         }
        printf("\n\t+============+\n\t!Sorting done!");
        break;
 case(2):
         for (i=0;i<employees_count-1;i++)
         {
             for (j=0;j<employees_count-1-i;j++)
            {
             if  (strcmp(employees[j].lName,employees[j+1].lName)>0)
             {
                 temp1=employees[j];
                 employees[j]=employees[j+1];
                 employees[j+1]=temp1;
             }
            }
          }  printf("\n\t+============+\n\t!Sorting done!");
        break;
 case(3):
         for (i=0;i<employees_count-1;i++)
         {
             for (j=0;j<employees_count-1-i;j++)
            {
             if (atof(employees[j].salary)<atof(employees[j+1].salary))
             {
                 temp1=employees[j];
                 employees[j]=employees[j+1];
                 employees[j+1]=temp1;
             }
            }
            printf("\n***&s",employees[j].salary);
         }  printf("\n\t+============+\n\t!Sorting done!");
       break;
    default:
            printf("You did NOT enter a valid input \n");
            break; }

    saveflag = 1;
 }
void save(){//saving data in the bath global variable  and lowers the flag if the user modified
    FILE* fp = fopen(path,"w");
    for( i = 0; i<employees_count;i++){
        if(!strcasecmp(employees[i].Id,"0"))
            continue;
        fprintf(fp,"%s,%s,%s,%s,%d-%d-%d,%s,%s,%s\n",employees[i].Id,employees[i].lName,employees[i].fName,employees[i].salary,employees[i].bdate.d,employees[i].bdate.m,employees[i].bdate.y,employees[i].address,employees[i].pNum,employees[i].email);
   } printf("\n=====SAVING DONE=====");
   saveflag = 0;
}
void quit(){ // checks if save flag is risen asking the user if he save or not then quit the program
    if(!saveflag)
        exit(0);
    printf("WARNING!! You didn't save\nDo you want to exit anyway enter 0 or any number to continue to main menu:\n>>");
    int x;
    scanf("%d",&x);
    if(x == 0){
            printf("! BYE BYE !");
        exit(0);
    }
}

// validation functions
int Svalidation(char input[100],int option){//1:names 2:id,salary 3:phone 4:address 5:email
    //printf("%s",input[100]);
    int i, flag1=0,flag2=0;;
      switch(option){
        case (1): //last and first name check
            for(i=0;input[i]!='\0';i++)
                if(!(isalpha(input[i]))&& input[i] != ' ')
                    return 0;
            return 1;
            break;
        case (2): //id and salary check
            for(i=0;input[i]!='\0';i++)
                if(!isdigit(input[i]))
                    return 0;
            return 1;
        case (3): //phone number check
            if(input[0] != '0' || input[1] != '1' || input[10]== '\0'|| input[11]!= '\0')
                return 0;
            for(i=2;input[i]!='\0';i++)
                if(!isdigit(input[i]))
                    return 0;
            return 1;
        case (4): // address check
           for(i=0;input[i]!='\0';i++)
                if(!isdigit(input[i]) || !isalpha(input[i])||input[i]!=' ')
                    return 0;
                return 1;
        case (5): // email check
            for(i=0;input[i]!='\0';i++){
                if(input[i]=='@')
                    ++flag1;
                if(input[i]=='.'&&input[i+1]=='c'&&input[i+2]=='o'&&input[i+3]=='m')
                    ++flag2;
            }
            if(flag1==1&&flag2==1)
                return 1;
            else
                return 0;
            }
}
int Nvalidation(int n , int option){//validate 1 for day, 2 for month  and 3 for year
 switch(option){
 case(1):{ //check the day date
     if(n>=1&&n<=31)
        return 1;
     else return 0;
 case(2):{ //check the month date
     if(n>=1&&n<=12)
        return 1;
     else return 0;
 case(3):{ //check the year date
     if(n>=1900&&n<=2022)
        return 1;
     else return 0;

 }
}}}}

// printing functions
void print_sorted(){//prints all employees using print employee and neglecting deleted ones
    for( i =0;i<employees_count;i++)
        if(strcmp(employees[i].Id,"0"))
            print_employee(i);
}
void print_employee(int i){
    if(strcmp(employees[i].Id,"0")){
    printf("\nID:%s\t LastName:%s \tFirstName:%s\tSalary:%f\tDate:%d/%d/%d\t",employees[i].Id,employees[i].lName,employees[i].fName,atof(employees[i].salary),employees[i].bdate.d,employees[i].bdate.m,employees[i].bdate.y);
    printf("Address:%s\tphone-number:%s\temail:%s\n",employees[i].address,employees[i].pNum,employees[i].email);
    }
}

// main function
int main ()
{
    read_data("employeesDB.txt");
    //printf("%d",employees_count);
    //print_employee(2);
    int restart,option;
    printf("\t\tWelcome");
   // print_sorted();
    while(1){
        printf("\n\t++====================++\nEnter the number of the function you want\n1:Search\n2:Add\n3:Delete\n4:Modify\n5:sort employees\n6:Save\n7:Quit\n>>");
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
            sort();
            break;
        case (6):
            save();
            break;
        case (7):
            quit();
            break;
        default:
            printf("You did NOT enter a valid input \n");
            break;


        }
    }

  return 0;
}
