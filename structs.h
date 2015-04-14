#ifndef	__STRUCTS_H
#define __STRUCTS_H 1

struct building
{
	int (*__delete)(void *self);                   //释放某指针指向的内存的位置
	char code[10];                                 //教学楼编号
	char name[20];                                 //教学楼名称
	char phone_number[15];                         //管理员电话
	int rooms_count;                               //教室间数
	int students_count;                            //容纳学生人数
	float building_area;                           //教室总面积
	struct building *next;
	struct rooms *rooms;
};

struct rooms
{
	int (*__delete)(void *self);
	char type;                                      //是否为多媒体教室
	char name[10];                                  //教室编号
	int courses_count;
	int floor;                                      //楼层
	float price;                                    //教室面积
	float mark;                                     //(这个好像和下面的courses有关系)
	int student_count;                              //容纳学生人数
	struct rooms *next;
	struct building *building;
	struct courses *courses;
};

struct courses
{
	int (*__delete)(void *self);
	char date[10];                                   //学期
	char name[30];                                   //课程名
	int week;                                        //星期
	int mark;
	char jieci[6];                                   //节次，例如09-12
	char room[30];                                   //教室编号
	int student_count;                               //学生人数
	char acdemic[30];                                //所属学院
	char weekly[30];                                 //周次，例如1-12,14-16
	struct courses *next;
	struct rooms *rooms;
};

struct funcs
{
	char name[20];
	int courses_count;
	float areas_count;
	float mark;
	struct funcs *next;
};

typedef struct building Building;
typedef struct rooms Rooms;
typedef struct courses Courses;
typedef struct funcs Funcs;

struct call_func
{
	int (*__delete)(void *self);
};

typedef struct call_func Call_func;

#endif /* struct.h */
