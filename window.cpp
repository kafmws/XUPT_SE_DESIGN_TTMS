#include "stdafx.h"
#include "statements.h"


/*void choice() {//文本移动函数
	HANDLE handle_move = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_info;
	GetConsoleScreenBufferInfo(handle_move, &screen_info);
	SMALL_RECT move = {0,0,1,0};//定义移动区域
	COORD position = { 1,10 };//目标区域
	CHAR_INFO  c_fill;
	c_fill.Char.AsciiChar =' ';
	c_fill.Attributes = screen_info.wAttributes;
	printf("00000"); 
	ScrollConsoleScreenBuffer(handle_move, &move, NULL, position, &c_fill);
}*/

int choice_judge(int i) {//读取键盘事件          i  // 界面选择   参见screen_clear界面
	int highlight=1;                         
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//定义输入事件结构体
	DWORD res;//定义返回记录
	while(true){
		ReadConsoleInput(handle, &event, 1, &res);      //读取输入事件  
		if (event.EventType == KEY_EVENT)      //如果当前事件是键盘事件  
		{
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP&& event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↑  
			{
				highlight = screen_clear(i, highlight, -1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下↓ 
			{
				highlight = screen_clear(i, highlight, 1);
			}
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true ) //按下ESC  
			{
				if (i == 1) {//主界面ESC直接退出
					show_bye();
					system("cls");
					system("color ff");
					exit(0);
					//system("taskkill /im cmd.exe /T /F");
					//quick_exit(0);
				}
				else {
					return 0;//最为返回上一层
				}
			}
			if (event.Event.KeyEvent.uChar.AsciiChar ==13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下回车  
			{
				SetColor(7, 0);
				return highlight;
			}
		}
	}
}

int screen_clear(int order,int i,int change) {
	/*主界面的高亮控制  i表示当前高亮选项 默认为1
									   参数change表改变量  order表示界面的选择  函数返回当前选项编号*/
	i += change;
	if (order == 1) {//主界面
		i == 0 ? i = 3 : i = i;//高亮控制
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 8); printf("登录");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 10); printf("注册");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(40, 12); printf("离开");
	}
	else if (order==2) {
		i == 0 ? i = 5 : i = i;//高亮控制
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("剧目查询及管理");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("影厅查询及管理");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("演出查询及管理");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("销售统计与查询");
		i == 5?SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 14); printf("我的账号及密码\n");
	}
	else if (order >= 3 && order <= 10) {
		char obj[5];
		switch (order) {
		case 3:strcpy(obj, "剧目"); break;
		case 4:strcpy(obj, "影厅"); break;
		case 5:strcpy(obj, "用户"); break;
		case 6:strcpy(obj, ""); break;
		default:
			print_re(); break;
		}
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("查询%s信息",obj);
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("修改%s信息",obj);
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("新增%s信息",obj);
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("删除%s信息",obj);
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("浏览所有%s\n",obj);
	}
	else if (order == 11) {
		i == 0 ? i = 4 : i = i;
		i > 4 ? i = 1: i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("系统用户管理");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("登录记录查询");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("增加新邀请码");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("管理我的信息\n");
	}
	else if (order == 12) {
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		set_position(35, 4);
		SetColor(10, 0);
		printf("演出查询及管理");
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("查询演出计划");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("修改演出计划");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("新增演出计划");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("删除演出计划");
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("浏览所有计划");
	}
	else if (order == 13) {
		i == 0 ? i = 5 : i = i;//高亮控制
		i > 5 ? i = 1 : i = i;
		set_position(36, 4);
		SetColor(10, 0);
		printf("售票与统计");
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 6); printf("演出检索与查询");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 8); printf("票务查询及管理");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 10); printf("销售统计与查询");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 12); printf("演出计划浏览器");
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(34, 14); printf("我的账号及密码\n\n");
	}
	else if (order == 14) {
		i == 0 ? i = 3 : i = i;//高亮控制
		i > 3 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("查询演出票");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10);printf("售出演出票");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("退还演出票\n");
	}
	else if (order == 15) {
		i == 0 ? i = 4 : i = i;
		i > 4 ? i = 1 : i = i;
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("查询票务信息");//废弃   查询交易记录
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("查询售票情况");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("查询销售业绩");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("查询剧目票房\n");
	}
	else if (order == 30) {
		i == 0 ? i = 5 : i = i;
		i > 5 ? i = 1 : i = i;
		set_position(35, 4);
		SetColor(10, 0);
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("推荐影片");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("查找心中的影片");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("近期上映一览");
		i == 4 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 12); printf("购票与退票");
		i == 5 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 14); printf("我的账号信息\n");
	}
	else if (order == 31) {
		i == 0 ? i = 3 : i = i;
		i > 3 ? i = 1 : i = i;
		set_position(35, 4);
		SetColor(10, 0);
		i == 1 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 6); printf("剧名搜索");
		i == 2 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 8); printf("演出时间查找");
		i == 3 ? SetColor(11, 0) : SetColor(7, 0);
		set_position(36, 10); printf("标签查找\n\n");
	}
	else {
		print_re();
	}
	SetColor(7, 0);
	return i;
}

int select_seat(Studio *p) {//判别位置  ↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3  返回值表示是否保存
	char num[15][30] = { 0 }; int choice, i, j, flag = 0,cnt = 0;
	if (p == NULL) { return flag; }
	Seat *k = p->element.seat_head->next;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			num[i][j] = k->seat_condition; k = k->next;
		}
	}
	set_position(0, 0); catch_cursor();
	i = 1, j = 1;//  i 当前行数   j  当前列数
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD position;
	position = info.dwCursorPosition;//经验证COORD存储的坐标位置X为字节数  Y为行数
	while ((choice = turn_page(),1)) {
		hide_cursor();
		if (choice == -1 && i != 0) {
			position.Y--; i--; set_position(position);
		}
		else if (choice == -2 && j != 0) {//↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3
			position.X -= 2; j--; set_position(position);
		}
		else if (choice == 1 && i != p->element.seatx) {
			position.Y++; i++; set_position(position);
		}
		else if (choice == 2 && j != p->element.seaty) {
			position.X += 2; j++; set_position(position);
		}
		else if (choice == 0) {
			position.Y = p->element.seatx + 1; position.X = 0;
			set_position(position);
			if (enquiry(1)) {//是否保存数据
				flag = 1;
				k = p->element.seat_head->next;
				/*for (i = 1; i <= p->element.seatx; i++) {
					for (j = 1; j <= p->element.seaty; j++) {
						printf("%2d", num[i][j]);
					}printf("\n");
				}*///调试
				for (i = 1; i <= p->element.seatx; i++) {
					for (j = 1; j <= p->element.seaty; j++) {
						k->seat_condition = (seat_conditions)num[i][j]; if (num[i][j] == 1) { cnt++; }
						k = k->next;
					}
				}
			}
			p->element.seatsum = cnt;
			return flag;
		}
		else if (choice == 3) {
			clear_seat(position, num[i][j]);
			switch (num[i][j]) {
			case 0:num[i][j] = 1; break;
			case 1:num[i][j] = 9; break;
			case 9:num[i][j] = 0; break;
			}
		}
		Sleep(100); catch_cursor();
	}
}

/*未完成*/
int select_seat(Plan *q, int limit) {//判别位置  ↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3  返回值表示所购票数  limit 最大购买量
	char num[15][30] = { 0 }, str[20]; int choice, i, j, flag = 0, cnt = 0, cntt = 0,judge=0;
	sprintf(str, "%d", q->element.studio_ID); Studio *p = search_studio(str,0);
	if (p == NULL) { return flag; }
	Seat *k = p->element.seat_head->next;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			num[i][j] = k->seat_condition; k = k->next;//可用座位 1 2   损坏座位9   无座位0
		}
	}
	Ticket *t = q->element.ticket_head->next;
	for (t; t; t = t->next) {
		if (t->ticket_status == TICKET_sold)
			num[t->seatx][t->seaty] == 1?num[t->seatx][t->seaty]=-1:num[t->seatx][t->seaty]=-2;
		//有座位有票 1 2  有座位无票-1 -2  无座位 0  损坏座位9
	}
	set_position(0, 0); catch_cursor();
	i = 1, j = 1;//  i 当前行数   j  当前列数
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD position;
	position = info.dwCursorPosition;//经验证COORD存储的坐标位置X为字节数  Y为行数
	while ((choice = turn_page(), 1)) {
		hide_cursor();
		if (choice == -1 && i != 0) {
			position.Y--; i--; set_position(position);
		}
		else if (choice == -2 && j != 0) {//↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3
			position.X -= 2; j--; set_position(position);
		}
		else if (choice == 1 && i != p->element.seatx) {
			position.Y++; i++; set_position(position);
		}
		else if (choice == 2 && j != p->element.seaty) {
			position.X += 2; j++; set_position(position);
		}
		else if (choice == 0) {
			position.Y = p->element.seatx + 1; position.X = 0;
			set_position(position);
			if (enquiry(1)) {//是否保存数据
				//有座位有票 1 2  有座位无票-1 -2  无座位 0  损坏座位9
				Ticket *t = q->element.ticket_head->next;
				for (t; t; t = t->next) {
					if (t->ticket_status != (ticket_statuses)num[t->seatx][t->seaty]) {//产生销售记录

					}
					switch (num[t->seatx][t->seaty]) {
					case -2:
					case -1:t->ticket_status = TICKET_sold; break;
					case 1:
					case 2: t->ticket_status = TICKET_available; break;
					default:print_re(); break;
					}
					if (t->ticket_status == TICKET_available)cnt++;
				}
				q->element.ticket_head->price = cnt;
			}
			return flag;
		}
		else if (choice == 3) {//有座位有票 1 2  有座位无票-1 -2  无座位 0  损坏座位9
			if (flag == limit) {
				set_position(18, 1);
				printf("抱歉，一次最多购买%d张票\n",limit);
				set_position(position);
			}
			clear_ticket(position, num[i][j]);
			switch (num[i][j]) {
			case -2:num[i][j] = 2; flag--; break;
			case -1:num[i][j] = 1; flag--; break;
			case 1:num[i][j] = -1; flag++; break;
			case 2:num[i][j] = -2; flag++; break;
			default:
				set_position(18,1);
				printf("抱歉，不能选择该位置\n");
				set_position(position); break;
			}
		}
		Sleep(100); catch_cursor();
	}
}

inline  void clear_seat(COORD position, char status) {//COORD  当前位置   status 座位状态
	switch (status) {//空位0   可用1    损坏9
	case 0:printf("○"); break;
	case 1:printf("●"); break;
	case 9:printf("  "); break;
	}
	set_position(position);
}

inline  void clear_ticket(COORD position, char status) {//COORD  当前位置   status 票状态
	switch (status) {//有座位无票 1 2  有座位无票-1 -2  无座位 0  损坏座位9
	case 1:printf("●"); break;
	case 2:printf("★"); break;
	}
	set_position(position);
}

inline int turn_page() {//翻页器     ↑ -1   ← -2   ↓ 1    → 2    ESC 0   回车3
	int highlight = 1;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD event;//定义输入事件结构体
	DWORD res;//定义返回记录
	while (true) {
		ReadConsoleInput(handle, &event, 1, &res);      //读取输入事件  
		if (event.EventType == KEY_EVENT){      //如果当前事件是键盘事件  
			if (event.Event.KeyEvent.wVirtualKeyCode == VK_UP && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//按下↑  
				return -1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_LEFT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {
				return -2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_DOWN && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//按下↓ 
				return 1;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//按下↓ 
				return 2;
			}
			else if (event.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE && event.Event.KeyEvent.bKeyDown == (BOOL)true) //按下ESC  
			{
				return 0;
			}
			else if (event.Event.KeyEvent.uChar.AsciiChar == 13 && event.Event.KeyEvent.bKeyDown == (BOOL)true) {//按下回车  
				return 3;
			}
		}
	}
}

//0-黑色, 1-蓝色,   2-绿色,      3-浅绿色,     4-红色,   5-紫色,   6-黄色,   7-白色,
//8-灰色, 9-淡蓝色, 10-淡绿色,   11-淡浅绿色   12-淡红色 13-淡紫色 14-淡黄色 15-亮白色*/
void SetColor(short foreColor, short backColor){
	HANDLE winHandle;                  //句柄
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(winHandle, foreColor + backColor * 0x10);     //设置控制台文本的属性
}

POINT get_position() {//得到当前光标坐标
	POINT point;
	GetCursorPos(&point);
	return point;
}

void set_position(short x, short y){//设置光标位置
	HANDLE winHandle;                  
	COORD position = { x,y };
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
	//CloseHandle(winHandle);
}

inline void set_position(COORD position) {//设置光标位置
	HANDLE winHandle;
	winHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(winHandle, position);
	//CloseHandle(winHandle);
}

void hide_cursor() {//隐藏光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &cci);
	//CloseHandle(hOut);
}

void catch_cursor() {//显示光标
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(hOut, &cci);
	cci.bVisible = TRUE;
	SetConsoleCursorInfo(hOut, &cci);
	//CloseHandle(hOut);
}

/*
void Clear(int x, int y, int rowCount)
{
	int i, j;
	for (i = 0; i<rowCount; ++i)
	{
		SetPosition(x, y + i);
		for (j = 0; j<70; ++j)
			printf(" ");
	}
}
*/