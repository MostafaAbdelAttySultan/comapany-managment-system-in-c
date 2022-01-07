#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct
{
  int y;
  int m;
  int d;
}date;
typedef struct
{
  int Id;
  char lName[15], fName[15],address[30],pNum[12], email[40];
  float salary;
  date bdate;
}employee;
void read_date(char d[],employee* e){
        char* value = strtok(d, ",");
        e->bdate.d = value;
        value = strtok(NULL, ", ");
        value = strtok(d, ",");
        e->bdate.m = value;
        value = strtok(NULL, ", ");
        value = strtok(d, ",");
        e->bdate.y = value;
}
int main ()
{
    int counter = 0;
   FILE* fp = fopen("employeesDB.txt", "r");
    employee emplys[100];
    if (fp) {
        char line[1024]; // a string to hold lines and separate them
        int row = 0, column = 0; // to konw where we are and to navigate
        while (fgets(line,1024, fp)) {
            column = 0;
            row++;
            if (row == 1)// not to read first line as it is columns names in the CSV file
                continue;

            char* value = strtok(line, ",");    // Splitting the data making pointer to hold data

            while (value) { // to know if the previous line returned or not

                if (column == 0) // Column 1
                   // employee[counter].id = value;
                if (column == 1) // Column 2
                    strcpy(emplys[counter].lName,value);
                if (column == 2) // Column 3
                    strcpy(emplys[counter].fName,value);
                if (column == 3) // Column 1
                    strcpy(emplys[counter].address,value);
                if (column == 4) // Column 2
                    strcpy(emplys[counter].pNum,value);
                if (column == 5) // Column 3
                    strcpy(emplys[counter].email,value);
                if (column == 6) // Column 1
                   // employee[counter].salary = value;
                if (column == 7) // Column 2
                   read_date(value,&emplys[counter]);
                //printf("%s", value);
                puts(emplys[counter].fName);
                value = strtok(NULL, ", ");
                column++;
                counter++;
            }

            //printf("\n");
            }
    }else
          printf("Can't open file\n");
        //printf("\n***************%d***********\n",emplys[2].bdate.m);

  fclose(fp);// Close the file

  return 0;
}
