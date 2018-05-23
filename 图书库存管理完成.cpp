#include <iostream> 
#include <cstring> 
#include <fstream> 
#include <stdlib.h>
using namespace std;

//------------------以下是类定义：Book -----------------------------------------

class bookList;

class Book				//书类
{
	char bookNo[15];	    //书号
	char bookName[10];	//书名
	int  Num;			//数量
public:
	Book(char *bNo=NULL, char *bNa=NULL, int n=0);	//构造函数，各参数均有缺省值
	void Show();									//显示一本图书信息
	void print(ofstream &out);				    //将一本图书信息写入数据文件
	void setInfo(char *nop, char *nap, int n);		//设置一本图书信息
	void setNum(int n);							//设置书库现有图书种类数
	int  getNum();								//获取书库现有图书种类数
	friend class bookList;						//将bookList类说明为友元类。
    //……										//根据需要添加公有函数接口…… 
};

Book::Book(char *bNo, char *bNa, int n)
{
	if(bNo)
		strcpy(bookNo, bNo);
	else
		bookNo[0]='\0';
	if(bNa)
		strcpy(bookName, bNa);
	else
		bookName[0]='\0';

	Num=n;
}

void Book::Show()
{
	cout<<bookNo<<'\t'<<bookName<<'\t'<<Num<<endl;
}

void Book::print(ofstream &out)
{
	out<<bookNo<<'\t'<<bookName<<'\t'<<Num<<endl;
}

void Book::setInfo(char *nop, char *nap, int n)
{
	strcpy(bookNo, nop);
	strcpy(bookName, nap);
	Num=n;
}

void Book::setNum(int n)	//设置书库现有图书种类数
{
	Num=n;
}

int Book::getNum()		//获取书库现有图书种类数
{
	return Num;
}

//-----------以下是类定义：bookList-----------------------------------------------------

class bookList				//书库类
{
	Book *Books;					//图书线性表首指针
	int curLen;						//现有图书种类数
	int maxLen;						//图书最大种类数
public:
	bookList(int Len=20);			//构造函数，初始化书库
	~ bookList ( ); 				//析构函数，释放书库空间
	
	void appendBook(char *nop,char *nap, int n);	//追加一种图书
	int isIn(char *bkNo);			//按书号查找图书，若存在，返回其下标；否则返回-1
	Book & getBooks(int i);			//返回下标为i的图书对象的引用
	void deleteBook(char * bkNo);	//删除指定书号的图书
	void sortBooks();				//按书号关键字排成升序
	void showAll( );				//显示全部图书
	int  curBookLen( );				//返回现有图书种类数	
	void setCurBookLen(int len);	//设置现有图书种类数
	void initBookList();			//从文件bookdata.txt中读入全部信息存入书库Books结构
	void readFromFile(char *filename);//从参数指定文件中读入所有的图书
	void writeToFile(char *filename);//将书库中所有种类的图书写入参数指定文件中
	void reverseBookList();			 //图书库存记录逆序
};

bookList::bookList(int Len)  //构造函数，初始化书库
{
	maxLen = Len;
	curLen = 0;

	if (Len)
	{
		Books = new Book[Len];
		bookList::initBookList();
	}
	else
		Books = NULL;
}

bookList::~ bookList ( ) 		//析构函数，释放书库空间		
{
	if(Books) delete []Books;
}


void bookList::appendBook(char *nop,char *nap, int n)	//将追加一本图书//completed
{
	if (curLen == maxLen)
	{
		Book *newptr;
		newptr = new Book[maxLen + 10];
		for (int i = 0; i < curLen; i++)
			newptr[i] = Books[i];
		delete[]Books;
		maxLen += 10;
		Books = newptr;
	}
	if (isIn(nop) == -1)
	{
		Books[curLen].setInfo(nop, nap, n);
		curLen++;
		cout << "sucessful" << endl;
	}
	else
		Books[isIn(nop)].setInfo(nop, nap, n);
}


int bookList::isIn(char *bkNo)  //按书号查找图书，若存在，返回其下标；否则返回-1//completed
{
	for (int i = 0; i < curLen; i++)
		if (!strcmp(bkNo, Books[i].bookNo))
			return i;

	return -1;
}


Book & bookList::getBooks(int i)	//返回下标为i的图书对象的引用//completed		
{
	return Books[i];
}

void bookList::deleteBook(char * bkNo) //删除指定书号的图书//completed
{
	for (int i = 0; i < curLen; i++)
		Books[i] = Books[i + 1];

	setCurBookLen(curLen - 1);
}

void bookList::sortBooks()		//按书号关键字排成升序		//completed//completed
{
	Book t;
	int p, j;

	for (int i = 0; i < curLen - 1; i++)
	{
		p = i;
		for (j = i + 1; j < curLen; j++)
			if (strcmp(Books[j].bookNo, Books[p].bookNo) < 0)
				p = j;
		if (p != i)
		{
			t = Books[i];
			Books[i] = Books[p];
			Books[p] = t;
		}
	}
}

void bookList::showAll()	 //显示全部图书			//completed
{
	cout << curLen << endl;

	for (int i = 0; i < curLen; i++)
		Books[i].Show();
}

int bookList::curBookLen( )	//返回现有图书种类数		//completed	
{
	return curLen;
}

void bookList::setCurBookLen(int len) //设置现有图书种类数//completed
{
	curLen = len;
}


void bookList::initBookList()	//从文件bookdata.txt中读入全部信息存入书库Books结构//completed
{
	char data[40] = "g:\\bookdata.txt";
	ifstream infile;
	infile.open(data);
	if (infile)
	{
		infile.close();
		readFromFile(data);
	}
}

void bookList::readFromFile(char *filename)		//从参数指定文件中读入所有的图书	//completed
{
	int tNum, Num;
	char no[20], name[20];
	ifstream infile;
	infile.open(filename);
	if (!infile)
	{
		cout << "Cannot open file:" << filename << endl;
		exit(1);
	}
	infile >> tNum;
	for (int i = 0; i < tNum; i++)
	{
		infile >> no >> name >> Num;
		appendBook(no, name, Num);
	}
}

void bookList::writeToFile(char *filename)     //将书库中所有种类的图书写入参数指定文件中//completed
{
	ofstream outfile;
	outfile.open(filename);
	if (!outfile)
	{
		cout << "Cannot creat file:" << filename << endl;
		exit(1);
	}

		outfile << curBookLen() << endl;
		for (int i = 0; i < curLen; i++)
			Books[i].print(outfile);
	outfile.close();
}

void bookList::reverseBookList()//need change
{
	Book t;

	for (int i = 0; i < curLen/2; i++)
	{
		t = Books[i];
		Books[i] = Books[curLen - i];
		Books[curLen - i] = t;
	}
}
//-----------以下是主函数中，每个菜单选项处理函数的定义-----------------------------------------------------

void appendRecord(bookList &booksObj)//completed
{
	char no[15];
	char na[10];
	int n = 0;
	cin >> no >> na >> n;
	booksObj.appendBook(no, na, n);
}


void delRecord(bookList &booksObj)//completed
{
	char ans, No[15];
	cin >> No;
	if (booksObj.isIn(No) == -1)
		cout << "书库中没有此书" << endl;
	else
	{
		cout << "确定删除吗？y/n ?" << endl;
		cin >> ans;
		if (ans == 'y')
			booksObj.deleteBook(No);
	}
}

void showAll(bookList &booksObj)//completed
{
	if (booksObj.curBookLen() == 0)
		cout << "书库中没有图书" << endl;
	else
		booksObj.showAll();
}

void query(bookList &booksObj)//completed
{
	char No[15];
	cout << "请输入书号：" << endl;
	cin >> No;
	if (booksObj.isIn(No) == -1)
		cout << "书库中没有此本图书" << endl;
	else
		cout << "书库中有这本书" << endl;
		booksObj.getBooks(booksObj.isIn(No)).Show();
}

void addBooks(bookList &booksObj)//completed
{
	char No[15];
	int  N, i;
	i = booksObj.isIn(No);
	cout << "请输入书号：" << endl;
	cin >> No;
	if (booksObj.isIn(No) == -1)
		cout << "书库中没有此本图书" << endl;
	else
		cout << "请输入入库数量" << endl;
		cin >> N;	
		booksObj.getBooks(i).setNum(booksObj.getBooks(i).getNum() + N);
}		

void sellBooks(bookList &booksObj)//completed
{
	char No[15];
	int  N, i;
	cout << "请输入书号及销售数量：" << endl;
	cin >> No >> N;
	i = booksObj.isIn(No);
	if (i == -1)
		cout << "书库中没有此本图书" << endl;
	else 
	{
		if (N > booksObj.getBooks(i).getNum())
			cout << "库存不足！" << endl;
		else
			booksObj.getBooks(i).setNum(booksObj.getBooks(i).getNum() - N);
	}
}


void appendFromTxtFile(bookList &booksObj)//completed
{
	char filename[40];
	cout << "请输入文件路径" << endl;
	cin >> filename;
	booksObj.readFromFile(filename);
}

void writeToTxtFile(bookList &booksObj)//completed
{
	char filename[80];
	cin >> filename;
	booksObj.writeToFile(filename);
}


void sortByNo(bookList &booksObj)//completed
{
	booksObj.sortBooks();
	cout << "successful" << endl;
}

void delAll(bookList &booksObj)//completed
{
	char ans;
	cout << "确定全部删除吗？y/n ?" << endl;
	cin >> ans;
	if (ans == 'y')
		booksObj.setCurBookLen(0);
}

void reverseBooks(bookList &booksObj)//completed
{
	booksObj.reverseBookList();
}

char Quit(bookList &booksObj)//completed
{
	char ans;

	cout<<"确定退出？y/n: "; 
	cin>>ans;
	if(ans=='y')
		booksObj.writeToFile("bookdata.txt");
	return ans;
}

//-----------以下是主函数以及菜单函数的定义-----------------------------------------------------

int menu_select( ); //函数声明

void main()  
{ 

	bookList booksObj; //定义图书记录对象
	int sel;

	// booksObj.initBookList();  //此函数要完成的任务，可以做到构造函数中 

	for( ; ; )
	{
		switch(sel=menu_select()) 
		{
		   case 1: cout << "请输入一本书的信息（书号 书名 数量）： " << endl; 
			       appendRecord(booksObj);
			       system("pause");break;
		   case 2: cout << "请输入要删除的书号 : " << endl;
			        delRecord(booksObj); 
			       system("pause");break;
		   case 3: cout << "" << endl;
			       showAll(booksObj); 
			       system("pause");break;
		   case 4: cout << "请输入书号： " << endl;
			       query(booksObj);
			       system("pause");break;
		   case 5: cout << "请输入书号及入库数量： " << endl;
			       addBooks(booksObj); 
			       system("pause");break;
		   case 6: cout << "请输入书号及销售数量： " << endl;
			       sellBooks(booksObj); 
		           system("pause");break;
		   case 7: cout << "请输入导入文件路径: " << endl;
			       appendFromTxtFile(booksObj); 
			       system("pause");break;
		   case 8: cout << "function 8 " << endl;
			       writeToTxtFile(booksObj); 
			       system("pause");break;
		   case 9: cout << " " << endl;
			       sortByNo(booksObj);
			       system("pause");break;
		   case 10:cout << " " << endl; 
			       delAll(booksObj); 
			       system("pause");break;
		   case 11:cout << " " << endl;
				   reverseBooks(booksObj);
				   system("pause"); break;
		   case 0: if(Quit(booksObj)!='y')  continue;
		}

		if(sel==0)	break;  
	}
}

int menu_select( ) // 菜单实现
{
	char *menu[ ]={
				"   1.	增加图书记录",
				"   2.	删除图书记录",
				"   3.	显示所有图书记录",
				"   4.	查询图书",
				"   5.	图书入库",
				"   6.	图书销售",
				"   7.	批量导入图书记录",
				"   8.	导出图书记录",
				"   9.	按书号排序",
				"  10.	删除全部图书记录",
				"  11.  图书库存记录逆序",
				"   0.	退出",
				NULL
				};

	int choice;

	do {
		system("cls");          //  清屏   
		cout<<"\n\n ==============图书记录管理============== \n\n";
		for(int i=0; menu[i]; i++)
			cout<<menu[i]<<endl;
		cout<<"\n ======================================= \n";

		cout<<"请输入选择：";
		cin>>choice;
	} while(choice<0 || choice>11);

	return(choice);
}
