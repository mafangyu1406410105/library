// tushuguanli.cpp : Defines the entry point for the console application.
//
#include <string>//�ַ���ͷ�ļ�
#include <fstream>//�ļ�ͷ�ļ�
#include <iostream>//��ָ��׼���������������ͷ�ļ�, cout�Ͷ��������ͷ�ļ���
using namespace std;//ʹ�����ֿռ�std
const int BMAX=50;   //��������

//ͼ�����ģ��

//ͼ����
class book
{
public:
	int no;                                      //ͼ����
	char name[20];                               //ͼ������
	int b_flag;                                  //1Ϊ�ڼܣ�2Ϊ���
	int b_del;                                   //1Ϊ����, 2Ϊɾ��
public :
	book(){}                               //���캯��
	void setno(int n)
	{
		no=n;                             //ͼ����ȡֵ
	}
	int getno()
	{
		return no;           //����ͼ����ֵ
	}
	void setname(char na[])
	{
		strcpy(name, na);   //�ַ�������
	}
	char* getname()
	{
		return name;  //����ͼ������
	}
	void borbook()
	{
		b_flag=2;     //�����־
	}
	void delbook()
	{
		b_del=2;   //ɾ����־
	}
	void addbook(int no,char na[])    //����ͼ�鹦��
	{
		setno(no);
		setname(na);
		b_flag=1;
		b_del=1;
	}
}
;
//ͼ�����ݿ���

class bdatabase
{
	public:
	book btarray[BMAX];                                         //ͼ�鼯��
	int top;
	public:
		bdatabase()
		{
			
			book b; 
			top=-1; 
			fstream file("book.txt",ios::in);    //���ļ�
			while (1) 
			{ 
			file.read((char *)&b,sizeof(b)); 
			if (!file) break; 
			top++; 
			btarray[top] = b; 
			} 
			file.close(); 			 //�ر��ļ�
		}

		~bdatabase()                      //����������    ��btarray[]д��book.txt�ļ��� 
		{ 
			fstream file("book.txt",ios::out); 
			for (int i=0;i<=top;i++)
			{
				if (btarray[i].b_del==1) 
					file.write((char *)&btarray[i],sizeof(btarray[i])); 
			}
			file.close(); 
		} 

		void addbooks()                                     //��ͼ�����ݿ��м�ͼ��
		{
			book bk;
			int no;
			char bname[20];
			cout<<"���������: ";
			cin>>no;
			cout<<endl<<"����������: ";
			cin>>bname;
			cout<<endl;
			bk.b_flag=1;
			bk.addbook(no, bname);
			top++;
			btarray[top]=bk;
			return;
		}

		int findbooks(int suffix)        //����ͼ�飬����������ڽ������������suffix�������±�
		{
			int no;
			cout<<"���������: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(btarray[i].no==no && btarray[i].b_del==1)
				{				
					return i;
				}
			}
			return -1;
		}

		int findbooks()                                //����ͼ��,�����������ͼ��ά��  
		{
			int no;
			char value[6];
			cout<<"���������: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(btarray[i].no==no && btarray[i].b_del==1)
				{
					if(btarray[i].b_flag==1) strcpy(value,"�ڼ�");
					if(btarray[i].b_flag==2) strcpy(value,"���");
					cout<<"���: "<<btarray[i].no<<" �������: "<<btarray[i].name<<" ͼ��״̬ :"<<value<<endl;
					return i;
				}
			}
			return -1;
		}

		void editbooks()                                          //�༭ͼ��
		{		
			int cur;			
			cur = findbooks();
			if (cur==-1)
			{	cout<<"û���Ȿ��"<<endl;
				return;
			}
			cout<<"���: "<<btarray[cur].no<<" �������: "<<btarray[cur].name<<endl;
			cout<<"���޸����ݣ�"<<endl;		
			cout<<endl<<"�������: ";
			cin>>btarray[cur].name;
			return ;
		}

		void delbooks()                                             //ɾ��ͼ��
		{
			int cur;		
			cur = findbooks();
			if (cur==-1)
			{
				return;
			}
			if(btarray[cur].b_flag==2)                              //ɾ��ʱ�ж�ͼ���Ƿ���
			{
				cout<<"��ͼ���Ѿ���������ڹ黹����ɾ����"<<endl;
				return;
			}
			btarray[cur].b_del=2;
			return;
		}

		void listbooks()                                             //��ʾȫ��ͼ��
		{
			char value[6];
			for(int i=0; i<=top; i++)
			{
			
				if(btarray[i].b_del==1)
				{
			        if(btarray[i].b_flag==1) strcpy(value,"�ڼ�");
					if(btarray[i].b_flag==2) strcpy(value,"���");
					cout<<"���: "<<btarray[i].no<<" �������: "<<btarray[i].name<<" ͼ��״̬ :"<<value<<endl;
				}
			}
			return;
		}
}
;
//���߹���ģ��
//������
class reader
{
	public:
	int no;
	char name[20];
	int r_del;  //1���ڣ�2ɾ��
	int r_bor;  //1����飬2û�н���
	book brbook;
	public:
	void addreader(int id, char na[])//���Ӷ���
	{	
		no = id;
		strcpy(name, na);
		r_del=1;		
	}
	void setbrbook(book bt)  //���ý�����
	{
		brbook = bt;
	}

	book getbrbook()
	{
		return brbook;   //���ؽ�����Ϣ
	}
};
//�������ݿ���
class rdatabase
{
	public:
	reader rdarray[BMAX];
	int top;

	public:
		rdatabase()
		{
			reader rd; 
			top=-1; 
			fstream file("reader.txt",ios::in); //���ļ�
			while (1) 
			{ 
			file.read((char *)&rd,sizeof(rd)); 
			if (!file) break; 
			top++; 
			rdarray[top]=rd;
			} 
			file.close(); 	//�ر��ļ�		 
		}
		
		~rdatabase()//��������
		{ 
			fstream file("reader.txt",ios::out); 
			for (int i=0;i<=top;i++)
			{
				if (rdarray[i].r_del==1) 
					file.write((char *)&rdarray[i],sizeof(rdarray[i])); 
			}
			file.close(); 
		}

	

		void addreaders()                                            //��Ӷ���
		{
			reader rd;
			int no;
			char rname[20];
			cout<<"������ѧ��: ";
			cin>>no;
			cout<<endl<<"����������: ";
			cin>>rname;
			cout<<endl;
			rd.addreader(no, rname);
			rd.r_bor=2;
			top++;
 			rdarray[top]=rd;
			return;
		}
		int findreaders(int suffix)     //���Ҷ��ߣ�����������ڽ��黹������� ����suffix�������±�
		{
			int no;
			cout<<"������ѧ��: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(rdarray[i].no==no && rdarray[i].r_del==1)
				{
					return i;
				}
			}
			return -1;

		}
		int findreaders()                              //���Ҷ��ߣ�����������ڶ���ά������
		{
			int no;
			char value[3];
			cout<<"������ѧ��: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(rdarray[i].no==no && rdarray[i].r_del==1)
				{
					if(rdarray[i].r_bor==1) strcpy(value,"��");
					if(rdarray[i].r_bor==2) strcpy(value,"��");
					cout<<"ѧ��: "<<rdarray[i].no<<" ����: "<<rdarray[i].name<<" �Ƿ����: "<<value<<endl;
					return i;
				}
			}
			return -1;
		}
		void editreaders()                                            //�༭������Ϣ
		{
					
			int cur;			
			cur = findreaders();
			if (cur==-1)
			{	cout<<"û�и�ѧ��"<<endl;
				return;
			}			
			cout<<"���޸����ݣ�"<<endl;		
			cout<<endl<<" ����: ";
			cin>>rdarray[cur].name;
			return ;
		}
		void delreaders()                            //ɾ�����ߣ������������Ҫ��������ɾ��
		{ 
			int cur;		
			cur = findreaders();
			if (cur==-1)
			{
				return;
			}
			if(rdarray[cur].r_bor==1)
			{
				cout<<"���û�����ͼ�飬�뻹�����ɾ��"<<endl;
				return;
			}
			rdarray[cur].r_del=2;
			return;
		}
		void listreaders()                                                 //��ʾ���ж���
		{
			char value[3];
			for(int i=0; i<=top; i++)
			{
			
				if(rdarray[i].r_del==1)
				{
					if(rdarray[i].r_bor==1) strcpy(value,"��");
					if(rdarray[i].r_bor==2) strcpy(value,"��");
					cout<<"ѧ��: "<<rdarray[i].no<<" ����: "<<rdarray[i].name<<" �Ƿ����: "<<value<<endl;
				}		
			}
			return;
		}


}
;

void bookjiemain()                                                     //ͼ��ά���Ӳ˵�
{
	cout<<"|---------------------|"<<endl;
	cout<<"|    ͼ��ά��         |"<<endl;
	cout<<"|   (1)�� ��          |"<<endl;
	cout<<"|   (2)�� ��          |"<<endl;
	cout<<"|   (3)ɾ ��          |"<<endl;
	cout<<"|   (4)�� ��          |"<<endl;
	cout<<"|   (5)�� ʾ          |"<<endl;
	cout<<"|   (6)������һ��     |"<<endl;
	cout<<"|---------------------|"<<endl;
}

void readerjiemian()                                                       //����ά���Ӳ˵�
{
	cout<<"|---------------------|"<<endl;
	cout<<"|    ����ά��         |"<<endl;
	cout<<"|   (1)�� ��          |"<<endl;
	cout<<"|   (2)�� ��          |"<<endl;
	cout<<"|   (3)ɾ ��          |"<<endl;
	cout<<"|   (4)�� ��          |"<<endl;
	cout<<"|   (5)�� ʾ          |"<<endl;
	cout<<"|   (6)������һ��     |"<<endl;
	cout<<"|---------------------|"<<endl;
}

void mainjiemian()                                                               //������
{	
	cout<<"***********************************************"<<endl;
	cout<<"*               ͼ �� �� �� ϵ ͳ             *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (1) �� ��                     *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (2) �� ��                     *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (3) ͼ�����                  *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (4) �û�����                  *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (0) �� ��                     *"<<endl;
	cout<<"***********************************************"<<endl;
}

void borrowtoreturn(char br) 
//���黹�麯��.����br�����ж��ǡ����顱���ǡ����顱.1Ϊ�����顱,2Ϊ�����顱
{
	int rdid=0;
	int bkid=0;
	int rsuffix, bsuffix;
	bdatabase t_bd;
	rdatabase t_rd;
	if(br=='1')           //����
	{
		rsuffix=t_rd.findreaders(rdid);
		bsuffix=t_bd.findbooks(bkid);
		if (rsuffix==-1 || bsuffix==-1) 
			return;
		if(t_bd.btarray[bsuffix].b_flag==2)
		{
			cout<<"ͼ���Ѿ��������ѡ������ͼ��"<<endl;
			return;
		}
		if(t_rd.rdarray[rsuffix].r_bor==1)
		{
			cout<<"���Ѿ����ͼ�飬���ȹ黹�ٽ�����ͼ��"<<endl;
			return;
		}
		t_bd.btarray[bsuffix].b_flag=2;
		t_rd.rdarray[rsuffix].r_bor=1;
		t_rd.rdarray[rsuffix].brbook=t_bd.btarray[bsuffix];
		return;

	}
	if(br=='2')
	{		
		rsuffix=t_rd.findreaders(rdid);
		bsuffix=t_bd.findbooks(bkid);
		if (rsuffix==-1 || bsuffix==-1 )
			return;
		
		if(t_rd.rdarray[rsuffix].brbook.no==t_bd.btarray[bsuffix].no)
		{
			t_bd.btarray[bsuffix].b_flag=1;
			t_rd.rdarray[rsuffix].r_bor=2;
			t_rd.rdarray[rsuffix].brbook=t_bd.btarray[bsuffix];
		}
		else
		{
			cout<<"���������룬���߽��ͼ��Ų���ȷ"<<endl;
			return;
		}
		return;
	}
}

void booksmange()
{
    char in;	
	bdatabase  bd;
	do{
		bookjiemain();
		cin>>in;
		switch (in)
		{
		case '1':
			bd.addbooks();
			break;
		case '2':
			bd.editbooks();
			break;
		case '3':
			bd.delbooks();
			break;
		case '4':
			bd.findbooks();
			break;
		case '5':
			bd.listbooks();
			break;
		case '6':			
			break;
		default:cout<<"���������������롣"<<endl;; 
		}
	}while(in!='6');
	return;
}

void readersmange()
{
    char in;
	rdatabase  bd;
	do{
		readerjiemian();
		cin>>in;
		switch (in)
		{
		case '1':
			bd.addreaders();
			break;
		case '2':
			bd.editreaders();
			break;
		case '3':
			bd.delreaders();
			break;
		case '4':
			bd.findreaders();
			break;
		case '5':
			bd.listreaders();
			break;
		case '6':			
			break;
		default:cout<<"���������������롣"<<endl; 
		}
	}while(in!='6');
	return;

}


int main(int argc, char* argv[])
{	char in;
	do{
		mainjiemian();
		cin>>in;
		switch (in)
		{
		case '1':
			borrowtoreturn(in);
			break;
		case '2':
			borrowtoreturn(in);
			break;
		case '3':
			booksmange();
			break;
		case '4':
			readersmange();
			break;
		case '0':
			break;
		default:cout<<"���������������롣"<<endl; 
		}
	}while(in!='0');
	return 0;
}
