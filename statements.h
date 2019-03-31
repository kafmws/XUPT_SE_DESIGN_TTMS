#pragma once
//////////////////////////////////////静态全局变量\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

const int NAME = 15, PASSWORD = 12;


//////////////////////////////////////枚举类型定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef enum {
	FILM_KEY = 1,
	OPERA_KEY = 2,
	CONCERT_KEY = 3,
	PLAN_KEY = 4,
	RECORD_KEY = 5,
	TICKET_KEY = 6,
	ACCOUNT_KEY = 7,
}Key_status;

typedef enum {//定义剧目枚举类型
	PROGRAM_movie = 1,//电影
	PROGRAM_opera = 2,//歌剧
	PROGRAM_concert = 3//音乐会
}program_types;

typedef enum {//定义账户枚举类型
	USER_admin = 1,
	USER_manager = 2,
	USER_conductor = 3,
	USER_customer = 4,
	USER_frozen = 5,//冻结状态
}user_types;

typedef enum {//定义电影分级枚举类型
	RATING_child = 1,//儿童可观看
	RATING_teens = 2,//青少年可观看
	RATING_adult = 3//成人可观看
}program_ratings;

typedef enum {//定义座位情况枚举类型
	SEAT_none = 0,	//空位
	SEAT_available = 1,//有座位
	SEAT_private=2,//雅座
	SEAT_unrepaired = 9//损坏的座位
}seat_conditions;

typedef enum {
	TICKET_available=0,//待售
	TICKET_sold = 1,//已售
	TICKET_reserve = 2,//预留
}ticket_statuses;

typedef enum {
	SALE_sold=1,//卖出
	SALE_return=2,//退票
}sale_types;

//////////////////////////////////////结构定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct {
	int year;
	int month;
	int day;
}date_status;//日期结构体

typedef struct {
	int hour;
	int minute;
}time_status;//时间结构体

////////////////////////////////////////先行定义

typedef struct linklist_key {
	long key;
	char type;//实体类型    1  电影    2 歌剧   3音乐会     4演出计划     5销售记录
	struct linklist_key  *pre, *next;
}Key;

typedef struct linklist_seat {
	int stduio_ID;//座位所在放映厅编号
	int seatx;//座位所在行
	int seaty;//座位所在列
	seat_conditions seat_condition;//位置状态   参见enum seat_conditions
	struct linklist_seat *pre, *next;
}Seat;

typedef struct linklist_ticket {
	long ticket_ID;//入场券编号
	long plan_ID;//演出计划编号
	int seatx;//座位所在行
	int seaty;//座位所在列
	int price;//票价    剧目决定
	ticket_statuses ticket_status;//票的状态     参见enum tickets_statuses
	struct linklist_ticket *pre, *next;
}Ticket;

typedef struct linklist_record{//交易记录
	long record_ID;//交易记录ID
	long conductor_ID;//记录产生者
	long plan_ID;//演出计划ID
	long ticket_ID;//票ID
	int price;//票价
	char datetime[17];//处理时间
	sale_types sale_type;//交易类型
	struct linklist_record *pre, *next;
}Record;

//////////////////////////////////////实体数据域定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

typedef struct em{//剧目数据域
	char program_ID[NAME/2+1];//  剧目编号
	char program_name[NAME * 2 + 1];//15汉字    剧目名称
	program_types program_type;//剧目类型  参见enum program_types枚举定义
	program_ratings program_rating;//剧目等级 参见program_ratings枚举定义
	char director[NAME];//7个汉字     导演   音乐会为指挥
	char performer[2][NAME];//7个汉字      主演   两名
	char start_date[11]; //上映日期   格式2018-05-12 长度为10
	char end_date[11]; //结束日期   格式2018-05-12 长度为10s
	int duration;//剧目时长       minute   [1,600]
	char  label[5];//剧目标签   比如  喜剧  动作   惊悚 
	char area[5];//地区   2个汉字
	char language[NAME];//语言
	int price;//票价   [5,100]
	int cost;//放映成本    （万元)
	long contributions;//票房
}data_program;

typedef struct emm {
	char studio_ID[NAME/2];//最多六位数字   放映厅编号
	char studio_name[NAME];//最多七个汉字    放映厅名称
	int seatsum;//可用座位个数
	int seatx;//5~12
	int seaty;//10~25  放映厅座位 的行和列    固有属性   用来设置二维数组
	Seat *seat_head, *seat_tail;//次链表
}data_studio;

typedef struct emmm {//演出计划数据域
	long plan_ID;//演出计划编号
	char program_name[NAME * 2 + 1];//演出剧目名称
	int studio_ID;//放映厅编号
	char date[11]; //演出日期   格式2018-05-12 长度为10
	char time[6];//开始时间    格式hh:mm  长度为5 24小时制
	int ticketnum;//计划中总票数//余票存在票的头结点
	long contributions;//销售额
	int button;//计划的有效性   删除后此值变为0    载入时为0的值跳过
	Ticket *ticket_head, *ticket_tail;//次链表
}data_plan;

typedef struct emmmm {//账号数据域
	char UID[NAME-6];//账号编号   8位   用于修改密码或找回密码
	char username[NAME];//用户名   4~14个字符/2~7个汉字
	char password[PASSWORD+1];//登录口令  6~12
	user_types user_type;//账号类型     参见enum user_types枚举定义
	long contributions;//       本月业绩\购买额
	//Record *record_head, *record_tail;//销售记录、购买记录 链表
}data_account;

/////读取销售记录时计算业绩      新增销售记录时实时更新     销售排名时不再重新计算
////////////////////////////////////////实体定义\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


typedef struct linklist_program {//剧目
	data_program element;
	struct linklist_program *pre,*next;
}Program;

typedef struct linklist_studio {//放映厅
	data_studio element;
	struct linklist_studio *pre, *next;
}Studio;

typedef struct linklist_plan {//演出计划
	data_plan element;
	struct linklist_plan *pre, *next;
}Plan;

typedef struct linklist_account {//账号
	data_account element;
	struct linklist_account *pre, *next;
}Account;



typedef struct ctrl {//链表类型
	Program *program_head, *program_tail;
	Studio *studio_head, *studio_tail;
	Plan *plan_head, *plan_tail;
	Plan *plan_tem_head, *plan_tem_tail;
	Account *account_head, *account_tail;
	Record *record_head, *record_tail;
	Key *key_head, *key_tail;
}List;

////////////////////////////////////////全局变量\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

extern List list;
extern data_account PRESENT;
extern struct tm *now;

/////////////////////////////////////////函数\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

int choice_judge(int i);//读取键盘事件  判断选择
void set_position(short x, short y);//设置光标位置
void set_position(COORD position);//设置光标位置
void SetColor(short foreColor, short backColor);//设置字体颜色
void hide_cursor();//隐藏光标
void catch_cursor();//显示光标
POINT get_position();//得到当前光标y坐标
int screen_clear(int order, int i, int change);/*主界面的高亮控制  i表示当前高亮选项 默认为1
										参数change表改变量  order表示界面的选择  函数返回当前选项编号*/
int turn_page();//翻页器
int select_seat(Studio *p);//判别位置  ↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3  返回值判断是否修改
int select_seat(Plan *p, int limit);//售票选择位置  ESC 0   回车3  返回值表示所购票数  limit 最大购买量
void clear_seat(COORD position, char status);//改变座位显示  COORD  当前位置   status 座位状态
void clear_ticket(COORD position, char status);//COORD  当前位置   status 票状态

/////////////////////////////////////////////////window.cpp

void show_welcome();//欢迎界面
void show_main();//主界面
void show_sign();//登录界面
void show_bye();//再见界面
void show_register();//注册界面

void show_customer();//顾客主界面
void show_manager();//剧院经理主界面
void show_program();//剧目查询及管理界面
void show_studio();//影厅查询及管理界面
void show_plan();//演出计划查询及管理
void show_record();//销售统计与查询

void show_admin();//系统管理员主界面
void show_account();//账户管理界面
void show_account_type();//账户类型选择界面

void show_conducter();//售票员管理界面
void show_ticket();//售票员票务管理界面

//////////////////////////////////////////////////welcom.cpp

void print_re();//获得反馈
void print_examinput();//非法输入报错
void go_on();//按任意键继续
void exam_NULL(void *p, int choice);//空指针报错   0 malloc   1文件
int enquiry(int i);//判断是否进行本次操作   i==1   enquiry   i==2 warnning
void print_ok(); //提示操作成功
void print_instruction(int i);//显示操作说明
void print_planhead();//打印演出计划表头
void print_planhead2();//打印演出计划顾客端表头
void print_programhead();//打印剧目排行榜表头
void print_accounthead();//打印账号表头

/////////////////////////////////////////////////friendly.cpp

void process_all();//程序入口
void process_sign();//登录过程
void process_register();//注册过程

void process_admin();//管理员过程
void process_account();//账户管理过程

void process_manager();//剧院经理过程
void process_program();//剧目查询及管理过程
void process_studio();//影厅查询及管理过程
void process_plan();//放映计划查询及管理过程
void process_record();//销售统计与查询   
void process_plan_inquiry(Plan *head); //查询演出计划过程

void process_conducter();//售票员过程
void process_ticket();//售票员票务管理过程
void process_count(Account *a);//业绩统计查询过程

void process_customer();//顾客过程

void process_appeal();//账号申诉过程
////////////////////////////////////////////////process.cpp

char *username_get(int judge);//用户名的获取
int sign_judge();//登陆成功及账户类型的判断
char *password_get(int judge);//用户密码的获取
char *get_string(int down, int up,int judge);//字符串检查函数    down~up   字符串字节数限制
int get_num(int down, int up, int ndown, int nup);//读取数字    并检查输入   范围[down,up]   位数n[ndown,nup]
char *get_date();//日期的获取及判断
char *get_time();//时间的获取及判断
data_program get_program_infomation();//获取剧目主要信息  并进行初始化
void program_viewer(Program *head);//剧目浏览器
void studio_viewer();//放映厅查看器
void seat_changer(Studio *p);//可视化座位修改器
void plan_viewer(Plan *head);//演出计划浏览器
void ticket_changer(Plan *p);//售票浏览器
void account_viewer(Account *head);//账号浏览器
void log_viewer();//记录浏览器

void account_count(Account *a);//统计售票员销售额
void account_count(Account *a, char *begin,char *end);//按日期区间统计销售额
void program_count(Program *pro);//统计票房   按售出的票
void count_program();//统计所有剧目票房


void timer();//读取系统时间
void clean_plan();//检查并处理过期演出计划

void password_change(char *obj, int i);//密码的加密解密处理，1 :  加密     2:解密
void play_bgm();
void log(int choice);//登录记录  1 success    0 fail
//////////////////////////////////////////////sonfunction.cpp

void file_check();//文件检查

void import_key();//导入主键信息到链表
void import_account();//导入账号信息到链表
void import_program();//导入剧目信息到链表
void import_studio_and_seat();//导入放映厅及座位信息到链表
void import_plan_and_ticket();//导入演出计划信息到链表
void import_plan_and_ticket_bin();// 导入演出计划信息到链表
void import_record();//导入销售记录到链表
//void import_plan_and_ticket_tem();//导入已过期演出计划到链表


void save_key();//保存主键信息到文件
void save_program();//保存剧目信息到文件
void save_studio_and_seat();//保存放映厅及座位到文件
void save_plan_and_ticket();//保存演出计划及票到文件
void save_plan_and_ticket(Plan *p); //追加演出计划与票的信息到文件
void save_plan_and_ticket_bin();//保存演出计划及票到二进制文件
void save_account();//保存账号链表信息到文件
void save_account(Account *p);//追加账号信息到文件
void save_record(Record *r);//追加新的记录到文件末尾
int save_invitation_code(char *obj);//比较 并 局部修改邀请码  //返回值为比对结果
void add_invitation_code(char *obj);//补充邀请码

void rewrite_ticket(Plan *p, Ticket *t);//局部覆写文件    更改票的状态
void clean_plan_atFirst();//将过期的演出计划标记过期

///////////////////////////////////////////////////filefunction.cpp

void initialize_linklist();//初始化链表

long get_newkey(int judge);//返回judge对应的新主键值  1  电影    2 歌剧   3音乐会     4演出计划     5销售记录

Program *search_program(char *obj, int judge);//按ID或名称查找剧目 judge 控制是否进行相似反馈
void add_program();//增加剧目
void delete_program(Program *p);//按照ID或名字删除剧目
void print_program(Program *p , int i);////输出某个影片信息
void print_program_cnt(Program *p);//打印票房
void modify_program(Program *p);//修改影片信息
void sort_program();//按票房排序

Studio *search_studio(char *obj, int judge);//按ID或名称查找放映厅    judge 控制是否进行相似反馈
void add_studio();//增加放映厅
void print_studio(Studio *p);////打印放映厅及座位信息

//Seat *search_seat(char *obj);//根据放映厅编号查找座位
void delete_studio(Studio *p);//删除指定放映厅
void modify_studio(Studio *p);//修改放映厅名称及座位

void initialize_seat(Studio *p);//为新放映厅初始化座位
void delete_seat(Studio *k);//删除放映厅时删除其座位
void initialize_ticket(Plan *p);//为演出计划按座位生成票

void add_plan();//新增演出计划
void print_plan(Plan *p);//打印演出计划信息
Plan *search_plan(long obj, int judge, Plan *head);//按plan_ID检索演出计划
void search_plan(char *obj, int choice, Plan *head);//按各种ID/名称输出演出计划 1plan_ID  2program  3studio
void delete_plan(Plan *p);//隐藏演出计划
void modify_plan(Plan *p);//修改演出计划
void sort_plan(Plan *head);//链表冒泡。。排序

void delete_ticket(Plan *p);//删除演出计划下的票
void print_ticket(Plan *p);//打印演出计划下票的情况
Ticket *search_ticket(long ID, Plan *head);//根据ID查找票  head 查找范围 judge控制相似反馈
void sale_ticket(Plan *p);//售票退票
void return_ticket(Ticket *t);//退票    产生销售记录  并更新主键
void draw_ticket(Plan *p, Ticket *t);//画一张票
void draw_ticket(Ticket *t);//画一张票  0售票员   1剧院经理

void print_account(Account *p);//打印账号信息
void add_account(int choice);//增加账户信息
void modify_account(Account *p);//修改账户信息
void delete_account(Account *p);//删除账户信息
Account* search_account(char *obj, int judge);//查找账户信息

Record *add_record(Plan *p, Ticket *t, long UID, sale_types type);//产生一条销售记录加到记录链表  并刷新业绩
Record *search_record(long obj);//根据Ticket_ID倒序查找销售记录

////////////////////////////////////////////////////////Linklist.cpp

void import_all();//导入账户信息
void initialize();//初始化准备
void initialize_present();//初始化当前账户
void initialize_window();//初始化显示窗口

//initialize.cpp

//////////////////////////////顾客端
void search_plan_name(char *obj, int judge, Plan *head, int choose);//根据1剧目名或2演出日期查找演出计划并打印信息
Program *search_program3(char *obj, int choose, int judge);//按标签或剧目查找剧目  judge 控制是否进行相似反馈
Plan *search_plan3(char *obj, int judge, Plan *head); //按剧目查找演出计划 judge 控制是否进行相似反馈
void search_pragram_type(char *obj, int judge);//按剧目标签查找打印
void advice();

void show_customer_find();

void process_find();