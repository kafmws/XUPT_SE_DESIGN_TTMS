#include"stdafx.h"
#include"statements.h"

void initialize_linklist() {//初始化链表
	list.account_head = (Account *)malloc(sizeof(Account));
	list.program_head = (Program *)malloc(sizeof(Program));
	list.studio_head = (Studio *)malloc(sizeof(Studio));
	list.plan_head = (Plan *)malloc(sizeof(Plan));
	list.plan_tem_head = (Plan *)malloc(sizeof(Plan));
	//list.seat_head = (Seat *)malloc(sizeof(Seat));
	//list.ticket_head = (Ticket *)malloc(sizeof(Ticket));
	list.record_head = (Record *)malloc(sizeof(Record));
	list.key_head = (Key *)malloc(sizeof(Key));
	list.account_head->next = list.account_head->pre = NULL;
	list.program_head->next = list.program_head->pre =  NULL;
	list.studio_head->next =list.studio_head->pre = NULL;
	list.plan_head->next = list.plan_head->pre = NULL;
	list.plan_tem_head->next = list.plan_tem_head->pre = NULL;
	//list.seat_head->next = list.seat_head->pre = NULL;
	//list.ticket_head->next = list.ticket_head->pre = NULL;
	list.record_head->next = list.record_head->pre = NULL;
	list.key_head->next = list.key_head->pre = NULL;
	list.account_tail = list.account_head;
	list.program_tail = list.program_head;
	list.studio_tail = list.studio_head;
	list.plan_tail = list.plan_head;
	list.plan_tem_tail = list.plan_tem_head;
	//list.seat_tail = list.seat_head;
	//list.ticket_tail = list.ticket_head;
	list.record_tail = list.record_head;
	list.key_tail = list.key_head;
}

//////////////////////////////////////////key

long get_newkey(int type) {//返回judge对应的新主键值    并更新主键记录
	int flag = 0;// 1  电影    2 歌剧   3音乐会     4演出计划     5销售记录   6票   7账号UID
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		if (type == p->type) {
			p->key++; flag = 1; break;
		}
	}
	if (flag == 0) {
		print_re();
	}
	return p->key;
}

//////////////////////////////////////////program

void add_program() {//增加剧目
	Program *p = (Program *)malloc(sizeof(Program));
	exam_NULL(p, 0);
	p->element = get_program_infomation();//剧目信息获取
	if (enquiry(1)) {
		printf("具体信息已置为默认值\n如有需要请记得修改\n");
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		save_program();
		list.program_head->element.cost += 1;
		save_key();
		print_ok();
	}
	else {
		free(p);
		printf("新增已取消\n"); rewind(stdin);
	}
}

Program *search_program(char *obj,int judge) {//按ID或名字查找剧目  judge 控制是否进行相似反馈
	int flag = 0;
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.program_ID, obj) == 0 || strcmp(p->element.program_name, obj) == 0) {
			flag = 1;//找到
			break;
		}
	}
	if (flag)
		return p;
	if (judge&&flag == 0) {
		printf("没有这个剧目哦\n");
		for (p = list.program_head->next; p; p = p->next) {
			if (strstr(p->element.program_ID, obj) != NULL || strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); printf("也许你想找的是：\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s  %s\n", p->element.program_ID, p->element.program_name);
			}
		}
		if(flag==1)printf("请确认后重新查找\n");
	}return NULL;
}

void delete_program(Program *p) {//按照ID或名字删除剧目
	if (p) {
		printf("将要删除的剧目是\n");
		print_program(p, 0);
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next)//p不为最后一个
				p->next->pre = p->pre;
			if (p == list.program_tail)list.program_tail = p->pre;
			free(p);
			save_program();
			list.program_head->element.cost -= 1;
			print_ok();
		}
		else {
			printf("删除已取消\n"); rewind(stdin);
		}
	}
}

void print_program(Program *p , int i) {//输出某个剧目信息    i  控制是否清屏
	if (p) {
		if(i)system("cls");
		char rating[8],type[7],person[11];
		switch (p->element.program_rating) {
		case 1:strcpy(rating, "Child"); break;
		case 2:strcpy(rating, "Teen"); break;
		case 3:strcpy(rating, "Adult"); break;
		default:
			print_re();
		}
		switch (p->element.program_type) {
		case 1:strcpy(type, "电影"); strcpy(person,"导演"); break;
		case 2:strcpy(type, "歌剧"); strcpy(person, "导演"); break;
		case 3:strcpy(type, "音乐会"); strcpy(person, "指挥"); break;
		default:
			print_re();
		}
		printf("\n");
		printf("	==================================================================\n");
		printf("	||								||\n");
		printf("	||%s名称:%-15s		%s:%-12s	||\n",type, p->element.program_name,person, p->element.director);
		printf("	||								||\n");
		printf("	||主演:%12s	%-14s	时长:%dmin		||\n", p->element.performer[0], p->element.performer[1], p->element.duration);
		printf("	||								||\n");
		printf("	||剧目标签:%-s                 地区:%-8s	票价:%-5d	||\n", p->element.label, p->element.area, p->element.price);
		printf("	||								||\n");
		PRESENT.user_type == USER_customer?printf("	||放映等级:%-8s		语言:%-10s			||\n", rating, p->element.language):\
			printf("	||放映等级:%-8s		语言:%-10s	ID%-8s	||\n", rating, p->element.language,p->element.program_ID);
		printf("	==================================================================\n");
		rewind(stdin);
	}
}

void print_program_cnt(Program *p) {//打印票房
	if (p) {
		int cnt = p->element.contributions / p->element.price;
		printf("%-30s%-4s%14s%14s%12d%12d\n\n", p->element.program_name, p->element.area, \
			p->element.start_date, p->element.end_date, p->element.contributions, cnt);
	}
}

void modify_program(Program *p) {//修改电影信息
	if (p) {
		print_program(p,1);
		printf("请选择你想要更改的\n");
		printf("1.票价 2.放映等级 3.时长 4.地区 \n5.语言 6.剧目标签 7.主演 8.导演\n");
		int choice = 0; char *str; rewind(stdin);
		data_program tem=p->element;
		choice = get_num(1, 8, 1, 1);
		switch (choice) {
		case 1:printf("请输入新的票价(5~100):"); choice = get_num(5, 100, 1, 3); tem.price = choice; break;
		case 2:printf("请输入放映等级(1~3):"); choice = get_num(1, 3, 1, 1); tem.program_rating = (program_ratings)choice; break;
		case 3:printf("请输入影片时长(1~600):"); choice = get_num(1, 600, 1, 3); tem.duration = choice; break;
		case 4:printf("请输入影片地区(2个汉字):"); str = get_string(4, 4, 2); strcpy(tem.area, str); free(str); break;
		case 5:printf("请输入影片语言(最多14个字符):"); str = get_string(1, 15, 0); strcpy(tem.language, str); free(str); break;
		case 6:printf("请输入影片标签(2个汉字):"); str = get_string(4, 4, 2); strcpy(tem.label, str); free(str); break;
		case 7:if (p->element.program_type != PROGRAM_concert) {
			printf("请输入第一位主演姓名(最多7个汉字):"); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			printf("是否继续输入第二主演?(0/1):"); rewind(stdin); if (choice = get_num(0, 1, 1, 1)) {
				printf("请输入第二位主演姓名(最多7个汉字):");
				str = get_string(1, 14, 0); strcpy(tem.performer[1], str); free(str);
			}
		}else {
			printf("请输入主演的乐团名称(最多7个汉字)："); str = get_string(1, 14, 0); strcpy(tem.performer[0], str); free(str);
			   }break;
		case 8:printf("请输入导演姓名(最多7个汉字):"); str = get_string(1, 14, 0); strcpy(tem.director, str); free(str); break;
		default:
			break;
		}
		if (enquiry(1)) {
			p->element = tem;
			save_program();
			print_ok();
		}
		else {
			printf("修改已取消\n"); rewind(stdin);
		}
		printf("是否继续修改?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_program(p);
		}
	}
}

void sort_program() {//按票房排序
	Program *p = list.program_head->next; int flag = 0, i; data_program t;
	for (i = 1; i < list.program_head->element.cost; i++) {
		flag = 0;
		for (p = list.program_head->next; p->next; p=p->next) {
			if (p->element.contributions > p->next->element.contributions) {
				t = p->element;
				p->element = p->next->element;
				p->next->element = t;
				flag = 1;
			}
		}if (flag == 0)break;//冒泡排序辣鸡优化
	}
}

///////////////////////////////////////////studio

void add_studio() {//增加放映厅
	Studio *p = (Studio *)malloc(sizeof(Studio));
	exam_NULL(p, 0);
	printf("\n请输入新的放映厅编号(4~6位数字):\n"); rewind(stdin);
	char *str = get_string(4, 6, 1);
	while (search_studio(str, 0)) {
		printf("该编号已被使用，请重新输入\n"); rewind(stdin);free(str);
		str = get_string(4, 6, 1);
	}
	strcpy(p->element.studio_ID, str); free(str);
	printf("请输入放映厅名称(7个汉字以内):\n"); rewind(stdin);
	str = get_string(1,14,0);
	while (search_studio(str, 0)) {
		printf("该名称已被使用，请重新输入\n"); rewind(stdin); free(str);
		str = get_string(1, 14, 1);
	}
	strcpy(p->element.studio_name, str); free(str);
	printf("请输入该影厅座位的行数(5~12):");
	int choice = get_num(5, 12, 1, 2);
	p->element.seatx=choice;
	printf("请输入该影厅座位的列数(10~25):");
	choice = get_num(10, 25, 2, 2);
	p->element.seaty = choice;
	p->element.seatsum = p->element.seatx*p->element.seaty;//计算初始化后的可用座位
	if (enquiry(1)) {
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		initialize_seat(p);
		save_studio_and_seat();
		print_ok();
		printf("所有座位已置为可用状态\n如有需要请记得修改\n");
		list.studio_head->element.seatx++;
	}
	else {
		free(p);
		printf("放映厅新增已取消\n");
	}
}

Studio *search_studio(char *obj,int judge) {//按ID或名称查找放映厅  judge  控制是否进行相似反馈
	Studio *p=list.studio_head->next;
	int flag = 0;
	for (p; p; p = p->next) {
		if (strcmp(p->element.studio_ID, obj) == 0 || strcmp(p->element.studio_name, obj) == 0) {
			flag = 1; break;
		}
	}
	if (flag) {
		return p;
	}
	if (judge&&flag == 0) {
		printf("该放映厅不存在哦\n");
		for (p = list.studio_head->next; p; p = p->next) {
			if (strstr(p->element.studio_ID, obj) != NULL || strstr(p->element.studio_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); Sleep(1000); printf("也许你要找的是\n"); rewind(stdin); flag = 1;
				}printf("%s    %s\n",p->element.studio_ID,p->element.studio_name);
			}
		}if (flag)printf("请确认后重新查找\n");
	}
	return NULL;
}

void delete_studio(Studio *p) {//删除指定放映厅
	if (p) {
		if(enquiry(2)){
			p->pre->next = p->next;
			if (p->next)
				p->next->pre = p->pre;
			delete_seat(p);//删除该放映厅所有座位
			if (p == list.studio_tail)list.studio_tail = p->pre;
			free(p);
			list.studio_head->element.seatx--;
			save_studio_and_seat();
			print_ok();
		}
		else {
			printf("删除已取消\n"); rewind(stdin);
		}
	}
}

void print_studio(Studio *p) {//打印放映厅及座位信息
	if (p) {
		int i, j, cnt = 0;//cnt 计算可用座位数
		system("cls");
		Seat *k = p->element.seat_head->next;
		printf("\n");
		printf("	====================================================================\n");
		printf("			放映厅编号：%s	名称：%s\n\n",p->element.studio_ID,p->element.studio_name);
		printf("			○表示可用座位  ●表示损坏座位   座位 %d x %d\n\n",p->element.seatx,p->element.seaty);
		printf("			╭——————————————————╮\n");
		printf("					↑荧幕\n\n");
		for (i = 1; i <= p->element.seatx; i++) {
			if(p->element.seaty>30)
				printf("		");
			else if(p->element.seaty>21)
				printf("		   ");
			else if(p->element.seaty>15)
				printf("			");
			else if(p->element.seaty<=15)
				printf("			    ");
			for (j = 1; j <= p->element.seaty; j++) {
				switch (k->seat_condition) {
				case 0:printf("  "); break;
				case 1:printf("○"); cnt++; break;
				case 2:printf("☆"); cnt++; break;
				case 9:printf("●"); break;
				default:
					print_re(); break;
				}
				k = k->next;
			}printf("\n");
		}/*if(cnt == p->element.seatsum )*/printf("\n\n			本放映厅共有%d张可用座位\n", cnt);
		//else { printf("座位校对出现问题\n"); print_re(); }
	}
}

void modify_studio(Studio *p) {//修改影厅信息及座位情况
	if (p) {
		print_studio(p);
		printf("提醒:有演出计划使用该放映厅时时请勿修改座位\n请选择要修改的：\n");
		printf("1.放映厅名称 2.座位行数 3.座位列数 4.座位设置\n");//2.座位行数 3.座位列数
		int choice = get_num(1, 4, 1, 1); char *str = NULL; data_studio tem=p->element;
		switch (choice) {
		case 1:printf("请输入新的放映厅名称:"); str = get_string(1, 14, 0); strcpy(tem.studio_name, str); free(str); break;
		case 2:printf("请输入新的行数(5~12):"); choice = get_num(5, 12, 1, 2); tem.seatx = choice; break;
		case 3:printf("请输入新的列数(10~25):"); choice = get_num(10, 25, 2, 2); tem.seaty = choice; break;
		case 4:print_instruction(1); seat_changer(p); break;
		}if (choice != 4) {
			if (enquiry(1)) {
				if (tem.seatx != p->element.seatx || tem.seaty != p->element.seaty) {//初始化座位
					if(tem.seatx > p->element.seatx || tem.seaty > p->element.seaty)printf("已默认新增行或列无座位\n");
					int i, j; Seat *k = p->element.seat_head->next;

					//辣鸡方法 弃用

					//char seat[13][26] = { 0 }; 
					//for (i = 1; i <= p->element.seatx; i++) {
					//	for (j = 1; j <= p->element.seaty; j++) {//录入原有座位
					//		seat[i][j] = k->seat_condition; k = k->next;
					//	}
					//}
					//delete_seat(p);//删除原有座位
					//int ID = atoi(p->element.studio_ID); Seat *q = NULL;
					//p->element.seat_head = (Seat *)malloc(sizeof(Seat)); exam_mallocX(p->element.seat_head);
					//p->element.seat_tail = p->element.seat_head;
					//p->element.seat_head->pre = p->element.seat_tail->next = NULL;//初始化座位链表
					//for (i = 1; i <= tem.seatx; i++) {
					//	for (j = 1; j <= tem.seaty; j++) {
					//		q = (Seat *)malloc(sizeof(Seat));
					//		exam_mallocX(q);
					//		q->seatx = i; q->seaty = j; q->stduio_ID = ID; q->seat_condition = (seat_conditions)seat[i][j];
					//		q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail; 
					//		p->element.seat_tail->next = q; p->element.seat_tail = q;
					//	}
					//}//数组转化为链表
					//tem.seat_head = p->element.seat_head; tem.seat_tail = p->element.seat_tail;

					///////////链表的实时更改    内存管理
					int tID = atoi(p->element.studio_ID);
					k = p->element.seat_head->next;
					if (tem.seatx > p->element.seatx){//增加行数
						for (i = p->element.seatx + 1; i <= tem.seatx; i++) {
							for (j = 1; j <= p->element.seaty; j++) {//插入新节点
								if (i > p->element.seatx || j > p->element.seaty) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = i; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = p->element.seat_tail->next; q->pre = p->element.seat_tail;
									p->element.seat_tail->next = q; p->element.seat_tail = q;
								}
							}
						}
					}
					else if (tem.seaty > p->element.seaty) {//增加列数
						for (i = 1; i <= p->element.seatx*p->element.seaty; i++) {
							if(i%p->element.seaty==0)
								for (j = p->element.seaty + 1; j <= tem.seaty; j++) {
									Seat *q = (Seat *)malloc(sizeof(Seat));
									q->seatx = (i - 1) / p->element.seaty + 1; q->seaty = j; q->seat_condition = (seat_conditions)0; q->stduio_ID = tID;
									q->next = k->next; q->pre = k;
									k->next = q; k = q;
							}k = k->next;
						}
					}
					else if (tem.seaty < p->element.seaty) {//减少列数
						i = 1;
						while ( k ) {
							if (i%tem.seaty == 0) {
								j = p->element.seaty - tem.seaty;
								k = k->next;
								while (j--) {
									if (k) {
										Seat *dead = k;
										k->pre->next = k->next;
										if (k->next) {
											k->next->pre = k->pre;
										}k = k->next;
										free(dead); i = 1;
									}
								}
							}
							if(k)k = k->next; i++;
						}
					}
					else if (tem.seatx < p->element.seatx) {//减少行数
						for (i = 1, k; i <= tem.seatx*p->element.seaty; i++, k = k->next);
						while (k) {
							Seat *dead = k;
							k->pre->next = k->next;
							if (k->next) {
								k->next->pre = k->pre;
							}
							k = k->next;
							free(dead);
						}
					}
				}
				p->element = tem;
				save_studio_and_seat();
				print_ok();
			}	
			else {
				printf("修改已取消\n");
			}
		}
	}
}

/////////////////////////////////////////////seat

void initialize_seat(Studio *p) {//为新放映厅初始化座位
	p->element.seat_head = (Seat *)malloc(sizeof(Seat));
	exam_NULL(p->element.seat_head, 0);
	p->element.seat_head->pre = p->element.seat_head->next = NULL;//次链表初始化
	p->element.seat_tail = p->element.seat_head;
	int i, j;
	for (i = 1; i <= p->element.seatx; i++) {
		for (j = 1; j <= p->element.seaty; j++) {
			Seat *k = (Seat *)malloc(sizeof(Seat));
			exam_NULL(k ,0);
			k->seatx = i, k->seaty = j, k->stduio_ID = atoi(p->element.studio_ID);
			k->seat_condition = (seat_conditions)1;
			k->next = p->element.seat_tail->next;
			k->pre = p->element.seat_tail;
			p->element.seat_tail->next = k;
			p->element.seat_tail = k;
		}
	}
}

//Seat *search_seat(char *obj) {//根据放映厅及行列数查看座位信息
//	int flag = 0;
//	Studio *k = search_studio(obj);
//	if (k) {
//		Seat *p = k->element.seat_head->next;
//		for (p; p; p = p->next) {
//			if (p->stduio_ID == atoi(obj)) {
//				flag = 1;
//				return p;
//			}
//		}
//		printf("");
//		return NULL;
//	}
//}

void delete_seat(Studio *k) {//删除放映厅时删除其座位
	if (k) {
		Seat *dead = k->element.seat_head;
		Seat *p = dead->next;
		while (p) {
			free(dead);
			dead = p;
			p = p->next;
		}free(dead);
	}
}

////////////////////////////////////////////plan

void add_plan() {//新增演出计划
	Plan *p = (Plan *)malloc(sizeof(Plan)); char *tem;
	exam_NULL(p, 0);
	p->element.button = 1;
	p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
	p->element.ticket_head->next = p->element.ticket_head->pre = NULL;
	p->element.ticket_tail = p->element.ticket_head;
	p->element.contributions = 0;
	char *str = NULL; Program *k = NULL; Studio *s = NULL; int flag = 1;
	p->element.plan_ID = get_newkey(PLAN_KEY);
	printf("\n已为演出计划分配ID为 %ld\n", p->element.plan_ID);
	printf("请输入演出剧目的ID或名称:");
	do {
		if (flag == 0)printf("该剧目不存在！\n请重新输入：");
		str = get_string(1, 30, 0);
	} while (((k = search_program(str, 0)) == NULL)&&(free(str),flag=0,1));
	flag = 1;
	strcpy(p->element.program_name , k->element.program_name);
	printf("请输入上演剧目的影厅名称或ID:");
	do {
		if (flag == 0)printf("该放映厅不存在！\n请重新输入：");
		str = get_string(1, 14, 0);
	} while (((s = search_studio(str, 0)) == NULL) && (free(str), flag=0,1));
	p->element.studio_ID = atoi(s->element.studio_ID);
	p->element.ticketnum = s->element.seatsum;
	printf("该剧目上架日期：%s  下架日期：%s\n",k->element.start_date,k->element.end_date);
	printf("请输入演出日期(year-month-day):");
	do {
		if (flag == 0)printf("演出计划与剧目上架日期不符\n请重请输入:");
		flag = 1;
		tem = get_date();
		if (strcmp(tem, k->element.start_date) < 0 || strcmp(k->element.end_date, tem) < 0) { flag = 0; }
		else { strcpy(p->element.date, tem); }free(tem);
	} while (flag == 0);
	printf("请输入演出开始时间(24小时制)(hour:min):");
	tem = get_time(); strcpy(p->element.time, tem); free(tem);
	if (enquiry(1)) {
		initialize_ticket(p);
		p->element.ticket_head->price = p->element.ticketnum;
		p->next = list.plan_tail->next; p->pre = list.plan_tail;
		list.plan_tail->next = p; list.plan_tail = p;
		list.plan_head->element.ticketnum += 1;
		save_key();
		save_plan_and_ticket(p);
		print_ok();
		printf("已自动生成所有票\n");
	}
	else {
		printf("演出计划新增已取消\n");
	}
}

void search_plan(char *obj, int choice, Plan *head) {//按各种ID/名称输出演出计划 1plan_ID  2program  3studio
	Plan *p = head->next;
	long objnum = atol(obj); Program *k = search_program(obj, 0); Studio *r = search_studio(obj, 0);
	if ((choice == 2 || choice ==3) && k == NULL && r == NULL) { if (choice == 2 && k == NULL) { search_program(obj, 1); } if (choice == 3 && r == NULL) { search_studio(obj, 1); } return; }
	char program_name[40]; if(k)strcpy(program_name, k->element.program_name);
	int studio_ID, flag = 0, judge = 0; if(r) studio_ID = atoi(r->element.studio_ID);
	if (choice == 1) {
		p = search_plan(objnum , 1,head);
		if (p) { print_planhead(); print_plan(p);}//judge标识是否有输出
	}
	else {
		for (p; p; p = p->next) {
			//if (p->element.button == 0) { continue; }//button 屏蔽
			flag = 0;
			switch (choice) {
			case 2:if (strcmp(p->element.program_name, program_name) == 0)flag = 1; break;
			case 3:if (p->element.studio_ID == studio_ID)flag = 1; break;
			case 4:if (strcmp(p->element.date, obj) == 0)flag = 1; break;
			}
			if (flag) { if (judge == 0) { print_planhead(); } print_plan(p); judge = 1; }
		}
		if(judge == 0)printf("没有这样的演出计划哟\n");
	}
}

Plan *search_plan(long obj, int judge, Plan *head) {//按plan_ID检索演出计划  judge控制是否进行相似反馈
	Plan *p = head->next;
	int flag = 0;
	for (p; p; p = p->next) {
		if (p->element.plan_ID == obj) {
			flag = 1; break;
		}
	}
	if (flag)return p;
	if (judge && flag == 0) {
		head == list.plan_head ?printf("该ID不属于有效演出计划哟\n"):printf("该ID不属于过期演出计划哟\n"); 
		int flagnum = 0; char tem[10],objstr[10];
		sprintf(objstr, "%ld", obj);
		for (p = head->next; p; p = p->next) {
			sprintf(tem, "%ld", p->element.plan_ID);
			if (strstr(tem, objstr) != NULL) {
				if (flagnum == 0) { printf("嗯  "); Sleep(500); printf("你也许要找的是\n"); Sleep(1000); flagnum = 1; }
				printf("%ld\n", p->element.plan_ID);
			}
		}if (flagnum) {
			printf("请确认后重新查找\n"); rewind(stdin);
		}
	}
	return NULL;
}

void delete_plan(Plan *p) {//隐藏放映计划及票
	if (p) {
		printf("将要删除的计划是：\n");
		print_planhead();
		print_plan(p);
		if (enquiry(2)) {
			p->element.button = 2;//   0过期      1有效
			save_plan_and_ticket();
			p->pre->next = p->next; 
			if(p->next)
				p->next->pre = p->pre;
			//p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			//list.plan_tem_tail->next = p; list.plan_tem_tail = p;//移动p到plan_tem链表
			delete_ticket(p);
			if (p == list.plan_tail)list.plan_tail = p->pre;
			free(p);
			print_ok();
		}
		else {
			printf("删除已取消\n");
		}
	}
	else printf("没有这样的演出计划哟\n");
}

void print_plan(Plan *p) {//打印演出计划信息
	if (p) {
		printf("    %ld    %-20s%8d	%3d	%3d %12s%8s\n\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID,\
		p->element.ticketnum,p->element.ticket_head->price,p->element.date,p->element.time);//p->element.ticket_head->price当前剩余票数
	}
	else {
		printf("没有这样的演出计划哟\n");
	}
}

void modify_plan(Plan *p) {//修改演出计划信息
	data_plan tem = p->element;char *str = NULL;
	printf("1.演出日期 2.演出时间 3.放映厅\n请选择：");
	int choice = get_num(1, 3, 1, 1), flag = 1;
	if (choice == 1) {//演出日期
		Program *k = search_program(p->element.program_name, 0); if (k == NULL)print_re();
		printf("该剧目上架日期：%s  下架日期：%s\n", k->element.start_date, k->element.end_date);
		printf("请输入演出日期(year-month-day):");
		do {
			if (flag == 0)printf("演出计划与剧目上架日期不符\n请重请输入:");
			flag = 1;
			str = get_date();
			if (strcmp(str, k->element.start_date) < 0 || strcmp(k->element.end_date, str) < 0) { flag = 0; }
			else { strcpy(tem.date, str); }free(str);
		} while (flag == 0);
	}
	else if (choice == 2) {//演出时间
		printf("请输入演出开始时间(24小时制)(hour:min):");
		str = get_time(); strcpy(tem.time, str); free(str);
	}
	if (enquiry(1)) {
		p->element = tem;
	}
	else {
		printf("修改已取消\n");
	}
	if (choice == 3) {//放映厅   同时重新生成票
		printf("请输入上演剧目的影厅名称或ID:");
		Studio *s = NULL; 
		do {
			if (flag == 0)printf("该放映厅不存在！\n请重新输入：");
			str = get_string(1, 14, 0);
		} while (((s = search_studio(str, 0)) == NULL) && (free(str), flag = 0, 1));
		tem.studio_ID = atoi(s->element.studio_ID);
		tem.ticketnum = s->element.seatsum;
		printf("修改放映厅会删除当前已有票并重新生成\n");
		if (enquiry(2)) {
			delete_ticket(p);
			p->element = tem;
			p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
			p->element.ticket_head->next = p->element.ticket_head->pre = NULL;
			p->element.ticket_tail = p->element.ticket_tail;
			initialize_ticket(p);
		}else{
			printf("修改已取消\n");
		}
	}
}

void sort_plan(Plan *head) {//链表冒泡排序
	Plan *p = head->next; data_plan t; int flag = 0, i = 1,j;
	for (i; i <= head->element.ticketnum - 1; i++) {
		flag = 0;
		for (j = 0; j < head->element.ticketnum - i;j++) {
			if (strcmp(p->element.date, p->next->element.date) > 0) {
				t = p->element;
				p->element = p->next->element;
				p->next->element = t;
				flag = 1;
			}if(p->next)p = p->next;
		}
		p = head->next;
		if (flag == 0)break;//冒泡排序辣鸡优化
	}
}

///////////////////////////////////////ticket

void initialize_ticket(Plan *p) {//为演出计划按座位生成票
	char str[20]; sprintf(str, "%s", p->element.program_name);
	int cnt = 0, price = search_program(str, 0)->element.price;
	sprintf(str, "%d", p->element.studio_ID);
	Studio *k = search_studio(str,0);
	Seat *q = k->element.seat_head->next;
	for (q; q; q = q->next) {
		if (q->seat_condition != 1 && q->seat_condition != 2) {//2雅座
			continue;
		}
		Ticket *r = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(r, 0);
		r->ticket_ID = get_newkey(TICKET_KEY);	save_key();
		r->plan_ID = p->element.plan_ID;
		r->seatx = q->seatx; r->seaty = q->seaty;
		r->price = price;
		r->ticket_status = (ticket_statuses)TICKET_available;
		r->next = p->element.ticket_tail->next; r->pre = p->element.ticket_tail;
		p->element.ticket_tail->next = r; p->element.ticket_tail = r;
		cnt++;
	}if (cnt != k->element.seatsum) { printf("座位与票数校验错误\n"); print_re(); }
}

void delete_ticket(Plan *p) {//删除演出计划下的票
	if (p) {
		Ticket *dead = p->element.ticket_head;
		Ticket *k = dead->next;
		while (k) {
			free(dead);
			dead = k;
			k = k->next;
		}free(dead);
	}
}

void print_ticket(Plan *p)//打印票的情况   ○/☆未售  ●/★已售出  x座位损坏
{
	if (p) {
		char seat[100][100] = { 0 }; char ID[12];
		sprintf(ID, "%d", p->element.studio_ID);
		Ticket *t = p->element.ticket_head->next;
		Studio *k = search_studio(ID, 0);
		Seat *s = k->element.seat_head->next;
		for (s; s; s = s->next) {
			if (s->seat_condition == SEAT_available || s->seat_condition == SEAT_private)
				seat[s->seatx][s->seaty] = s->seat_condition;
			else if (s->seat_condition == 9)//损坏
				seat[s->seatx][s->seaty] = 9;
		}//可用座位1   雅座2  无座位0   损坏9
		for (t; t; t = t->next) {
			if (t->ticket_status == TICKET_sold)
				seat[t->seatx][t->seaty] == 1 ? seat[t->seatx][t->seaty] = -1 : seat[t->seatx][t->seaty] = -2;
			//有座位有票 为1、2  有座位无票 为-1    无座位0   损坏座位9
		}
		system("cls");
		printf("\n\n		=============================================================\n");
		printf("		   演出计划ID:%-12ld演出厅:%-15s剩余票数%d    \n		   演出日期:%-14s开始时间:%-14s\n\n", p->element.plan_ID, k->element.studio_name\
			, p->element.ticket_head->price, p->element.date, p->element.time);
		printf("			○/☆可选  ●/★已售  ×损坏座位  座位 %d x %d\n\n", k->element.seatx, k->element.seaty);
		printf("			╭——————————————————╮\n");
		printf("					↑荧幕\n\n");
		for (int i = 1; i <= k->element.seatx; i++) {
			if (k->element.seaty > 30)
				printf("		");
			else if (k->element.seaty > 21)
				printf("		   ");
			else if (k->element.seaty > 15)
				printf("			");
			else if (k->element.seaty <= 15)
				printf("			    ");
			for (int j = 1; j <= k->element.seaty; j++) {
				switch (seat[i][j]) {
				case -2:printf("★"); break;
				case -1:printf("●"); break;
				case 0:printf("  "); break;
				case 1:printf("○"); break;
				case 2:printf("☆"); break;
				case 9:printf("×"); break;
				}
			}
			printf("\n");
		}
	}
}

void sale_ticket(Plan *p) {//售票   //结束后刷新key
	system("cls"); int flag = 0;
	char ID[15]; sprintf(ID, "%d", p->element.studio_ID);
	Studio *s = search_studio(ID, 0); Ticket *t = p->element.ticket_head->next; Account *a = search_account(PRESENT.UID, 0);
	print_ticket(p);
	printf("\n请输入所选座位行数(1~%d):",s->element.seatx);
	int x = get_num(1, s->element.seatx, 1, 2);
	printf("请输入所选座位列数(1~%d):", s->element.seaty);
	int y = get_num(1, s->element.seaty, 1, 2);
//	for (int i = 1; i <= (x - 1) *(s->element.seaty) + y - 1; i++) {
	for (t; t; t = t->next) {
		if (t->seatx == x && t->seaty == y) {
			break; 
		}
	}
	//printf("%d  %d,%d %d\n",x,y, t->seatx, t->seaty);
	if(t){
		PRESENT.user_type == USER_conductor ? printf("是否确认售出(0/1)?:"): printf("是否确认购买(0/1)?:") ;
		//分角色处理
	if (get_num(0, 1, 1, 1)) {
		if (t->ticket_status == TICKET_available) {
			t->ticket_status = TICKET_sold;
			p->element.ticket_head->price--;//刷新余票数
			save_record(add_record(p, t, atol(PRESENT.UID), SALE_sold));
			rewrite_ticket(p, t);
			draw_ticket(p, t);
		}
			else {
				printf("请选择空闲的座位哦\n");
		}
	}
	else {
		PRESENT.user_type == USER_conductor ? printf("购买已取消\n"): printf("交易已关闭\n");
	}
		/*else if (t->ticket_status == TICKET_sold) {
			t->ticket_status = TICKET_available;
			save_record(add_record(p, t, search_account(PRESENT.UID, 0), SALE_return));
		}*/
	}
	else {
		printf("请选择可用的座位哦\n");
	}
	printf("是否继续购票(0/1)?:");
	if (get_num(0, 1, 1, 1)) {
		sale_ticket(p);
	}
}

void return_ticket(Ticket *t) {//退票    并产生销售记录  //退票时记录售票者的ID
	if (t) {
		if (PRESENT.user_type == USER_customer) {//判断票的持有者
			Record *r = search_record(t->ticket_ID);//倒序查找
			long owner = r->conductor_ID;
			if (atol(PRESENT.UID) != owner || r->sale_type != SALE_sold) {//分角色处理
				printf("你尚未持有这张票哦\n"); return;
			}
		}
		if (t->ticket_status != TICKET_sold) {
			printf("这张票没有卖出去哦\n");
		}
		else {
			if (enquiry(1)) {
				Plan *p = search_plan(t->plan_ID, 0, list.plan_head);
				timer(); char date[25];
				sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
				if (strcmp(date, p->element.date) < 0) {//可退
					long objID = atol(PRESENT.UID);
					Record *r = search_record(t->ticket_ID); Account *a = NULL;//退票时记录售出此票者的ID
					t->ticket_status = TICKET_available;
					rewrite_ticket(p, t);
					if ((r->conductor_ID) != atol(PRESENT.UID)) { //票为他人卖出
						char ID[10]; sprintf(ID, "%ld", r->conductor_ID);
						a = search_account(ID,0); 
						objID = atol(a->element.UID);//记录他人UID
					}
					p->element.ticket_head->price++;//刷新余票数
					save_record(add_record(p, t, objID, SALE_return));
					print_ok();
				}
				else {
					if (PRESENT.user_type == USER_customer)printf("抱歉，");//分角色处理
					printf("退票截止时间在演出前一日\n");
				}
			}
		}
	}
	else {
		printf("没有这张票，或者票已经过期\n");
	}
}

void draw_ticket(Plan *p,Ticket *t) {//画一张票
	if (t) {
		system("cls"); char ID[15], type[8]; sprintf(ID, "%d", p->element.studio_ID);
		Studio *s = search_studio(ID, 0); Program *q = search_program(p->element.program_name, 0);
		switch (q->element.program_type) {
		case 1:strcpy(type, "电影"); break;
		case 2:strcpy(type, "歌剧"); break;
		case 3:strcpy(type, "音乐会"); break;
		default:
			print_re();
		}
		printf("\n\n");
		printf("	==============================================================\n");
		printf("	||﹎ ┈ ┈ .o┈ ﹎  ﹎.. ○              嘉 禾 天 橙 大 剧 院  ||\n");
		printf("	||﹎┈┈┈﹎ ●   ○ .﹎ ﹎o▂▃▅▆                           ||\n");
		printf("	||┈┈   ┈ /█\\ /▓\\ ﹎ ┈ ﹎﹎ ┈ ﹎   %8d%s        ||\n", p->element.studio_ID, "号放映厅");
		printf("	|| ┈▅▆▇█████▇▆▅▃▂┈﹎       %d row  %d line       ||\n", t->seatx, t->seaty);
		printf("	||                                                          ||\n");
		printf("	||                           %s     %-22s||\n", type, p->element.program_name);
		printf("	||%10s  %6s                       恭 候 光 临      ||\n", p->element.date, p->element.time);
		printf("	||ID%-9ld                                               ||\n", t->ticket_ID);
		printf("	=============================================================\n\n");
	}
	else {
		PRESENT.user_type == USER_conductor ? printf("没有这张票，或者票已经过期\n") : printf("没有这张票哟\n");
	}
}

void draw_ticket(Ticket *t) {//画一张票
	if (t) {
		Plan *p = search_plan(t->plan_ID, 0, list.plan_head);
		if (p == NULL)p = search_plan(t->plan_ID, 0, list.plan_tem_head);
		//售票员看不到过期票
		draw_ticket(p, t);
	}
	else {
		PRESENT.user_type == USER_conductor ? printf("没有这张票，或者票已经过期\n") : printf("没有这张票哟\n");
	}
}

Ticket *search_ticket(long ID ,Plan *head) {//根据ID查找票  head 查找范围
	Plan *p = head->next; int flag  = 0;// head   //售票员看不到过期票
	for (p; p; p = p->next) {//定位到演出计划
		if (p->element.ticket_tail->ticket_ID >= ID&&p->element.ticket_head->next->ticket_ID<=ID)
			break;
	}
	if (p == NULL) return NULL;
	Ticket *t = p->element.ticket_head->next;
	for (t; t; t = t->next) {
		if (t->ticket_ID == ID) {
			flag = 1; break;
		}
	}
	if (flag)
		return t;
	else
		return NULL;
}

/////////////////////////////////////////record

Record  *add_record(Plan *p, Ticket *t,long UID, sale_types type) {//产生一条销售记录加到记录链表尾  更新主键并刷新业绩
	timer();
	Record *r = (Record *)malloc(sizeof(Record)); exam_NULL(r, 0);
	r->conductor_ID = UID;
	r->plan_ID = p->element.plan_ID; r->record_ID = get_newkey(RECORD_KEY); save_key();
	sprintf(r->datetime, "%d-%02d-%02d-%02d:%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min);
	r->ticket_ID = t->ticket_ID; r->sale_type = type; type == SALE_return ? r->price = t->price *-1 : r->price = t->price;
	//r->next = a->element.record_tail->next; r->pre = a->element.record_tail;
	//a->element.record_tail->next = r; a->element.record_tail = r;
	//if (type == SALE_sold)a->element.contributions += t->price;无合适意义
	r->next = list.record_tail->next; r->pre = list.record_tail;
	list.record_tail->next = r; list.record_tail = r;
	return r;
}

Record *search_record(long obj) {//根据Ticket_ID倒序查找销售记录
	Record *r = list.record_tail; int flag = 0;
	for (r; r!=list.record_head; r = r->pre) {
		if (r->ticket_ID == obj) {
			flag = 1; break;
		}
	}
	if (flag)
		return r;
	else
		return NULL;
}

/////////////////////////////////////////account

void add_account(int choice){
	int flag = 0, tag = 0;
	char *str = NULL, *str2 = NULL;
	Account *p = (Account *)malloc(sizeof(Account));
	exam_NULL(p, 0);
	p->element.user_type = (user_types)choice;
	sprintf(p->element.UID, "%ld", get_newkey(ACCOUNT_KEY));
	printf("已分配ID为：%s\n", p->element.UID);
	printf("请输入需要添加的用户名:\n");
	str = get_string(4, 14, 0);
	do {
		flag = 0;
		if (search_account(str, 0)) {
			flag = 1;
			printf("用户名已存在，请重新输入：\n");
			str = get_string(4, 14, 0);
		}
	} while (flag);
	strcpy(p->element.username, str);

	free(str);
	do {
		printf("请输入需要添加的密码: \n");
		str = password_get(1);
		printf("\n请确认密码：\n");
		str2 = password_get(1);
		if (!strcmp(str, str2)) {
			printf("\n密码设置成功！\n");
			strcpy(p->element.password, str);
		}
		else {
			tag = 1;
			printf("两次输入不一样哦,请重新输入！\n");
		}
	} while (tag);
	free(str);
	free(str2);
	p->element.contributions = 0;
	//p->element.record_head = (Record *)malloc(sizeof(Record));
	//p->element.record_head->pre = p->element.record_head->next = NULL;//次链表初始化
	//p->element.record_tail = p->element.record_head;
	if (enquiry(1)) {
		p->next = list.account_tail->next;
		p->pre = list.account_tail;
		list.account_tail->next = p;
		list.account_tail = p;
		save_account(p);
		list.program_head->element.cost += 1;
		save_key();
		print_ok();
	}
	else {
		free(p);
		printf("新增已取消\n"); rewind(stdin);
	}
}

void modify_account(Account *p){
	int flag = 0, tag = 0, count = 1, count1 = 1, flagnum = 1;
	char *str = NULL, *str2 = NULL;
	if (p) {
		printf("\n\n修改用户名请按1，密码请按2\n");
		int choice = 0;
		choice = get_num(1, 2, 1, 1);
		data_account t = p->element;
		switch (choice) {
		case 1: {
			printf("请输入新的用户名:");
			str = get_string(4, 14, 0);
			do {
				flag = 0;
				if (search_account(str, 0)) {
					flag = 1;
					printf("用户名已存在，请重新输入:\n");
					str = get_string(4, 14, 0);
				}
			} while (flag);
			strcpy(t.username, str);
			break;
		}
		case 2: {
			printf("请输入旧密码:\n");
			str = password_get(1);
			while (count <= 3 && count1 <= 3 && flagnum) {
				if (!strcmp(str, t.password)) {
					do {
						printf("\n请输入新的密码:\n");
						str = password_get(1);
						printf("\n请确认密码:\n");
						str2 = password_get(1);
						if (!strcmp(str, str2)) {
							printf("\n密码设置成功！\n");
							strcpy(t.password, str);
							flagnum = 0;
						}
						else {
							tag = 1;
							count1++;
							printf("\n两次输入不一样哦,请重新输入！");
						}
					} while (tag && count1 <= 3 && flagnum);
				}
				else {
					printf("\n密码错误，请重新输入:\n");
					free(str);
					str = password_get(1);
					count++;
				}
				if (count > 3) {
					return;
				}
			}
			free(str);
			free(str2);
			break;
		}
		}
		if ((flagnum == 0 || flag == 0) && enquiry(1)) {
			p->element = t;
			save_account();
			print_ok();
		}
		else {
			printf("修改已取消!\n");
		}
		printf("是否继续修改?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			modify_account(p);
		}
	}
}

Account *search_account(char *obj, int judge){//按UID/用户名查找，judge控制是否进行相似反馈
	Account *t;int flag = 0;
	for (t = list.account_head->next; t != NULL; t = t->next) {
		if (!strcmp(t->element.UID, obj) || !strcmp(t->element.username, obj)) {
			flag = 1;break;
		}
	}
	if (flag)
		return t;
	if (judge && flag == 0) {
		printf("没有这个账号哦\n");
		for (t = list.account_head->next; t; t = t->next) {
			if (strstr(t->element.UID, obj) || strstr( t->element.username, obj)) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); printf("也许你想找的是：\n"); Sleep(1000);
					flag = 1;
					printf("UID\t    用户昵称\n");
				}
				printf("%s    %s\n", t->element.UID, t->element.username);
			}
		}
		if (flag == 1) {
			printf("请确认后重新查找\n");
		}
	}
	return NULL;
}

void  delete_account(Account *p){//删除账号信息
	if (p) {
		if (enquiry(2)) {
			p->pre->next = p->next;
			if (p->next) {
				p->next->pre = p->pre;
			}
			if (p == list.account_tail)list.account_tail = p->pre;
			free(p);
			save_account();
			print_ok();

		}
		else {
			printf("删除已取消\n");
			rewind(stdin);
		}
	}
}

void print_account(Account *p){//打印账户信息
	if (p) {
		printf("\t\t%-12s%-15s%-14s", p->element.UID, p->element.username, p->element.password);
		switch (p->element.user_type) {
		case 1: printf("系统管理员\n"); break;
		case 2: printf("剧院经理\n"); break;
		case 3: printf("售票员\n"); break;
		case 4: printf("顾客\n"); break;
		case 5: printf("冻结状态\n"); break;
		}
		printf("\n");
	}
	/*else {
		printf("没有这样的账号哦\n");
	}*/
}

/////////////////////////////////////////////顾客端

void search_plan_name(char *obj, int judge, Plan *head, int choose)//根据1剧目名或2演出日期查找演出计划并打印信息
{
	Plan *p = head->next;
	char type[26];
	int flagnum2 = 0;
	Program *q = list.program_head->next;
	int flag = 0;
	if (choose == 1) {
		for (p; p; p = p->next) {
			//flag = 0;
			if (!strcmp(p->element.program_name, obj)) {
				Program *t = search_program3(p->element.program_name, 1, 0);
				if (flagnum2 == 0) {
					print_planhead2();
					switch (t->element.program_type) {
					case 1:strcpy(type, "电影");  break;
					case 2:strcpy(type, "歌剧");  break;
					case 3:strcpy(type, "音乐会"); break;
					}
				}
				if (t) {
					printf("%-30s %s %s %s   %d  %s  %d   %d\n", p->element.program_name, type, p->element.date, p->element.time, t->element.duration, t->element.label, t->element.price, p->element.ticketnum);
				}
				flagnum2++;
			}
		}
	}
	else {
		flagnum2 = 0;
		for (p; p; p = p->next) {
			if (!strcmp(p->element.date, obj)) {
				Program *t = search_program3(p->element.program_name, 1, 0);
				if (flagnum2 == 0) {
					print_planhead2();
					switch (t->element.program_type) {
					case 1:strcpy(type, "电影");  break;
					case 2:strcpy(type, "歌剧");  break;
					case 3:strcpy(type, "音乐会"); break;
					}
				}
				if (t) {
					printf("%-30s  %s  %s  %s   %d  %s  %d  %d\n", p->element.program_name, type, p->element.date, p->element.time, t->element.duration, t->element.label, t->element.price, p->element.ticketnum);
				}
				flagnum2++;
			}
		}
	}
	if (judge && flagnum2 == 0) {
		printf("没有这样的演出哟\n");
		int flagnum = 0;
		//printf("%ld", obj);
		for (p = head->next; p; p = p->next) {
			//int flagnum = 0; char tem[10], objstr[10];
			//printf("%s\n", p->element.program_name);
			if (strstr(p->element.program_name, obj) != NULL || strstr(p->element.date, obj) != NULL) {
				if (flagnum == 0) { printf("嗯  "); Sleep(500); printf("你也许要找的是\n"); Sleep(1000); flagnum = 1; }
				printf("%s\n", p->element.program_name);
			}
		}if (flagnum) {
			printf("请确认后重新查找\n"); rewind(stdin);
		}
	}
}

Program *search_program3(char *obj, int choose, int judge) {//按标签或剧目查找剧目  judge 控制是否进行相似反馈
	int flag = 0;
	Program *p = list.program_head->next;
	if (choose == 1) {
		for (p; p; p = p->next) {
			if (strcmp(p->element.label, obj) == 0 || !strcmp(p->element.program_name, obj)) {
				flag = 1;//找到
				break;
			}
		}
	}
	if (flag)
		return p;
	if (judge&&flag == 0) {
		printf("没有这个剧目哦\n");
		for (p = list.program_head->next; p; p = p->next) {
			if (strstr(p->element.label, obj) != NULL || strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); printf("也许你想找的是：\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s  %s\n", p->element.label, p->element.program_name);
			}
		}
		if (flag == 1)printf("请确认后重新查找\n");
	}return NULL;
}

Plan *search_plan3(char *obj, int judge, Plan *head) {//按剧目查找演出计划 judge 控制是否进行相似反馈
	int flag = 0;
	Plan *p = head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.program_name, obj) == 0) {
			flag = 1;//找到
			break;
		}
	}
	if (flag)
		return p;
	if (judge&&flag == 0) {
		printf("没有这个剧目哦\n");
		for (p = head->next; p; p = p->next) {
			if (strstr(p->element.program_name, obj) != NULL) {
				if (flag == 0) {
					Sleep(500); printf("嗯  "); printf("也许你想找的是：\n"); Sleep(1000);
					flag = 1;
				}
				printf("%s\n", p->element.program_name);
			}
		}
		if (flag == 1)printf("请确认后重新查找\n");
	}return NULL;
}

void search_pragram_type(char *obj, int judge){//按剧目标签查找打印
	Program *p = list.program_head->next;
	char type[26];
	int flagnum2 = 0;
	for (p; p; p = p->next) {
		//flag = 0;
		if (!strcmp(p->element.label, obj)) {
			Plan *t = search_plan3(p->element.program_name, 0, list.plan_head);
			if (flagnum2 == 0) {
				print_planhead2();
				switch (p->element.program_type) {
				case 1:strcpy(type, "电影");  break;
				case 2:strcpy(type, "歌剧");  break;
				case 3:strcpy(type, "音乐会"); break;
				}
				/*if (t) {
				printf("%s %s %s %s %d %s %d %d\n", p->element.program_name, type, p->element.date, p->element.time, t->element.duration, t->element.label, t->element.price, p->element.ticketnum);
				}*/
			}
			if (t) {
				printf("%-29s%6s %s %s   %d  %s  %d   %d\n", p->element.program_name, type, t->element.date, t->element.time, p->element.duration, p->element.label, p->element.price, t->element.ticketnum);
			}
			flagnum2++;
		}
	}
	if (judge && flagnum2 == 0) {
		printf("没有这样的演出哟\n");
		int flagnum = 0;
		//printf("%ld", obj);
		for (p = list.program_head->next; p; p = p->next) {
			//printf("%s\n", p->element.program_name);
			if (strstr(p->element.label, obj) != NULL) {
				if (flagnum == 0) { printf("嗯  "); Sleep(500); printf("你也许要找的是\n"); Sleep(1000); flagnum = 1; }
				printf("%s\n", p->element.label);
			}
		}if (flagnum) {
			printf("请确认后重新查找\n"); rewind(stdin);
		}
	}
}

void advice(){
	system("cls");
	int count = 0;
	char date[15];
	sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		if (strcmp(p->element.start_date, date) <= 0 && strcmp(p->element.end_date, date) >= 0) {
			count++;
			print_program(p, 0);
			if (count == 2)break;
		}
	}
	if (count == 0) {
		printf("抱歉，最近没有影片上映！\n");
	}
}