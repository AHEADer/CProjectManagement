#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <gtk/gtk.h>

#include "structs.h"
#include "defines.h"
#include "functions.h"

/**
 * 函数名称: error_out
 * 函数功能: 打印出错信息.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void error_out(char *error){
  g_print("%s\n", error);
}

/**
 * 函数名称: clean_var
 * 函数功能: 删除所有数据.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void clean_var(){
  data_delete();
  building_head = NULL;
}


/**
 * 函数名称: call_last_func
 * 函数功能: 检查函数指针last_func，从而调用删除函数.
 * 输入参数: 字符串
 * 输出参数:
 * 返 回 值:
 * 调用说明:
 */
void call_last_func(){
  if(last_func){
    (*last_func)(NULL, CALL_TYPE_REDO);
  }
}

/**
 * 函数名称: contain
 * 函数功能: 判断输入周数是否有课.
 * 输入参数: char *,int
 * 输出参数:
 * 返 回 值: int
 *
 * 调用说明: 比如说原来录入周数1-17，输入10，返回1
 */
int contain(char *s,int t)
{
    int i,q=0;
    int p=0;
    char b[3];
    int a[4];
    for(i=0;i<strlen(s);i++)
    {
		if(s[i]!='-' && s[i]!=',')
		b[p]=s[i];
		else if(s[i]=='-')
		{
			a[q]=atoi(b);
			q++;
			int m;
			for(m=0;m<p;m++)
			b[m]=0;
			p=0;
		}
    }
    if(q<=a[1]&&q>=a[0])
    return 1;
    else
    return 0;
}


/**
 * 函数名称: calculate
 * 函数功能: 分析字符串，根据字符串统计出总周数.
 * 输入参数: 字符串
 * 输出参数:
 * 返 回 值: int
 *
 * 调用说明:  .
 */
int calculate(char *s)
{
    int i,k=0,t;
    char b[3];
    int a[2];
    int n=0,m=0;
    for(i=0;i<strlen(s);i++)
    {

        if(*(s+i)!='-'&&*(s+i)!=',')
        {
            b[k]=s[i];
            k++;
        }

        if(*(s+i)=='-'||*(s+i)==','||i==strlen(s)-1)
        {
            a[m]=(int)atoi(b);
            for(t=0;t<strlen(b);t++)
            {
                b[t]='\0';
            }
            k=0;
            m++;
            if(m==2)
            {
            n=n+a[1]-a[0]+1;
            m=0;
            }
        }
        if(*(s+i)==','&&(*(s+i-3)==','||*(s+i-2)==',')&&m==1)
        {
            m=0;
            n++;
        }
        if(*(s+i)<='9'&&*(s+i)>='0'&&(*(s+i-1)==','||*(s+i-2)==',')&&m==1)
        {
            m=0;
            n++;
        }



    }
    return n;
}
/**
 * 函数名称: build_UI
 * 函数功能: 解析XML文件，构建回调函数，连接功能函数.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */

void build_UI(){
  GtkBuilder *builder = NULL;
  GError *error = NULL;
  builder = gtk_builder_new();
  if(!gtk_builder_add_from_file(builder, UI_FILE, &error)){
    g_warning("%s", error->message);
    g_free(error);
    exit(1);
  }

  /* Get objects */
  /* Main window */
  window = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
  treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview"));
  /* -File menu */
  GtkWidget *menuitem_file_new = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_new"));
  GtkWidget *menuitem_file_open = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_open"));
  GtkWidget *menuitem_file_save = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_save"));
  GtkWidget *menuitem_file_quit = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_file_quit"));
  /* -Query menu */
  /* --Query building menu */
GtkWidget *menuitem_query_building_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_building_all"));
  GtkWidget *menuitem_query_building_code = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_building_code"));
  /* --Query rooms menu */
  GtkWidget *menuitem_query_rooms_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_rooms_all"));
  GtkWidget *menuitem_query_rooms_name = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_rooms_name"));
  GtkWidget *menuitem_query_rooms_code_price = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_rooms_code_price"));
  /* --Query courses menu */
  GtkWidget *menuitem_query_courses_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_courses_all"));
  GtkWidget *menuitem_query_courses_funcs_date = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_courses_funcs_date"));
  GtkWidget *menuitem_query_courses_name_mark = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_query_courses_name_mark"));
  /* -Maintenance menu */
  /* --Maintenance add menu */
  GtkWidget *menuitem_maintenance_add_building = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_building"));
  GtkWidget *menuitem_maintenance_add_rooms = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_rooms"));
  GtkWidget *menuitem_maintenance_add_courses = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_add_courses"));
  /* --Maintenance edit */
  GtkWidget *menuitem_maintenance_edit = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_edit"));
  /* --Maintenance delete */
  GtkWidget *menuitem_maintenance_delete = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_maintenance_delete"));
  /* -Statistics menu */
  GtkWidget *menuitem_statistics_building = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_building"));
  GtkWidget *menuitem_statistics_year = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_year"));
  GtkWidget *menuitem_statistics_funcs = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_funcs"));
  GtkWidget *menuitem_statistics_quarter = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_quarter"));
  GtkWidget *menuitem_statistics_all = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_statistics_all"));
  /* -Other menu */
  GtkWidget *menuitem_other_about = GTK_WIDGET(gtk_builder_get_object(builder, "menuitem_other_about"));
  /* End Get objects */

  /* Connect signals */
  /* Main window */
  g_signal_connect(G_OBJECT(window), "delete-event", G_CALLBACK(file_quit), NULL);
  /* -File menu */
  g_signal_connect(G_OBJECT(menuitem_file_new), "activate", G_CALLBACK(file_new), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_open), "activate", G_CALLBACK(file_open), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_save), "activate", G_CALLBACK(file_save), NULL);
  g_signal_connect(G_OBJECT(menuitem_file_quit), "activate", G_CALLBACK(file_quit), NULL);
  /* -Query menu */
  /* --Query building menu */
  g_signal_connect(G_OBJECT(menuitem_query_building_all), "activate", G_CALLBACK(query_building_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_building_code), "activate", G_CALLBACK(query_building_code), NULL);
  /* --Query rooms menu */
  g_signal_connect(G_OBJECT(menuitem_query_rooms_all), "activate", G_CALLBACK(query_rooms_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_rooms_name), "activate", G_CALLBACK(query_rooms_name), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_rooms_code_price), "activate", G_CALLBACK(query_rooms_code_price), NULL);
  /* --Query courses menu */
  g_signal_connect(G_OBJECT(menuitem_query_courses_all), "activate", G_CALLBACK(query_courses_all), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_courses_funcs_date), "activate", G_CALLBACK(query_courses_funcs_date), NULL);
  g_signal_connect(G_OBJECT(menuitem_query_courses_name_mark), "activate", G_CALLBACK(query_courses_name_mark), NULL);

  /* -Maintenance menu */
  /* --Maintenance add menu */
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_building), "activate", G_CALLBACK(maintenance_add_building), NULL);
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_rooms), "activate", G_CALLBACK(maintenance_add_rooms), NULL);
  g_signal_connect(G_OBJECT(menuitem_maintenance_add_courses), "activate", G_CALLBACK(maintenance_add_courses), NULL);
  /* --Maintenance edit */
  g_signal_connect(G_OBJECT(menuitem_maintenance_edit), "activate", G_CALLBACK(maintenance_edit), NULL);
  /* --Maintenance delete */
  g_signal_connect(G_OBJECT(menuitem_maintenance_delete), "activate", G_CALLBACK(maintenance_delete), NULL);
  /* -Statistics menu */
  g_signal_connect(G_OBJECT(menuitem_statistics_building), "activate", G_CALLBACK(statistics_building), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_year), "activate", G_CALLBACK(statistics_year), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_funcs), "activate", G_CALLBACK(statistics_funcs), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_quarter), "activate", G_CALLBACK(statistics_quarter), NULL);
  g_signal_connect(G_OBJECT(menuitem_statistics_all), "activate", G_CALLBACK(statistics_all), NULL);
  /* -Other menu */
  g_signal_connect(G_OBJECT(menuitem_other_about), "activate", G_CALLBACK(other_about), NULL);
  /* End Connect signals */

  /* Destroy builder */
  g_object_unref(G_OBJECT(builder));

  /* Show window */
  gtk_widget_show_all(GTK_WIDGET(window));
}

/**
 * 函数名称: create_message_dialog
 * 函数功能: 创建确定弹窗.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值: GtkWidget **
 *
 * 调用说明:
 */
GtkWidget **create_message_dialog(GtkWindow *fwindow, char *messages, GtkMessageType type, GtkWidget **dialog_response){

  GtkButtonsType buttons;

  switch(type){
    case GTK_MESSAGE_ERROR: buttons = GTK_BUTTONS_OK; break;
    case GTK_MESSAGE_WARNING: buttons = GTK_BUTTONS_OK; break;
    case GTK_MESSAGE_QUESTION: buttons = GTK_BUTTONS_YES_NO; break;
  }

  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

  dialog_response[0] = GTK_WIDGET(gtk_message_dialog_new(
    fwindow,
    flags,
    type,
    buttons,
    messages));

  return dialog_response;
}

/**
 * 函数名称: create_edit_dialog
 * 函数功能: 创建确定弹窗.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值: GtkWidget **
 *
 * 调用说明:
 */
GtkWidget **create_edit_dialog(GtkWindow *fwindow, int rws, char argi[][100], GtkWidget **dialog_response){

  GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

  dialog_response[0] = GTK_WIDGET(gtk_dialog_new_with_buttons(
    argi[0],
    window,
    flags,
    "确定", GTK_RESPONSE_ACCEPT,
    "取消", GTK_RESPONSE_REJECT,
    NULL));

  dialog_response[1] = gtk_grid_new();
  gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 0);
  gtk_grid_insert_column(GTK_GRID(dialog_response[1]), 1);

  int i;
  for(i=0; i<rws; i++){
    gtk_grid_insert_row(GTK_GRID(dialog_response[1]), i);
  }

  gtk_grid_set_row_spacing(GTK_GRID(dialog_response[1]), 5);
  gtk_grid_set_column_spacing(GTK_GRID(dialog_response[1]), 5);

  for(i=1; i<=rws; i++){
    dialog_response[2*i] = gtk_label_new(argi[i]);
    dialog_response[2*i+1] = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(dialog_response[2*i+1]), argi[i+rws]);
    gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i], 0, i, 1, 1);
    gtk_grid_attach(GTK_GRID(dialog_response[1]), dialog_response[2*i+1], 1, i, 1, 1);
  }

  gtk_container_add(GTK_CONTAINER(gtk_dialog_get_content_area(GTK_DIALOG(dialog_response[0]))), dialog_response[1]);

  return dialog_response;
}

/**
 * 函数名称: save_confirmation
 * 函数功能: 退出时存储数据的弹窗.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值: GtkWidget **
 *
 * 调用说明:
 */
void save_confirmation(){
  if(!updated){

    GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
    question_dialog = create_message_dialog(window, "更改尚未保存，要保存吗?", GTK_MESSAGE_QUESTION, question_dialog);
    gtk_widget_show_all(question_dialog[0]);

    if(gtk_dialog_run(GTK_DIALOG(question_dialog[0])) == GTK_RESPONSE_YES){
      file_save();
    }
    gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
    free(question_dialog);
  }
}

/**
 * 函数名称: building_create
 * 函数功能: 创建主链.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值: int类型.
 *
 * 调用说明: 功能函数，功能实现后返回1
 */
int building_create(Building **head ,char code[], char name[], char phone_number[], int rooms_count, int students_count, float building_area, Rooms *rooms){
  Building *tmp = NULL;
  tmp = (Building *)malloc(sizeof(Building));
  strcpy(tmp->code, code);
  strcpy(tmp->name, name);
  strcpy(tmp->phone_number,phone_number);
  tmp->rooms_count = rooms_count;
  tmp->rooms = rooms;
  tmp->__delete = &building_delete;


  tmp->next = *head;
  *head = tmp;

  return 1;
}

int rooms_create(Rooms **head, char name[], char type, float price, int student_count, int floor, float mark, Building *building, Courses *courses){
  Rooms *tmp = NULL;
  tmp = (Rooms *)malloc(sizeof(Rooms));
  strcpy(tmp->name, name);                                //教室编号
  tmp->student_count=student_count;                       //容纳学生人数
  tmp->type = type;                                       //是否为多媒体教室
  tmp->price = price;                                     //教室面积
  tmp->floor = floor;                                     //楼层
  tmp->mark = mark;
  tmp->building = building;
  tmp->courses = courses;
  tmp->__delete = &rooms_delete;

  tmp->next = *head;
  *head = tmp;

  /* edit the building stats */
  (building->rooms_count)++;

  return 1;
}

/**
 * 函数名称: courses_create
 * 函数功能: 创建课程链.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值: int类型.
 *
 * 调用说明: 功能函数，功能实现后返回1
 */
int courses_create(Courses **head, char date[], char name[], int mark, char jieci[], char room[], int student_count, char acdemic[], char weekly[], Rooms *rooms){
  Courses *tmp = NULL;
  tmp = (Courses *)malloc(sizeof(Courses));
  strcpy(tmp->date, date);
  strcpy(tmp->name, name);
  strcpy(tmp->jieci, jieci);
  strcpy(tmp->room,room);
  tmp->student_count = student_count;
  strcpy(tmp->acdemic, acdemic);
  strcpy(tmp->weekly, weekly);
  tmp->week = mark;
  tmp->mark = mark;
  tmp->rooms = rooms;
  tmp->__delete = &courses_delete;

  tmp->next = *head;
  *head = tmp;

  /* edit the rooms stats */
  tmp->rooms->mark = (tmp->rooms->mark * tmp->rooms->courses_count + mark) / (tmp->rooms->courses_count + 1.0);
  (tmp->rooms->courses_count)++;

  return 1;
}

int funcs_create(Funcs **head, char name[], int courses_count, float areas_count, float mark){
  Funcs *tmp = NULL;
  tmp = (Funcs *)malloc(sizeof(Funcs));
  strcpy(tmp->name, name);
  tmp->courses_count = courses_count;
  tmp->areas_count = areas_count;
  tmp->mark = mark;

  tmp->next = *head;
  *head = tmp;

  return 1;
}


/**
 * 函数名称: data_delete
 * 函数功能: 删除主节点.
 * 输入参数:
 * 输出参数:
 * 返 回 值: int
 *
 * 调用说明:
 */
int data_delete(){
  /* delete target data */
  // self: target struct pointer

  Building **building_itor = &(building_head);
  while(*building_itor){
    building_delete(building_itor);
  }

  return 1;
}

/**
 * 函数名称: building_delete
 * 函数功能: 删除主链.
 * 输入参数: 指针
 * 输出参数:
 * 返 回 值: int类型.
 *
 * 调用说明: 功能函数，功能实现后返回1
 */
int building_delete(void *self){
  /* init */
  Building **target = (Building **)self;
  Building *needfreeca = *target;

  /* delete rooms */
  Rooms **rooms_itor = &(needfreeca->rooms);
  while(*rooms_itor){
    rooms_delete(rooms_itor);
  }

  /* delete self */
  *target = needfreeca->next;
  free(needfreeca);
  needfreeca = NULL;

  return 1;
}

int rooms_delete(void *self){
  /* init */
  Rooms **target = (Rooms **)self;
  Rooms *needfreecl = *target;

  /* delete rooms */
  Courses **courses_itor = &(needfreecl->courses);
  while(*courses_itor){
    courses_delete(courses_itor);
  }

  /* delete self */
  ((*target)->building->rooms_count)--;
  *target = needfreecl->next;
  free(needfreecl);
  needfreecl = NULL;

  return 1;
}

/**
 * 函数名称: courses_delete
 * 函数功能: 删除主链.
 * 输入参数: 指针
 * 输出参数:
 * 返 回 值: int类型.
 *
 * 调用说明: 功能函数，功能实现后返回1
 */
int courses_delete(void *self){
  /* init */
  Courses **target = (Courses **)self;
  Courses *needfreeor = *target;

  /* delete self */
  ((*target)->rooms->courses_count)--;
  *target = needfreeor->next;
  free(needfreeor);
  needfreeor = NULL;

  return 1;
}

int funcs_delete(void *self){
  Funcs **target = (Funcs **)self;
  Funcs *needfreecu = *target;

  *target = needfreecu->next;
  free(needfreecu);
  needfreecu = NULL;

  return 1;
}

/**
 * 函数名称: building_search
 * 函数功能: 根据教学楼编号搜索主链.
 * 输入参数: 教学楼编号(字符串)
 * 输出参数:
 * 返 回 值: Building **类型
 *
 * 调用说明:
 */
Building **building_search(char code[]){
  Building **building_itor = &building_head;

  while(*building_itor){
    if(strstr(code, (*building_itor)->code)){
      return building_itor;
    }
    building_itor = &((*building_itor)->next);
  }

  return NULL;
}

/**
 * 函数名称: building_search
 * 函数功能: 根据教学楼名称搜索主链.
 * 输入参数: 教学楼编号(字符串)
 * 输出参数:
 * 返 回 值: Building **类型
 *
 * 调用说明:
 */
Building **building_search_name(char code[]){
  Building **building_itor = &building_head;

  while(*building_itor){
    if(strstr((*building_itor)->name,code)){
      return building_itor;
    }
    building_itor = &((*building_itor)->next);
  }

  return NULL;
}


Rooms **rooms_search(char name[30]){
  Building **building_itor = &building_head;
  while(*building_itor){
    Rooms **rooms_itor = &((*building_itor)->rooms);
    while(*rooms_itor){
      if(!strcmp((*rooms_itor)->name, name)){
        return rooms_itor;
      }
      rooms_itor = &((*rooms_itor)->next);
    }
    building_itor = &((*building_itor)->next);
  }

  return NULL;
}

Funcs **funcs_search(Funcs **head, char name[20]){
  while(*head){
    if(!strcmp((*head)->name, name)){
      return head;
    }
    head = &((*head)->next);
  }
  return NULL;
}

/**
 * 函数名称: create_list_store
 * 函数功能: 创建表格类型.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void create_list_store(GtkListStore **liststore, int type){
  if(type == BUILDING_ALL){
    *liststore = gtk_list_store_new(
      BUILDING_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //BUILDING_ALL_CODE
      G_TYPE_STRING, //BUILDING_ALL_NAME
      G_TYPE_STRING,
      G_TYPE_INT     //BUILDING_ALL_ROOMS_COUNT
    );
  } else if (type == ROOMS_ALL){
    *liststore = gtk_list_store_new(
      ROOMS_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //ROOMS_ALL_CODE
      G_TYPE_STRING, //ROOMS_ALL_NAME
      G_TYPE_STRING, //ROOMS_ALL_CTYPE
      G_TYPE_FLOAT,  //ROOMS_ALL_PRICE
      G_TYPE_INT     //ROOMS_ALL_COURSES_COUNT
    );
  } else if (type == COURSES_ALL){
    *liststore = gtk_list_store_new(
      COURSES_ALL_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //COURSES_ALL_CNAME
      G_TYPE_STRING, //COURSES_ALL_DATE
      G_TYPE_STRING, //COURSES_ALL_NAME
      G_TYPE_INT,    //COURSES_ALL_MARK
      G_TYPE_STRING,
      G_TYPE_INT,
      G_TYPE_STRING,
      G_TYPE_STRING
    );
  } else if(type == BUILDING_STATS){
    *liststore = gtk_list_store_new(
      BUILDING_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //BUILDING_STATS_CODE
      G_TYPE_STRING, //BUILDING_STATS_NAME
      G_TYPE_INT,    //BUILDING_STATS_COURSES_COUNT
      G_TYPE_FLOAT,  //BUILDING_STATS_SALES_COUNT
      G_TYPE_INT,    //BUILDING_STATS_MARKL3_COUNT
      G_TYPE_INT     //BUILDING_STATS_MARKG3_COUNT
    );
  } else if(type == ROOMS_YEAR){
    *liststore = gtk_list_store_new(
      ROOMS_YEAR_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //ROOMS_YEAR_NAME
      G_TYPE_INT,    //ROOMS_YEAR_CNAME
      G_TYPE_INT,    //ROOMS_YEAR_COURSES_COUNT
      G_TYPE_INT,    //ROOMS_YEAR_SALES_COUNT
      G_TYPE_INT     //ROOMS_YEAR_MARK
    );
  } else if(type == Funcs_STATS){
    *liststore = gtk_list_store_new(
      Funcs_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING, //Funcs_STATS_NAME
      G_TYPE_STRING,    //Funcs_STATS_COURSES_COUNT
      G_TYPE_STRING,  //Funcs_STATS_MONEY_COUNT
      G_TYPE_STRING,   //Funcs_STATS_MARK
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_STRING
    );
  } else if(type == ALL_STATS){
    *liststore = gtk_list_store_new(
      Funcs_STATS_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_INT,    //ALL_STATS_COURSES_COUNT
      G_TYPE_FLOAT,  //ALL_STATS_SALES_COUNT
      G_TYPE_INT,    //ALL_STATS_MARKL3_COUNT
      G_TYPE_INT     //ALL_STATS_MARKG3_COUNT
    );
  } else if(type == COURSE_STATSD){
    *liststore = gtk_list_store_new(
      COURSE_ALLD_COLUMNS,
      G_TYPE_POINTER,
      G_TYPE_INT,
      G_TYPE_STRING,    //ALL_STATS_COURSES_COUNT
      G_TYPE_STRING,  //ALL_STATS_SALES_COUNT
      G_TYPE_STRING,    //ALL_STATS_MARKL3_COUNT
      G_TYPE_STRING,     //ALL_STATS_MARKG3_COUNT
      G_TYPE_STRING,
      G_TYPE_STRING,
      G_TYPE_STRING
    );
  }
}

/**
 * 函数名称: insert_into_list_store
 * 函数功能: 将数据插入到表格中.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void insert_into_list_store(GtkListStore **liststore, void *data, int type){
  GtkTreeIter iter;
  if(type == BUILDING_ALL){
    Building **building_itor = (Building **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      BUILDING_ALL_POINTER, building_itor,
      BUILDING_ALL_TYPE, TYPE_BUILDING,
      BUILDING_ALL_CODE, (*building_itor)->code,
      BUILDING_ALL_NAME, (*building_itor)->name,
      BUILDING_PHONE_NUMBER, (*building_itor)->phone_number,
      BUILDING_ALL_ROOMS_COUNT, (*building_itor)->rooms_count,
      -1);
  } else if(type == ROOMS_ALL){
    Rooms **rooms_itor = (Rooms **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      ROOMS_ALL_POINTER, rooms_itor,
      ROOMS_ALL_TYPE, TYPE_ROOMS,
      ROOMS_ALL_CODE, (*rooms_itor)->building->code,
      ROOMS_ALL_NAME, (*rooms_itor)->name,
      ROOMS_ALL_CTYPE, ((*rooms_itor)->type)=='y'?"是":"否",
      ROOMS_ALL_PRICE, (*rooms_itor)->price,
      ROOMS_ALL_COURSES_COUNT, (*rooms_itor)->floor,
      -1);
  } else if(type == COURSES_ALL){
    Courses **courses_itor = (Courses **)data;
    gtk_list_store_append(*liststore, &iter);
    gtk_list_store_set(
      *liststore, &iter,
      COURSES_ALL_POINTER, courses_itor,
      COURSES_ALL_TYPE, TYPE_COURSES,
      COURSES_ALL_CNAME, (*courses_itor)->rooms->name,
      COURSES_ALL_DATE, (*courses_itor)->date,
      COURSES_ALL_NAME, (*courses_itor)->name,
      COURSES_ALL_MARK, (*courses_itor)->mark,
      COURSES_ALL_JIECI, (*courses_itor)->jieci,
      COURSES_ALL_STUDENTS_COUNT,(*courses_itor)->student_count,
      COURSES_ALL_ACDEMIC,(*courses_itor)->acdemic,
      COURSES_ALL_WEEKLY,(*courses_itor)->weekly,
      -1);
  }
}
void append_column(char column_title[][20], int column_line[], int cls){
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  renderer = gtk_cell_renderer_text_new();
  int i = 0;
  for(i=0; i<cls; i++){
    column = gtk_tree_view_column_new_with_attributes(
      column_title[i],
      renderer,
      "text", column_line[i],
      NULL);
    gtk_tree_view_column_set_sort_column_id(column, column_line[i]);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
  }
}

/**
 * 函数名称: create_column
 * 函数功能: 创建表格.
 * 输入参数: int
 * 输出参数:
 * 返 回 值:  .
 *
 * 调用说明:
 */
void create_column(int type){
  if(type == BUILDING_ALL){
    char column_title[4][20] = {"分类编码", "分类名称", "管理员电话", "教室数"};
    int column_line[4] = {BUILDING_ALL_CODE, BUILDING_ALL_NAME, BUILDING_PHONE_NUMBER,BUILDING_ALL_ROOMS_COUNT};
    int cls = 4;
    append_column(column_title, column_line, cls);
  } else if(type == ROOMS_ALL){
    char column_title[5][20] = {"教学楼编码", "教室编号", "是否多媒体", "教室面积", "楼层"};
    int column_line[5] = {ROOMS_ALL_CODE, ROOMS_ALL_NAME, ROOMS_ALL_CTYPE, ROOMS_ALL_PRICE, ROOMS_ALL_COURSES_COUNT};
    int cls = 5;
    append_column(column_title, column_line, cls);
  } else if(type == COURSES_ALL){
    char column_title[8][20] = {"教室名称", "学期", "课程名称", "星期", "节次", "学生人数", "学院", "周次"};
    int column_line[8] = {COURSES_ALL_CNAME, COURSES_ALL_DATE, COURSES_ALL_NAME, COURSES_ALL_MARK, COURSES_ALL_JIECI, COURSES_ALL_STUDENTS_COUNT, COURSES_ALL_ACDEMIC, COURSES_ALL_WEEKLY};
    int cls = 8;
    append_column(column_title, column_line, cls);
  } else if(type == BUILDING_STATS){
    char column_title[6][20] = {"教学楼编号", "教学楼名称", "教室数量", "总面积", "容纳学生人数", "多媒体教室数"};
    int column_line[6] = {BUILDING_STATS_CODE, BUILDING_STATS_NAME, BUILDING_STATS_COURSES_COUNT, BUILDING_STATS_SALES_COUNT, BUILDING_STATS_MARKL3_COUNT, BUILDING_STATS_MARKG3_COUNT};
    int cls = 6;
    append_column(column_title, column_line, cls);
  } else if(type == ROOMS_YEAR){
    char column_title[5][20] = {"教学楼名称", "教室间数", "开课总学时", "学生人次", "使用单位数"};
    int column_line[5] = {ROOMS_YEAR_NAME, ROOMS_YEAR_CNAME, ROOMS_YEAR_COURSES_COUNT, ROOMS_YEAR_SALES_COUNT, ROOMS_YEAR_MARK};
    int cls = 5;
    append_column(column_title, column_line, cls);
  } else if(type == Funcs_STATS){
    char column_title[4][20] = {" ", " ", " ", " "};
    int column_line[4] = {Funcs_STATS_NAME, Funcs_STATS_COURSES_COUNT, Funcs_STATS_MONEY_COUNT, Funcs_STATS_MARK};
    int cls = 4;
    append_column(column_title, column_line, cls);
  } else if(type ==ALL_STATS){
    char column_title[4][20] = {"教学楼数量", "总面积", "教室总数量", "课程总数量"};
    int column_line[4] = {ALL_STATS_COURSES_COUNT, ALL_STATS_SALES_COUNT, ALL_STATS_MARKL3_COUNT, ALL_STATS_MARKG3_COUNT};
    int cls = 4;
    append_column(column_title, column_line, cls);
  } else if(type ==COURSE_STATSD){
    char column_title[7][20] = {"教室", "1-2节", "3-4节", "5-6节", "7-8节", "9-10节", "11-12节"};
    int column_line[7] = {COURSE_ALLD_NAME, ONE_TWO, THREE_FOUR, FIVE_SIX, SEVEN_EIGHT, NINE_TEN, ELE_TWL};
    int cls = 7;
    append_column(column_title, column_line, cls);
  } else if(type ==LAST_STAT){
    char column_title[6][20] = {"课程名", "教学楼", "教室编号", "周次", "星期", "节次"};
    int column_line[6] = {COURSE_ALLD_NAME, ONE_TWO, THREE_FOUR, FIVE_SIX, SEVEN_EIGHT, NINE_TEN};
    int cls = 6;
    append_column(column_title, column_line, cls);
  }
}

/**
 * 函数名称: clean_column
 * 函数功能: 清屏.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void clean_column(){
  int columns;
  GtkTreeViewColumn *column;
  columns = gtk_tree_view_get_n_columns(treeview);

  while(columns){
    column = gtk_tree_view_get_column(treeview, 0);
    gtk_tree_view_remove_column(treeview, column);
    columns--;
  }
}


/**
 * 函数名称: string
 * 函数功能: 将char类型转化为char*类型.
 * 输入参数:char
 * 输出参数:
 * 返 回 值:char *
 *
 * 调用说明:
 */
char *string(char code){
  char *str = (char *)malloc(sizeof(char) * 2);
  str[0] = code;
  str[1] = '\0';
  return str;
}

/**
 * 函数名称: intstring
 * 函数功能: 将只有一位的int类型转化为char*类型.
 * 输入参数:int
 * 输出参数:
 * 返 回 值:char *
 * 调用说明:
 */
char *intstring(int code){
  char *str = (char *)malloc(sizeof(char) * 2);
  str[0] = code+'0';
  str[1] = '\0';
  return str;
}

/* End Helper function */

/* Basic I/O */
/**
 * 函数名称: save_file
 * 函数功能: 保存数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:int
 *
 * 调用说明:
 */
int save_file(){
  if(!file){
    error_out("save_file: No file loaded.");
    return 0;
  } else {
    Building *building_itor = building_head;

    if(building_itor){
      /* clean file */
      error_out("save_file: clean original file.");
      ftruncate(fileno(file), 0);
    }

    rewind(file);
    while(building_itor){
      fwrite(building_itor, sizeof(Building), 1, file);

      Rooms *rooms_itor = building_itor->rooms;
      while(rooms_itor){
        fwrite(rooms_itor, sizeof(Rooms), 1, file);

        Courses *courses_itor = rooms_itor->courses;
        while(courses_itor){
          fwrite(courses_itor, sizeof(Courses), 1, file);
          courses_itor = courses_itor->next;
        }

        rooms_itor = rooms_itor->next;
      }

      building_itor = building_itor->next;
    }
    updated = TRUE;
    error_out("save_file: finished saving.");
    return 1;
  }
}

/**
 * 函数名称: open_file
 * 函数功能: 打开数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:int
 *
 * 调用说明:
 */
void open_file(char *filename){
  file = fopen(filename, "rb+");
}

int load_file(){
  if(!file){
    error_out("load_file: No file opened.");
    return 0;
  } else {
    /* the ways to load building, rooms, or courses are same
     if you want to see how it works, search "load courses" is enough */

    /* load building */
    if(!feof(file)){
      int count = 0;
      Building *load_building_head = NULL, *load_building_tail = NULL, *load_building_temp = NULL;
      load_building_head = (Building *)malloc(sizeof(Building));
      load_building_tail = load_building_head;
      load_building_temp = NULL;

      do{
        /* load current building */
        if(!fread(load_building_tail, sizeof(Building), 1, file)){
          /* load failed, file ended */
          break;
        }
        count++;
        load_building_tail->__delete = &building_delete;

          /* load rooms */
          if(load_building_tail->rooms_count){
            Rooms *load_rooms_head = NULL, *load_rooms_tail = NULL, *load_rooms_temp = NULL;
            load_rooms_head = (Rooms *)malloc(sizeof(Rooms));
            load_rooms_tail = load_rooms_head;
            load_rooms_temp = NULL;

            int rooms_processed = 0;

            do{
              /* load current rooms */
              fread(load_rooms_tail, sizeof(Rooms), 1, file);
              load_rooms_tail->building = load_building_tail;
              load_rooms_tail->__delete = &rooms_delete;


                /* load courses */
                if(load_rooms_tail->courses_count){
                  Courses *load_courses_head = NULL, *load_courses_tail = NULL, *load_courses_temp = NULL;
                  load_courses_head = (Courses *)malloc(sizeof(Courses));
                  load_courses_tail = load_courses_head;
                  load_courses_temp = NULL;

                  int courses_processed = 0;

                  do{
                    /* load current courses */
                    fread(load_courses_tail, sizeof(Courses), 1, file);
                    load_courses_tail->rooms = load_rooms_tail;
                    load_courses_tail->__delete = &courses_delete;
                    /* end load current courses */
                    /* prepare for next courses */
                    courses_processed++;
                    load_courses_temp = load_courses_tail;
                    load_courses_tail->next = (Courses *)malloc(sizeof(Courses));
                    load_courses_tail = load_courses_tail->next;
                  } while(courses_processed < load_rooms_tail->courses_count);
                  load_courses_temp->next = NULL;
                  free(load_courses_tail);
                  load_courses_tail = NULL;

                  load_rooms_tail->courses = load_courses_head;
                } else {
                  load_rooms_tail->courses = NULL;
                }
                /* end load courses */

              /* end load current rooms */
              /* prepare for next rooms */
              rooms_processed++;
              load_rooms_temp = load_rooms_tail;
              load_rooms_tail->next = (Rooms *)malloc(sizeof(Rooms));
              load_rooms_tail = load_rooms_tail->next;
            } while(rooms_processed < load_building_tail->rooms_count);
            load_rooms_temp->next = NULL;
            free(load_rooms_tail);
            load_rooms_tail = NULL;

            load_building_tail->rooms = load_rooms_head;
          } else {
            load_building_tail->rooms = NULL;
          }
          /* end load rooms */

        /* end load current building */
        /* prepare for next building */
        load_building_temp = load_building_tail;
        load_building_tail->next = (Building *)malloc(sizeof(Building));
        load_building_tail = load_building_tail->next;
      } while(!feof(file));
      free(load_building_tail);
      load_building_tail = NULL;

      if(count){
        load_building_temp->next = NULL;
        building_head = load_building_head;
      } else {
        building_head = NULL;
      }
    } else {
      building_head = NULL;
    }
    /* end load building */
    updated = TRUE;
    g_print("load_file: finished loading.\n");
    return 1;
  }
}

/**
 * 函数名称: close_file
 * 函数功能: 关闭打开的数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void close_file(){
  if(file){
    fclose(file);
    file = NULL;
  }
}

/**
 * 函数名称: file_choose
 * 函数功能: 根据名字寻找数据文件.
 * 输入参数: int
 * 输出参数:
 * 返 回 值: 字符串
 *
 * 调用说明:
 */
char *file_choose(int type){
  GtkWidget *dialog = NULL;
  GtkFileChooser *chooser = NULL;

  if(type == FILE_CHOOSE_OPEN){
    dialog = gtk_file_chooser_dialog_new(
      "打开", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
      "取消", GTK_RESPONSE_CANCEL,
      "确定", GTK_RESPONSE_ACCEPT, NULL);
  } else if(type == FILE_CHOOSE_SAVE){
    dialog = gtk_file_chooser_dialog_new(
      "保存", NULL, GTK_FILE_CHOOSER_ACTION_SAVE,
      "取消", GTK_RESPONSE_CANCEL,
      "确定", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(dialog), TRUE);
  }

  if(gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT){
    char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

    error_out(filename);

    gtk_widget_destroy(dialog);
    return filename;
  } else {
    gtk_widget_destroy(dialog);
    return NULL;
  }

}

/**
 * 函数名称: file_new
 * 函数功能: 创建新的数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void file_new(){
  save_confirmation();
  close_file();
  clean_var();
  clean_column();
  updated = TRUE;
}

/**
 * 函数名称: file_open
 * 函数功能: 打开数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void file_open(){
  save_confirmation();
  char *filename = file_choose(FILE_CHOOSE_OPEN);
  if(filename){
    if(file){
      close_file();
      clean_var();
    }
    open_file(filename);
    if(file){
      if(!load_file()){
        error_out("Load failed.");
      }
    } else {
      error_out("Open failed.");
    }
  } else {
    error_out("Open failed.");
  }
  free(filename);
  filename = NULL;
  clean_column();
}

/**
 * 函数名称: file_save
 * 函数功能: 保存数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void file_save(){
  int save_error;
  if(file){
    if(!save_file()){
      save_error = 1;
    }
  } else {
    char *filename = file_choose(FILE_CHOOSE_SAVE);
    if(filename){
      file = fopen(filename, "wb+");
      if( !(file && save_file()) ){
        save_error = 1;
      }
    }
    free(filename);
    filename = NULL;
  }

  if(save_error){
    error_out("Save failed.");
  }
}

/**
 * 函数名称: file_quit
 * 函数功能: 退出数据文件.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void file_quit(){
  save_confirmation();
  close_file();
  gtk_main_quit();
}
/* End Basic I/O */

/* Query */
/**
 * 函数名称: query_building_all
 * 函数功能: 查询所有教学楼.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_building_all(void *pass, int call_type){
  last_func = &query_building_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, BUILDING_ALL);

  Building **building_itor = &building_head;
  while(*building_itor){
    insert_into_list_store(&liststore, building_itor, BUILDING_ALL);
    building_itor = &((*building_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(BUILDING_ALL);
}

/**
 * 函数名称: query_rooms_all
 * 函数功能: 查询所有教室.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_rooms_all(void *pass, int call_type){
  last_func = &query_rooms_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, ROOMS_ALL);

  Building **building_itor = &building_head;
  while(*building_itor){
    Rooms **rooms_itor = &((*building_itor)->rooms);
    while(*rooms_itor){
      insert_into_list_store(&liststore, rooms_itor, ROOMS_ALL);
      rooms_itor = &((*rooms_itor)->next);
    }
    building_itor = &((*building_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(ROOMS_ALL);
}

/**
 * 函数名称: query_courses_all
 * 函数功能: 查询所有课程.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_courses_all(void *pass, int call_type){
  last_func = &query_courses_all;
  clean_column();

  GtkListStore *liststore;
  create_list_store(&liststore, COURSES_ALL);

  Building **building_itor = &building_head;
  while(*building_itor){
    Rooms **rooms_itor = &((*building_itor)->rooms);
    while(*rooms_itor){
      Courses **courses_itor = &((*rooms_itor)->courses);
      while(*courses_itor){
        insert_into_list_store(&liststore, courses_itor, COURSES_ALL);
        courses_itor = &((*courses_itor)->next);
      }
      rooms_itor = &((*rooms_itor)->next);
    }
    building_itor = &((*building_itor)->next);
  }

  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(COURSES_ALL);
}

/**
 * 函数名称: query_building_code
 * 函数功能: 根据编号查询教学楼.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_building_code(void *pass, int call_type){
  static char code[20];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 1;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询教学楼名称");
    strcpy(argi[1], "教学楼名称");
    strcpy(argi[2], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(code, gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(code[0]=='\0'){
        strcpy(validate_message, "请输入完数据");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_building_code;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, BUILDING_ALL);

    Building **building_itor = building_search_name(code);
    if(building_itor){
      insert_into_list_store(&liststore, building_itor, BUILDING_ALL);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(BUILDING_ALL);
  }
}

/**
 * 函数名称: query_rooms_name
 * 函数功能: 根据编号查询教室.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_rooms_name(void *pass, int call_type){
  static char name[30];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 1;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询教室编号");
    strcpy(argi[1], "教室编号");
    strcpy(argi[2], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    char us_name[1000];
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(us_name, gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(!us_name){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(us_name) > 30){
        strcpy(validate_message, "服装名称过长");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      strcpy(name, us_name);
      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_rooms_name;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, ROOMS_ALL);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor){
        if(strstr((*rooms_itor)->name, name)){
          insert_into_list_store(&liststore, rooms_itor, ROOMS_ALL);
        }
        rooms_itor = &((*rooms_itor)->next);
      }
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(ROOMS_ALL);
  }
}

/**
 * 函数名称: query_rooms_code_muti
 * 函数功能: 根据多项数据查询教室.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_rooms_code_muti(void *pass, int call_type){
  static char code[10];
  static float price_max;
  static float price_min;
  static int floor;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 4;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询教室信息");
    strcpy(argi[1], "教学楼编号");
    strcpy(argi[2], "学生数上限(包含)");
    strcpy(argi[3], "学生数下限(包含)");
    strcpy(argi[4], "楼层");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[7], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(code, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      price_max = atof(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      price_min = atof(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
      floor = atoi(gtk_entry_buffer_get_text(buffer));


      /* error check */
      if(code[0]=='\0' || !price_max || !price_min || !floor){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && price_max < price_min){
        strcpy(validate_message, "请准确输入学生人数");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_rooms_code_price;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, ROOMS_ALL);

    Building **building_itor = building_search(code);
    if(building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor){
        if( (!price_max || (*rooms_itor)->student_count <= price_max) &&
            (!price_min || (*rooms_itor)->student_count >= price_min) && (*rooms_itor)->floor == floor){
          insert_into_list_store(&liststore, rooms_itor, ROOMS_ALL);
        }
        rooms_itor = &((*rooms_itor)->next);
      }
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(ROOMS_ALL);
  }
}

/**
 * 函数名称: query_courses_funcs_date
 * 函数功能: 根据多项数据查询课程.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_courses_funcs_date(void *pass, int call_type){
  static char name[30];
  static char room[30];
  static char date[10];
  static int mark;
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 4;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询课程信息");
    strcpy(argi[1], "课程名");
    strcpy(argi[2], "教室编号");
    strcpy(argi[3], "学期");
    strcpy(argi[4], "星期");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[8], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(name, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      strcpy(room, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      strcpy(date, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
      mark = atoi(gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(name[0]=='\0' || room[0]=='\0' || date[0]=='\0' || !mark){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(name) > 30){
        strcpy(validate_message, "课程名过长");
      }
      if(validate_message[0] == '\0' && strlen(room) > 30){
        strcpy(validate_message, "教室编号过长");
      }
      if(validate_message[0] == '\0' && strlen(date) > 10){
        strcpy(validate_message, "学期格式有误");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_courses_funcs_date;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, COURSES_ALL);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor){
        Courses **courses_itor = &((*rooms_itor)->courses);
        while(*courses_itor){
          if( strstr((*courses_itor)->name, name) &&
              strstr((*courses_itor)->room,room) && strstr((*courses_itor)->date, date) && (*courses_itor)->mark == mark ){
            insert_into_list_store(&liststore, courses_itor, COURSES_ALL);
          }
          courses_itor = &((*courses_itor)->next);
        }
        rooms_itor = &((*rooms_itor)->next);
      }
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(COURSES_ALL);
  }
}

/**
 * 函数名称: query_courses_name_mark
 * 函数功能: 根据多项数据查询课程.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void query_courses_name_mark(void *pass, int call_type){
  static char name[30];
  static char acdemic[30];
  static char coname[30];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 3;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "查询课程信息");
    strcpy(argi[1], "学期");
    strcpy(argi[2], "所属学院");
    strcpy(argi[3], "课程名");
    strcpy(argi[4], "");
    strcpy(argi[5], "");
    strcpy(argi[6], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(name, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      strcpy(acdemic, gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      strcpy(coname, gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(name[0]=='\0' && coname[0]=='\0' && acdemic[0]=='\0'){
        strcpy(validate_message, "请输入完数据");
      }
      if(validate_message[0] == '\0' && strlen(coname) > 30){
        strcpy(validate_message, "课程名称过长");
      }
      if(validate_message[0] == '\0' && strlen(acdemic) > 30){
        strcpy(validate_message, "学院名称过长");
      }
      if(validate_message[0] == '\0' && strlen(name) > 10){
        strcpy(validate_message, "学期名称过长");
      }

      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &query_courses_name_mark;
    clean_column();

    GtkListStore *liststore;
    create_list_store(&liststore, COURSES_ALL);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor){
        Courses **courses_itor = &((*rooms_itor)->courses);
        while(*courses_itor){
          if( strstr((*courses_itor)->date, name) && strstr((*courses_itor)->acdemic, acdemic) && strstr((*courses_itor)->name, coname)){
            insert_into_list_store(&liststore, courses_itor, COURSES_ALL);
          }
          courses_itor = &((*courses_itor)->next);
        }
        rooms_itor = &((*rooms_itor)->next);
      }
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(COURSES_ALL);
  }
}
/* End Query */

/* Maintenance */
/**
 * 函数名称: maintenance_building_dialog
 * 函数功能: 添加教学楼.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
int maintenance_building_dialog(void *self){
  /* init */

  Building **building = (Building **)self;
  int rws = 3;
  char title[100];
  char argi[rws*2+1][100];
  if(!building){
    strcpy(title, "添加教学楼分类");
    strcpy(argi[4], "");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
  } else {
    strcpy(title, "修改教学楼分类");
    strcpy(argi[4], (*building)->code);
    strcpy(argi[5], (*building)->phone_number);
    strcpy(argi[6], (*building)->name);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "分类编码");
  strcpy(argi[2], "管理员电话");
  strcpy(argi[3], "分类名称");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];                                                       //在validate_message输入错误警告
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char code[100];
  char name[100];
  char phone_number[100];
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    strcpy(code, gtk_entry_buffer_get_text(buffer));                        //教学楼编号
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(phone_number, gtk_entry_buffer_get_text(buffer));                //管理员电话
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[3*2+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));                        //教学楼名称

    /* error check */
    if(code[0] == '\0' || name[0] == '\0'){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 9){
      strcpy(validate_message, "分类名称过长");
    }
    if(validate_message[0] == '\0' && strlen(phone_number) > 14){
      strcpy(validate_message, "电话号码过长");
    }
    Building **search_result;
    if(validate_message[0] == '\0' && ((search_result = building_search(code)) && ((!building) || (building && ((*building)->code != code))))){
      strcpy(validate_message, "分类编码重复");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */

    if(!building){
      building_create(&building_head, code, name, phone_number, 0, 0, 0, NULL);
    } else {
      strcpy((*building)->code, code);
      strcpy((*building)->name, name);
      strcpy((*building)->phone_number, phone_number);
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

  free(warning_dialog);
  free(dialog_result);

  return success;
}

/**
 * 函数名称: maintenance_rooms_dialog
 * 函数功能: 添加教室.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
int maintenance_rooms_dialog(void *self){
  /* init */
  Rooms **rooms = (Rooms **)self;
  int rws = 5;
  char title[100];
  char argi[rws*5+1][100];
  if(!rooms){
    strcpy(title, "添加教室信息");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[8], "");
    strcpy(argi[9], "");
    strcpy(argi[10], "");
  } else {
    strcpy(title, "修改教室信息");
    strcpy(argi[6], string((*rooms)->type));
    strcpy(argi[7], (*rooms)->name);
    sprintf(argi[8],"%d",(*rooms)->floor);
    sprintf(argi[9], "%f", (*rooms)->price);
	sprintf(argi[10], "%d", (*rooms)->student_count);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "是否多媒体");
  strcpy(argi[2], "教室编号");
  strcpy(argi[3], "教室楼层");
  strcpy(argi[4], "教室面积");
  strcpy(argi[5], "容纳学生人数");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char code[100];                                              //所属教学楼编号
  char name[1000];                                            //教室的编号
  char type;                                                  //这里是"'是否为多媒体教室'"
  float price;                                                //教室面积
  int student_count;                                          //容纳学生人数
  int floor;                                                  //楼层
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    type = gtk_entry_buffer_get_text(buffer)[0];                        //是否多媒体
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));                    //教室编号
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
    floor = atoi(gtk_entry_buffer_get_text(buffer));                    //教室楼层
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
    price = atof(gtk_entry_buffer_get_text(buffer));                    //教室面积
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*5+1]));
    student_count = atoi(gtk_entry_buffer_get_text(buffer));            //容纳学生人数

    /* error check */
    if(name[0] == '\0' || !type || !price || !floor || !student_count){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 30){
      strcpy(validate_message, "教室名称过长");
    }
    Rooms **search_result;
    if(validate_message[0] == '\0' && ((search_result = rooms_search(name)) && ((!rooms) || (rooms && (strcmp((*rooms)->name, name)))))){
      strcpy(validate_message, "教室名称重复");
    }
    Building **building;
    if(validate_message[0] == '\0' && !(building = building_search(name))){
      strcpy(validate_message, "没有所属教学楼");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */


    if(!rooms){
      rooms_create(&((*building)->rooms), name, type, price, student_count, floor, 0, *building, NULL);
    } else {
      Rooms *rooms_old = *rooms;

      /* remove from original list */
      ((*rooms)->building->rooms_count)--;
      *rooms = (*rooms)->next;

      /* insert into new list */
      rooms_old->next = (*building)->rooms;
      (*building)->rooms = rooms_old;
      rooms_old->building = (*building);
      ((*building)->rooms_count)++;

      strcpy(rooms_old->name, name);
      rooms_old->type = type;
      rooms_old->price = price;
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

  free(warning_dialog);
  free(dialog_result);

  return success;
}

/**
 * 函数名称: maintenance_courses_dialog
 * 函数功能: 添加课程.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
int maintenance_courses_dialog(void *self){
  /* init */
  Courses **courses = (Courses **)self;
  int rws = 8;
  char title[100];
  char argi[rws*8+1][100];
  if(!courses){
    strcpy(title, "添加课程信息");
    strcpy(argi[9], "");
    strcpy(argi[10], "");
    strcpy(argi[11], "");
    strcpy(argi[12], "");
    strcpy(argi[13], "");
    strcpy(argi[14], "");
    strcpy(argi[15], "");
    strcpy(argi[16], "");
  } else {
    strcpy(title, "修改课程信息");
    strcpy(argi[9], ((*courses)->rooms->name));
    strcpy(argi[10], (*courses)->date);
    strcpy(argi[11], (*courses)->name);
    sprintf(argi[12], "%d", (*courses)->mark);            //星期
    strcpy(argi[13], (*courses)->jieci);
    sprintf(argi[14], "%d", (*courses)->student_count);
    strcpy(argi[15], (*courses)->acdemic);
    strcpy(argi[16], (*courses)->weekly);
  }
  strcpy(argi[0], title);
  strcpy(argi[1], "教室编号");
  strcpy(argi[2], "学期");
  strcpy(argi[3], "课程名");
  strcpy(argi[4], "星期");
  strcpy(argi[5], "节次");
  strcpy(argi[6], "学生人数");
  strcpy(argi[7], "所属学院");
  strcpy(argi[8], "周次");

  GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
  dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
  gtk_widget_show_all(dialog_result[0]);

  char validate_message[100];
  validate_message[0] = '\0';
  int success = 0;
  GtkEntryBuffer *buffer;
  char cname[100];
  char date[100];
  char name[100];
  int mark;
  char jieci[100];
  int student_count;
  char acdemic[100];
  char weekly[100];
  GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

  while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
    validate_message[0] = '\0';
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
    strcpy(cname, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
    strcpy(date, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
    strcpy(name, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
    mark = atoi(gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*5+1]));
    strcpy(jieci, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*6+1]));
    student_count = atoi(gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*7+1]));
    strcpy(acdemic, gtk_entry_buffer_get_text(buffer));
    buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*8+1]));
    strcpy(weekly, gtk_entry_buffer_get_text(buffer));

    /* error check */
    if(!cname || date[0] == '\0' || name[0] == '\0' || !mark || jieci[0] == '\0' || !student_count || acdemic[0]=='\0' || weekly[0]=='\0'){
      strcpy(validate_message, "请输入完数据");
    }
    if(validate_message[0] == '\0' && strlen(name) > 30){
      strcpy(validate_message, "教室编号过长");
    }
    Rooms **rooms;
    if(validate_message[0] == '\0' && !(rooms = rooms_search(cname))){
      strcpy(validate_message, " 此教室");
    }

    if(validate_message[0] != '\0'){
      warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
      gtk_widget_show_all(warning_dialog[0]);
      gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
      gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
      continue;
    }
    /* end error check */


    if(!courses){
      courses_create(&((*rooms)->courses), date, name, mark, jieci, cname, student_count, acdemic, weekly, *rooms);
    } else {
      Courses *courses_old = *courses;

      /* remove from original list */
      if(((*courses)->rooms->courses_count) == 1){
        (*courses)->rooms->mark = 0;
      } else {
        (*courses)->rooms->mark = ( ((*courses)->rooms->mark) * ((*courses)->rooms->courses_count) - ((*courses)->mark) ) / (((*courses)->rooms->courses_count)-1);
      }
      ((*courses)->rooms->courses_count)--;
      *courses = (*courses)->next;

      /* insert into new list */
      courses_old->next = (*rooms)->courses;
      (*rooms)->courses = courses_old;
      courses_old->rooms = (*rooms);
      (*rooms)->mark = ( ((*rooms)->mark) * ((*rooms)->courses_count) + (courses_old->mark) ) / (((*rooms)->courses_count)+1);
      ((*rooms)->courses_count)++;

      strcpy(courses_old->date, date);
      strcpy(courses_old->name, name);
      (*rooms)->mark = ( ((*rooms)->mark) * ((*rooms)->courses_count) - (courses_old->mark) + mark ) / ((*rooms)->courses_count);
      courses_old->mark = mark;
    }
    success = 1;
    break;
  }

  gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

  free(warning_dialog);
  free(dialog_result);

  return success;
}

/**
 * 函数名称: maintenance_add_building
 * 函数功能: 添加教学楼.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void maintenance_add_building(){
  if(maintenance_building_dialog(NULL)){
    updated = FALSE;
    call_last_func();
  } else {
    error_out("Add buildings failed.");
  }
}

/**
 * 函数名称: maintenance_add_building
 * 函数功能: 添加教室.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void maintenance_add_rooms(){
  if(maintenance_rooms_dialog(NULL)){
    updated = FALSE;
    call_last_func();
  } else {
    error_out("Add rooms failed.");
  }
}

/**
 * 函数名称: maintenance_add_building
 * 函数功能: 添加课程.
 * 输入参数: void型指针
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void maintenance_add_courses(){
  if(maintenance_courses_dialog(NULL)){
    updated = FALSE;
    call_last_func();
  } else {
    error_out("Add courses failed.");
  }
}
/**
 * 函数名称: maintenance_delete
 * 函数功能: 删除指定数据.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void maintenance_delete(){
  GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gpointer *self;

  if(gtk_tree_selection_get_selected(selection, &model, &iter)){
    /* check */
    gtk_tree_model_get(model, &iter, 0, &self, -1);
    if(!self) return;

    GtkWidget **question_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));
    question_dialog = create_message_dialog(window, "确定要删除吗?", GTK_MESSAGE_QUESTION, question_dialog);
    gtk_widget_show_all(question_dialog[0]);

    if(gtk_dialog_run(GTK_DIALOG(question_dialog[0])) == GTK_RESPONSE_YES){
      gtk_tree_model_get(model, &iter, 0, &self, -1);
      Call_func **target = (Call_func **)self;
      (*((*target)->__delete))(self);
      updated = FALSE;
    }
    gtk_widget_destroy(GTK_WIDGET(question_dialog[0]));
    free(question_dialog);
  }

  call_last_func();
}

/**
 * 函数名称: maintenance_edit
 * 函数功能: 修改指定数据.
 * 输入参数:
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void maintenance_edit(){
  GtkTreeSelection *selection = gtk_tree_view_get_selection(treeview);
  GtkTreeIter iter;
  GtkTreeModel *model;
  gpointer *self;
  gint type;
  int success;

  if(gtk_tree_selection_get_selected(selection, &model, &iter)){
    gtk_tree_model_get(model, &iter, 0, &self, -1);
    gtk_tree_model_get(model, &iter, 1, &type, -1);

    switch(type){
      case TYPE_BUILDING: success = maintenance_building_dialog(self);break;
      case TYPE_ROOMS: success = maintenance_rooms_dialog(self);break;
      case TYPE_COURSES: success = maintenance_courses_dialog(self);break;
      case TYPE_OTHER: return;
    }
    if(success){
      updated = FALSE;
      call_last_func();
    } else {
      error_out("Edit failed.");
    }
  } else {
    error_out("Choose first.");
  }
}
/* End Maintenance */

/* Statistics */
/**
 * 函数名称: statistics_building
 * 函数功能: 统计1功能.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void statistics_building(void *pass, int call_type){
  last_func = &statistics_building;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;
  create_list_store(&liststore, BUILDING_STATS);

  Building **building_itor = &building_head;
  while(*building_itor){
    int floor = 0;
    float sales_count = 0;
    int markl3_count = 0;
    int markg3_count = 0;
    Rooms **rooms_itor = &((*building_itor)->rooms);
    while(*rooms_itor){
      Courses **courses_itor =  &((*rooms_itor)->courses);
      while(*courses_itor){
        courses_itor = &((*courses_itor)->next);
      }
      if((*rooms_itor)->type == 'y')
      markg3_count += 1;

      markl3_count += ((*rooms_itor)->student_count);
      floor += 1;
      sales_count += ((*rooms_itor)->price);
      rooms_itor = &((*rooms_itor)->next);
    }
    gtk_list_store_append(liststore, &iter);
    gtk_list_store_set(
      liststore, &iter,
      BUILDING_STATS_POINTER, building_itor,
      BUILDING_STATS_TYPE, TYPE_BUILDING,
      BUILDING_STATS_CODE, (*building_itor)->code,
      BUILDING_STATS_NAME, (*building_itor)->name,
      BUILDING_STATS_COURSES_COUNT, floor,                 //教室数量
      BUILDING_STATS_SALES_COUNT, sales_count,                 //总面积
      BUILDING_STATS_MARKL3_COUNT, markl3_count,               //容纳学生人数
      BUILDING_STATS_MARKG3_COUNT, markg3_count,               //多媒体教室数量
      -1);
    building_itor = &((*building_itor)->next);
  }
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(BUILDING_STATS);
}

/**
 * 函数名称: statistics_year
 * 函数功能: 统计2功能.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void statistics_year(void *pass, int call_type){

  static char dateyear[10];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 1;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "统计(根据学期）");
    strcpy(argi[1], "学期");
    strcpy(argi[2], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(dateyear,gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &statistics_year;
    clean_column();

    GtkListStore *liststore;
    GtkTreeIter iter;
    create_list_store(&liststore, ROOMS_YEAR);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      int floor = 0;
	  int course_count = 0;
	  int student_count = 0;
	  int mark = 0;
	  int p;
      while(*rooms_itor){
        Courses **courses_itor = &((*rooms_itor)->courses);
        char danwei[20][30];
        int i=0;
        while(*courses_itor){
          if( strstr((*courses_itor)->date,dateyear) ){
            floor += (calculate((*courses_itor)->jieci))*(calculate((*courses_itor)->weekly));
            course_count += 1;
            student_count += (*courses_itor)->student_count;
            if(i==0)
            mark += 1;
            else
            for(p=0;p<i;p++)
            {
				if(!strcmp(danwei[1],(*courses_itor)->acdemic))
				break;
				if(p==i-1)
				mark += 1;
            }
          }
          courses_itor = &((*courses_itor)->next);
        }

        rooms_itor = &((*rooms_itor)->next);
      }
      gtk_list_store_append(liststore, &iter);
        gtk_list_store_set(
		liststore, &iter,
		ROOMS_YEAR_POINTER, rooms_itor,
		ROOMS_YEAR_TYPE, TYPE_ROOMS,
		ROOMS_YEAR_NAME, (*building_itor)->name,
		ROOMS_YEAR_CNAME, course_count,                           //开课门数
		ROOMS_YEAR_COURSES_COUNT, floor,                          //开课总学时数
		ROOMS_YEAR_SALES_COUNT, student_count,                    //听课学生人次数
		ROOMS_YEAR_MARK, mark,                                    //使用单位数
          -1);
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(ROOMS_YEAR);
  }
}

/**
 * 函数名称: statistics_funcs
 * 函数功能: 统计3功能.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void statistics_funcs(void *pass, int call_type){
  static char dateyear[10];
  static int weekly;
  static int week;
  static char code[10];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 4;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "统计(根据学期，周次，星期，教学楼）");
    strcpy(argi[1], "学期");
    strcpy(argi[2], "周次");
    strcpy(argi[3], "星期");
    strcpy(argi[4], "教学楼编号");
    strcpy(argi[5], "");
    strcpy(argi[6], "");
    strcpy(argi[7], "");
    strcpy(argi[8], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(dateyear,gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      weekly = atoi(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*3+1]));
      week = atoi(gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*4+1]));
      strcpy(code,gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &statistics_year;
    clean_column();

    GtkListStore *liststore;
    GtkTreeIter iter;
    create_list_store(&liststore, COURSE_STATSD);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor && strstr((*building_itor)->code,code)){
        Courses **courses_itor = &((*rooms_itor)->courses);
        int i=0;
        char cou[6][20]={"","","","","",""};
        while(*courses_itor){
        if(strstr((*courses_itor)->date,dateyear) && /*contain((*courses_itor)->weekly,weekly) &&*/ (*courses_itor)->week == week)
			{
				if(strstr((*courses_itor)->jieci,"1-2") || strstr((*courses_itor)->jieci,"01-02"))
				{
					strcpy(cou[0],(*courses_itor)->name);
				}
				else
				if(strstr((*courses_itor)->jieci,"3-4") || strstr((*courses_itor)->jieci,"03-04"))
				{
					strcpy(cou[1],(*courses_itor)->name);
				}
				else
				if(strstr((*courses_itor)->jieci,"5-6") || strstr((*courses_itor)->jieci,"05-06"))
				{
					strcpy(cou[2],(*courses_itor)->name);
				}
				if(strstr((*courses_itor)->jieci,"7-8") || strstr((*courses_itor)->jieci,"07-08"))
				{
					strcpy(cou[3],(*courses_itor)->name);
				}
				else
				if(strstr((*courses_itor)->jieci,"9-10") || strstr((*courses_itor)->jieci,"09-10"))
				{
					strcpy(cou[4],(*courses_itor)->name);
				}
				else
				if(strstr((*courses_itor)->jieci,"11-12"))
				{
					strcpy(cou[5],(*courses_itor)->name);
				}

			}




          courses_itor = &((*courses_itor)->next);
        }
				gtk_list_store_append(liststore, &iter);
				gtk_list_store_set(
				liststore, &iter,
				COURSE_ALLD_POINTER, courses_itor,
				COURSE_ALLD_TYPE, TYPE_COURSE_ALL,
				COURSE_ALLD_NAME, (*rooms_itor)->name,
				ONE_TWO, cou[0],
				THREE_FOUR, cou[1],
				FIVE_SIX, cou[2],
				SEVEN_EIGHT, cou[3],
				NINE_TEN, cou[4],
				ELE_TWL, cou[5],
				-1);

        rooms_itor = &((*rooms_itor)->next);
      }
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(COURSE_STATSD);
  }
}

/**
 * 函数名称: statistics_quarter
 * 函数功能: 统计4功能.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void statistics_quarter(void *pass, int call_type){
  static char dateyear[10];
  static char code[30];
  int success = 0;

  if(call_type != CALL_TYPE_REDO){
    int rws = 2;
    char title[100];
    char argi[rws*2+1][100];
    strcpy(argi[0], "统计(根据学期，学员名）");
    strcpy(argi[1], "学期");
    strcpy(argi[2], "学院名");
    strcpy(argi[3], "");
    strcpy(argi[4], "");

    GtkWidget **dialog_result = (GtkWidget **)malloc(sizeof(GtkWidget *)*(rws*2+2));
    dialog_result = create_edit_dialog(window, rws, argi, dialog_result);
    gtk_widget_show_all(dialog_result[0]);

    char validate_message[100];
    validate_message[0] = '\0';
    GtkEntryBuffer *buffer;
    GtkWidget **warning_dialog = (GtkWidget **)malloc(sizeof(GtkWidget *)*(1));

    while(gtk_dialog_run(GTK_DIALOG(dialog_result[0])) == GTK_RESPONSE_ACCEPT){
      validate_message[0] = '\0';
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*1+1]));
      strcpy(dateyear,gtk_entry_buffer_get_text(buffer));
      buffer = gtk_entry_get_buffer(GTK_ENTRY(dialog_result[2*2+1]));
      strcpy(code,gtk_entry_buffer_get_text(buffer));

      /* error check */
      if(validate_message[0] != '\0'){
        warning_dialog = create_message_dialog(GTK_WINDOW(dialog_result[0]), validate_message, GTK_MESSAGE_WARNING, warning_dialog);
        gtk_widget_show_all(warning_dialog[0]);
        gtk_dialog_run(GTK_DIALOG(warning_dialog[0]));
        gtk_widget_destroy(GTK_WIDGET(warning_dialog[0]));
        continue;
      }
      /* end error check */

      success = 1;
      break;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog_result[0]));

    free(warning_dialog);
    free(dialog_result);
  }

  if(success || call_type == CALL_TYPE_REDO){
    last_func = &statistics_year;
    clean_column();

    GtkListStore *liststore;
    GtkTreeIter iter;
    create_list_store(&liststore, COURSE_STATSD);

    Building **building_itor = &building_head;
    while(*building_itor){
      Rooms **rooms_itor = &((*building_itor)->rooms);
      while(*rooms_itor){
        Courses **courses_itor = &((*rooms_itor)->courses);
        int i=0;
        while(*courses_itor){
        if(strstr((*courses_itor)->date,dateyear) && strstr((*courses_itor)->acdemic,code))
			{
				gtk_list_store_append(liststore, &iter);
				gtk_list_store_set(
				liststore, &iter,
				COURSE_ALLD_POINTER, courses_itor,
				COURSE_ALLD_TYPE, TYPE_COURSE_ALL,
				COURSE_ALLD_NAME, (*courses_itor)->name,
				ONE_TWO, (*building_itor)->name,
				THREE_FOUR, (*rooms_itor)->name,
				FIVE_SIX, (*courses_itor)->weekly,
				SEVEN_EIGHT, intstring((*courses_itor)->week),
				NINE_TEN, (*courses_itor)->jieci,
				-1);
			}


          courses_itor = &((*courses_itor)->next);
        }
        rooms_itor = &((*rooms_itor)->next);
      }
      building_itor = &((*building_itor)->next);
    }
    gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
    create_column(LAST_STAT);
  }
}

/**
 * 函数名称: statistics_all
 * 函数功能: 统计5功能.
 * 输入参数: void型指针，int型回调值
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void statistics_all(void *pass, int call_type){
  last_func = &statistics_all;
  clean_column();

  GtkListStore *liststore;
  GtkTreeIter iter;
  create_list_store(&liststore, ALL_STATS);
  int floor = 0;
  float sales_count = 0;
  int markl3_count = 0;
  int markg3_count = 0;

  Building **building_itor = &building_head;
  while(*building_itor){
	floor += 1;
    Rooms **rooms_itor = &((*building_itor)->rooms);
    while(*rooms_itor){
      Courses **courses_itor =  &((*rooms_itor)->courses);
      markl3_count++;
      while(*courses_itor){
        markg3_count++;
        courses_itor = &((*courses_itor)->next);
      }
      sales_count += (*rooms_itor)->price;
      rooms_itor = &((*rooms_itor)->next);
    }
    building_itor = &((*building_itor)->next);
  }

  gtk_list_store_append(liststore, &iter);
  gtk_list_store_set(
    liststore, &iter,
    ALL_STATS_POINTER, NULL,
    ALL_STATS_TYPE, TYPE_OTHER,
    ALL_STATS_COURSES_COUNT, floor,
    ALL_STATS_SALES_COUNT, sales_count,
    ALL_STATS_MARKL3_COUNT, markl3_count,
    ALL_STATS_MARKG3_COUNT, markg3_count,
    -1);
  gtk_tree_view_set_model(treeview, GTK_TREE_MODEL(liststore));
  create_column(ALL_STATS);
}
/* End Statistics */

/* Other Function */
/**
 * 函数名称: other_about
 * 函数功能: 关于.
 * 输入参数: ...
 * 输出参数:
 * 返 回 值:
 *
 * 调用说明:
 */
void other_about(){
  GtkWidget *about_window = NULL;
  about_window = gtk_about_dialog_new();
  gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(about_window), program_name);
  gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(about_window), version);
  gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(about_window), comments);
  gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(about_window), website);
  gtk_about_dialog_set_website_label(GTK_ABOUT_DIALOG(about_window), website_lable);
  gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG(about_window), author);
  gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(about_window), NULL);
  gtk_about_dialog_set_license_type(GTK_ABOUT_DIALOG(about_window), GTK_LICENSE_GPL_2_0);
  gtk_widget_show_all(about_window);
}
/* End Other Function */
