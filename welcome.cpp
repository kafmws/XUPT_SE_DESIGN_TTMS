#include"stdafx.h"
#include"statements.h"

/*void show_welcome() {//欢迎界面
	char str[20];
	strcpy_s(str, "橙天嘉禾大剧院");
	DWORD tem=0,font=2;
	COORD pos = { 10,10 };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	set_position(10,10);
	CONSOLE_FONT_INFOEX setfont;
	CONSOLE_FONT_INFO getfont;
	GetCurrentConsoleFont(handle, true,&getfont);
	//if (FillConsoleOutputAttribute(handle, , 20, pos, &tem) == 0) { printf("fail"); }
	setfont.nFont = getfont.nFont;
	//setfont.dwFontSize = GetConsoleFontSize(handle, font);
	SetCurrentConsoleFontEx(handle, true,&setfont);//设置字体
	for (int i = 0; i < strlen(str); i++) {//设置颜色
		SetConsoleTextAttribute(handle, (i+2 )* 0x10);  //设置控制台文本的属性
		printf("%c", str[i]);
	}
	//ScrollConsoleScreenBuffer(handle);
	puts(str);
}*/

void show_welcome() {//欢迎界面
	initgraph(1070, 600);//默认窗口大小
	setbkcolor(WHITE);
	cleardevice();
	IMAGE yinghua, title;
	loadimage(&title, _T("jpg"), _T("title"));
	loadimage(&yinghua, _T("jpg"), _T("yinghua"));
	putimage(350, 100, &yinghua);
	Sleep(2000);
	cleardevice();
	putimage(280, 150, &title);
	Sleep(3000);
	closegraph();
}

void show_bye() {
	initgraph(1070, 600);//默认窗口大小
	setbkcolor(WHITE);
	cleardevice();
	IMAGE yinghua, title;
	loadimage(&title, _T("jpg"), _T("title"));
	loadimage(&yinghua, _T("jpg"), _T("yinghua"));
	putimage(280, 150, &title);
	Sleep(2000);
	cleardevice();
	putimage(350, 100, &yinghua);
	Sleep(3000);
	closegraph();
}

void show_main() {//主界面
	WCHAR title[40] = TEXT("嘉禾天橙");
	SetConsoleTitle(title);
	system("color 08");
	system("cls");
	set_position(32, 5);
	SetColor(14, 0);
	printf("嘉 禾 天 橙 大 剧 院");
	set_position(40, 8);
	SetColor(11, 0);
	printf("登录");
	set_position(40, 10);
	SetColor(7, 0);
	printf("注册");
	set_position(40, 12);
	printf("离开");
}

void show_sign() {//登录界面
	rewind(stdin);
	system("cls");
	SetColor(10, 0);
	set_position(30,8);
	printf("您的昵称:");
	set_position(30, 10);
	printf("登录口令:");
	SetColor(13, 0);
	//catch_cursor();//显示光标
}

void show_register() {//注册界面
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                     账号注册                     \n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * \n");
}

void abandon() {//弃用
	system("color f8");
	char str[90], i;
	WCHAR title[40] = TEXT("嘉禾天橙大影院");
	strcpy_s(str, "嘉禾天橙大影院欢迎您");
	set_position(25, 10);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(title);
	//settextstyle(80, 0, _T("楷体"), 0, 0, 0, true, true, true);				//字体样式
	for (i = 0; i < (char)strlen(str); i++) {
		printf("%c", str[i]);
	}
	for (i = 0; i < 2; i++) {
		system("color ff"); Sleep(300);
		system("color fe"); Sleep(300);
		system("color fa"); Sleep(300);
		system("color fc"); Sleep(300);
		system("color fd"); Sleep(300);
		system("color fb"); Sleep(300);
	}
	system("color f8");
}

/////////////////////////////////////manager

void show_manager() {//剧院经理主界面
	system("cls");
	rewind(stdin);
	set_position(36,4);
	SetColor(10,0);
	printf("查询与管理");
	SetColor(11, 0);
	set_position(34,6);
	printf("剧目查询及管理");
	SetColor(7, 0);
	set_position(34, 8);
	printf("影厅查询及管理");
	set_position(34, 10);
	printf("演出查询及管理");
	set_position(34,12);
	printf("销售统计与查询");//按演出计划查询
	set_position(34, 14);
	printf("我的账号及密码\n");
}

void show_program() {//剧目查询及管理界面
	rewind(stdin);
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);
	printf("剧目查询及管理");
	SetColor(11, 0);
	set_position(36, 6);
	printf("查询剧目信息");
	SetColor(7, 0);
	set_position(36, 8);
	printf("修改剧目信息");
	set_position(36, 10);
	printf("新增剧目信息");
	set_position(36, 12);
	printf("删除剧目信息");
	set_position(36, 14);
	printf("浏览所有剧目");
}

void show_studio(){//影厅查询及管理界面
	rewind(stdin);
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);
	printf("影厅查询及管理");
	SetColor(11, 0);
	set_position(36, 6);
	printf("查询影厅信息");
	SetColor(7, 0);
	set_position(36, 8);
	printf("修改影厅信息");
	set_position(36, 10);
	printf("新增影厅信息");
	set_position(36, 12);
	printf("删除影厅信息");
	set_position(36, 14);
	printf("浏览所有影厅");
}

void show_plan() {//演出计划查询及管理界面
	rewind(stdin);
	system("cls");
	set_position(35, 4);
	SetColor(10, 0);printf("演出查询及管理");
	SetColor(11, 0);set_position(36, 6);printf("查询演出计划");
	SetColor(7, 0);set_position(36, 8);printf("修改演出计划");
	set_position(36, 10);printf("新增演出计划");
	set_position(36, 12);printf("删除演出计划");
	set_position(36, 14);printf("浏览所有计划");
}

void show_record() {//销售统计与管理
	rewind(stdin);
	system("cls");
	SetColor(11, 0); set_position(36, 6); printf("查询票务信息");//查询交易记录
	SetColor(7, 0); set_position(36, 8); printf("查询售票情况");
	set_position(36, 10); printf("查询销售业绩");//统计销售员业绩
	set_position(36, 12); printf("查询剧目票房\n");//统计票房   从票统计
	//set_position(36, 14); printf("");//
}

///////////////////////////////////admin

void show_admin() {//系统管理员主界面
	system("cls");
	rewind(stdin);
	set_position(35, 4);
	SetColor(10, 0);
	printf("查询与管理");
	SetColor(11, 0);
	set_position(34, 6);
	printf("系统用户管理");
	SetColor(7, 0);
	set_position(34, 8);
	printf("登录记录查询");
	set_position(34, 10);
	printf("增加新邀请码");
	set_position(34, 12); 
	printf("管理我的信息\n");
}

void show_account() {//账户查询及管理界面
	rewind(stdin);
	system("cls");
	set_position(38, 4);
	SetColor(10, 0);
	printf("用户管理");
	SetColor(11, 0);
	set_position(36, 6);
	printf("查询用户信息");
	SetColor(7, 0);
	set_position(36, 8);
	printf("修改用户信息");
	set_position(36, 10);
	printf("新增用户信息");
	set_position(36, 12);
	printf("删除用户信息");
	set_position(36, 14);
	printf("浏览所有用户\n");
}

void show_account_type(){//账户类型选择界面
	system("CLS");
	printf("\t\t|-----请选择需要添加账户的类型-----|\n");
	printf("\t\t|-----------剧院经理请按2----------|\n");
	printf("\t\t|------------售票员请按3-----------|\n");
	printf("\t\t|-----------系统管理员请按1--------|\n");
	printf("\t\t|----------- 顾客请按4-------------|\n");
	printf("请输入:");
}

///////////////////////////////////conducter

void show_conducter() {//售票员主界面
	system("cls");
	rewind(stdin);
	set_position(36, 4);
	SetColor(10, 0);
	printf("售票与统计");
	SetColor(11, 0);
	set_position(34, 6);
	printf("演出检索与查询");
	SetColor(7, 0);
	set_position(34, 8);
	printf("票务查询及管理");
	set_position(34, 10);
	printf("销售统计与查询");
	set_position(34, 12);
	printf("演出计划浏览器");
	set_position(34, 14);
	printf("我的账号及密码\n\n");
}

void show_ticket() {//售票 退票 查票
	system("cls");
	rewind(stdin);
	SetColor(11, 0);
	set_position(36, 8);
	printf("查询演出票");
	SetColor(7, 0);
	set_position(36, 10);
	printf("售出演出票");
	set_position(36, 12);
	printf("退还演出票\n");
}

//弃用
/*void show_program_types() {//显示剧目类型   配合choice_judege进行选择
//	printf("请选择剧目类型\n");
//	int x = get_positionx(), y = get_positiony();
//	SetColor(11, 0);
//	printf("电影");
//	set_position(x + 5, y);
//}*/


///////////////////////////////////////////customer

void show_customer() {//顾客主界面
	system("cls");
	rewind(stdin);
	hide_cursor();
	set_position(36, 6);
	SetColor(11, 0);
	printf("推荐影片");
	SetColor(7, 0);
	set_position(36, 8);
	printf("查找心中的影片");
	set_position(36, 10);
	printf("近期上映一览");
	set_position(36, 12);
	printf("购票与退票");
	set_position(36, 14);
	printf("我的账号信息\n");
}

void show_customer_find(){
	system("cls");
	rewind(stdin);
	hide_cursor();
	set_position(36, 6);
	SetColor(11, 0);
	printf("剧名搜索");
	SetColor(7, 0);
	set_position(36, 8);
	printf("演出时间查找");
	set_position(36, 10);
	printf("标签查找\n\n");
}