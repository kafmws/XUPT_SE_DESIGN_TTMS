#include"stdafx.h"
#include"statements.h"

void process_all() {//��¼����
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

void process_sign() {//��¼����
	int re = 0, cnt = 0;
	re = sign_judge();
	while ((re <= 0 || re > 4) && cnt < 3) {
		cnt++;
		re = sign_judge();
	}
	play_bgm();
	switch (re) {
	case 0:process_appeal(); break;//�˺�����
	case 1:process_admin(); break;
	case 2:process_manager(); break;
	case 3:process_conducter(); break;
	case 4:process_customer(); break;
	default:
			print_re(); exit(1);
		break;
	}
}

void process_register() {//ע�����
	show_register();
	char *str = NULL;
	printf("\n���������������:\n");
	str = get_string(1, 12, 0);
	if (save_invitation_code(str)) {
		add_account(4);
		printf("ע��ɹ���\n");
		printf("�����Ʊ������UIDŶ��\n");
	}
	else {
		printf("��Ǹ����û�������룬 ����������֮������ע�ᣡ\n");
	}
	go_on();
	free(str);
}

void process_appeal() {//�˺����߹���
	SetColor(7, 0);
	char *str = NULL, *str2 = NULL;
	system("CLS");
	printf("\n\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	printf("\t\t                       �˺�����                             \n");
	printf("\n\n��ȷ���Ƿ�����˺�����(1����2�˳�):");
	switch (get_num(1, 2, 1, 1)) {
	case 1:
		printf("\n����������û���:\n");
		str = get_string(4, 14, 0);
		if (Account *t = search_account(str, 0)) {
			free(str);
			printf("���������ID��\n");
			str = get_string(1, 8, 0);
			if (!strcmp(str, t->element.UID)) {
				free(str);
				printf("������ȷ��������޸����������!\n");
				printf("\n�������µ�����: \n");
				str = password_get(1);
				printf("\n��ȷ�����룺\n");
				str2 = password_get(1);
				if (!strcmp(str, str2)) {
					printf("\n�������óɹ���\n");
					strcpy(t->element.password, str);
				}
				else {
					printf("�������벻һ��Ŷ������������\n");
				}
			}
			else {
				printf("UID����������������ߣ�\n");
			}
		}
		else {
			printf("�û����������!\n");
		}
		break;
	case 2:return; break;
	}
}

///////////////////////////////////////ϵͳ����Ա����

void process_admin() {//����Ա����
	int choice; char *str = NULL;
	while (1) {
		show_admin();
		choice = choice_judge(11);
		switch (choice) {
		case 0:break;
		case 1:process_account(); break;
		case 2:log_viewer(); break;
		case 3:printf("�������µ�key(12λ):"); str = get_string(12, 12, 0);
			add_invitation_code(str); print_ok(); free(str); break;
		case 4:modify_account(search_account(PRESENT.username, 0)); break;
		}if (choice == 0) {
			printf("\n�Ƿ��˳���¼?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1) { go_on(); break; }
		} go_on();
	}
}

void process_account() {//�˻��������        //�����������д���������
	int choice; char *str = NULL; Account *a = NULL;
	while (1) {
		show_account();
		choice = choice_judge(5);
		switch (choice) {
		case 0: break;
		case 1: printf("\n\n������Ҫ���ҵ��˺�ID������:\n"); a = search_account(str = get_string(1, 14, 0), 1); if (a)print_accounthead(); print_account(a); free(str); break;
		case 2: printf("\n\n������Ҫ�޸ĵ��˺�ID������:\n");  modify_account(search_account(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3: show_account_type(); choice = get_num(1, 4, 1, 1); add_account(choice); break;
		case 4: printf("\n\n����������Ҫɾ�����˺���Ϣ:\n"); delete_account(search_account(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:account_viewer(list.account_head); break;
		}
		if (choice == 0)break;if (choice < 5)go_on();
	}
}

///////////////////////////////////////��Ժ����

void process_manager() {//��Ժ�������
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
			printf("\n�Ƿ��˳���¼?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1){go_on(); break;} go_on();
		}
	}
}

void process_program() {//��Ŀ��ѯ���������
	int choice; char *str;
	while (1) {
		show_program();
		choice = choice_judge(3);
		switch (choice) {
		case 0:break;
		case 1:printf("\n������Ҫ��ѯ��ӰƬID������:"); print_program(search_program(str = get_string(1, 30, 0), 1), 1); free(str); break;
		case 2:printf("\n������Ҫ�޸ĵ�ӰƬID������:"); modify_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 3:add_program(); break;
		case 4:printf("\n������Ҫɾ����ӰƬID������:"); delete_program(search_program(str = get_string(1, 30, 0), 1)); free(str); break;
		case 5:program_viewer(list.program_head); break;
		}if (choice == 0)break; if (choice < 5)go_on();
	}
}

void process_studio() {//Ӱ����ѯ���������
	int choice; char *str = NULL;
	while (1) {
		show_studio();
		choice = choice_judge(4); 
		switch (choice){
		case 0:break;
		case 1:printf("\n������Ҫ��ѯ�ķ�ӳ��ID�����ƣ�\n"); print_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 2:printf("\n������Ҫ�޸ĵķ�ӳ��ID�����ƣ�\n"); modify_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 3:add_studio();break;
		case 4:printf("\n������Ҫɾ���ķ�ӳ��ID�����ƣ�\n"); delete_studio(search_studio(str = get_string(1, 14, 0), 1)); free(str); break;
		case 5:studio_viewer(); break;
		}if (choice == 0)break; if (choice < 5) go_on();
	}
}

void process_plan() {//��ӳ�ƻ���ѯ���������
	int choice, num; Plan *p = NULL; clean_plan_atFirst();
	while (1) {
		show_plan();
		choice = choice_judge(12);
		switch (choice) {
		case 0:break;
		case 1:printf("\n\n1.��ǰ�ݳ��ƻ� 2.�����ݳ��ƻ�\n��ѡ���ѯ��Χ��");
			num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head; process_plan_inquiry(p); break;
		case 2:printf("������Ҫ�޸ĵ��ݳ��ƻ�ID:"); modify_plan(search_plan(get_num(1, 999999, 1, 6) , 1, list.plan_head)); break;
		case 3:add_plan(); break;
		case 4:printf("\n\n������Ҫɾ�����ݳ��ƻ�ID:"); num = get_num(1, 999999, 1, 6); p = search_plan(num, 0, list.plan_head); if (p == NULL) { p = search_plan(num, 0, list.plan_tem_head); } delete_plan(p); break;
		case 5:printf("\n\n1. �����ǰ�ƻ� 2.������ڼƻ�\n��ѡ��"); num = get_num(1, 2, 1, 1); if (num == 1)p = list.plan_head; else p = list.plan_tem_head;plan_viewer(p); break;
		}if (choice == 0)break;go_on(); 
	}
}

void process_plan_inquiry(Plan *head) {//��ѯ�ݳ��ƻ�
	int num; char *str = NULL;
	printf("1.�ݳ��ƻ�ID  2.��Ŀ����/ID 3.�ݳ�������/ID 4.����\n��ѡ�������ʽ��");
	num = get_num(1, 4, 1, 1);
	if (num < 4) {
		printf("����������/ID��");
		search_plan(str = get_string(1, 30, 0), num, head); free(str);
	}
	else {
		printf("����������(yyyy-mm-dd):"); str = get_date();
		search_plan(str, num, head); free(str);
	}
}

void process_record() {//����ͳ�����ѯ 
	timer(); char *str = NULL;
	int choice; long ID; Ticket *t = NULL; Plan *p = NULL; Account *a = NULL;
	while (1) {
		show_record();
		choice = choice_judge(15);
		switch (choice) {
		case 0:break;
		case 1:printf("\n������Ʊ��ID:"); ID = (long)get_num(1, 999999999, 1, 9); t = search_ticket(ID, list.plan_head);
			if (t == NULL)t = search_ticket(ID, list.plan_tem_head); draw_ticket(t);
			if (t) {
				if (t->ticket_status == TICKET_sold)printf("		��");
				else printf("		δ"); printf("�۳�\n");
			}break;
		case 2:printf("\n�������ݳ��ƻ�ID:"); ID = (long)get_num(1, 999999, 1, 6); p = search_plan(ID, 1, list.plan_head);
			if(p==NULL)p = search_plan(ID, 1, list.plan_tem_head); if(p)print_ticket(p); break;
		case 3:printf("\n\n��������ƱԱID���ǳ�:"); str = get_string(1, 15, 0);
					a = search_account(str, 0);
					if (a&&a->element.user_type == USER_conductor) {
						process_count(a); free(str);
					}
					else { printf("��ID������ƱԱŶ\n"); }
					break;
		case 4:count_program();
			printf("\n1.������Ŀ 2.Ʊ�����а�\n��ѡ��:"); choice = get_num(0, 2, 1, 1);
			switch (choice) {
			case 1:printf("�������ĿID/����:"); str = get_string(1, 9, 0);
				print_programhead();
				print_program_cnt(search_program(str, 0)); free(str); break;
			case 2:	sort_program();
						system("cls");
						printf("\n				    Ʊ�����а�");
						print_programhead();
						for (Program *p = list.program_tail; p!=list.program_head; p = p->pre)
							print_program_cnt(p);
					break;
				}break;
			}
		if (choice == 0)break; go_on();
	}
}

void process_count(Account *a) {//ҵ��ͳ�Ʋ�ѯ����
	if (a) {
		printf("1.����ҵ�� 2.����ҵ�� 3.��ҵ�� 4.�Զ�����������\n��ѡ��:");
		int choice = choice = get_num(1, 4, 1, 1);
		char begin[30], end[30], *temb, *teme;
		sprintf(begin, "%d-%02d-%02d-00:00", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		sprintf(end, "%d-%02d-%02d-23:59", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
		switch (choice) {// 1���� 2����  3��
		case 1:account_count(a, begin, end); break;
		case 2:begin[8] = '0'; begin[9] = '1'; end[8] = '3'; end[9] = '1'; account_count(a, begin, end); break;
		case 3:account_count(a); break;
		case 4:printf("�����뿪ʼ����(yyyy-mm-dd):"); temb = get_date(); printf("�������������(yyyy-mm-dd):"); teme = get_date();
			sprintf(begin, "%s-00:00", temb); sprintf(end, "%s-23:59", teme);
			account_count(a, begin, end); free(temb); free(teme); break;
		}
		printf("��ʱ�����%s��", a->element.username); if (choice < 3)choice == 2 ? printf("����") : printf("����");
		printf("���۶�Ϊ%ld\n", a->element.contributions);
		printf("�Ƿ������ѯ?(0/1):");
		if (get_num(0, 1, 1, 1)) {
			process_count(a);
		}
	}
}

///////////////////////////////////////////��ƱԱ

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
			printf("\n�Ƿ��˳���¼?(0/1):");
			choice = get_num(0, 1, 1, 1); if (choice == 1) { go_on(); break; }
		} go_on();
	}
}

void process_ticket() {//Ʊ���ѯ����Ʊ��Ʊ
	int choice; Plan *p = NULL; Ticket *t = NULL;
	while (1) {
		show_ticket();
		choice = choice_judge(14);
		switch (choice) {
		case 0:break;
		case 1:printf("\n������Ʊ��ID:"); t = search_ticket((long)get_num(111111, 999999999, 1, 9), list.plan_head); draw_ticket(t);
			if (t) {
				if (t->ticket_status == TICKET_sold)printf("		��");
				else printf("		δ"); printf("�۳�\n");
			}
			break;
		case 2:printf("�������ݳ��ƻ�ID:"); p = search_plan((long)get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)sale_ticket(p); break;
		case 3:printf("���������۳���Ʊ��ID:"); return_ticket(search_ticket((long)get_num(111111, 999999999, 1, 9), list.plan_head)); break;
		}if (choice == 0)break; go_on();
	}
}

///////////////////////////////////////////�˿�

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
		case 4:printf("\n\n1.��Ʊ  2.��Ʊ\n��ѡ��:"); choice = get_num(1, 2, 1, 1);
			switch (choice) {
			case 1:printf("�������ݳ��ƻ�ID:"); p = search_plan((long)get_num(1, 999999, 1, 6), 1, list.plan_head); if (p)sale_ticket(p); break;
			case 2:printf("����������Ʊ��ID:"); ID = get_num(111111, 99999999, 1, 8); t = search_ticket(ID, list.plan_head); return_ticket(t); break;
			} break;
		case 5:modify_account(search_account(PRESENT.UID, 0)); break;
		}if (choice == 0) {
			printf("\n�Ƿ��˳���¼?(0/1):");
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
		case 1:printf("\n�������Ŀ����:\n"); str = get_string(1, 30, 0); search_plan_name(str, 1, list.plan_head, 1); free(str); break;
		case 2:printf("\n�밴���ָ�ʽ�������ڲ��ң�XXXX-XX-XX:\n"); str = get_date(); search_plan_name(str, 1, list.plan_head, 2); free(str); break;
		case 3:printf("\n\n������Ҫ���ҵı�ǩ�����簮�飬�ֲ�������....\n"); str = get_string(1, 5, 0); search_pragram_type(str, 1); free(str); break;
		}if (choice == 0)break; go_on();
	}
}

