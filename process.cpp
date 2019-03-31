#include"stdafx.h"
#include"statements.h"

void process_all() {//登录过程
	int choice;
	while (1) {
		show_main();
		choice = choice_judge(1);
		switch (choice) {
		case 0:break;
		case 1:process_sign(); break;
		case 2:process_register(); break;
		case 3:show_bye(); //system("taskkill /im cmd.exe /T /F");
			system("exit");
		}
	}
}

void process_sign() {//登录过程
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	play_bgm();
	switch (re) {
	case 0:process_appeal(); break;//账号申诉
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); exit(1);
		break;
	}
}

void process_register() {//注册过程
	show_register();
	char *str = NULL;
	printf("\n请输入你的邀请码:\n");
	str = get_string(1, 12, 0);
	if (save_invitation_code(str)) {
		add_account(4);
		printf("注册成功！\n");
		printf("请妥善保存你的UID哦！\n");
	}
	else {
		printf("抱歉，您没有邀请码， 请获得邀请码之后再来注册！\n");
	}
	go_on();
	free(str);
}

void process_appeal() {//账号申诉过程
	SetColor(7, 0);
	char *str = NULL, *str2 = NULL;
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                       账号申诉                             \n");
	printf("\n\n请确认是否进行账号申诉(1申诉2退出):");
	switch (get_num(1, 2, 1, 1)) {
	case 1:
		printf("\n请输入你的用户名:\n");
		str = get_string(4, 14, 0);
		if (Account *t = search_account(str, 0)) {
			free(str);
			printf("请输入你的ID：\n");
			str = get_string(1, 8, 0);
			if (!strcmp(str, t->element.UID)) {
				free(str);
				printf("输入正确，你可以修改你的密码了!\n");
				printf("\n请输入新的密码: \n");
				str = password_get(1);
				printf("\n请确认密码：\n");
				str2 = password_get(1);
				if (!strcmp(str, str2)) {
					printf("\n密码设置成功！\n");
					strcpy(t->element.password, str);
				}
				else {
					printf("两次输入不一样哦，请重新申诉\n");
				}
			}
			else {
				printf("UID输入错误，请重新申诉！\n");
			}
		}
		else {
			printf("用户名输入错误!\n");
		}
		break;
	case 2:return; break;
	}
}

///////////////////////////////////////系统管理员过程

void process_admin() {//管理员过程
	int choice; char *str = NULL;
	while (1) {
		show_admin();
		choice = choice_judge(11);
		switch (choice) {
		case 0:break;
		case 1:process_account(); break;
		case 2:log_viewer(); break;
		case 3:printf("请输入新的key(12位):"); str = get_string(12, 12, 0);
			add_invitation_code(str); print_ok(); free(str); break;
		case 4:modify_account(search_account(PRESENT.username, 0)); break;
		}if (choice == 0) {
			printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1) { go_on(); break; }
		} go_on();
	}
}

void process_account() {//账户管理过程        //在这里调用你写的链表操作
	int choice; char *str = NULL; Account *a = NULL;
	while (1) {
		show_account();
		choice = choice_judge(5);
		switch (choice) {
		case 0: break;
		case 1: printf("\n\n请输入要查找的账号ID或名称:\n"); a = search_account(str = get_string(1, 14, 0), 1); if (a)print_accounthead(); print_account(a); free(str); break;
		case 2: printf("\n\n请输入要修改的账号ID或名称:\n");  modify_account(search_account(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3: show_account_type(); choice = get_num(1, 4, 1, 1); add_account(choice); break;
		case 4: printf("\n\n请输入你需要删除的账号信息:\n"); delete_account(search_account(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:account_viewer(list.account_head); break;
		}
		if (choice == 0)break;if (choice < 5)go_on();
	}
}

///////////////////////////////////////剧院经理

void process_manager() {//剧院经理过程
	int choice;
	while (1) {
		show_manager();
		choice = choice_judge(2);
		switch (choice) {
		case 0:break;
		case 1:process_program(); break;
		case 2: process_studio(); break;
		case 3:process_plan(); break;
		case 4:process_record(); break;
		case 5:modify_account(search_account(PRESENT.UID, 0)); break;
		}if (choice == 0) {
			printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1){go_on(); break;} go_on();
		}
	}
}

void process_program() {//剧目查询及管理过程
	int choice; char *str;
	while (1) {
		show_program();
		choice = choice_judge(3);
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入要查询的影片ID或名称:"); print_program(search_program(str = get_string(1, 30, 0), 1), 1); free(str); break;
		case 2:printf("\n请输入要修改的影片ID或名称:"); modify_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 3:add_program(); break;
		case 4:printf("\n请输入要删除的影片ID或名称:"); delete_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 5:program_viewer(list.program_head); break;
		}if (choice == 0)break; if (choice < 5)go_on();
	}
}

void process_studio() {//影厅查询及管理过程
	int choice; char *str = NULL;
	while (1) {
		show_studio();
		choice = choice_judge(4); 
		switch (choice){
		case 0:break;
		case 1:printf("\n请输入要查询的放映厅ID或名称：\n"); print_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 2:printf("\n请输入要修改的放映厅ID或名称：\n"); modify_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3:add_studio();break;
		case 4:printf("\n请输入要删除的放映厅ID或名称：\n"); delete_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:studio_viewer(); break;
		}if (choice == 0)break; if (choice < 5) go_on();
	}
}

void process_plan() {//放映计划查询及管理过程
	int choice, num; Plan *p = NULL; clean_plan_atFirst();
	while (1) {
		show_plan();
		choice = choice_judge(12);
		switch (choice) {
		case 0:break;
		case 1:printf("\n\n1.当前演出计划 2.过期演出计划\n请选择查询范围：");
			num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; process_plan_inquiry(p); break;
		case 2:printf("请输入要修改的演出计划ID:"); modify_plan(search_plan(get_num(1, 999999, 1, 6) , 1, list.plan_head)); break;
		case 3:add_plan(); break;
		case 4:printf("\n\n请输入要删除的演出计划ID:"); num = get_num(1, 999999, 1, 6); p = search_plan(num, 0, list.plan_head); if (p == NULL) { p = search_plan(num, 0, list.plan_tem_head); } delete_plan(p); break;
		case 5:printf("\n\n1. 浏览当前计划 2.浏览过期计划\n请选择："); num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head;plan_viewer(p); break;
		}if (choice == 0)break;go_on(); 
	}
}

void process_plan_inquiry(Plan *head) {//查询演出计划
	int num; char *str = NULL;
	printf("1.演出计划ID  2.剧目名称/ID 3.演出厅名称/ID 4.日期\n请选择检索方式：");
	num = get_num(1, 4, 1, 1);
	if (num < 4) {
		printf("请输入名称/ID：");
		search_plan(str = get_string(1, 30, 0), num, head); free(str);
	}
	else {
		printf("请输入日期(yyyy-mm-dd):"); str = get_date();
		search_plan(str, num, head); free(str);
	}
}

void process_record() {//销售统计与查询 
	timer(); char *str = NULL;
	int choice; long ID; Ticket *t = NULL; Plan *p = NULL; Account *a = NULL;
	while (1) {
		show_record();
		choice = choice_judge(15);
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入票的ID:"); ID = (long)get_num(1, 999999999, 1, 9); t = search_ticket(ID, list.plan_head);
			if (t == NULL)t = search_ticket(ID, list.plan_tem_head); draw_ticket(t);
			if (t) {
				if (t->ticket_status == TICKET_sold)printf("		已");
				else printf("		未"); printf("售出\n");
			}break;
		case 2:printf("\n请输入演出计划ID:"); ID = (long)get_num(1, 999999, 1, 6); p = search_plan(ID, 1, list.plan_head);
			if(p==NULL)p = search_plan(ID, 1, list.plan_tem_head); if(p)print_ticket(p); break;
		case 3:printf("\n\n请输入售票员ID或昵称:"); str = get_string(1, 15, 0);
					a = search_account(str, 0);
					if (a&&a->element.user_type == USER_conductor) {
						process_count(a); free(str);
					}
					else { printf("该ID不是售票员哦\n"); }
					break;
		case 4:count_program();
			printf("\n1.单个剧目 2.票房排行榜\n请选择:"); choice = get_num(0, 2, 1, 1);
			switch (choice) {
			case 1:printf("请输入剧目ID/名称:"); str = get_string(1, 9, 0);
				print_programhead();
				print_program_cnt(search_program(str, 0)); free(str); break;
			case 2:	sort_program();
						system("cls");
						printf("\n				    票房排行榜");
						print_programhead();
						for (Program *p = list.program_tail; p!=list.program_head; p = p->pre)
							print_program_cnt(p);
					break;
				}break;
			}
		if (choice == 0)break; go_on();
	}
}

void process_count(Account *a) {//业绩统计查询过程
	if (a) {
		printf("1.本日业绩 2.本月业绩 3.总业绩 4.自定义日期区间\n请选择:");
		int choice = choice = get_num(1, 4, 1, 1);
		char begin[30], end[30], *temb, *teme;
		sprintf(begin, "%d-%02d-%02d-00:00", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		sprintf(end, "%d-%02d-%02d-23:59", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		switch (choice) {// 1本日 2本月  3总
		case 1:account_count(a, begin, end); break;
		case 2:begin[8] = '0'; begin[9] = '1'; end[8] = '3'; end[9] = '1'; account_count(a, begin, end); break;
		case 3:account_count(a); break;
		case 4:printf("请输入开始日期(yyyy-mm-dd):"); temb = get_date(); printf("请输入结束日期(yyyy-mm-dd):"); teme = get_date();
			sprintf(begin, "%s-00:00", temb); sprintf(end, "%s-23:59", teme);
			account_count(a, begin, end); free(temb); free(teme); break;
		}
		printf("该时间段内%s的", a->element.username); if (choice < 3)choice == 2 ? printf("本月") : printf("本日");
		printf("销售额为%ld\n", a->element.contributions);
		printf("是否继续查询?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			process_count(a);
		}
	}
}

///////////////////////////////////////////售票员

void process_conducter() {
	int choice; Plan *p = NULL; Account *a = NULL;
	while (1) {
		show_conducter();
		choice = choice_judge(13);
		switch (choice) {
		case 0:break;
		case 1: printf("\n\n"); process_plan_inquiry(list.plan_head); break;//ticket_viewer(); break;
		case 2:process_ticket(); break;
		case 3:a = search_account(PRESENT.UID, 0);
			process_count(a);break;
		case 4:plan_viewer(list.plan_head); break;
		case 5:modify_account(search_account(PRESENT.UID, 0)); break;
		case 6:modify_account(search_account(PRESENT.UID, 0)); break;
		}if (choice == 0) {
			printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1) { go_on(); break; }
		} go_on();
	}
}

void process_ticket() {//票务查询及售票退票
	int choice; Plan *p = NULL; Ticket *t = NULL;
	while (1) {
		show_ticket();
		choice = choice_judge(14);
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入票的ID:"); t = search_ticket((long)get_num(111111, 999999999, 1, 9), list.plan_head); draw_ticket(t);
			if (t) {
				if (t->ticket_status == TICKET_sold)printf("		已");
				else printf("		未"); printf("售出\n");
			}
			break;
		case 2:printf("请输入演出计划ID:"); p = search_plan((long)get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)sale_ticket(p); break;
		case 3:printf("请输入已售出的票的ID:"); return_ticket(search_ticket((long)get_num(111111, 999999999, 1, 9), list.plan_head)); break;
		}if (choice == 0)break; go_on();
	}
}

///////////////////////////////////////////顾客

void process_customer() {
	int choice; long ID = 0;
	char *str = NULL;
	Plan *p = NULL; Ticket *t = NULL;
	while (1) {
		show_customer();
		choice = choice_judge(30);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:advice(); break;
		case 2:process_find();  break;
		case 3:plan_viewer(list.plan_head); break;
		case 4:printf("\n\n1.购票  2.退票\n请选择:"); choice = get_num(1, 2, 1, 1);
			switch (choice) {
			case 1:printf("请输入演出计划ID:"); p = search_plan((long)get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)sale_ticket(p); break;
			case 2:printf("请输入所退票的ID:"); ID = get_num(111111, 99999999, 1, 8); t = search_ticket(ID, list.plan_head); return_ticket(t); break;
			} break;
		case 5:modify_account(search_account(PRESENT.UID, 0)); break;
		}if (choice == 0) {
			printf("\n是否退出登录?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1) { go_on(); break; }
		}
		go_on();
	}
}

void process_find(){
	char *str = NULL;
	int choice;
	while (1) {
		show_customer_find();
		choice = choice_judge(31);
		if (choice != 0)catch_cursor();
		switch (choice) {
		case 0:break;
		case 1:printf("\n请输入剧目名称:\n"); str = get_string(1, 30, 0); search_plan_name(str, 1, list.plan_head, 1); free(str); break;
		case 2:printf("\n请按这种格式输入日期查找：XXXX-XX-XX:\n"); str = get_date(); search_plan_name(str, 1, list.plan_head, 2); free(str); break;
		case 3:printf("\n\n请输入要查找的标签，比如爱情，恐怖，悬疑....\n"); str = get_string(1, 5, 0); search_pragram_type(str, 1); free(str); break;
		}if (choice == 0)break; go_on();
	}
}

