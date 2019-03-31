#include"stdafx.h"
#include"statements.h"
///////////////////////////////////////////import

void file_check() {//文件检查
	if (access(".\\key.txt", 0) != 0) {
		FILE *fp = fopen(".\\key.txt", "w");
		fprintf(fp, "111111 1\n666666 2\n888888 3\n111111 4\n111111 5\n111111 6\n12345678 7\n");
		fclose(fp);
	}
	if (access(".\\account.txt", 0) != 0) {
		FILE *fp = fopen(".\\account.txt", "w"); fclose(fp);
		printf("正在初始化系统\n"); printf("正在设置系统管理员\n");
		import_key();
		add_account(1);
		initialize_linklist();//稍稍内存泄漏   实在不想写了
	}
	if (access(".\\program.txt", 0) != 0) { FILE *fp = fopen(".\\program.txt", "w"); fclose(fp); }
	if (access(".\\studio.txt", 0) != 0) { FILE *fp = fopen(".\\studio.txt", "w"); fclose(fp); }
	if (access(".\\plan.txt", 0) != 0) { FILE *fp = fopen(".\\plan.txt", "w"); fclose(fp); }
	if (access(".\\record.txt", 0) != 0) { FILE *fp = fopen(".\\record.txt", "w"); fclose(fp); }
}

void import_key() {//导入主键信息到链表
	FILE *fp = fopen(".\\key.txt", "r");
	exam_NULL(fp, 1);
	long key;int type;
	while (fscanf(fp, "%ld %d", &key, &type) != EOF) {
		Key *p = (Key *)malloc(sizeof(Key));
		p->next = list.key_tail->next;
		p->pre = list.key_tail;
		p->key = key; p->type = type;
		list.key_tail->next = p;
		list.key_tail = p;
	}
	fclose(fp);
}

void import_account() {//导入账号信息到链表
	int cnt = 0;
	FILE *fp = fopen(".\\account.txt","r");
	exam_NULL(fp, 1);
	int t;data_account tem;
	while (fscanf(fp,"%s %s %s %d",tem.UID,tem.username,tem.password,&t)!=EOF) {
		tem.contributions = 0;
		tem.user_type = user_types(t);
		password_change(tem.password, 2);
		Account *p = (Account *)malloc(sizeof(Account));
		exam_NULL(p, 0);
		p->element = tem;//每成功读取一组数据做一个结点，连接到链表上
		p->next = list.account_tail->next;
		p->pre = list.account_tail;
		list.account_tail->next = p;
		list.account_tail = p;
		cnt++;//计数
	}
	list.account_head->element.contributions = cnt;//计数
	fclose(fp);
}

void import_program() {//导入剧目信息到链表
	FILE *fp = fopen(".\\program.txt", "r");
	exam_NULL(fp, 1);
	data_program tem = {0};
	int type, rating, cnt = 0;
	while (fscanf(fp, "%s %s %d %d %s %s %s",tem.program_ID, tem.program_name, &type, &rating, tem.director,\
		tem.performer[0], tem.performer[1])==7&&fscanf(fp,"%s %s", tem.start_date, tem.end_date)== 2&&fscanf(fp,\
		"%d %s %s %s %d %d", &tem.duration, tem.label, tem.area, tem.language, &tem.price, &tem.cost)==6){
		tem.program_type = (program_types)type,tem.program_rating=(program_ratings)rating;
		Program *p = (Program *)malloc(sizeof(Program));
		exam_NULL(p, 0);
		p->element = tem; p->element.contributions = 0;//票房置零
		p->next = list.program_tail->next;
		p->pre = list.program_tail;
		list.program_tail->next = p;
		list.program_tail = p;
		cnt++;
	}
	list.program_head->element.cost = cnt;//头结点计数
	fclose(fp);
}

void import_studio_and_seat() {//导入放映厅及座位信息到链表
	FILE *fp = fopen(".\\studio.txt", "r");
	exam_NULL(fp, 1);
	data_studio tem;
	int i, j, t, ID;
	list.studio_head->element.seatx = 0;
	while (fscanf(fp, "%s %s %d %d %d", tem.studio_ID, tem.studio_name, &tem.seatx,&tem.seaty,&tem.seatsum) != EOF) {
		Studio *p = (Studio *)malloc(sizeof(Studio)); int cnt = 0;
		exam_NULL(p, 0);
		p->element = tem;
		p->element.seat_head = (Seat *)malloc(sizeof(Seat));
		exam_NULL(p->element.seat_head, 0);
		p->element.seat_head->pre = p->element.seat_head->next = NULL;//次链表初始化
		p->element.seat_tail = p->element.seat_head;
		p->next = list.studio_tail->next;
		p->pre = list.studio_tail;
		list.studio_tail->next = p;
		list.studio_tail = p;
		list.studio_head->element.seatx++;//计数
		//座位的读取与处理
		ID = atoi(p->element.studio_ID);
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				Seat *k = (Seat *)malloc(sizeof(Seat));
				exam_NULL(k, 0);
				k->seatx = i, k->seaty = j,k->stduio_ID=ID;
				fscanf(fp, "%d", &t); if (t == 1 || t == 2) cnt++;
				k->seat_condition = (seat_conditions)t;
				k->next = p->element.seat_tail->next;
				k->pre = p->element.seat_tail;
				p->element.seat_tail->next = k;
				p->element.seat_tail = k;
			}
		}/*if (p->element.seatsum != cnt) { printf("座位文件校验错误\n"); print_re(); }*/
	}
	fclose(fp);
}

void import_plan_and_ticket() {//导入演出计划信息到链表
	FILE *fp = fopen(".\\plan.txt", "r");
	exam_NULL(fp, 1);
	data_plan tem; int i, cnt = 0, cntt = 0, cnttt = 0;
	while (fscanf(fp, "%ld %s %d %s %s %d %d",&tem.plan_ID,&tem.program_name,&tem.studio_ID,\
tem.date,tem.time,&tem.ticketnum, &tem.button) != EOF) {
		Plan *p = (Plan *)malloc(sizeof(Plan)); exam_NULL(p, 0);
		p->element = tem;
		p->element.contributions = 0;
		p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(p->element.ticket_head, 0);
		p->element.ticket_head->pre = p->element.ticket_head->next = NULL;
		p->element.ticket_tail = p->element.ticket_head;//票的链表初始化
		cntt = 0;
		for (i = 1; i <= p->element.ticketnum; i++) {
			Ticket *k = (Ticket *)malloc(sizeof(Ticket)); exam_NULL(k, 0); int t;
			fscanf(fp, "%ld %d %d %d %d", &k->ticket_ID, &k->seatx, &k->seaty, &k->price, &t);
			k->plan_ID = p->element.plan_ID;
			k->ticket_status = (ticket_statuses)t; if (k->ticket_status != TICKET_sold)cntt++;//余票计数
			else p->element.contributions += k->price;
			k->next = p->element.ticket_tail->next; k->pre = p->element.ticket_tail;
			p->element.ticket_tail->next = k; p->element.ticket_tail = k;
		}
		p->element.ticket_head->price = cntt;//
		if (p->element.button) {
			p->next = list.plan_tail->next; p->pre = list.plan_tail;
			list.plan_tail->next = p; list.plan_tail = p;  cnt++;//可用演出计划计数
		}
		else {
			p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
			list.plan_tem_tail->next = p; list.plan_tem_tail = p; cnttt++;//过期演出计划计数
		}
	}
	list.plan_head->element.ticketnum = cnt;
	list.plan_tem_head->element.ticketnum = cnttt;
	fclose(fp);
}

void import_record() {//导入销售记录到链表
	FILE *fp = fopen(".\\record.txt", "r");
	exam_NULL(fp, 0);
	long record_ID, plan_ID, ticket_ID, conductor_ID, price;
	int type; char time[50];
	while (fscanf(fp, "%ld %d %ld %s %d %ld %ld", &record_ID,&type, &conductor_ID,\
		time, &price, &ticket_ID, &plan_ID) != EOF) {
		Record *r = (Record *)malloc(sizeof(Record));exam_NULL(r, 0);
		r->sale_type = (sale_types)type; strcpy(r->datetime, time);
		r->conductor_ID = conductor_ID; r->plan_ID = plan_ID; r->record_ID = record_ID;
		r->price = price; r->ticket_ID = ticket_ID;
		r->next = list.record_tail->next; r->pre = list.record_tail;
		list.record_tail->next = r; list.record_tail = r;
	}
	fclose(fp);
}


//弃用

//void import_plan_and_ticket_tem() {//导入已过期演出计划
//	FILE *fp = fopen(".\\plantem.txt", "r");
//	exam_NULL(fp, 1);
//	data_plan tem; int cnt = 0;
//	while (fscanf(fp, "%ld %s %d %s %s %d %d", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
//		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
//		Plan *p = (Plan *)malloc(sizeof(Plan)); exam_NULL(p ,0);
//		p->element = tem; cnt++;
//		p->element.ticket_tail = p->element.ticket_head = NULL;//票的链表的置空
//		p->next = list.plan_tem_tail->next; p->pre = list.plan_tem_tail;
//		list.plan_tem_tail->next = p; list.plan_tem_tail = p;
//	}
//	list.plan_tem_head->element.ticketnum = cnt;
//	fclose(fp);
//}

void import_plan_and_ticket_bin() {//导入二进制数据至链表
	FILE *fp = fopen(".\\plan.bin", "rb");
	exam_NULL(fp, 1);
	int size_plan = sizeof(data_plan), size_ticket = sizeof(Ticket); data_plan tem;
	while (fread(&tem, size_plan, 1, fp) == 1) {
		Plan *p = (Plan *)malloc(sizeof(Plan)); p->element = tem;
		p->element.ticket_head = (Ticket *)malloc(sizeof(Ticket)); //exam_mallocX(p->element.ticket_head);
		p->element.ticket_head->pre = p->element.ticket_head->next = NULL;
		p->element.ticket_tail = p->element.ticket_head;//票的链表初始化
		for (int i = 1; i <= tem.ticketnum; i++) {
			Ticket *k = (Ticket *)malloc(sizeof(Ticket)); //exam_mallocX(k);
			fread(k, size_ticket, 1, fp);
			k->next = p->element.ticket_tail->next; k->pre = p->element.ticket_tail;
			p->element.ticket_tail->next = k; p->element.ticket_tail = k;
		}
		p->next = list.plan_tail->next; p->pre = list.plan_tail;
		list.plan_tail->next = p; list.plan_tail = p;
	}
	fclose(fp);
}

//////////////////////////////////////////save

void save_key() {//保存主键信息到文件
	FILE *fp = fopen(".\\key.txt", "w");
	exam_NULL(fp, 1);
	Key *p = list.key_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %d\n", p->key, p->type);
	}
	fclose(fp);
}

void save_program() {//保存剧目信息到文件
	FILE *fp = fopen(".\\program.txt","w+");
	exam_NULL(fp, 1);
	Program *p = list.program_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %s %s %s %s %s %d %s %s %s %d %d\n", p->element.program_ID\
		,p->element.program_name, p->element.program_type, p->element.program_rating, p->element.director,\
		p->element.performer[0], p->element.performer[1],p->element.start_date, p->element.end_date,\
		p->element.duration, p->element.label, p->element.area, p->element.language, p->element.price, p->element.cost);
	}
	fclose(fp);
}

void save_studio_and_seat() {//保存放映厅及其座位数据
	int i, j;
	FILE *fp = fopen(".\\studio.txt", "w+");
	exam_NULL(fp, 1);
	Studio *p = list.studio_head->next;
	Seat *k = NULL;
	for (p; p; p = p->next) {
		fprintf(fp, "%s %s %d %d %d\n", p->element.studio_ID, p->element.studio_name, p->element.seatx, p->element.seaty,p->element.seatsum);
		k = p->element.seat_head->next;
		for (i = 1; i <= p->element.seatx; i++) {
			for (j = 1; j <= p->element.seaty; j++) {
				/*if (k->seatx > p->element.seatx || k->seaty > p->element.seaty) {
					j--,k = k->next; continue; }*/
				fprintf(fp, "%d ", k->seat_condition);
				k = k->next;
			}fprintf(fp, "\n");
		}
	}
	fclose(fp);
}

void save_plan_and_ticket() {//保存演出计划及票
	FILE *fp = fopen(".\\plan.txt", "w");
	exam_NULL(fp, 1);
	Plan *p = list.plan_head->next;
	for (p; p; p = p->next) {
		if (p->element.button != 1 ) { continue; }//0  过期   1可用
		fprintf(fp, "%ld %s %d %s %s %d %d\n",p->element.plan_ID,p->element.program_name,p->element.studio_ID,\
		p->element.date,p->element.time,p->element.ticketnum, p->element.button);
		Ticket *k = p->element.ticket_head->next;
		for (int i = 1; i <= p->element.ticketnum; i++) {
			fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
			k = k->next;
			//if (i % 5 == 0) { fprintf(fp, "\n"); }
		}
		fprintf(fp, "\n");
	}
	p = list.plan_tem_head->next;
	for (p; p; p = p->next) {
		fprintf(fp, "%ld %s %d %s %s %d %d\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID, \
			p->element.date, p->element.time, p->element.ticketnum, p->element.button);
		Ticket *k = p->element.ticket_head->next;
		for (int i = 1; i <= p->element.ticketnum; i++) {
			fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
			k = k->next;
			//if (i % 5 == 0) { fprintf(fp, "\n"); }
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void save_plan_and_ticket(Plan *p) {//追加演出计划与票的信息到文件
	FILE *fp = fopen(".\\plan.txt", "a+");
	exam_NULL(fp, 1);
	fprintf(fp, "%ld %s %d %s %s %d %d\n", p->element.plan_ID, p->element.program_name, p->element.studio_ID, \
		p->element.date, p->element.time, p->element.ticketnum, p->element.button);
	Ticket *k = p->element.ticket_head->next;
	for (int i = 1; i <= p->element.ticketnum; i++) {
		fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
		k = k->next;
		//if (i % 5 == 0) { fprintf(fp, "\n"); }
	}
	fprintf(fp, "\n");
	fclose(fp);
}

void save_plan_and_ticket_bin() {//二进制文件
	FILE *fp = fopen(".\\plan.bin", "wb");
	exam_NULL(fp, 1);
	Plan *p = list.plan_head->next; 
	int size_plan = sizeof(data_plan), size_ticket = sizeof(Ticket);
	for (p; p; p = p->next) {
		fwrite(&(p->element),size_plan,1,fp);
		for (Ticket *k = p->element.ticket_head->next; k; k = k->next) {
			fwrite(k, size_ticket, 1, fp);
		}
	}
	fclose(fp);
}

void rewrite_ticket(Plan *p,Ticket *t) {//局部覆写文件     改变票的状态
	FILE *fp = fopen(".\\plan.txt", "r+");
	exam_NULL(fp, 1);
	char ttt[50000]; data_plan tem;
	int seatx, seaty, price, status, flag = 0; long ticket_ID;
	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
		if (tem.plan_ID != p->element.plan_ID) {
			fgets(ttt,50000,fp);//读完一整行
		}//fprintf(fp, "%ld %d %d %d %d     ", k->ticket_ID, k->seatx, k->seaty, k->price, k->ticket_status);
		else {
			while (fscanf(fp, "%ld %d %d %d %d", &ticket_ID, &seatx, &seaty, &price, &status)) {
				if (t->ticket_ID == ticket_ID) {
					flag = 1; break;
				}
			}
			if (flag) {
				fseek(fp, -1, SEEK_CUR);
				status == 0 ? status = 1 : status = 0;
				fprintf(fp, "%d", status);
				break;
			}
			else print_re();
		}
	}
	fclose(fp);
}

void clean_plan_atFirst() {//程序开始将过期的演出计划标记过期
	timer();
	char date[15],time[10];
	sprintf(date, "%d-%02d-%02d", now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
	sprintf(time, "%02d:%02d", now->tm_hour, now->tm_min);
	FILE *fp = fopen(".\\plan.txt", "r+");
	exam_NULL(fp, 1);
	char t[20000]; data_plan tem;
	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
		if (strcmp(date, tem.date) > 0 || (strcmp(date, tem.date) == 0 && strcmp(time, tem.time) > 0)) {
			fseek(fp, -3, SEEK_CUR);
			fprintf(fp, "%d", 0);
			fseek(fp, 3, SEEK_CUR);
		}
		//else { fscanf(fp, "%[^\r\n]", t); fscanf(fp, "%[^\r\n]", t); }
		fgets(t, 20000, fp);//读完一整行
	}
	fclose(fp);
}

//void modify_ticket(Plan *p) {//局部覆写文件   修改票的状态
//	FILE *fp = fopen(".\\plan.txt", "r+");
//	exam_NULL(fp, 1);
//	char t[50000]; data_plan tem;
//	while (fscanf(fp, "%ld %s %d %s %s %d %d\r\n", &tem.plan_ID, &tem.program_name, &tem.studio_ID, \
//		tem.date, tem.time, &tem.ticketnum, &tem.button) != EOF) {
//		if (tem.plan_ID != p->element.plan_ID) {
//			fgets(t, 50000, fp);//读完一整行
//		}
//		else break;
//	}
//	fseek(fp, 0, SEEK_CUR);
//	Ticket *q = p->element.ticket_head->next;
//	for (q; q; q = q->next) {
//		
//	}
//	
//	fclose(fp);
//}

void save_account(Account *p){
	char str[13];
	FILE *fp = fopen("account.txt", "a+");
	exam_NULL(fp, 1);
	strcpy(str, p->element.password);
	password_change(str, 1);
	fprintf(fp, "%s %s %s %d\n", p->element.UID, p->element.username, str, p->element.user_type);
	fclose(fp);
}

void save_account(){
	char str[13];
	FILE *fp = fopen("account.txt", "w");
	exam_NULL(fp, 1);
	for (Account *p = list.account_head->next; p; p = p->next) {
		strcpy(str, p->element.password);
		password_change(str, 1);
		fprintf(fp, "%s %s %s %d\n", p->element.UID, p->element.username, str, p->element.user_type);
	}

	fclose(fp);
}

void save_record(Record *r) {//追加新的记录到文件末尾
	FILE *fp = fopen(".\\record.txt", "a");
	exam_NULL(fp, 1);
	fprintf(fp, "%ld %d %d %s %d %ld %ld\n", r->record_ID, r->sale_type, r->conductor_ID, \
		r->datetime, r->price, r->ticket_ID, r->plan_ID);
	fclose(fp);
}

int save_invitation_code(char *obj) {//比较 并 局部修改邀请码  //返回值为比对结果
	FILE *fp = fopen(".\\invitation.txt", "r");
	FILE *fpp = fopen(".\\invitation_tem.txt", "w+");
	exam_NULL(fp, 1); exam_NULL(fpp, 1);
	char str[15]; int flag = 0;
	while (fscanf(fp, "%s", str) != EOF) {
		if (strcmp(str, obj) == 0) { 
			flag = 1;
			continue; 
		}
		fprintf(fpp, "%s\n", str);
	}
	fclose(fp);
	fclose(fpp);
	remove(".\\invitation.txt");
	rename("invitation_tem.txt", "invitation.txt");
	return flag;
}

void add_invitation_code(char *obj) {//补充邀请码
	FILE *fp = fopen(".\\invitation.txt", "a");
	exam_NULL(fp, 1);
	fprintf(fp, "%s\n", obj);
	fclose(fp);
}