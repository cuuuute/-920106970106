//养猪模拟
//小明开了个养猪场，一共有100个猪圈（按照0-99编号），每个猪圈最多养10头猪（按照0到9编号）
//猪一共有三个品种：黑猪、小花猪和大花白猪，其中黑猪不能与其他两种猪放在一个猪圈里，会打架
//规定每3个月，养猪场要出圈一批猪，包括：体重超过150斤的和饲养超过1年的
//同时补充一批猪崽儿（猪的品种、数量录入或者选择随机生成）
//试利用随机数方法构造猪崽儿的初始体重等信息（20-50kg），利用随机数方法按照秒或次数刷新每头猪随时间的体重增长函数（一秒/一次表示一天，一天增重0.0 ~1.2kg）
//试利用结构体链表形式管理猪圈的猪，为新进的猪自动分配猪圈（要求猪均匀分布在各个猪圈中）
//自动统计本次出圈的猪的总体售价（黑猪15元一斤，小花猪7元一斤，大花白猪6元一斤）
//（1）可任意查询当前某一猪圈的猪的数量和种类；
//（2）可任意查询当前某一猪圈某头猪的状态信息；
//（3）可任意统计当前猪场每个品种猪的数量和体重、饲养时间分布情况；70
//（4）可任意查询近5年猪的销售记录和猪崽儿的购入记录（记录用文件形式存储）；
//（5）所有当前猪的信息使用文件形式保存，程序再启动时，自动读取养猪场信息并显示。75
//（6）模拟养猪场某一只猪得了猪瘟，猪瘟的扩展几率是，同一个猪圈的猪每天被传染几率是50%，相邻猪圈的猪每天被传染的几率是15%，不相邻的猪圈的猪不传染
//编写程序模拟多久后养猪场的猪死光光
//（7）当发现有猪得了猪瘟已经发病后，请采取合理的隔离措施，进行风险控制。80
//提高部分
//（1）可使用MFC 或者QT等IDE设计用户界面；
//（2）显示每个品种猪的数量和体重、饲养时间分布图；
//（3）可根据自己的理解，加入功能（比如转换为一个养猪游戏）。90

//存在一百个猪圈，猪圈内的猪形成了一个链表，购猪卖猪即在链表内增加或移除成员

#include<bits/stdc++.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<stdlib.h>
#include<cassert>
using namespace std;
int Day=180;													//时间 

class Date{
private:
	int year,month,day;
public:
	Date(int y,int m,int d):year(y),month(m),day(d){}		//设定当前日期 
//	Date(){
//		time_t ltime=time(NULL);							//取本地时间为当前日期 
//		tm *today=localtime(&ltime);
//		year=today->tm_year+1900;
//		month=today->tm_mon+1;
//		day=today->tm_mday;
//	}
	
	int getYear(){return year;}
	int getMonth(){return month;}
	int getDay(){return day;}
	
	void setDate(int day){									//1个月默认30天 1年默认360天 
		int a,b,c;
		c=Day;
		a=c/360;
		year+=a;
		c=c-a*360;
		b=c/30;
		month+=b;
		c=c-b*30;
		c+=c;
	}
};

//Date time2(2019,1,1);
Date time0(2020,1,1);										//游戏开始时间
Date time1=time0;

class pigInf{
private:
	int pigType;											//猪猪的种类 黑猪black 0 小花猪flower 1 大花白猪white 2
	double pigWeight;										//猪猪的体重 初始为20-50之间 
	int pigData1;											//猪猪的编号0-9 
	int pigData2;											//猪猪所属猪圈的编号0-99 
	Date pigAge=time0;										//猪猪的进圈/购买的时间 
	int pigTime;											//猪猪的饲养时间（月） 
	int pigHealth;										//猪猪的健康状况 0为健康 1为传染 
public: 
	pigInf *next;											//指向下一个猪猪的指针 
	void setInf(){
		pigType=rand()%3;
		double w=rand()/double(RAND_MAX);					//随机初始化猪猪的体重 
		pigWeight=rand()%31+20+w;
		pigData1=0;
		pigData2=0;
		Date pigAge=time1;
		pigAge.setDate(Day);
		pigTime=0;
		pigHealth=0;
		next=NULL;											//初始化指针 
	}
	
	void setType(int type){pigType=type;}
	void setWeight(double weight){pigWeight=weight;}
	void setData1(int data1){pigData1=data1;}
	void setData2(int data2){pigData2=data2;}
	void setAge(Date age){pigAge=age;}
	void setHealth(int health){pigHealth=health;}
	
	int getType(){return pigType;}
	int getWeight(){return pigWeight;}
	int getData1(){return pigData1;}
	int getData2(){return pigData2;}
	Date getAge(){return pigAge;}
	int getTime(){
//		pigTime=12*(time1.getYear()-pigAge.getYear())+(time1.getMonth()-pigAge.getMonth());
		pigTime=14;
		return pigTime; 
	}
	int getHealth(){return pigHealth;}
	int getYear(){return pigAge.getYear();}
	int getMonth(){return pigAge.getMonth();}
	int getDay(){return pigAge.getDay();} 
	
//	double addWeight(double g){return pigWeight+g;}
	double addWeight(double g){
			pigWeight+=g;
			return pigWeight;
	}
	
	string stringType(){
		if(pigType==0){return "Black";}
		else if(pigType==1){return "Flower";}
		else {return "White";} 
	}
};

class pigPen{
private:
	int penNumber;
	int pigNumber;											//盖猪圈中猪猪的数量 最多10个  
	int pigBlack;											//1有黑猪猪 0无黑猪猪 
//	int pigFlag;											//0为无猪 1为有猪 2为满 
//	pigInf Pig[10];
public:
	pigInf Pig[10];
	pigPen(){
		pigNumber=0;
		pigBlack=0;
//		pigFlag=0;
	}
	void setPen(){
		if(pigNumber==0)
			pigBlack=0;
	}
	void setNumber0(int number){penNumber=number;}
	void setNumber(int number){pigNumber=number;}
	void setNumber(){pigNumber++;}
	void setBlack(int black){
		if(!pigNumber) pigBlack=0;
		else pigBlack=black;
	}
//	void setPig(pigInf *&head){
//	pigInf *p=head;
//	while(p->next!=NULL){
//		if(p->getData2()==)
//	}
//}
//	void setFlag(){
//		if(pigNumber==10) pigFlag=2;
//		else if(pigNumber>0&&pigNumber<10) pigFlag=1;
//		else pigFlag=0;
//	}
	
	int getNumber0(){return penNumber;}
	int getNumber(){return pigNumber;}
	int getBlack(){return pigBlack;}
//	int getFlag(){return pigFlag;}
}Pen[100];

void setPenNumber(pigPen Pen[],int n){
	for(int i=0;i<100;i++)
		Pen[i].setNumber0(i);
}

void setPig(pigInf *&head){
	pigInf *p=head;
	int k=0;
	for(int i=0;i<100;i++){
		if(p->getData2()==i){
			Pen[i].Pig[k]=*p;
			k++;
			p=p->next;
		}
		if(p->next==NULL){
			if(p->getData2()==i){
				Pen[i].Pig[k]=*p;
				k++;
				p=p->next;
			}
			break;	
		}		
	}
}

const int b=30,f=14,w=12,b0=800,f0=400,w0=300;				//设置猪猪的单价 黑猪15元一斤800 小花猪7元一斤400 大花白猪6元一斤300
int balance=2000;												//卖猪猪得到的钱 

//pigInf *create(){											//创建猪猪的链表 
////	pigInf Pig[10];
////	int t[100]={0};
////	for(int i=0;i<10;i++){
////		Pig[i].setInf();
////		if(!Pig[i].getType()){
////			t[0]++;
////			Pig[i].setData2(0);
////			Pen[0].setNumber(t[0]);
////			Pen[0].setBlack(1);
////		}
////		else{
////			int initial=rand()%99+1;
////			t[initial]++;
////			Pig[i].setData2(initial);
////			Pen[initial].setNumber(t[initial]);
////		}
////	}
////	pigInf *head=&Pig[0];
////	pigInf *p1=head,*p2;
////	for(int i=0;i<10;i++){
////		*p1=Pig[i];
////		p1->next=NULL;											//创建新建结点
////		if(head==NULL)
////			head=p1;											//第一个创建的结点 头指针指向该结点
////		else{
////			p2->next=p1;
////			p2=p1;												//定义链尾结点 指向p1并使p1成为新的链尾结点 
////		} 
////	}
//	pigInf *head=NULL;
//	pigInf *p=new pigInf;
//	for(int i=0;i<10;i++){
//		p->setInf();
//		if(p->getType()==0){
//			Pen[0].setNumber();
//			Pen[0].setBlack(1);
//			p->setData1(Pen[0].getNumber()-1);
//			p->setData2(0);
//		}
//		else{
//			int k=rand()%99+1;
//			Pen[k].setNumber();
//			p->setData1(Pen[k].getNumber()-1);
//			p->setData2(k);
//		}
//		if(!i) head=p;
//		p=p->next;
//	}
//	p->next=NULL;
//	return head;
//}

//bool isSell(int Day){
//	static int d;
//	if((!Day%90)&&Day!=0) return true;
//	return false;
//	
//}
pigInf *create(){											//创建猪猪的链表 correct 仅调用一次 
	pigInf *head=NULL;
	pigInf *p1=NULL,*p2=NULL;
	for(int i=0;i<10;i++){									//定义猪猪类型指针p1 p2 p1申请动态内存 
		p1=new pigInf;
		p1->setInf();
		p1->next=NULL; 
		if(p1->getType()==0){
			Pen[0].setNumber();
			Pen[0].setBlack(1);
			p1->setData1(Pen[0].getNumber()-1);
			p1->setData2(0);
		}
		else{
			int k=rand()%99+1;
			Pen[k].setNumber();
			p1->setData1(Pen[k].getNumber()-1);
			p1->setData2(k);
		}
		if(head==NULL) head=p1;
		else
			p2->next=p1;
		p2=p1;
	}
	setPig(head);
	return head;
}

//void allocatePig(pigInf *&pig){									//分配一头新猪 
//	pig.setInf();
//	if(pig.getType()==0){											//黑猪猪 
//		for(int i=0;i<99;i++)
//			for(int j=0;j<99;j++)
//				if(Pen[i].getBlack()==1&&Pen[j].getBlack()==1&&Pen[i].getNumber()<=Pen[j].getNumber()){
//					Pen[i].plusNumber();
//					pig.setData1(Pen[i].getNumber());
//					pig.setData2(i);
//				}
//	}
//	else{															//白花猪猪 
//		for(int i=0;i<99;i++)
//			for(int j=0;j<99;j++)
//				if(Pen[i].getBlack()==0&&Pen[j].getBlack()==0&&Pen[i].getNumber()<=Pen[j].getNumber()){
//					Pen[i].plusNumber();
//					pig.setData1(Pen[i].getNumber());
//					pig.setData2(i);
//				}
//	}
//	pigInf *p1=head,*p=&pig;										//插入至链尾 
//	if(head==NULL) {
//		head->next=p;
//		p->next=NULL;
//	}
//	else while(p1->next!=NULL) p1=p1->next;
//	p1->next=p;
//	p->next=NULL;
//}

//void allocatePig(pigInf *&head,pigInf *&pig){
//	pigInf *p=head;
//	while(p->next!=NULL)
//		p=p->next;
//	p=p->next;
//	p->next=pig;
//	pig->next=NULL;
//	pig->setInf();
//	if(pig->getType()==0){											//黑猪猪 
//		for(int i=0;i<100;i++)
//			for(int j=0;j<100;j++){
//				if(Pen[i].getBlack()==1&&Pen[j].getBlack()==1&&Pen[i].getNumber()<=Pen[j].getNumber()&&Pen[i].getFlag()==1&&Pen[j].getFlag()==1){
//					Pen[i].setNumber();
//					Pen[i].setFlag(); 
//					pig->setData1(Pen[i].getNumber());
//					pig->setData2(i);
//				}
//				else{
//					Pen[i].setNumber();
//					Pen[i].setFlag(); 
//					Pen[i].setBlack(1);
//					pig->setData1(Pen[i].getNumber());
//					pig->setData2(i);
//				}
//			}
//				
//	}
//	else{															//白花猪猪 
//		for(int i=0;i<100;i++)
//			for(int j=0;j<100;j++)
//				if(Pen[i].getBlack()==0&&Pen[j].getBlack()==0&&Pen[i].getNumber()<=Pen[j].getNumber()&&Pen[i].getFlag()==1&&Pen[j].getFlag()==1){
//					Pen[i].setNumber();
//					Pen[i].setFlag();
//					pig->setData1(Pen[i].getNumber());
//					pig->setData2(i);
//				}
//				else{
//					Pen[i].setNumber();
//					Pen[i].setFlag(); 
//					pig->setData1(Pen[i].getNumber());
//					pig->setData2(i);
//				}
//	}
//}

void allocatePig(pigInf *&head,pigInf *&pig){
	pigInf *p=head;
	while(p->next!=NULL)
		p=p->next;
	p=p->next;
	p->next=pig;
	pig->next=NULL;
	pig->setInf();
	int min=10,data;
	if(pig->getType()==0){											//黑猪猪 
		for(int i=0;i<100;i++)
			if(Pen[i].getBlack()==1&&Pen[i].getNumber()<min&&Pen[i].getNumber()!=0){
				min=Pen[i].getNumber();
				data=i;
			}
	if(min==10){
		pig->setData1(0);
		for(int j=0;j<100;j++)
			if(Pen[j].getNumber()==0){
				pig->setData2(j);
				Pen[j].setBlack(1);
				break;
			}
	}
		pig->setData1(min);
		pig->setData2(data);
		balance-=b0;
	}	
	else{															//白花猪猪 
		for(int i=0;i<100;i++)
			if(Pen[i].getBlack()==0&&Pen[i].getNumber()<min&&Pen[i].getNumber()!=0){
				min=Pen[i].getNumber();
				data=i;
			}
		if(min==10){
			pig->setData1(0);
			for(int j=0;j<100;j++)
				if(Pen[j].getNumber()==0){
					pig->setData2(j);
					break;
				}
		}
		pig->setData1(min);
		pig->setData2(data);
		if(pig->getType()==1) balance-=f0;
		if(pig->getType()==2) balance-=w0;	
	}
	setPig(head);
}

pigInf* sellPig(pigInf *&head){										//每过三个月（默认一个月三十天,一年360天）
	pigInf *p,*p1,*p2; 
//	cout<<"Done Successful!"<<endl;
	if(head==NULL) {
		cout<<"猪猪卖光了"<<endl;
		system("pause");
	}
	if(head->getTime()>=12||head->getWeight()>=75){
			if(head->getType()==0){
				balance+=b*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售黑猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售黑猪一只"<<endl;
			} 
			else if(head->getType()==1){
				balance+=f*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售小花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售小花猪一只"<<endl;
			}
			else{
				balance+=w*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售大白花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  出售大白花猪一只"<<endl;
			} 
			p=head;
			head=head->next;
			delete p;
	}
	p1=p2=head;
	while(p1->next!=NULL){	
		if(p1->getTime()>=12||p1->getWeight()>=75){
			if(p1->getType()==0){
				balance+=b*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售黑猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售黑猪一只"<<endl;
			} 
			else if(p1->getType()==1){
				balance+=f*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售小花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售小花猪一只"<<endl;
			}
			else{
				balance+=w*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售大白花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售大白花猪一只"<<endl;
			}
			p2=p1;
			p1=p1->next;
			delete p2;
		}
	}
	if(p1->next=NULL){	
		if(p1->getTime()>=12||p1->getWeight()>=75){
			if(p1->getType()==0){
				balance+=b*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售黑猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售黑猪一只"<<endl;
			} 
			else if(p1->getType()==1){
				balance+=f*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售小花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售小花猪一只"<<endl;
			}
			else{
				balance+=w*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售大白花猪一只"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
//				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  出售大白花猪一只"<<endl;
			}
			delete p1;
		}
	}																//关闭文件 
	for(int i=0;i<100;i++) Pen[i].setPen();							//重置猪圈 
//	cout<<"Done Successful!"<<endl;
	for(int i=0;i<10;i++){											//卖完以后立即补录新猪猪 每次10头 
		pigInf *pig=new pigInf;
		allocatePig(head,pig);
	}
//	cout<<"Done Successful!"<<endl;
	setPig(head);
	return head;
}

void searchPen(int n,pigInf *&head){								//查询猪圈信息 n为猪圈编号 correct
	int blackNumber=0,flowerNumber=0,whiteNumber=0;
	pigInf *p=head;
	while(p->next!=NULL){
		if(p->getData2()==n){
			if(p->getType()==0) blackNumber++;
			else if(p->getType()==1) flowerNumber++;
			else whiteNumber++;
		}
		p=p->next;
	}
	if(p->next==NULL){
		if(p->getData2()==n){
			if(p->getType()==0) blackNumber++;
			else if(p->getType()==1) flowerNumber++;
			else whiteNumber++;
		}
	}
	cout<<"猪圈中共有"<<Pen[n].getNumber()<<"只猪猪。"<<endl;
	cout<<"黑猪："<<blackNumber<<"只；"<<endl;
	cout<<"小花猪："<<flowerNumber<<"只；"<<endl;
	cout<<"大花白猪："<<whiteNumber<<"只；"<<endl; 
}

void searchPig(int m,int n,pigInf *&head){							//查询猪猪的信息状态 m为猪圈编号 n为猪猪编号 correct 健康状况 
	pigInf *p=head;
	while(p->next!=NULL){
		if(p->getData1()==n&&p->getData2()==m){
			cout<<m<<"号猪圈的"<<n<<"号猪情况如下："<<endl;
			cout<<"品种："<<p->stringType()<<endl;;
			cout<<"体重："<<p->getWeight()<<"kg"<<endl;
			cout<<"入圈日期："<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<endl;
		}	
		p=p->next;
	}
}

void countPig(int s,pigInf *&head){								//统计每种猪猪的成长情况 
	pigInf *p=head;
	int num=0,t1=0,t2=0,t3=0;									//w1 0-35 w2 35-55 w3 55+ t1 0-1 t2 1-3 t3 3+
	double weight=0,w1=0,w2=0,w3=0,avrw=0;
	while(p->next!=NULL){
		if(p->getType()==s){
			num++;
			weight+=p->getWeight();
			if(p->getWeight()<=35) w1++;
			else if(p->getWeight()>=55) w3++; 
			else w2++;
			if((12*(time0.getYear()-p->getYear())+time0.getMonth()-p->getMonth())<=1) t1++;
			else if((12*(time0.getYear()-p->getYear())+time0.getMonth()-p->getMonth())>=3) t3++;
			else t2++;
		}
		p=p->next;
	}
	if(p->next==NULL){
		if(p->getType()==s){
			num++;
			weight+=p->getWeight();
			if(p->getWeight()<=35) w1++;
			else if(p->getWeight()>=55) w3++; 
			else w2++;
			if((12*(time0.getYear()-p->getYear())+time0.getMonth()-p->getMonth())<=1) t1++;
			else if((12*(time0.getYear()-p->getYear())+time0.getMonth()-p->getMonth())>=3) t3++;
			else t2++;
		}
	} 
	avrw=weight/num;
	cout<<"该品种的猪查询结果如下："<<endl;
	cout<<"数量："<<num<<endl;
	cout<<"平均体重："<<avrw<<"kg"<<endl;
	cout<<"体重分布：(kg)"<<endl;
	cout<<setw(5)<<"20-35"<<'\t'<<setw(5)<<"35-55"<<'\t'<<setw(5)<<"55+"<<endl;
	cout<<setw(5)<<w1<<'\t'<<setw(5)<<w2<<'\t'<<setw(5)<<w3<<endl;
	cout<<setw(5)<<"1月以内"<<'\t'<<setw(5)<<"1-3个月"<<'\t'<<setw(5)<<"3个月以上"<<endl;
	cout<<setw(5)<<t1<<'\t'<<setw(5)<<t2<<'\t'<<setw(5)<<t3<<endl;
}

//void searchRecord_input(pigInf *&head){											//查询近5年购买记录 （不会 希望按入圈先后show） 读写文件 
//	ofstream ofs;																	//创建对象 
//	ofs.open("pig_input.txt",ios::out);												//打开文件（文件路径/文件名，打开方式/写文件）
//	pigInf *p=head;
//	while(p->next!=NULL){
//		if(p->getType()==0)
//			ofs<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入黑猪一只"<<endl;
//		else if(p->getType()==1)
//			ofs<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入小花猪一只"<<endl;
//		else
//			ofs<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入大白花猪一只"<<endl;
//	}
//	ofs.close();																	//关闭文件 
//	ifstream ifs;																	//创建对象 
//	ifs.open("pig_input.txt",ios::in);												//打开文件（文件路径/文件名，打开方式/读文件） 
//	if(!ifs.is_open()){																//利用成员函数判断是否打开成功 
//		cout<<"Open Failure!";
//		system("pause");
//	}
//	char buffer[1024]={0};															//创建数组（缓冲空间）存放输入数据 
//	while(ifs.getline(buffer,sizeof(buffer))){										//按行读取并输出 
//		cout<<buffer<<endl;
//	}
//}

void searchRecord_input(pigInf *&head){												//查询近5年购买记录 （不会 希望按入圈先后show） 读写文件 correct
	pigInf *p=head;
	while(p->next!=NULL){
		if(p->getType()==0){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入黑猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear(); 
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入黑猪一只"<<endl;
		}	
		else if(p->getType()==1){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入小花猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入小花猪一只"<<endl;
		}	
		else{
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入大白花猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入大白花猪一只"<<endl;
		}	
			p=p->next;
	}
	if(p->next==NULL){
		if(p->getType()==0){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入黑猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入黑猪一只"<<endl;
		}
		else if(p->getType()==1){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入小花猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入小花猪一只"<<endl;
		}
		else{
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入大白花猪一只"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  购入大白花猪一只"<<endl;
		}		
	}
}

void readTxt(string file)
{
    ifstream infile; 
    infile.open(file.data());									 //将文件流对象与文件连接起来 
    assert(infile.is_open());  									 //若失败,则输出错误消息,并终止程序运行 

    string s;
    while(getline(infile,s))
    {
        cout<<s<<endl;
    }
    infile.close();          								  	//关闭文件输入流 
}

void searchRecord_output(pigInf *&head)
{
	readTxt("pig_output.txt");									//创建对象 ifs.open("pig_output.txt",ios::in);												//打开文件（文件路径/文件名，打开方式/读文件） 
	
}

int pigNum(pigInf *&head){															//计算猪猪的总数 
	int num=0;
	pigInf *p=head;
	while(p->next!=NULL){
		num++;
		p=p->next;
	}
	num++;
	return num;
}

//void spreadVirus(pigInf *&head){													//模拟猪瘟 
//	int illTime=0;
//	int num=pigNum(head);
//	int n=rand()%num;
//	pigInf *p=head;
//	for(int i=0;i<n;i++)
//		p=p->next;
//}

//void spreadVirus(pigInf *&head){													//模拟猪瘟 
//	pigInf *p=head;
//	int virus;
//	int illTime=0;
//	int n=0;
//	int num=pigNum(head);
//	int x=rand()%100;
//	int y=rand()%Pen[x].getNumber();
//	Pen[x].Pig[y].setHealth(1);
//	illTime++;
//	cout<<x<<"号猪圈的"<<Pen[x].Pig[y].getData1()<<"号猪已染上猪瘟"<<endl;
//	while(n!=num){
//		for(p=head;p->next!=NULL;p++){
//			if(p->getData2()==x&&p->getHealth()!=1){														//猪猪同一猪圈 
//				virus=rand()%50;
//				if(virus<=50)
//					p->setHealth(1);
//				n++;
//			}
//			if(x-1>=0){
//				if(p->getData2()==x-1&&p->getHealth()!=1){
//					virus=rand()%15;
//					if(virus<=15)
//						p->setHealth(1);
//					n++;
//				}
//			}
//			if(x+1>=0){
//				if(p->getData2()==x+1&&p->getHealth()!=1){
//					virus=rand()%15;
//					if(virus<=15)
//						p->setHealth(1);
//					n++;
//				}
//			}
//		}
//		if(p->next!=NULL){
//			if(p->getData2()==x&&p->getHealth()!=1){														//猪猪同一猪圈 
//				virus=rand()%50;
//				if(virus<=50)
//					p->setHealth(1);
//				n++;
//			}
//			if(x-1>=0){
//				if(p->getData2()==x-1&&p->getHealth()!=1){
//					virus=rand()%15;
//					if(virus<=15)
//						p->setHealth(1);
//					n++;
//				}
//			}
//			if(x+1>=0){
//				if(p->getData2()==x+1&&p->getHealth()!=1){
//					virus=rand()%15;
//					if(virus<=15)
//						p->setHealth(1);
//					n++;
//				}
//			}
//		}
//		illTime++;
//	}
//	cout<<illTime<<"天后所有猪猪染上猪瘟"<<endl;
//}

void spreadVirus(pigInf *&head){													//模拟猪瘟 
	pigInf *p=head;
	int virus;																		//病毒变量 
	int illTime=0;																	//患病天数 
	int n=0;																		//得病的猪的数量 
	int num=pigNum(head);															//目前的猪的总数 
	srand(time(NULL));
	int x=rand()%100,y;																//随机一只猪生成猪瘟 猪圈没猪重新随机生成 
//	if(Pen[x].getNumber()>0)
//		y=rand()%Pen[x].getNumber();
//	else
//		spreadVirus(head);
	Pen[x].Pig[y].setHealth(1);														//将这只猪的健康状况修改为生病 
	illTime++;																		//第一只猪得病为第一天 
	cout<<x<<"号猪圈的"<<Pen[x].Pig[y].getData1()<<"号猪已染上猪瘟"<<endl;
	while(n!=num){																	//得病猪的数量未到猪的总数时循环 
		for(int i=0;i<99;i++)														//猪圈循环 
			for(int j=0;j<Pen[i].getNumber();j++)									//猪猪循环 
				if(Pen[i].Pig[j].getHealth()==1){									//找到生病的猪猪 
					for(int k=0;k<Pen[i].getNumber();k++)							//本猪圈传染 
						if(Pen[i].Pig[k].getHealth()!=1){							//如果未感染则有50%几率感染 
							virus=rand()%50;
							if(virus<=50)
								Pen[i].Pig[k].setHealth(1);
							n++;													//生病猪猪数量增加 
						}
					if(i-1>=0){														//邻居传播 左邻居 原理同上 
						for(int k=0;k<Pen[i-1].getNumber();k++)
							if(Pen[i-1].Pig[k].getHealth()!=1){
								virus=rand()%15;
								if(virus<=15)
									Pen[i-1].Pig[k].setHealth(1);
								n++;
							}
					}
					if(i+1<=99){													//右 
						for(int k=0;k<Pen[i+1].getNumber();k++)
							if(Pen[i+1].Pig[k].getHealth()!=1){
								virus=rand()%15;
								if(virus<=15)
									Pen[i+1].Pig[k].setHealth(1);
								n++;
							}
					}
				}
				illTime++;															//都得病了就快死了 具体多少天死再说 
	}
	cout<<illTime<<"天后所有猪猪染上猪瘟"<<endl;
}

void endVirus(pigInf *&head){
	
}

//void growPig(pigInf *&head){														//猪猪每天增重 调用距离上次登陆天数的次数 
//	double g=rand()%13/10;
//	pigInf *p=head; 
//	for(p=head;p->next!=NULL;p=p->next){
//		int t=365*(time0.getYear()-p->getYear())+30*(time0.getMonth()-p->getMonth())+(time0.getDay()-p->getDay());
//		for(int i=0;i<t;i++)
//		p->addWeight(g);			
//	}
//}

void growPig(pigInf *&head){														//猪猪每天增重 调用距离上次登陆天数的次数 定时调用 
//	srand(time(NULL));
	double g=(rand()%13)/10.0;
	pigInf *p=head; 
	for(p=head;p->next!=NULL;p=p->next)
		p->addWeight(Day*g);
	if(p->next==NULL)
		p->addWeight(Day*g);
//	Day++;
}

void pushButton(int button,pigInf *&head){
	int button0,button1;
	string button2;
	switch(button){
		case 1:
			cout<<"输入猪圈编号：";
			cin>>button0;
			cout<<endl;
			searchPen(button0,head);
		break;
		case 2:
			cout<<"输入猪圈编号：";
			cin>>button0;
			cout<<"输入猪猪编号：";
			cin>>button1;
			cout<<endl;
			searchPig(button0,button1,head);
		break;
		case 3:
			cout<<"输入猪猪种类：";													//首字母大写 
			cin>>button2;
			if(button2=="Black") countPig(0,head);
			else if(button2=="Flower") countPig(1,head);
			else countPig(2,head);
		break;
		case 4:
			cout<<"5年内出售/购入猪猪记录如下："<<endl;
			searchRecord_input(head);
			cout<<endl;
			searchRecord_output(head);
		break;
		case 5:
			spreadVirus(head);
		break;
		case 6:
			cout<<balance<<endl;
		break;
		case 7:
			freopen("balance.txt","a",stdout);
			cout<<balance<<endl;
			freopen("CON","w",stdout);
			freopen("Day.txt","a",stdout);
			cout<<Day<<endl;
			freopen("CON","w",stdout);
			exit(0);
		break;
		default:
		break;
	}
}

void menu(){
	for(int i=0;i<3;i++)
		cout<<endl;
	cout<<"					   "<<"养猪模拟"<<endl;
	cout<<endl;
	cout<<"					"<<"1.查询猪圈；"<<endl;
	cout<<endl;
	cout<<"					"<<"2.查询猪猪；"<<endl;
	cout<<endl;
	cout<<"					"<<"3.查询某一种猪猪；"<<endl;
	cout<<endl;
	cout<<"					"<<"4.查询销售/购入记录；"<<endl;
	cout<<endl;
	cout<<"					"<<"5.猪瘟模拟"<<endl;
	cout<<endl;
	cout<<"					"<<"6.金币查询"<<endl;
	cout<<endl;
	cout<<"					"<<"7.退出"<<endl;
	cout<<endl;
	cout<<"                     ========================================================="<<endl;
}

int main(){
//	Date initialtime(2021,1,1);	
	srand(time(NULL));	
	time1.setDate(Day);
	setPenNumber(Pen,100);
//	cout<<time0.getYear()<<'.'<<time0.getMonth()<<'.'<<time0.getDay()<<endl;
//	cout<<time1.getYear()<<'.'<<time1.getMonth()<<'.'<<time1.getDay()<<endl;
	pigInf* head=create();										//所有猪猪的头指针 
//	growPig(head);
//	pigInf pig[10];
//	if((!Day%90)&&Day!=0) 					
	while (1) {	
		growPig(head);
//		if(Day==180) sellPig(head);											//每3个月举行一次卖猪猪活动 
		menu();
		int button;
		cin>>button;
		pushButton(button,head);
		if(balance>=50000) cout<<"Game Over!"<<endl;
	}
	return 0;
}

//grow函数怎么调用
//create链表创建函数调用出现问题 
//显示5年内购猪记录不会写 
//金币 过去的天数写入文件里 
