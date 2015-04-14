#ifndef	__DEFINES_H
#define __DEFINES_H 1

#define UI_FILE "UI.xml"

const char *version = "0.1";
const char *program_name = "Manager of a simple Course";
const char *comments = "Full of Bugs.\nIt Works.";
const char *website = "https://zhangjunda.org";
const char *website_lable = "MyWebsite";
const char *author[] = {"Aheader", NULL};

FILE *file = NULL;
short updated = TRUE;
GtkWindow *window = NULL;
GtkTreeView *treeview = NULL;
void (*last_func)(void *pass, int call_type);

Building *building_head;  /* Main head of the linked list */

enum {
	FILE_CHOOSE_OPEN,
	FILE_CHOOSE_SAVE,
	FILE_CHOOSE_SAVE_AS,
};

enum {
	TYPE_BUILDING,
	TYPE_ROOMS,
	TYPE_COURSES,
	TYPE_OTHER,
	TYPE_COURSE_ALL
};

enum {
	BUILDING_ALL,
	ROOMS_ALL,
	COURSES_ALL,
	BUILDING_STATS,
	ROOMS_YEAR,
	Funcs_STATS,
	ALL_STATS,
	COURSE_STATSD,
	LAST_STAT
};

enum {
	BUILDING_ALL_POINTER,
	BUILDING_ALL_TYPE,
	BUILDING_ALL_CODE,
	BUILDING_ALL_NAME,
	BUILDING_PHONE_NUMBER,
	BUILDING_ALL_ROOMS_COUNT,
	BUILDING_ALL_COLUMNS
};

enum {
	ROOMS_ALL_POINTER,
	ROOMS_ALL_TYPE,
	ROOMS_ALL_CODE,
	ROOMS_ALL_NAME,
	ROOMS_ALL_CTYPE,
	ROOMS_ALL_PRICE,
	ROOMS_ALL_COURSES_COUNT,
	ROOMS_ALL_COLUMNS
};

enum {
	COURSE_ALLD_POINTER,
	COURSE_ALLD_TYPE,
	COURSE_ALLD_NAME,
	ONE_TWO,
	THREE_FOUR,
	FIVE_SIX,
	SEVEN_EIGHT,
	NINE_TEN,
	ELE_TWL,
	COURSE_ALLD_COLUMNS
};

enum {
	COURSES_ALL_POINTER,
	COURSES_ALL_TYPE,
	COURSES_ALL_CNAME,
	COURSES_ALL_DATE,
	COURSES_ALL_NAME,
	COURSES_ALL_MARK,
	COURSES_ALL_JIECI,
	COURSES_ALL_STUDENTS_COUNT,
	COURSES_ALL_ACDEMIC,
	COURSES_ALL_WEEKLY,
	COURSES_ALL_COLUMNS
};

enum {
	BUILDING_STATS_POINTER,
	BUILDING_STATS_TYPE,
	BUILDING_STATS_CODE,
	BUILDING_STATS_NAME,
	BUILDING_STATS_COURSES_COUNT,
	BUILDING_STATS_SALES_COUNT,
	BUILDING_STATS_MARKL3_COUNT,
	BUILDING_STATS_MARKG3_COUNT,
	BUILDING_STATS_COLUMNS
};

enum {
	ROOMS_YEAR_POINTER,
	ROOMS_YEAR_TYPE,
	ROOMS_YEAR_NAME,
	ROOMS_YEAR_CNAME,
	ROOMS_YEAR_COURSES_COUNT,
	ROOMS_YEAR_SALES_COUNT,
	ROOMS_YEAR_MARK,
	ROOMS_YEAR_COLUMNS
};

enum {
	Funcs_STATS_POINTER,
	Funcs_STATS_TYPE,
	Funcs_STATS_NAME,
	Funcs_STATS_COURSES_COUNT,
	Funcs_STATS_MONEY_COUNT,
	Funcs_STATS_MARK,
	Funcs_STATS_COLUMNS
};

enum {
	QUARTER_STATS_POINTER,
	QUARTER_STATS_TYPE,
	QUARTER_STATS_NAME,
	QUARTER_STATS_C1_COUNT,
	QUARTER_STATS_C2_COUNT,
	QUARTER_STATS_C3_COUNT,
	QUARTER_STATS_C4_COUNT,
	QUARTER_STATS_C5_COUNT,
	QUARTER_STATS_COLUMNS
};

enum {
	ALL_STATS_POINTER,
	ALL_STATS_TYPE,
	ALL_STATS_COURSES_COUNT,
	ALL_STATS_SALES_COUNT,
	ALL_STATS_MARKL3_COUNT,
	ALL_STATS_MARKG3_COUNT,
	ALL_STATS_COLUMNS
};

enum {
	CALL_TYPE_NORMAL,
	CALL_TYPE_REDO,
};

#endif /* defines.h */
