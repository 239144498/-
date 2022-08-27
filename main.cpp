 #include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include"conio.h"
 #include"setjmp.h"
 #define MAX_LEN 10 //名字最大长度
 #define STU_NUM 30 //最多学生数
 #define COURSE_NUM 6 //最多的科目数
 #define PATH "C:\\Users\\23914\Desktop\\双向链表学生管理系统\\student.txt"
 jmp_buf Jump_Buffer;
 #define try if(!setjmp(Jump_Buffer))
 #define catch else
 #define throw longjmp(Jump_Buffer,1)
 
 /*学生成绩管理系统V1.0
某班有最多不超过30人（具体人数由键盘输入），最多不超过6门 （具体门数由键盘输入）
请使用结构体数组实现菜单驱动的学生成绩管理系统：
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ 
1.输入每个学生的学号，姓名和各科考试成绩；
2.删除学生记录；
3.修改学生记录；
4.按学生的总分由高到低排出名次表；
5.按学生的总分由低到高排出名次表；
6.按学号由小到大排出成绩表；
7.按姓名字典顺序排出成绩表；
8.按学号查询学生排名及其考试成绩；
9.按姓名查询学生排名及其考试成绩；
10.输出每个学生的学号、姓名、各科成绩，以及每门课程的总分和平均分；
11.将每个学生的记录信息写入文件；
12.从文件中读出每个学生的记录信息并显示；
0.退出。
请输入你的选择： 
＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
要求程序运行后先显示如上菜单，并提示用户输入选项，然后，根据用户输入的选项执行相应的操作。 
 */

typedef struct STUDENT{
	long num;	// 学号 
	char name[MAX_LEN];	//姓名 
	short cNum;
	float *score; //考试成绩 
	float sum;	// 总分 
	float aver; //平均分 
	STUDENT *last, *next;
}STU; 
 
 
int menu();//显示菜单并获得用户键盘输入的选项 	√ 
void readscore(STU *head); //输入n个学生m名门课成绩  √ 
void printStu(STU *p); //打印所有学生信息 √ 
void writetofile(STU *p, char* filePath);//输出n个学生的学号，姓名及m门课程的成绩到文件student.txt中（将学生人数和课程门数也写入文件） √ 
STU* readfromfile(STU *p, char* filePath);//从文件中读取学生的学号、姓名和成绩等信息到结构体数组stu中	√ 
STU *createHead(); 
void AddStuInfo(STU *p);
void delInfoStu(STU *head);
void delSumNode(long num, STU *head);
void delNameNode(char* name, STU *head);
void STUcopy(STU *p, STU *q);
void sortbyflag(STU *head, short flag);
void findbyflag(STU *head, short flag);
void setInfoStu(STU *head);
void setNameNode(char* name, STU *p);
void setSumNode(long num, STU *p);
int MENU();


int main()
{
	MENU();
}
/*
有余力的同学可以在此的基础上思考：
1.考虑如何在程序中加入异常处理，检查用户输入数据的有效性，以增强程序的健壮性。
2.增加添加记录、删除记录、修改记录和姓名的模糊查询等功能。
3.考虑用链表代替结构体数组实现学生成绩管理，体会动态数据结构和静态数据结构各自的优缺点。 

*/  

 int MENU()
 {
 	STU *head = createHead();
 	int select;
 	while(1)
 	{
 		select = menu();
 		switch(select){
 			case 0:
 				printf("\n程序已退出，感谢使用。\n");
 				exit(0); 
 			case 1:
 				readscore(head);
 				break;
 			case 2:
 				printStu(head);
				delInfoStu(head);
 				break;
 			case 3:
 				printStu(head);
 				break;
 			case 4:
				sortbyflag(head, 1);
				printStu(head);
				break;
			case 5:
				sortbyflag(head, 2);
				printStu(head);
				break;
			case 6:
				sortbyflag(head, 3);
				printStu(head);
				break;
			case 7:
				sortbyflag(head, 4);
				printStu(head);
				break;
			case 8:
				printStu(head);
				findbyflag(head, 1);
				break; 
			case 9:
				printStu(head);
				findbyflag(head, 2);
				break; 
 			case 10:
 				if(head->next == NULL)
 				{
 					printf("数据表为空，请先添加数据！\n");
				}else{
 					printStu(head);
				}
 				break;
 			case 11:
 				if(head->next == NULL)
 				{
 					printf("数据表为空，请先添加数据！\n");
				}else{
 					writetofile(head, PATH);
				} 
 				break;
 			case 12:
 				head = readfromfile(head, PATH);
 				break;
 			default:
 			 	printf("输入范围：0-12，请重新输入!");
 			 	break;
		 }
	}
 }

void delNameNode(char* name, STU *p)
{
	STU *head = p;
	if(head -> next == NULL)
	{
		printf("数据表为空！");
		return ;
	}
	do{
		if(strcmp(head -> next ->name, name) == 0)
		{
			printf("姓名为 %s 学生已删除。\n", head -> next -> name);
			if(head -> next -> next != NULL)
				head -> next = head -> next -> next;
			else
				head -> next = NULL;
			return ;
		}
		else
			head = head -> next;
	}while(head->next != NULL);
	printf("未找到姓名为 %s 学生\n", name);
	return ;
}

void delSumNode(long num, STU *head)
{
	if(head -> next == NULL)
	{
		printf("数据表为空！");
		return;
	}
	do{
		if(head -> next -> num == num)
		{
			printf("学号为 %s 学生已删除。\n", head -> next -> name);
			if(head -> next -> next != NULL)
				head -> next = head -> next -> next;
			else
				head -> next = NULL;
			return ;
		}
		else 
			head = head -> next;
	}while(head->next != NULL);
	printf("未找到学号为 %ld 学生\n", num);
	return ; 
}

void delInfoStu(STU *head)
{
	printf("请选择要删除的姓名或学号[1姓名 | 2学号]：");
	union{
		long num;
		char name[10];
	}temp;
	short _;
	select:
		scanf("%d", &_);
		scanf("%*[^\n]%*c");
	switch(_)
	{
		case 1:
			printf("请输入姓名：");
			scanf("%s", &temp.name);
			delNameNode(temp.name, head);
			printStu(head);
			break;
		case 2:
			printf("请输入学号：");
			scanf("%ld", &temp.num);
			delSumNode(temp.num, head); 
			break;
		default:
			printf("请输入正确序号：");
			goto select;
	} 
	 return ;
}

void setInfoStu(STU *head)
{
	printf("请选择要修改的姓名或学号的成绩[1姓名 | 2学号]：");
	short _;
	union{
		long num;
		char name[10];
	};
	select:
		scanf("%d", &_);
		scanf("%*[^\n]%*c");
	
	switch(_)
	{
		case 1:
			printf("请输入姓名：");
			scanf("%s", &name);
			setNameNode(name, head);
			printStu(head);
			break;
		case 2:
			printf("请输入学号：");
			scanf("%ld", &num);
			setSumNode(num, head); 
			printStu(head);
			break;
		default:
			printf("请输入正确序号：");
			goto select;
	} 
	 return;
}

void setNameNode(char* name, STU *p)
{
	STU *head = p;
	if(head -> next == NULL)
	{
		printf("数据表为空！");
		return ;
	}
	do{
		if(strcmp(head -> next ->name, name) == 0)
		{
			printf("请输入课程共几门：");
			do{
				scanf("%d", &head -> next -> cNum);
				scanf("%*[^\n]%*c");
				if((head -> next -> cNum) > COURSE_NUM or (head -> next -> cNum) < 1 ){
					printf("\r课程数量超过6门或小于1门，请重新输入："); 
				}
				else{
					break;
				}
			}while(1);
			head -> next -> score = (float *)calloc(head -> next -> cNum, sizeof(float));
			head -> next -> sum = 0;
			head -> next -> aver = 0;
			for(int i=0; i < (head -> next ->cNum); i++)
			{
				do{
					printf("请输入第%d门课程新的成绩：", i+1);
					scanf("%f", &head -> next -> score[i]);
					scanf("%*[^\n]%*c");
				}while(!(head -> next -> score[i] >= 0));
				head -> next -> sum += head -> next -> score[i];
			}
			head -> next -> aver = head -> next -> sum / head -> next -> cNum;
			return;
		}
		else
			head = head -> next;
	}while(head->next != NULL);
	printf("未找到姓名为 %s 学生\n", name);
}

void setSumNode(long num, STU *p)
{
	STU *head = p;
	if(head -> next == NULL)
	{
		printf("数据表为空！");
		return;
	}
	do{
		if(head -> next -> num == num)
		{
						printf("请输入课程共几门：");
			do{
				scanf("%d", &head -> next -> cNum);
				scanf("%*[^\n]%*c");
				if((head -> next -> cNum) > COURSE_NUM or (head -> next -> cNum) < 1 ){
					printf("\r课程数量超过6门或小于1门，请重新输入："); 
				}
				else{
					break;
				}
			}while(1);
			head -> next -> score = (float *)calloc(head -> next -> cNum, sizeof(float));
			head -> next -> sum = 0;
			head -> next -> aver = 0;
			for(int i=0; i < (head -> next ->cNum); i++)
			{
				do{
					printf("请输入第%d门课程新的成绩：", i+1);
					scanf("%f", &head -> next -> score[i]);
					scanf("%*[^\n]%*c");
				}while(!(head -> next -> score[i] >= 0));
				head -> next -> sum += head -> next -> score[i];
			}
			head -> next -> aver = head -> next -> sum / head -> next -> cNum;
			return; 
		}
		else 
			head = head -> next;
	}while(head->next != NULL);
	printf("未找到学号为 %ld 学生\n", num);
}

void STUcopy(STU *p, STU *q)
{
	STU temp = *q;
	q->num = p->num;
	p -> num = temp.num;
	strcpy(q->name, p->name);
	strcpy(p->name, temp.name);
	q->cNum = p->cNum;
	p->cNum = temp.cNum;
	q->score = p->score;
	p->score = temp.score;
	q->sum = p->sum;
	p->sum = temp.sum;
	q->aver = p->aver;
	p->aver = temp.aver;
}

void sortbyflag(STU *head, short flag)
{
	STU *p, *q;
	int i,j;
	p = head;
	while(p -> next != NULL)
	{
		p = p -> next;
		q = p;
		while(q!=NULL)
		{
			if(flag == 1 and q -> sum > p -> sum)
			{
				STUcopy(p, q); 
			}
			else if(flag == 2 and q -> sum < p -> sum)
			{
				STUcopy(p, q); 
			}
			else if(flag == 3 and q -> num < p -> num)
			{
				STUcopy(p, q);
			}
			else if(flag == 4 and strcmp(q -> name, p -> name) == -1)
			{
				STUcopy(p, q);
			}
			q = q -> next;
		}
	}
}

void findbyflag(STU *head, short flag)
{
	STU *p = head;
	union {
		long num;
		char name[MAX_LEN];
	};

	if(flag == 1)
	{
		do{
			printf("\n输入学号查找结果：[纯数字>=5位数&&<=9位数]：");
			scanf("%ld", &num);
			fflush(stdin);
			if( num >=10000 and num < 1000000000)
			{
				break; 
			}
		}while(1);
		while(p -> next != NULL)
		{
			p = p -> next;
			if(p->num == num)
			{
				printf("%ld\t%s\t",p->num,p->name);
				for(int j=0;j<p->cNum;j++){
					printf("%.0f\t",p->score[j]);
				}
				printf("%.0f\t%.0f\n",p->sum,p->aver);
				return;
			}
		}
		printf("\n未找到！\n");
	}
	else if(flag == 2)
	{
		printf("\n输入名字查找你[只取前%d位字符]：", MAX_LEN);
		int i=0; 
		char _;
		do{
			for(i=0; ((_ = getchar())!='\n'); i++)
			{
				name[i] = _; 
				if( i > MAX_LEN-3)
				{
					break;
				}
			}
			if(i != 0)
			{
				break;
			}
		}while(1);
		fflush(stdin);
		while(p -> next != NULL)
		{
			p = p -> next;
			if(strcmp(p->name, name) == 0)
			{
				printf("%ld\t%s\t",p->num,p->name);
				for(int j=0;j<p->cNum;j++){
					printf("%.0f\t",p->score[j]);
				}
				printf("%.0f\t%.0f\n",p->sum,p->aver);
				return;
			}
		}
		printf("\n未找到！\n");
	}
}

void AddStuInfo(STU *p)
{
	do{
		printf("\n请输入学号[纯数字>=5位数&&<=9位数]：");
		scanf("%ld", &p -> num);
		fflush(stdin);
		if( p -> num >=10000 and p -> num < 1000000000)
		{
			break; 
		}
	}while(1);
	
	printf("\n请输入姓名[只取前%d位字符]：", MAX_LEN);
	int i=0; 
	char _;
	do{
		for(i=0; ((_ = getchar())!='\n'); i++)
		{
			p -> name[i] = _; 
			if( i > MAX_LEN-3)
			{
				break;
			}
		}
		if(i != 0)
		{
			break;
		}
	}while(1);
	fflush(stdin);
	
	printf("请输入课程共几门：");
	do{
		scanf("%d", &p -> cNum);
		scanf("%*[^\n]%*c");
		if(p -> cNum > COURSE_NUM or p -> cNum < 1 ){
			printf("\r课程数量超过6门或小于1门，请重新输入："); 
		}
		else{
			break;
		}
	}while(1);
	p -> score = (float *)calloc(p -> cNum, sizeof(float));
	for(int i=0; i < p ->cNum; i++)
	{
		do{
			printf("请输入第%d门课程成绩：", i+1);
			scanf("%f", &p -> score[i]);
			scanf("%*[^\n]%*c");
		}while(!(p -> score[i] >= 0));
		p -> sum += p -> score[i];
	}
	p -> aver = p -> sum / p -> cNum;
	
	printf("学生信息添加成功！\n");
	printf("学号：%ld\n姓名：%s\n成绩：", p -> num, p->name);
	for(int i=0; i<p -> cNum; i++)
	{
		printf("%.2f ", p -> score[i]);
	}
	printf("\n总分%.2f\t平均分：%.2f\n", p -> sum, p -> aver);
}

void readscore(STU *head)
{
	STU *p;
	STU *pr = head;
	
	p = (STU *)calloc(1, sizeof(STU));
	if(p == NULL)
	{
		printf("没有足够的内存！");
		exit(1);
	}

	while(head -> next != NULL)
	{
		head = head -> next;
	}
	head -> next = p;

	AddStuInfo(p);
	p -> next = NULL;
}

STU* readfromfile(STU *desc, char* filePath)
{
    FILE *fp;
    if(!(fp=fopen(filePath, "r")))
    {
        printf("打开文件失败!\n");
        exit(1);
    }
    
    STU *head = createHead();
	STU *pr = head;
    
	while(!feof(fp))
    {
    	STU *p = (STU *)calloc(1, sizeof(STU));
		if(p == NULL)
		{
			printf("没有足够的内存！\n");
			exit(1);
		}
		pr -> next = p;
		fscanf(fp, "%ld %s %d ", &p->num, p->name, &p->cNum);
		if(strlen(p->name) == 0)
		{
			printf("数据读取异常！\n");
			printf("格式为：学号 姓名 成绩1,成绩2...成绩, 总分，平均分\n");
			free(head);
			fclose(fp);
			return desc;
		}
        p -> score = (float *)calloc(p->cNum, sizeof(float));
		for(int i=0; i < p->cNum; i++)
		{
			fscanf(fp, "%f,", &p->score[i]);
		}
		fscanf(fp, " %f %f\n", &p->sum, &p->aver);
		p -> next = NULL;
		p -> last = pr;
		pr = pr -> next;
    }
    fclose(fp);
    printf("数据读取成功！\n");
    return head;
}

STU *createHead()
{
	STU *head;
	head = (STU *)calloc(1, sizeof(STU));
	if(head == NULL)
	{
		printf("没有足够的内存！");
		exit(1);
	}
	head -> next = NULL;
	head -> last = NULL;
	return head;
}

void writetofile(STU *p, char* filePath)
{	
	FILE *fp;
	
	if(!(fp = fopen(filePath, "w")))
	{
		printf("写入文件失败！");
		exit(1);
	}
	p = p -> next;
	while(p != NULL)
	{
		fprintf(fp, "%ld %s %d ", p->num, p->name, p->cNum);
		for(int i=0; i<p->cNum; i++)
		{
			fprintf(fp, "%f,", p->score[i]);
		}
		fprintf(fp, " %f %f\n", p->sum, p->aver);
		p = p -> next;
	}
//	fwrite(p -> next, sizeof(STU), 1, fp);
//	rewind(fp);
	fclose(fp);
	printf("文件写入成功！");
}

void printStu(STU *p)
{
	int i = 1; 
	if(p -> sum == 0)
	{
		p = p -> next;
	}

	printf("\t\t\t\t\t学生信息详情\n\n");
	printf("序号  学号\t姓名\t\t\t成绩\t\t\t\t总分\t平均分\n"); 
	printf("—————————————————————————————————————————————\n"); 
	while(p != NULL)
	{
		printf(" %d   %-10ld  %-10s |", i, p -> num, p->name);
		for(int i=0; i<p->cNum; i++)
		{
			printf("%.2f|", p -> score[i]);
		}
		for(int i=COURSE_NUM; i > p->cNum; i--)
			printf("%*.*s", 7, 10, "");
		printf("\t%.2f%7.2f\n", p -> sum, p -> aver);
		printf("—————————————————————————————————————————————\n"); 
		p = p -> next;
		i++;
	}
	printf("\n");
}

int menu()
{

	printf("\n\t\t\t\t\t学生成绩管理系统V1.0\n\
			某班有最多不超过30人（具体人数由键盘输入），最多不超过6门 （具体门数由键盘输入）\n\
			请使用结构体数组实现菜单驱动的学生成绩管理系统：\n\
			＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝ \n\
			1.输入每个学生的学号，姓名和各科考试成绩；\n\
			2.删除学生记录；\n\
			3.修改学生记录；\n\
			4.按学生的总分由高到低排出名次表；\n\
			5.按学生的总分由低到高排出名次表；\n\
			6.按学号由小到大排出成绩表；\n\
			7.按姓名字典顺序排出成绩表；\n\
			8.按学号查询学生排名及其考试成绩；\n\
			9.按姓名查询学生排名及其考试成绩；\n\
			10.输出每个学生的学号、姓名、各科成绩，以及每门课程的总分和平均分；\n\
			11.将每个学生的记录信息写入文件；\n\
			12.从文件中读出每个学生的记录信息并显示；\n\
			0.退出。\n\
			请输入你的选择： ");
	int _;
	scanf("%d", &_);
	system("cls");
	printf("你的选择：【%d】\n", _);
	return _;
}
 
 

