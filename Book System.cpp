// tushuguanli.cpp : Defines the entry point for the console application.
//
#include <string>//字符串头文件
#include <fstream>//文件头文件
#include <iostream>//是指标准库中输入输出流的头文件, cout就定义在这个头文件里
using namespace std;//使用名字空间std
const int BMAX=50;   //书最多个数

//图书管理模块

//图书类
class book
{
public:
	int no;                                      //图书编号
	char name[20];                               //图书名称
	int b_flag;                                  //1为在架，2为借出
	int b_del;                                   //1为存在, 2为删除
public :
	book(){}                               //构造函数
	void setno(int n)
	{
		no=n;                             //图书编号取值
	}
	int getno()
	{
		return no;           //返回图书编号值
	}
	void setname(char na[])
	{
		strcpy(name, na);   //字符串复制
	}
	char* getname()
	{
		return name;  //返回图书名称
	}
	void borbook()
	{
		b_flag=2;     //借书标志
	}
	void delbook()
	{
		b_del=2;   //删除标志
	}
	void addbook(int no,char na[])    //增加图书功能
	{
		setno(no);
		setname(na);
		b_flag=1;
		b_del=1;
	}
}
;
//图书数据库类

class bdatabase
{
	public:
	book btarray[BMAX];                                         //图书集合
	int top;
	public:
		bdatabase()
		{
			
			book b; 
			top=-1; 
			fstream file("book.txt",ios::in);    //打开文件
			while (1) 
			{ 
			file.read((char *)&b,sizeof(b)); 
			if (!file) break; 
			top++; 
			btarray[top] = b; 
			} 
			file.close(); 			 //关闭文件
		}

		~bdatabase()                      //析构函数，    将btarray[]写到book.txt文件中 
		{ 
			fstream file("book.txt",ios::out); 
			for (int i=0;i<=top;i++)
			{
				if (btarray[i].b_del==1) 
					file.write((char *)&btarray[i],sizeof(btarray[i])); 
			}
			file.close(); 
		} 

		void addbooks()                                     //往图书数据库中加图书
		{
			book bk;
			int no;
			char bname[20];
			cout<<"请输入书号: ";
			cin>>no;
			cout<<endl<<"请输入书名: ";
			cin>>bname;
			cout<<endl;
			bk.b_flag=1;
			bk.addbook(no, bname);
			top++;
			btarray[top]=bk;
			return;
		}

		int findbooks(int suffix)        //查找图书，这个函数用于借书这书操作，suffix是数组下标
		{
			int no;
			cout<<"请输入书号: ";
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

		int findbooks()                                //查找图书,这个函数用于图书维护  
		{
			int no;
			char value[6];
			cout<<"请输入书号: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(btarray[i].no==no && btarray[i].b_del==1)
				{
					if(btarray[i].b_flag==1) strcpy(value,"在架");
					if(btarray[i].b_flag==2) strcpy(value,"借出");
					cout<<"书号: "<<btarray[i].no<<" 书的名称: "<<btarray[i].name<<" 图书状态 :"<<value<<endl;
					return i;
				}
			}
			return -1;
		}

		void editbooks()                                          //编辑图书
		{		
			int cur;			
			cur = findbooks();
			if (cur==-1)
			{	cout<<"没有这本书"<<endl;
				return;
			}
			cout<<"书号: "<<btarray[cur].no<<" 书的名称: "<<btarray[cur].name<<endl;
			cout<<"请修改数据："<<endl;		
			cout<<endl<<"书的名称: ";
			cin>>btarray[cur].name;
			return ;
		}

		void delbooks()                                             //删除图书
		{
			int cur;		
			cur = findbooks();
			if (cur==-1)
			{
				return;
			}
			if(btarray[cur].b_flag==2)                              //删除时判断图书是否借出
			{
				cout<<"该图书已经借出，请在归还后再删除。"<<endl;
				return;
			}
			btarray[cur].b_del=2;
			return;
		}

		void listbooks()                                             //显示全部图书
		{
			char value[6];
			for(int i=0; i<=top; i++)
			{
			
				if(btarray[i].b_del==1)
				{
			        if(btarray[i].b_flag==1) strcpy(value,"在架");
					if(btarray[i].b_flag==2) strcpy(value,"借出");
					cout<<"书号: "<<btarray[i].no<<" 书的名称: "<<btarray[i].name<<" 图书状态 :"<<value<<endl;
				}
			}
			return;
		}
}
;
//读者管理模块
//读者类
class reader
{
	public:
	int no;
	char name[20];
	int r_del;  //1存在，2删除
	int r_bor;  //1借过书，2没有借书
	book brbook;
	public:
	void addreader(int id, char na[])//增加读者
	{	
		no = id;
		strcpy(name, na);
		r_del=1;		
	}
	void setbrbook(book bt)  //设置借书标记
	{
		brbook = bt;
	}

	book getbrbook()
	{
		return brbook;   //返回借书信息
	}
};
//读者数据库类
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
			fstream file("reader.txt",ios::in); //打开文件
			while (1) 
			{ 
			file.read((char *)&rd,sizeof(rd)); 
			if (!file) break; 
			top++; 
			rdarray[top]=rd;
			} 
			file.close(); 	//关闭文件		 
		}
		
		~rdatabase()//析构函数
		{ 
			fstream file("reader.txt",ios::out); 
			for (int i=0;i<=top;i++)
			{
				if (rdarray[i].r_del==1) 
					file.write((char *)&rdarray[i],sizeof(rdarray[i])); 
			}
			file.close(); 
		}

	

		void addreaders()                                            //添加读者
		{
			reader rd;
			int no;
			char rname[20];
			cout<<"请输入学号: ";
			cin>>no;
			cout<<endl<<"请输入姓名: ";
			cin>>rname;
			cout<<endl;
			rd.addreader(no, rname);
			rd.r_bor=2;
			top++;
 			rdarray[top]=rd;
			return;
		}
		int findreaders(int suffix)     //查找读者，这个函数用于借书还书操作。 参数suffix是数组下标
		{
			int no;
			cout<<"请输入学号: ";
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
		int findreaders()                              //查找读者，这个函数用于读者维护操作
		{
			int no;
			char value[3];
			cout<<"请输入学号: ";
			cin>>no;
			for(int i=0; i<=top; i++)
			{
				if(rdarray[i].no==no && rdarray[i].r_del==1)
				{
					if(rdarray[i].r_bor==1) strcpy(value,"借");
					if(rdarray[i].r_bor==2) strcpy(value,"无");
					cout<<"学号: "<<rdarray[i].no<<" 姓名: "<<rdarray[i].name<<" 是否借书: "<<value<<endl;
					return i;
				}
			}
			return -1;
		}
		void editreaders()                                            //编辑读者信息
		{
					
			int cur;			
			cur = findreaders();
			if (cur==-1)
			{	cout<<"没有该学生"<<endl;
				return;
			}			
			cout<<"请修改数据："<<endl;		
			cout<<endl<<" 姓名: ";
			cin>>rdarray[cur].name;
			return ;
		}
		void delreaders()                            //删除读者，读者如果借书要还书后才能删除
		{ 
			int cur;		
			cur = findreaders();
			if (cur==-1)
			{
				return;
			}
			if(rdarray[cur].r_bor==1)
			{
				cout<<"该用户借了图书，请还书后再删除"<<endl;
				return;
			}
			rdarray[cur].r_del=2;
			return;
		}
		void listreaders()                                                 //显示所有读者
		{
			char value[3];
			for(int i=0; i<=top; i++)
			{
			
				if(rdarray[i].r_del==1)
				{
					if(rdarray[i].r_bor==1) strcpy(value,"借");
					if(rdarray[i].r_bor==2) strcpy(value,"无");
					cout<<"学号: "<<rdarray[i].no<<" 姓名: "<<rdarray[i].name<<" 是否借书: "<<value<<endl;
				}		
			}
			return;
		}


}
;

void bookjiemain()                                                     //图书维护子菜单
{
	cout<<"|---------------------|"<<endl;
	cout<<"|    图书维护         |"<<endl;
	cout<<"|   (1)增 加          |"<<endl;
	cout<<"|   (2)更 改          |"<<endl;
	cout<<"|   (3)删 除          |"<<endl;
	cout<<"|   (4)查 找          |"<<endl;
	cout<<"|   (5)显 示          |"<<endl;
	cout<<"|   (6)返回上一层     |"<<endl;
	cout<<"|---------------------|"<<endl;
}

void readerjiemian()                                                       //读者维护子菜单
{
	cout<<"|---------------------|"<<endl;
	cout<<"|    读者维护         |"<<endl;
	cout<<"|   (1)增 加          |"<<endl;
	cout<<"|   (2)更 改          |"<<endl;
	cout<<"|   (3)删 除          |"<<endl;
	cout<<"|   (4)查 找          |"<<endl;
	cout<<"|   (5)显 示          |"<<endl;
	cout<<"|   (6)返回上一层     |"<<endl;
	cout<<"|---------------------|"<<endl;
}

void mainjiemian()                                                               //主界面
{	
	cout<<"***********************************************"<<endl;
	cout<<"*               图 书 管 理 系 统             *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (1) 借 书                     *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (2) 还 书                     *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (3) 图书管理                  *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (4) 用户管理                  *"<<endl;
	cout<<"*                                             *"<<endl;
	cout<<"*               (0) 退 出                     *"<<endl;
	cout<<"***********************************************"<<endl;
}

void borrowtoreturn(char br) 
//借书还书函数.参数br用来判断是“借书”还是“还书”.1为“借书”,2为“还书”
{
	int rdid=0;
	int bkid=0;
	int rsuffix, bsuffix;
	bdatabase t_bd;
	rdatabase t_rd;
	if(br=='1')           //借书
	{
		rsuffix=t_rd.findreaders(rdid);
		bsuffix=t_bd.findbooks(bkid);
		if (rsuffix==-1 || bsuffix==-1) 
			return;
		if(t_bd.btarray[bsuffix].b_flag==2)
		{
			cout<<"图书已经借出，请选择其它图书"<<endl;
			return;
		}
		if(t_rd.rdarray[rsuffix].r_bor==1)
		{
			cout<<"你已经借过图书，请先归还再借其它图书"<<endl;
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
			cout<<"请重新输入，读者借的图书号不正确"<<endl;
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
		default:cout<<"输入错误，请从新输入。"<<endl;; 
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
		default:cout<<"输入错误，请从新输入。"<<endl; 
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
		default:cout<<"输入错误，请从新输入。"<<endl; 
		}
	}while(in!='0');
	return 0;
}
