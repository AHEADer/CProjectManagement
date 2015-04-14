#ifndef	__FUNCTIONS_H
#define __FUNCTIONS_H 1
#include <gtk/gtk.h>
#include "structs.h"

/* Builder Function */
/* Helper function */
void clean_var();
void call_last_func();
void build_UI();

GtkWidget **create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response);
GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][100], GtkWidget **dialog_response);
void save_confirmation();

int calculate(char *s);
int contain(char *s,int t);
int building_create(Building **head ,char code[], char name[], char phone_number[], int rooms_count, int students_count, float building_area, Rooms *rooms);
int rooms_create(Rooms **head, char name[], char type, float price, int student_count, int floor, float mark, Building *building, Courses *courses);
int courses_create(Courses **head, char date[], char name[], int mark, char jieci[], char room[], int student_count, char acdemic[], char weekly[], Rooms *rooms);
int funcs_create(Funcs **head, char name[], int rooms_count, float areas_count, float mark);

int data_delete();
int building_delete(void *self);
int rooms_delete(void *self);
int courses_delete(void *self);
int funcs_delete(void *self);

Building **building_search(char code[]);
Building **building_search_name(char code[]);
Rooms **rooms_search(char name[30]);
Funcs **funcs_search(Funcs **head, char name[20]);

void data_out();

void create_list_store(GtkListStore **liststore, int type);
void insert_into_list_store(GtkListStore **liststore, void *data, int type);
void append_column(char column_title[][20], int column_line[], int cls);
void create_column(int type);
void clean_column();
char *string(char code);
char *intstring(int code);

/* End Helper function */

/* Basic I/O */
int save_file();
void open_file(char *filename);
int load_file();
void close_file(); /* clean data then you can change file */
char *file_choose(int type);

void file_new();
void file_open();
void file_save();
void file_save_as();
void file_quit();
/* End Basic I/O */

/* Maintenance */
int maintenance_building_dialog(void *self);

void maintenance_add_building();
void maintenance_add_rooms();
void maintenance_add_courses();

void maintenance_edit();
void maintenance_delete();
/* End Maintenance */

/* Query */
void query_building_all(void *pass, int call_type);
void query_rooms_all(void *pass, int call_type);
void query_courses_all(void *pass, int call_type);
void query_building_code(void *pass, int call_type);
void query_rooms_name(void *pass, int call_type);
void query_rooms_code_muti(void *pass, int call_type);
void query_courses_funcs_date(void *pass, int call_type);
void query_courses_name_mark(void *pass, int call_type);
/* End Query */

/* Statistics */
void statistics_building(void *pass, int call_type);
void statistics_year(void *pass, int call_type);
void statistics_funcs(void *pass, int call_type);
void statistics_quarter(void *pass, int call_type);
void statistics_all(void *pass, int call_type);
/* End Statistics */

/* Other Function */
void other_about();
/* End Other Function */

#endif /* functions.h */
