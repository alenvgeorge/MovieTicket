
#ifndef __MOVIE_H__
#define __MOVIE_H__

struct movie_details
{
    int movie_code;
    char movie_name[60];
    char show_timing[10];
    char release_date[20];
    int ticket_price;
    int seat_no;
};

extern struct movie_details m;

struct movie_details m;
int admin_login(char *admin_username, char *admin_password);
char* add_movies(int code, char *name, char *timing, char *date, int price, int seat);
char* user_reg(char *fname, char*uname, char *pass, char*mob_no);
char* user_login(char *username, char *password);
int view_movies();
char *book_tickets(char*movie, int seat);
char* search(char* m_name);
char *view_booked();
int view_bookings();


#endif // __MOVIE_H__

