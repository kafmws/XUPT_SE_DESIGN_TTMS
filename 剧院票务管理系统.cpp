// ��ԺƱ�����ϵͳ.cpp: �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"statements.h"
List list; 
data_account PRESENT;//��ǰ�û�
struct tm *now;
int main(){
	show_welcome();
	initialize();
	//print_instruction(1);
	//rewrite_ticket(list.plan_head->next->next, list.plan_head->next->next->element.ticket_head->next);
	//draw_ticket(list.plan_head->next,list.plan_head->next->element.ticket_head->next); go_on();
	//print_program(list.program_head->next->next, 0); go_on();
	//process_record();
	//print_accounthead(); Account *a = list.account_head->next;
	//log_viewer();
	process_all();
	//plan_viewer(list.plan_head);
	//print_ticket(list.plan_head->next); go_on();
	//process_conducter();
    return 0;
}

