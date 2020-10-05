
#include <stdio.h>
#include <stdlib.h>
#include<string.h>


//extern int flag_a;//flag for admin login
//extern int flag_u; //flag for user login
int flag_a=0;
int flag_u=0;
char res_log[30];


//admin login function

int admin_login(char *admin_username, char *admin_password)
{   char username[20]="admin";
    char password[20]="admin24";


    if((strcmp(username,admin_username)==0) && (strcmp(password,admin_password)==0)) //checking for validity of entered username and password
    {
        flag_a=1;
        printf("\n Login Successful \n");

    }
    else
    {
        printf("\n Invalid Login Credentials! Try Again \n");
        flag_a=0;
    }
    return(flag_a);

}

//Structure to store movie details
struct movie_details
{
    int movie_code;
    char movie_name[60];
    char show_timing[10];
    char release_date[20];
    int ticket_price;
    int seat_no;
};
struct movie_details m;

//function to add movie
char* add_movies(int code, char *name, char *timing, char *date, int price, int seat)
{
  if(flag_a) //if admin login is successful
  {
   FILE *fp;
   fp=fopen("movie_list.txt","a"); //opens file to append
   if(fp==NULL)
   {
       printf("\n File not found \n");
       exit(1);
   }

    m.movie_code=code;
    strcpy(m.movie_name,name);
    strcpy(m.show_timing,timing);
    strcpy(m.release_date,date);
    m.ticket_price=price;
    m.seat_no=seat;

   fwrite(&m,sizeof(struct movie_details), 1, fp); //writing structure to file
   printf("\nMovie Details Successfully added\n");

   fclose(fp);


  }
return "Movie Details Added Successfully";

}

//structure to store details of user
struct user_reg
{
    char fullname[30];
    char username[20];
    char password[20];
    char mob_no[20];
};
struct user_reg user;


//function for user registration
char* user_reg(char *fname, char*uname, char *pass, char*mob_no)
{
strcpy(user.fullname,fname);
strcpy(user.username,uname);
strcpy(user.password,pass);
strcpy(user.mob_no,mob_no);

FILE *fp;
fp = fopen("user_list.txt","a"); //opens file for appending
if(fp==NULL)
{
    printf("FILE NOT FOUND");
    exit(1);
}

fwrite(&user, sizeof(struct user_reg),1,fp); //writes structure to file
printf("\n User Registration Successful \n");
fclose(fp);

return "User Registration Successful";

}

//function for user login
char* user_login(char *username, char *password)
{

    FILE *fp;
    fp = fopen("user_list.txt","r"); // opens file for reading
    if(fp==NULL)
    {
        printf("FILE NOT FOUND");
        exit(1);
    }

    while(fread(&user, sizeof(struct user_reg),1,fp)) // reads till EOF
    {
        if((strcmp(user.username,username)==0) && (strcmp(user.password,password)==0)) //checks entered credentials with the values in structure
        {
            flag_u=1;
            printf("\n Login successful \n");
            strcpy(res_log,"Login successful");
            break;
        }
    }
    if(!flag_u)
    {
    printf("\n Not a registered user \n");
    strcpy(res_log,"Not a registered user");
    }
fclose(fp);
return(res_log);


}

//function to view available movies
void view_movies()
{
    if(flag_u)
    {
    system("cls");
   FILE *fp;
   fp=fopen("movie_list.txt","r"); // opens file for reading
   if(fp==NULL)
   {
       printf("FILE NOT FOUND");
       exit(1);
   }

   printf("\n********************************  MOVIES AVAILABLE ***********************************\n");
   printf("\n               | NAME     | SHOW TIMING   |   DATE     | ");
   printf("\n                ---------------------------------------\n");
   while(fread(&m, sizeof(struct movie_details),1,fp)) //reads file till EOF
   {

    printf("               %s\t     %s \t   %s",m.movie_name,m.show_timing,m.release_date);

     printf("\n");
   }
   printf("\n***************************************************************************************\n");
   fclose(fp);
}

printf("\n Press Enter to go to User Panel \n");
while((getchar())!='\n');
getchar();
system("cls");

}

//structure to store ticket details
struct book_tickets
{
    char movie_name[60];
    int seats;
    char name[30];
    char mob_no[20];
    int amount;
    char show_timing[20];
};
struct book_tickets ticket;


//function for ticket bookings
void book_tickets(char*movie, int seat)
{
    if(flag_u)
    {   int flag=0;
        system("cls");

        FILE *fp;
        fp=fopen("movie_list.txt","r+"); //opening file for reading and writing

        strcpy(ticket.movie_name,movie);

            while(fread(&m, sizeof(struct movie_details),1,fp))
            {
                if(strcmp(m.movie_name,ticket.movie_name)==0 && strcmp(ticket.movie_name," ")!=0) //check if entered movie exist in database
                {   flag=1;

                    ticket.seats=seat;

                    m.seat_no=m.seat_no-ticket.seats; //reducing the total seat count

                if(ticket.seats>0 && m.seat_no>=0)
                {
                    strcpy(ticket.name,user.fullname);
                    strcpy(ticket.mob_no,user.mob_no);
                    ticket.amount=ticket.seats*m.ticket_price; //calculating ticket amount
                    strcpy(ticket.show_timing,m.show_timing);


                    printf("\n**********************************TICKET****************************************************\n");
                    printf("\n");
                    printf("         Movie           : %s \n",ticket.movie_name);
                    printf("         Show Timing     : %s \n",ticket.show_timing);
                    printf("         Number of seats : %d \n",ticket.seats);
                    printf("         Name of customer: %s \n",ticket.name);
                    printf("         Mobile Number   : %s \n",ticket.mob_no);
                    printf("         Amount payable  : %d \n",ticket.amount);
                    printf("\n");
                    printf("\n*********************************************************************************************\n");

                    FILE *fp2;
                    fp2=fopen("booked_tickets.txt","a");
                    fwrite(&ticket, sizeof(struct book_tickets),1,fp2);
                    printf("\nDetails Successfully Saved\n");
                    fseek(fp, ftell(fp) - sizeof(struct movie_details), SEEK_SET);
                    fwrite(&m, sizeof(struct movie_details),1,fp);
                    printf("Number of seats left are : %d",m.seat_no);
                    fclose(fp2);
                    break;

                }
                else if(ticket.seats==0)
                    printf("\n You have to book atlease one seat \n");

                else if(ticket.seats<0)
                    printf("\n Please given a number greater than zero \n");
                else
                    printf("\n Desired Number of seats are not available \n");
                }
            }
if(!flag)
printf("\nInvalid  Movie Name \n");

printf("\nPress Enter to go back to User Panel\n");
while((getchar())!='\n');
getchar();
system("cls");

fclose(fp);
    }
}

//function to search for movies by name
void search(char* m_name)
{   int flag=0;

    FILE *fp;
        fp=fopen("movie_list.txt","r");
        if(fp==NULL)
        {
            printf("FILE NOT FOUND");
            exit(1);
        }
        printf("\n************************************ SEARCH MOVIE ****************************************\n");
        while(fread(&m, sizeof(struct movie_details),1,fp))
        {
            if(strcmp(m.movie_name,m_name)==0)
                {
                    printf("\n       Movie Code      : %d \n",m.movie_code);
                    printf("\n       Movie Name      : %s \n",m.movie_name);
                    printf("\n       Release Date    : %s \n",m.release_date);
                    printf("\n       Show Timing     : %s \n",m.show_timing);
                    printf("\n       Ticket Price    : %d \n",m.ticket_price);
                    printf("\n       Available Seats : %d \n",m.seat_no);
                    flag=1;
                }
        }
        if(!flag)
            printf("\nMOVIE NOT FOUND\n");

        printf("\n********************************************************************************************\n");
fclose(fp);

printf("Press Enter to continue");
while((getchar())!='\n');
getchar();
system("cls");
}

//funtion for user to see his/her booked tickets
void view_booked()
{
    if(flag_u)
    {
        int flag=0;
        FILE *fp;
        fp = fopen("booked_tickets.txt","r");

        while(fread(&ticket,sizeof(struct book_tickets),1,fp))
        {
        if(strcmp(ticket.name,user.fullname)==0)
        {           flag=1;
                    printf("\n**********************************TICKET****************************************************\n");
                    printf("\n");
                    printf("         Movie           : %s \n",ticket.movie_name);
                    printf("         Show Timing     : %s \n",ticket.show_timing);
                    printf("         Number of seats : %d \n",ticket.seats);
                    printf("         Name of customer: %s \n",ticket.name);
                    printf("         Mobile Number   : %s \n",ticket.mob_no);
                    printf("         Amount payable  : %d \n",ticket.amount);
                    printf("\n");
                    printf("\n********************************************************************************************\n");

        }
        }
if(!flag)
printf("\nYou have not booked any tickets! \n");
fclose(fp);
}

printf("\nPress Enter to continue\n");
while((getchar())!='\n');
getchar();
system("cls");
}

//function for admins to view all booked tickets
void view_bookings()
{
   if(flag_a)
    {   int sum=0;
        FILE *fp;
        fp = fopen("booked_tickets.txt","r");

        while(fread(&ticket,sizeof(struct book_tickets),1,fp))
              {     sum+=ticket.amount;
                    printf("\n********************************************************************************************\n");
                    printf("\n");
                    printf("         Movie           : %s \n",ticket.movie_name);
                    printf("         Show Timing     : %s \n",ticket.show_timing);
                    printf("         Number of seats : %d \n",ticket.seats);
                    printf("         Name of customer: %s \n",ticket.name);
                    printf("         Mobile Number   : %s \n",ticket.mob_no);
                    printf("         Amount payable  : %d \n",ticket.amount);
                    printf("\n");
                    printf("\n********************************************************************************************\n");
              }
    FILE *fp2;
    fp2=fopen("movie_list.txt","r");
    //summary of all bookings
    printf("\n ********************************* SUMMARY ****************************************\n");
while(fread(&m, sizeof(struct movie_details),1,fp2))
{
    printf("\n * Number of unbooked seats for %s is %d  \n",m.movie_name, m.seat_no);
}
    printf("\n * Total amount received = %d \n",sum);
    printf("\n **********************************************************************************\n");
    fclose(fp);
    fclose(fp2);
}
printf("\n Press Enter to go back to admin panel");
while((getchar())!='\n');
getchar();
system("cls");
}

