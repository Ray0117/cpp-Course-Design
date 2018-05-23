#include <iostream> 
#include <cstring> 
#include <fstream> 
#include <stdlib.h>
using namespace std;

//------------------�������ඨ�壺Book -----------------------------------------

class bookList;

class Book				//����
{
	char bookNo[15];	    //���
	char bookName[10];	//����
	int  Num;			//����
public:
	Book(char *bNo=NULL, char *bNa=NULL, int n=0);	//���캯��������������ȱʡֵ
	void Show();									//��ʾһ��ͼ����Ϣ
	void print(ofstream &out);				    //��һ��ͼ����Ϣд�������ļ�
	void setInfo(char *nop, char *nap, int n);		//����һ��ͼ����Ϣ
	void setNum(int n);							//�����������ͼ��������
	int  getNum();								//��ȡ�������ͼ��������
	friend class bookList;						//��bookList��˵��Ϊ��Ԫ�ࡣ
    //����										//������Ҫ��ӹ��к����ӿڡ��� 
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

void Book::setNum(int n)	//�����������ͼ��������
{
	Num=n;
}

int Book::getNum()		//��ȡ�������ͼ��������
{
	return Num;
}

//-----------�������ඨ�壺bookList-----------------------------------------------------

class bookList				//�����
{
	Book *Books;					//ͼ�����Ա���ָ��
	int curLen;						//����ͼ��������
	int maxLen;						//ͼ�����������
public:
	bookList(int Len=20);			//���캯������ʼ�����
	~ bookList ( ); 				//�����������ͷ����ռ�
	
	void appendBook(char *nop,char *nap, int n);	//׷��һ��ͼ��
	int isIn(char *bkNo);			//����Ų���ͼ�飬�����ڣ��������±ꣻ���򷵻�-1
	Book & getBooks(int i);			//�����±�Ϊi��ͼ����������
	void deleteBook(char * bkNo);	//ɾ��ָ����ŵ�ͼ��
	void sortBooks();				//����Źؼ����ų�����
	void showAll( );				//��ʾȫ��ͼ��
	int  curBookLen( );				//��������ͼ��������	
	void setCurBookLen(int len);	//��������ͼ��������
	void initBookList();			//���ļ�bookdata.txt�ж���ȫ����Ϣ�������Books�ṹ
	void readFromFile(char *filename);//�Ӳ���ָ���ļ��ж������е�ͼ��
	void writeToFile(char *filename);//����������������ͼ��д�����ָ���ļ���
	void reverseBookList();			 //ͼ�����¼����
};

bookList::bookList(int Len)  //���캯������ʼ�����
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

bookList::~ bookList ( ) 		//�����������ͷ����ռ�		
{
	if(Books) delete []Books;
}


void bookList::appendBook(char *nop,char *nap, int n)	//��׷��һ��ͼ��//completed
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


int bookList::isIn(char *bkNo)  //����Ų���ͼ�飬�����ڣ��������±ꣻ���򷵻�-1//completed
{
	for (int i = 0; i < curLen; i++)
		if (!strcmp(bkNo, Books[i].bookNo))
			return i;

	return -1;
}


Book & bookList::getBooks(int i)	//�����±�Ϊi��ͼ����������//completed		
{
	return Books[i];
}

void bookList::deleteBook(char * bkNo) //ɾ��ָ����ŵ�ͼ��//completed
{
	for (int i = 0; i < curLen; i++)
		Books[i] = Books[i + 1];

	setCurBookLen(curLen - 1);
}

void bookList::sortBooks()		//����Źؼ����ų�����		//completed//completed
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

void bookList::showAll()	 //��ʾȫ��ͼ��			//completed
{
	cout << curLen << endl;

	for (int i = 0; i < curLen; i++)
		Books[i].Show();
}

int bookList::curBookLen( )	//��������ͼ��������		//completed	
{
	return curLen;
}

void bookList::setCurBookLen(int len) //��������ͼ��������//completed
{
	curLen = len;
}


void bookList::initBookList()	//���ļ�bookdata.txt�ж���ȫ����Ϣ�������Books�ṹ//completed
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

void bookList::readFromFile(char *filename)		//�Ӳ���ָ���ļ��ж������е�ͼ��	//completed
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

void bookList::writeToFile(char *filename)     //����������������ͼ��д�����ָ���ļ���//completed
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
//-----------�������������У�ÿ���˵�ѡ������Ķ���-----------------------------------------------------

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
		cout << "�����û�д���" << endl;
	else
	{
		cout << "ȷ��ɾ����y/n ?" << endl;
		cin >> ans;
		if (ans == 'y')
			booksObj.deleteBook(No);
	}
}

void showAll(bookList &booksObj)//completed
{
	if (booksObj.curBookLen() == 0)
		cout << "�����û��ͼ��" << endl;
	else
		booksObj.showAll();
}

void query(bookList &booksObj)//completed
{
	char No[15];
	cout << "��������ţ�" << endl;
	cin >> No;
	if (booksObj.isIn(No) == -1)
		cout << "�����û�д˱�ͼ��" << endl;
	else
		cout << "��������Ȿ��" << endl;
		booksObj.getBooks(booksObj.isIn(No)).Show();
}

void addBooks(bookList &booksObj)//completed
{
	char No[15];
	int  N, i;
	i = booksObj.isIn(No);
	cout << "��������ţ�" << endl;
	cin >> No;
	if (booksObj.isIn(No) == -1)
		cout << "�����û�д˱�ͼ��" << endl;
	else
		cout << "�������������" << endl;
		cin >> N;	
		booksObj.getBooks(i).setNum(booksObj.getBooks(i).getNum() + N);
}		

void sellBooks(bookList &booksObj)//completed
{
	char No[15];
	int  N, i;
	cout << "��������ż�����������" << endl;
	cin >> No >> N;
	i = booksObj.isIn(No);
	if (i == -1)
		cout << "�����û�д˱�ͼ��" << endl;
	else 
	{
		if (N > booksObj.getBooks(i).getNum())
			cout << "��治�㣡" << endl;
		else
			booksObj.getBooks(i).setNum(booksObj.getBooks(i).getNum() - N);
	}
}


void appendFromTxtFile(bookList &booksObj)//completed
{
	char filename[40];
	cout << "�������ļ�·��" << endl;
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
	cout << "ȷ��ȫ��ɾ����y/n ?" << endl;
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

	cout<<"ȷ���˳���y/n: "; 
	cin>>ans;
	if(ans=='y')
		booksObj.writeToFile("bookdata.txt");
	return ans;
}

//-----------�������������Լ��˵������Ķ���-----------------------------------------------------

int menu_select( ); //��������

void main()  
{ 

	bookList booksObj; //����ͼ���¼����
	int sel;

	// booksObj.initBookList();  //�˺���Ҫ��ɵ����񣬿����������캯���� 

	for( ; ; )
	{
		switch(sel=menu_select()) 
		{
		   case 1: cout << "������һ�������Ϣ����� ���� �������� " << endl; 
			       appendRecord(booksObj);
			       system("pause");break;
		   case 2: cout << "������Ҫɾ������� : " << endl;
			        delRecord(booksObj); 
			       system("pause");break;
		   case 3: cout << "" << endl;
			       showAll(booksObj); 
			       system("pause");break;
		   case 4: cout << "��������ţ� " << endl;
			       query(booksObj);
			       system("pause");break;
		   case 5: cout << "��������ż���������� " << endl;
			       addBooks(booksObj); 
			       system("pause");break;
		   case 6: cout << "��������ż����������� " << endl;
			       sellBooks(booksObj); 
		           system("pause");break;
		   case 7: cout << "�����뵼���ļ�·��: " << endl;
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

int menu_select( ) // �˵�ʵ��
{
	char *menu[ ]={
				"   1.	����ͼ���¼",
				"   2.	ɾ��ͼ���¼",
				"   3.	��ʾ����ͼ���¼",
				"   4.	��ѯͼ��",
				"   5.	ͼ�����",
				"   6.	ͼ������",
				"   7.	��������ͼ���¼",
				"   8.	����ͼ���¼",
				"   9.	���������",
				"  10.	ɾ��ȫ��ͼ���¼",
				"  11.  ͼ�����¼����",
				"   0.	�˳�",
				NULL
				};

	int choice;

	do {
		system("cls");          //  ����   
		cout<<"\n\n ==============ͼ���¼����============== \n\n";
		for(int i=0; menu[i]; i++)
			cout<<menu[i]<<endl;
		cout<<"\n ======================================= \n";

		cout<<"������ѡ��";
		cin>>choice;
	} while(choice<0 || choice>11);

	return(choice);
}
