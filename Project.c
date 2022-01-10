#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
// ****** sort , search after delete and printing & add check in the quit to ask for saving or not //////// validation names AND DATE MODIFICATION change saving path
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
employee employees[100];
int employees_count = 0,saveflag = 0,i;
char path[100] = "employeesDB.txt";
void read_data(){
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
    }else
          printf("Can't open file\n");

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
void print_employee(int i){
    if(strcmp(employees[i].Id,"0")){
    printf("\nID:%s\t LastName:%s \tFirstName:%s\tSalary:%s\tDate:%d/%d/%d\t",employees[i].Id,employees[i].lName,employees[i].fName,employees[i].salary,employees[i].bdate.d,employees[i].bdate.m,employees[i].bdate.y);
    printf("Address:%s\tphone-number:%s\temail:%s\n",employees[i].address,employees[i].pNum,employees[i].email);
    }
}
void search(){
    char target[30];
    int flag = 0;
    printf("\n====================\nEntering search function\n");
    printf("Please Enter the last name of employee you want to search:");
    scanf("%s",&target);
    for( i = 0;i<employees_count;i++){
        if(!strcasecmp(employees[i].lName,target)){
            print_employee(i);
            flag ++ ;
        }//printf("%d",flag);
    }
    if(!flag)
        printf("NO match\nWe did not found an employee with last name: %s",target);



}
void add(){
    int i, flag = 1;
    printf("\n=========================\nAdding a new employee\nEnter ID:\n>>");
    scanf("%s",&employees[employees_count].Id);//check if id is repeated
    while(flag){
        flag = 0;
        for(i = 0;i<employees_count;i++)
            if(!strcmp(employees[employees_count].Id,employees[i].Id) || !strcmp(employees[employees_count].Id,"0"))
                flag =1;

        if (flag){
            printf("\nSorry we can not add This ID it is repeated or 0\nReenter the id\n>>");
            scanf("%s",&employees[employees_count].Id);
        }
        }
    printf("Enter last Name:\n>>");
    scanf("%s",&employees[employees_count].lName);
    while(!Svalidation(employees[employees_count].lName,1)){
        printf("XXXXXX Wrong input please enter a valid name XXXXX\n");
        scanf("%s",&employees[employees_count].lName);
    }
    printf("Enter first Name:\n>>");
    scanf("%s",&employees[employees_count].fName);
    while(!Svalidation(employees[employees_count].fName,1)){
        printf("XXXXXX Wrong input please enter a valid name XXXXX\n");
        scanf("%s",&employees[employees_count].fName);
    }
    printf("Enter salary:\n>>");
    scanf("%s",&employees[employees_count].salary);//check is num
    while(!Svalidation(employees[employees_count].salary,2)){
        printf("XXXXXX Wrong input please a number XXXXX\n");
        scanf("%s",&employees[employees_count].salary);
    }
    printf("Enter birth Date:\nday>>");
    scanf("%d",&employees[employees_count].bdate.d);
    while(!Nvalidation(employees[employees_count].bdate.d,1)){
        printf("XXXXXX Wrong input please reenter the day correctly XXXXX\n");
        scanf("%d",&employees[employees_count].bdate.d);
    }
    printf("month>>");
    scanf("%d",&employees[employees_count].bdate.m);
    while(!Nvalidation(employees[employees_count].bdate.m,2)){
        printf("XXXXXX Wrong input please reenter the month correctly XXXXX\n");
        scanf("%d",&employees[employees_count].bdate.m);
    }
    printf("year>>");
    scanf("%d",&employees[employees_count].bdate.y);
    printf("Enter address:\n>>");
    scanf("%s",&employees[employees_count].address);
    printf("Enter phone number:\n>>");
    scanf("%s",&employees[employees_count].pNum);//check the first 2 intials and lenght
    while(!Svalidation(employees[employees_count].pNum,3)){
        printf("XXXXXX Wrong input please reenter phone number XXXXXX\n");
        scanf("%s",&employees[employees_count].pNum);
    }
    getchar();
    printf("Enter email:\n>>");
    scanf("%s",&employees[employees_count].email);//check for @ and .
    while(!Svalidation(employees[employees_count].email,5)){
        printf("XXXXXX Wrong input please reenter the email XXXXX\n");
        scanf("%s",&employees[employees_count].email);
    }
    print_employee(employees_count);

    employees_count++;
    saveflag = 1;
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
        if(!(strcasecmp(employees[i].lName,ln) && strcasecmp(employees[i].fName,fn))){
            strcpy(employees[i].Id,"0");
            printf("\n*************** DELETING employee **************\n");
            break;
        }
    if(i == employees_count)
        printf("\n NO MATCH please retry");
    //print_sorted();
    saveflag = 1;
}
void modify(){
    char id[10],NEW[100];
    int i ,target_index,option,d,m,y;
    printf("===============\n Modifying employees Data\nEnter ID of the employee you want to modify\n>>");
    scanf("%s",&id);
    while(!Svalidation(id,2)){
                printf("XXXXXX Wrong input please a id XXXXXX\n");
                scanf("%s",&id);
            }
    for(i =0;i<employees_count;i++)
        if(!strcmp(employees[i].Id,id))
            break;

    printf("Enter the number for the value you want to change for employee %d\n1:firstName\n2:LastNAme\n3:salary\n4:birthdate\n5:address\n6:Phonenumber\n7:Email\n>>",i+1);
    scanf("%d",&option);
    printf("\nEnter New Value:\n>>");
    if(option==4){
    printf("Day: ");
    scanf("%d",&d);
    printf("Month: ");
    scanf("%d",&m);
    printf("year: ");
    scanf("%d",&y);}
    else
    scanf("%s",&NEW);
    switch(option){
        case (1):
            while(!Svalidation(NEW,1)){
                printf("XXXXXX Wrong input please a valid name XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].fName,NEW);
            break;
        case (2):
            while(!Svalidation(NEW,1)){
                printf("XXXXXX Wrong input please a valid name XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].lName,NEW);
            break;
        case (3):
            while(!Svalidation(NEW,2)){
                printf("XXXXXX Wrong input please a salary XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].salary,NEW);
            break;
        case (4):
            while(!Nvalidation(d,1)){
              printf("XXXXXX Wrong input please a valid day date XXXXXX\n");
              scanf("%d",&d);
            } employees[i].bdate.d=d;
            while(!Nvalidation(m,2)){
              printf("XXXXXX Wrong input please a valid month date XXXXXX\n");
              scanf("%d",&m);
            } employees[i].bdate.m=m;
            while(!Nvalidation(y,3)){
              printf("XXXXXX Wrong input please a valid year date XXXXXX\n");
              scanf("%d",&y);
            } employees[i].bdate.y=y;
            break;
        case (5):
            while(!Svalidation(NEW,4)){
                printf("XXXXXX Wrong input please a valid address XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].address,NEW);
            break;
        case (6):
            while(!Svalidation(NEW,3)){
                printf("XXXXXX Wrong input please a valid phone number XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].pNum,NEW);
            break;
        case (7):
            while(!Svalidation(NEW,5)){
                printf("XXXXXX Wrong input please a valid email XXXXXX\n");
                scanf("%s",&NEW);
            }
            strcpy(employees[i].email,NEW);
            break;
        default:
            printf("You did NOT enter a valid input ");
            break;

        }
        print_sorted();
        saveflag = 1;
}
void save(){
    FILE* fp = fopen(path,"w");
    for( i = 0; i<employees_count;i++){
        if(!strcasecmp(employees[i].Id,"0"))
            continue;
        fprintf(fp,"%s,%s,%s,%s,%d-%d-%d,%s,%s,%s\n",employees[i].Id,employees[i].lName,employees[i].fName,employees[i].salary,employees[i].bdate.d,employees[i].bdate.m,employees[i].bdate.y,employees[i].address,employees[i].pNum,employees[i].email);
   } printf("\n=====SAVING DONE=====");
   saveflag = 0;
}
void quit(){
    if(!saveflag)
        exit(0);
    printf("WARNING!! You didn't save\nDo you want to exit anyway enter 0 or 1 to continue to main menu:\n>>");
    int x;
    scanf("%d",&x);
    if(!x)
        exit(0);
}
int Svalidation(char input[100],int option){//1:names 2:id,salary 3:phone 4:address 5:email
    //printf("%s",input[100]);
    int i, flag1=0,flag2=0;;
      switch(option){
        case (1): //last and first name check
            for(i=0;input[i]!='\0';i++)
                if(!isalpha(input[i]))
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
            if(flag1&&flag2)
                return 1;
            else
                return 0;
            }
}
int Nvalidation(int n , int option){//validate 1 for day and 2 for month
 switch(option){
 case(1):{ //check the day date
     if(n>=1&&n<=31)
        return 1;
     else return 0;
 case(2):{ //check the month date
     if(n>=1&&n<=12)
        return 1;
     else return 0;

 }
 }



 }


}
void print_sorted(){
    for( i =0;i<employees_count;i++)
        if(strcmp(employees[i].Id,"0"))
            print_employee(i);
}
void sort (){
    int option,i,count = 0, count2 = 0;
    employee temp1;
    printf("===============\n Enter the sorting way \n1:Date of birth \n2:Last name \n3:Salary \n>>");
    scanf("%d",&option);

    switch(option){
case(1):
        while(!count){
            count = 0;
        for (i=0+count2;i<employees_count-1;i++)
        {

            if (employees[i].bdate.y>employees[i+1].bdate.y)
            {
                temp1=employees[i];
                employees[i]=employees[i+1];
                employees[i+1]=temp1;
                count ++;
            }
            else if (employees[i].bdate.y==employees[i+1].bdate.y)
            {
                if (employees[i].bdate.m>employees[i+1].bdate.m)
                {
                    temp1=employees[i];
                    employees[i]=employees[i+1];
                    employees[i+1]=temp1;
                    count ++;
                 }
                 else if (employees[i].bdate.m==employees[i+1].bdate.m)
                 {
                     if (employees[i].bdate.d>employees[i+1].bdate.d)
                     {
                        temp1=employees[i];
                        employees[i]=employees[i+1];
                        employees[i+1]=temp1;
                        count++;
                     }
                  }
             }
            count2 ++;
         }}
         //print_sorted();
        break;
 case(2):
     while(!count){
        count = 0;
         for (i=0+count2;i<employees_count-1;i++)
         {
             if  (strcasecmp(employees[i].lName,employees[i+1].lName)>0)
             {
                 temp1=employees[i];
                 employees[i]=employees[i+1];
                 employees[i+1]=temp1;
                count ++;
             }
             count2 ++;
          }
     }
          print_sorted();
        break;
 case(3):
        while(!count){
            count = 0;
         for (i=0+count2;i<employees_count-1;i++)
         {
             if (atoi(employees[i].salary)<atoi(employees[i+1].salary))
             {
                 temp1=employees[i];
                 employees[i]=employees[i+1];
                 employees[i+1]=temp1;
                count ++ ;
             }
             count2++;
         }
        }
         print_sorted();
       break;
    }
 }
int main ()
{
    read_data("employeesDB.txt");
    //printf("%d",employees_count);
    //print_employee(2);
    int restart,option;
    printf("\n\t\tWelcome");
    print_sorted();
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
            sort();
            print_sorted();
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
