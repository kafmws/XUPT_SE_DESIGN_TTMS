#include"stdafx.h"
#include"statements.h"

void print_re() {//请求bug反馈
	printf("其实输出这句话是不可能的\n");
	printf("出现错误请联系开发者qvq  \nQQ740721665或863139668\n"); rewind(stdin); go_on();
}

void print_examinput() {//非法输入报错
	printf("输入不符合要求，请重新输入\n");
	rewind(stdin);
}

inline void go_on() {//按任意键继续
	printf("按任意键继续\n");
	rewind(stdin);
	getch();
	//getch();//仅在VS中运行需要
}

void exam_NULL(void *p, int choice) {//空指针报错   0 malloc   1文件
	if (p == NULL) {
		if(choice == 0)printf("不能分配更多内存了\n");
		else if (choice == 1) {printf("打开文件失败\n"); print_re();}
		else {print_re();}
		exit(1);
	}
}

int enquiry(int i) {//判断是否进行本次操作   i==1   enquiry   i==2 warnning
	if (i == 1)
		printf("是否确认本次操作?(0/1):");
	else if (i == 2)
		printf("该操作不可恢复，是否继续?(0/1):");
	else
		print_re();
	int judge = 0;
	judge = get_num(0,1,1,1);
	return judge;
}

void print_ok() {//提示操作成功
	printf("操作成功了的说!\n");
	rewind(stdin);
}

void print_instruction(int i) {//显示说明
	if (i == 1) {
		system("cls");
		set_position(20, 6);
		printf("操作说明");
		printf("\n\n		方向键↑、↓、←、→操纵光标选择座位   ESC退出\n\n		\
○表示可用座位  ●表示座位损坏   回车键改变座位状态   \n\n		");
		go_on();
	}
}

void print_planhead() {//打印演出计划表头
	printf("    ===============================================================================\n");
	printf("    | ID  |         剧目名称       |演出厅编号|总票数|余票数|  演出日期  |开始时间|\n\n");
}

void print_planhead2(){
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("|====     剧目                 类型  演出日期 开始时间 时长 标签 票价 剩余票数 ===|\n");
}

void print_programhead() {//打印剧目排行榜表头
	printf("\n======================================================================================\n");
	printf("	  剧目名称	     |地区|   上映日期   |   下架日期   |    票房    |上座数量|\n\n");
}

void print_accounthead() {//打印账号表头
	printf("\n\t\t|-------------------账号信息---------------------|\n");
	printf("\t\t ID          用户名         密码          账号类型\n\n");
}

void 哈哈() {//我去，真有这种特性
	int 我去=5;
	printf("%d", 我去);
}

//弃用

//void print_label(int i) {//打印标签列表     i  = 1 电影       2 歌剧        3音乐会
//	if (i == 1)
//	printf("喜剧 动作 惊悚 爱情 悬疑 恐怖\n\
//纪录 科幻 艺术 青春 耽美 动画\n");
//	else if (i == 2) 
//	printf("请选择标签:");
//	rewind(stdin);
//}
