//����ģ��
//С�����˸�������һ����100����Ȧ������0-99��ţ���ÿ����Ȧ�����10ͷ������0��9��ţ�
//��һ��������Ʒ�֣�����С����ʹ󻨰������к��������������������һ����Ȧ�����
//�涨ÿ3���£�����Ҫ��Ȧһ�������������س���150��ĺ���������1���
//ͬʱ����һ�����̶������Ʒ�֡�����¼�����ѡ��������ɣ�
//����������������������̶��ĳ�ʼ���ص���Ϣ��20-50kg���������������������������ˢ��ÿͷ����ʱ�����������������һ��/һ�α�ʾһ�죬һ������0.0 ~1.2kg��
//�����ýṹ��������ʽ������Ȧ����Ϊ�½������Զ�������Ȧ��Ҫ������ȷֲ��ڸ�����Ȧ�У�
//�Զ�ͳ�Ʊ��γ�Ȧ����������ۼۣ�����15Ԫһ�С����7Ԫһ��󻨰���6Ԫһ�
//��1���������ѯ��ǰĳһ��Ȧ��������������ࣻ
//��2���������ѯ��ǰĳһ��Ȧĳͷ���״̬��Ϣ��
//��3��������ͳ�Ƶ�ǰ��ÿ��Ʒ��������������ء�����ʱ��ֲ������70
//��4���������ѯ��5��������ۼ�¼�����̶��Ĺ����¼����¼���ļ���ʽ�洢����
//��5�����е�ǰ�����Ϣʹ���ļ���ʽ���棬����������ʱ���Զ���ȡ������Ϣ����ʾ��75
//��6��ģ������ĳһֻ�������������������չ�����ǣ�ͬһ����Ȧ����ÿ�챻��Ⱦ������50%��������Ȧ����ÿ�챻��Ⱦ�ļ�����15%�������ڵ���Ȧ������Ⱦ
//��д����ģ���ú��������������
//��7��������������������Ѿ����������ȡ����ĸ����ʩ�����з��տ��ơ�80
//��߲���
//��1����ʹ��MFC ����QT��IDE����û����棻
//��2����ʾÿ��Ʒ��������������ء�����ʱ��ֲ�ͼ��
//��3���ɸ����Լ�����⣬���빦�ܣ�����ת��Ϊһ��������Ϸ����90

//����һ�ٸ���Ȧ����Ȧ�ڵ����γ���һ�������������������������ӻ��Ƴ���Ա

#include<bits/stdc++.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<stdlib.h>
#include<cassert>
using namespace std;
int Day;													//ʱ�� 

class Date{
private:
	int year,month,day;
public:
	Date(int y,int m,int d):year(y),month(m),day(d){}		//�趨��ǰ���� 
	
	int getYear(){return year;}
	int getMonth(){return month;}
	int getDay(){return day;}
	
	void setDate(int Day){									//1����Ĭ��30�� 1��Ĭ��360�� 
		int a,b,c;
		c=Day;
		a=c/360;											//�� 
		year+=a;
		c=c-a*360;
		b=c/30;												//�� 
		month+=b;
		c=c-b*30;											//�� 
		day+=c;
	}
};

Date time0(2020,1,1);										//��Ϸ��ʼʱ��
Date time1=time0;

class pigInf
{
private:
	int pigType;											//��������� ����black 0 С����flower 1 �󻨰���white 2
	double pigWeight;										//��������� ��ʼΪ20-50֮�� 
	int pigData1;											//����ı��0-9 
	int pigData2;											//����������Ȧ�ı��0-99 
	Date pigAge=time0;										//����Ľ�Ȧ/�����ʱ�� 
	int pigTime;											//���������ʱ�䣨�£� 
	int pigHealth;										//����Ľ���״�� 0Ϊ���� 1Ϊ��Ⱦ 
public: 
	pigInf *next;											//ָ����һ�������ָ�� 
	void setInf()
	{
		pigType=rand()%3;
		double w=rand()/double(RAND_MAX);					//�����ʼ����������� 
		pigWeight=rand()%31+20+w;
		pigData1=0;
		pigData2=0;
		Date pigAge=time1;
		pigAge.setDate(Day);
		pigTime=0;
		pigHealth=0;
		next=NULL;											//��ʼ��ָ�� 
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
		pigTime=360*(time1.getYear()-pigAge.getYear())+30*(time1.getMonth()-pigAge.getMonth())+(time1.getDay()-pigAge.getDay());
		return pigTime; 
	}
	int getHealth(){return pigHealth;}
	int getYear(){return pigAge.getYear();}
	int getMonth(){return pigAge.getMonth();}
	int getDay(){return pigAge.getDay();} 
	
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
	int pigNumber;											//����Ȧ����������� ���10��  
	int pigBlack;											//1�к����� 0�޺����� 
	int pigFlag;											//0ûë�� 1����ë�� 
public:
	pigInf Pig[10];
	pigPen(){
		pigNumber=0;
		pigBlack=0;
		pigFlag=0;
	}
	void setPen(){
		if(pigNumber==0)
			pigBlack=0;
	}
	void setFlag(int flag){pigFlag=flag;}
	void setNumber0(int number){penNumber=number;}
	void setNumber(int number){pigNumber=number;}
	void setNumber(){pigNumber++;}
	void setBlack(int black){
		if(!pigNumber) pigBlack=0;
		else pigBlack=black;
	}
	
	int getNumber0(){return penNumber;}
	int getNumber(){return pigNumber;}
	int getBlack(){return pigBlack;}
	int getFlag(){return pigFlag;}
}Pen[100];

void setPenNumber(pigPen Pen[],int n){
	for(int i=0;i<100;i++)
		Pen[i].setNumber0(i);
}

const int b=30,f=14,w=12,b0=800,f0=400,w0=300;				//��������ĵ��� ����15Ԫһ��800 С����7Ԫһ��400 �󻨰���6Ԫһ��300
int balance=2000;											//������õ���Ǯ 

pigInf *create(){											//������������� correct ������һ�� 
	pigInf *head=NULL;
	pigInf *p1=NULL,*p2=NULL;
	for(int i=0;i<10;i++){									//������������ָ��p1 p2 p1���붯̬�ڴ� 
		p1=new pigInf;
		p1->setInf();
		p1->next=NULL; 
		if(p1->getType()==0){
			Pen[0].setNumber();
			Pen[0].setBlack(1);
			p1->setData1(Pen[0].getNumber()-1);
			p1->setData2(0);
			Pen[0].Pig[Pen[0].getNumber()-1]=*p1;
		}
		else{
			int k=rand()%99+1;
			Pen[k].setNumber();
			p1->setData1(Pen[k].getNumber()-1);
			p1->setData2(k);
			Pen[k].Pig[Pen[0].getNumber()-1]=*p1;
		}
		if(head==NULL) head=p1;
		else
			p2->next=p1;
		p2=p1;
	}
	return head;
}

void findPen(pigInf *p,int type){
	int min=10,data;
	if(type==0)
	{															//������ 
		for(int i=0;i<100;i++)
			if(Pen[i].getBlack()==1)										//���к���Ȧ���� 
				if(Pen[i].getNumber()<=min)
				{								//��¼����Ȧ���������ٵ���Ȧ��ź��������� 
					min=Pen[i].getNumber();
					data=i;
					
				}		
		if(min==10)															//minΪ10��ʾ�������еĺ���Ȧ���� 
			for(int j=0;j<100;j++)											//�ҵ�һ������Ȧ 
				if(Pen[j].getNumber()==0)
				{
					Pen[j].setBlack(1);										//��ɺ���Ȧ 
					Pen[j].setNumber();										//���ú��� ���Ӹ���Ȧ������Ŀ 
					Pen[j].Pig[0]=*p;										//�ø���Ȧ�ĵ�һͷ������ͷ���� 
					p->setData1(0);											//�����������Ϣ 
					p->setData2(j);
				}
		else
		{
			Pen[data].setNumber();											//min��Ϊ10 �ҵ�������Ŀ���ٵ�δ������Ȧ ������Ŀ���� 
			Pen[data].Pig[Pen[data].getNumber()-1]=*p;						//����Ȧ������һͷ�� 
			p->setData1(Pen[data].getNumber()-1);							//����������Ϣ 
			p->setData1(data);
		}
	}
	else
	{
		for(int i=0;i<100;i++)
			if(Pen[i].getBlack()==0)										//ԭ��ͬ������ķ��� �ı���Ȧ�������� 
				if(Pen[i].getNumber()<=min)
				{
					min=Pen[i].getNumber();
					data=i;
				}		
		if(min==10)
			for(int j=0;j<100;j++)
				if(Pen[j].getNumber()==0)
				{
					Pen[j].setNumber();
					Pen[j].Pig[0]=*p;
					p->setData1(0);
					p->setData2(j);
				}
		else
		{
			Pen[data].setNumber();
			Pen[data].Pig[Pen[data].getNumber()-1]=*p;
			p->setData1(Pen[data].getNumber()-1);
			p->setData1(data);
		}
	}
}

pigInf* sellPig(pigInf *&head){										//ÿ�������£�Ĭ��һ������ʮ��,һ��360�죩
	pigInf *p,*p1,*p2,*p3,*p4; 
	if(head==NULL){
		cout<<"����������"<<endl;
		return head;
	}
	if(head->getTime()>=12||head->getWeight()>=75){
			if(head->getType()==0){
				balance+=b*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  ���ۺ���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			} 
			else if(head->getType()==1){
				balance+=f*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  ����С����һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			}
			else{
				balance+=w*head->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<head->getYear()<<'.'<<head->getMonth()<<'.'<<head->getDay()<<"  ���۴�׻���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
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
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ���ۺ���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			} 
			else if(p1->getType()==1){
				balance+=f*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ����С����һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			}
			else{
				balance+=w*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ���۴�׻���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
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
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ���ۺ���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			} 
			else if(p1->getType()==1){
				balance+=f*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ����С����һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			}
			else{
				balance+=w*p1->getWeight();
				freopen("pig_output.txt","a",stdout);
				cout<<p1->getYear()<<'.'<<p1->getMonth()<<'.'<<p1->getDay()<<"  ���۴�׻���һֻ"<<endl;
				freopen("CON","w",stdout);
				cout.clear();
			}
			delete p1;
		}
	}																//�ر��ļ� 
	for(int i=0;i<100;i++) Pen[i].setPen();							//������Ȧ
	cout<<"Done Successful!"<<endl; 
	for(int i=0;i<10;i++){
		cout<<"Done Successful!"<<endl;
		p3=head;
		while(p3->next!=NULL)
			p3=p3->next;
		p3=p3->next;
		p4=new pigInf;
		p4->setInf();
		p3->next=p4;
		cout<<"Done Successful!"<<endl;
		p4->next=NULL;
		cout<<"Done Successful!"<<endl;
		findPen(p4,p4->getType());
	}
	cout<<"Done Successful!"<<endl;
	return head;
}

void searchPen(int n,pigInf *&head){								//��ѯ��Ȧ��Ϣ nΪ��Ȧ��� correct
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
	cout<<"��Ȧ�й���"<<Pen[n].getNumber()<<"ֻ����"<<endl;
	cout<<"����"<<blackNumber<<"ֻ��"<<endl;
	cout<<"С����"<<flowerNumber<<"ֻ��"<<endl;
	cout<<"�󻨰���"<<whiteNumber<<"ֻ��"<<endl; 
}

void searchPig(int m,int n,pigInf *&head){							//��ѯ�������Ϣ״̬ mΪ��Ȧ��� nΪ������ correct ����״�� 
	pigInf *p=head;
	while(p->next!=NULL){
		if(p->getData1()==n&&p->getData2()==m){
			cout<<m<<"����Ȧ��"<<n<<"����������£�"<<endl;
			cout<<"Ʒ�֣�"<<p->stringType()<<endl;;
			cout<<"���أ�"<<p->getWeight()<<"kg"<<endl;
			cout<<"��Ȧ���ڣ�"<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<endl;
		}	
		p=p->next;
	}
	if(p->next==NULL){
		if(p->getData1()==n&&p->getData2()==m){
			cout<<m<<"����Ȧ��"<<n<<"����������£�"<<endl;
			cout<<"Ʒ�֣�"<<p->stringType()<<endl;;
			cout<<"���أ�"<<p->getWeight()<<"kg"<<endl;
			cout<<"��Ȧ���ڣ�"<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<endl;
		}
	}
}

void countPig(int s,pigInf *&head){								//ͳ��ÿ������ĳɳ���� 
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
			if(p->getTime()<=30) t1++;
			else if(p->getTime()>=90) t3++;
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
			if(p->getTime()<=30) t1++;
			else if(p->getTime()>=90) t3++;
			else t2++;
		}
	} 
	avrw=weight/num;
	cout<<"��Ʒ�ֵ����ѯ������£�"<<endl;
	cout<<"������"<<num<<endl;
	cout<<"ƽ�����أ�"<<avrw<<"kg"<<endl;
	cout<<"���طֲ���(kg)"<<endl;
	cout<<setw(5)<<"20-35"<<'\t'<<setw(5)<<"35-55"<<'\t'<<setw(5)<<"55+"<<endl;
	cout<<setw(5)<<w1<<'\t'<<setw(5)<<w2<<'\t'<<setw(5)<<w3<<endl;
	cout<<setw(5)<<"1������"<<'\t'<<setw(5)<<"1-3����"<<'\t'<<setw(5)<<"3��������"<<endl;
	cout<<setw(5)<<t1<<'\t'<<setw(5)<<t2<<'\t'<<setw(5)<<t3<<endl;
}

void searchRecord_input(pigInf *&head){												//��ѯ��5�깺���¼ ������ ϣ������Ȧ�Ⱥ�show�� ��д�ļ� correct
	pigInf *p=head;
	while(p->next!=NULL){
		if(p->getType()==0){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �������һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear(); 
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �������һֻ"<<endl;
		}	
		else if(p->getType()==1){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  ����С����һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  ����С����һֻ"<<endl;
		}	
		else{
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �����׻���һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �����׻���һֻ"<<endl;
		}	
			p=p->next;
	}
	if(p->next==NULL){
		if(p->getType()==0){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �������һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �������һֻ"<<endl;
		}
		else if(p->getType()==1){
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  ����С����һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  ����С����һֻ"<<endl;
		}
		else{
			freopen("pig_input.txt","a",stdout);
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �����׻���һֻ"<<endl;
			freopen("CON","w",stdout);
			cout.clear();
			cout<<p->getYear()<<'.'<<p->getMonth()<<'.'<<p->getDay()<<"  �����׻���һֻ"<<endl;
		}		
	}
}

void readTxt(string file)
{
    ifstream infile; 
    infile.open(file.data());									 //���ļ����������ļ��������� 
    assert(infile.is_open());  									 //��ʧ��,�����������Ϣ,����ֹ�������� 

    string s;
    while(getline(infile,s))
    {
        cout<<s<<endl;
    }
    infile.close();          													  	//�ر��ļ������� 
}

void searchRecord_output(pigInf *&head)
{
	readTxt("pig_output.txt");														//�������� ifs.open("pig_output.txt",ios::in);												//���ļ����ļ�·��/�ļ������򿪷�ʽ/���ļ��� 
	
}

int pigNum(pigInf *&head){															//������������� 
	int num=0;
	pigInf *p=head;
	while(p->next!=NULL){
		num++;
		p=p->next;
	}
	num++;
	return num;
}

void spreadVirus(pigInf *&head){													//ģ������ 
	pigInf *p=head;
	int num=pigNum(head);
	srand(time(NULL));
	int n=rand()%num;
	for(int i=0;i<n;i++)
		p=p->next;
	int virus;																		//�������� 
	int illTime=0;																	//�������� 
	int m=1;																		//�ò���������� 
	int sum=pigNum(head);															//Ŀǰ��������� 
	int x=p->getData2();
	int y=p->getData1();															//���һֻ���������� ��Ȧû������������� 
	Pen[x].Pig[y].setHealth(1);														//����ֻ��Ľ���״���޸�Ϊ���� 
	Pen[x].setFlag(1);
	illTime++;																		//��һֻ��ò�Ϊ��һ�� 
	cout<<x<<"����Ȧ��"<<Pen[x].Pig[y].getData1()<<"������Ⱦ������"<<endl;
	while(m!=sum){
		for(int i=0;i<100;i++){
			if(Pen[i].getFlag()==1){
				for(int j=0;j<Pen[i].getNumber();j++){
					virus=rand()%100+1;
					if(virus<=50){
						Pen[i].Pig[j].setHealth(1);
						m++;
					}
				}
					
				if(i-1>=0){
					for(int j=0;j<Pen[i-1].getNumber();j++){
						virus=rand()%100+1;
						if(virus<=15){
							Pen[i-1].Pig[j].setHealth(1);
							m++;
						}
					}	
				}
				if(i+1>=99){
					for(int j=0;j<Pen[i+1].getNumber();j++){
						virus=rand()%100+1;
						if(virus<=15){
							Pen[i+1].Pig[j].setHealth(1);
							m++;
						}
					}
				}
			}
		}
		illTime++;
	}
	cout<<illTime<<"�����������Ⱦ������"<<endl;
}

void growPig(pigInf *&head){														//����ÿ������ ���þ����ϴε�½�����Ĵ��� ��ʱ���� 
	srand(time(NULL));
	double g=(rand()%13)/10.0;
	int deta;
	pigInf *p=head;
	for(p=head;p->next!=NULL;p=p->next){
		deta=p->getTime();
		p->addWeight(deta*g);
	}
	if(p->next==NULL){
		deta=p->getTime();
		p->addWeight(deta*g);
	}
}

void pushButton(int button,pigInf *head){
	int button0,button1;
	string button2;
	switch(button){
		case 1:
			cout<<"������Ȧ��ţ�";
			cin>>button0;
			cout<<endl;
			searchPen(button0,head);
		break;
		case 2:
			cout<<"������Ȧ��ţ�";
			cin>>button0;
			cout<<"���������ţ�";
			cin>>button1;
			cout<<endl;
			searchPig(button0,button1,head);
		break;
		case 3:
			cout<<"�����������ࣺ";													//����ĸ��д 
			cin>>button2;
			if(button2=="Black") countPig(0,head);
			else if(button2=="Flower") countPig(1,head);
			else countPig(2,head);
		break;
		case 4:
			cout<<"5���ڳ���/���������¼���£�"<<endl;
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
	cout<<"					   "<<"����ģ��"<<endl;
	cout<<endl;
	cout<<"					"<<"1.��ѯ��Ȧ��"<<endl;
	cout<<endl;
	cout<<"					"<<"2.��ѯ����"<<endl;
	cout<<endl;
	cout<<"					"<<"3.��ѯĳһ������"<<endl;
	cout<<endl;
	cout<<"					"<<"4.��ѯ����/�����¼��"<<endl;
	cout<<endl;
	cout<<"					"<<"5.����ģ��"<<endl;
	cout<<endl;
	cout<<"					"<<"6.��Ҳ�ѯ"<<endl;
	cout<<endl;
	cout<<"					"<<"7.�˳�"<<endl;
	cout<<endl;
	cout<<"                     ========================================================="<<endl;
}

int main(){	
	srand(time(NULL));	
	setPenNumber(Pen,100);
	pigInf* head=create();										//���������ͷָ�� 				
	while (1) {	
		menu();
		cout<<"������ɳ�������";
		cin>>Day;
		time1.setDate(Day);
		growPig(head);
		int d=Day/90;
		for(int i=0;i<d;i++) sellPig(head);
		cout<<"�����빦�ܱ�ţ�";
		int button;
		cin>>button;
		pushButton(button,head);
		if(balance>=50000) cout<<"Game Over!"<<endl;
	}
	return 0;
}
