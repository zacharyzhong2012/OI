#include <bits/stdc++.h>
#include <windows.h>
#include <direct.h>
#include <conio.h>
using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState (VK_NONAME)&0x8000)? 1: 0)

mt19937 rnd(time(0));
POINT p;
HANDLE hstdin=GetStdHandle (STD_INPUT_HANDLE);
HANDLE hstdout=GetStdHandle (STD_OUTPUT_HANDLE);
COORD coord={0,0};
HWND h=GetForegroundWindow ();
CONSOLE_FONT_INFO consolecurrentfont;
int flg,x,y,usernum,nowuser,trt,pp;
int man[110][110];
int blood[15]={0,700,330,360,390,420,450,480,510,540,600};
int speed[15]={0,240,260,220,260,280,240,280,300,260,320};//B<R<A
int bull[15] ={0, 80, 60,100,100, 80,120,120,100,140,150};//A<R<B
int cati[15] ={0, 60, 70, 80, 50, 60, 70, 40, 50, 60, 35};//R<A<B
int dmg[15]  ={0,  5,  7, 10, 10, 14, 20, 15, 21, 30, 40};//R<A<B
int cst[4]={0,1,2,30};
int dx[8]={1,-1,0,1,-1,0,1,-1},dy[8]={1,1,1,-1,-1,-1,0,0};
int farr[4]={0,4,7,4};
int barr[4]={4,0,4,7};
char cmd[110],dead[60][110];
string mp[110][110];
string adminpassword;
string opts,gn[15]={"","R-1","A-1","B-1","R-2","A-2","B-2","R-3","A-3","B-3","RAB"};
string opti[6]={"","$","子弹","板砖","牢大（按 [g] 喝）","蛮牛冲撞(按 [n] 创)"};
string optc[5]={"","子弹","板砖","牢大"};
bool f[1010],isrl,usebomb;
int bm[110][110];
struct Enemy {int px,py,gun,bld,guai;};
vector<Enemy> ene;
struct Bullet {int px,py,dirx,diry,sp,tim,rd,dmg,cjd;};
stack<Bullet> bul;
struct Block {int px,py;};
stack<Block> bri;
class Users {
private:
	string username,password;
	int px,py,bld,lv,gun,rb,ca,isadmin;
	int num[10];
public:
	void Read ();
	void Save ();
	void Clear ();
	void MakeNew (string name,string pass,int isadmin);
	void LogIn (int isadmin);
	void SignUp (int isadmin);
	int GetReady ();
	void Init ();
	void AddEnemy (int px,int py,int gun,int bld,int kuai);
	void Shot (int px,int py,int dirx,int diry,int sp,int tim,int rd,int dmg,int cjd);
	void AddBrick (int px,int py,int dmg);
	void Update ();
	void ShowMap ();
	void ShowBag ();
	void ShowShop ();
	void Dead ();
	void GameTime ();
} Us;
Users User[1010];

void Getxy () {
	GetCursorPos (&p);
	ScreenToClient (h,&p);
	GetCurrentConsoleFont (hstdout,FALSE,&consolecurrentfont);
	x=p.x/=consolecurrentfont.dwFontSize.X;
	y=p.y/=consolecurrentfont.dwFontSize.Y;
}

void gotoxy (int x,int y) {
	COORD c;
	c.X=x;
	c.Y=y;
	SetConsoleCursorPosition (hstdout,c);
}

void SetColorAndBackground (int ForgC,int BackC) {
	WORD wColor=((BackC&0x0F)<<4)+(ForgC&0x0F);
	SetConsoleTextAttribute (hstdout,wColor);
}

void Ready () {
	Us.Read ();
	system ("mode con cols=100 lines=50 | title CS2D");
	DWORD mode;
	GetConsoleMode (hstdin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode (hstdin,mode);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo (hstdout,&CursorInfo);
    CursorInfo.bVisible=false;
    SetConsoleCursorInfo (hstdout,&CursorInfo);
	MessageBox (0,"抵制不良游戏，拒绝盗版游戏。\n注意自我保护，谨防受骗上当。\n适度游戏益脑，沉迷游戏伤身。\n合理安排时间，享受健康生活。\n","健康游戏忠告",MB_OK);
}

bool check (char c) {
	return (c>='0'&&c<='9')||(c>='A'&&c<='Z')||(c>='a'&&c<='z');
}

void Users::Read () {
	if (_access ("D:\\CS2D",0)==-1)
		_mkdir ("D:\\CS2D");
	fstream file;
	file.open ("D:\\CS2D\\save.txt");
	if (!file) {
		ofstream ofile ("D:\\CS2D\\save.txt");
		if (ofile)
			ofile.close ();
	}
	ifstream ifile;
	ifile.open ("D:\\CS2D\\save.txt",ios::in);
	for (int i=0;!ifile.eof();i++) {
		ifile>> User[i].username;
		ifile>> User[i].password;
		ifile>> User[i].px;
		ifile>> User[i].py;
		ifile>> User[i].bld;
		ifile>> User[i].lv;
		ifile>> User[i].gun;
		ifile>> User[i].rb;
		ifile>> User[i].ca;
		ifile>> User[i].isadmin;
		for (int j=1;j<=4;j++)
			ifile>> User[i].num[j];
		usernum++;
	}
	usernum--;
	ifile.close ();
}

void Users::Save () {
	ofstream ofile;
	ofile.open ("D:\\CS2D\\save.txt",ios::out);
	for (int i=0;i<usernum;i++) {
		if (!f[i]) {
			ofile<< User[i].username<< " ";
			ofile<< User[i].password<< " ";
			ofile<< User[i].px<< " ";
			ofile<< User[i].py<< " ";
			ofile<< User[i].bld<< " ";
			ofile<< User[i].lv<< " ";
			ofile<< User[i].gun<< " ";
			ofile<< User[i].rb<< " ";
			ofile<< User[i].ca<< " ";
			ofile<< User[i].isadmin<< " ";
			for (int j=1;j<=4;j++)
				ofile<< User[i].num[j]<< " ";
			ofile<< "\n";
		}
	}
	ofile.close ();
}

void Users::Clear () {
	for (int i=0;i<usernum;i++)
		f[i]=!User[i].isadmin;
}

void Users::MakeNew (string name,string pass,int isadmin) {
	User[usernum].username=name;
	User[usernum].password=pass;
	User[usernum].px=51;
	User[usernum].py=51;
	User[usernum].lv=1;
	User[usernum].bld=blood[1];
	User[usernum].gun=1;
	User[usernum].rb=bull[1];
	User[usernum].ca=0;
	User[usernum].isadmin=isadmin;
	User[usernum].num[1]=10;
	User[usernum].num[2]=1000;
	User[usernum].num[3]=100;
	User[usernum].num[4]=10;
	User[usernum].num[5]=5;
	nowuser=usernum++;
}

void Users::LogIn (int isadmin) {
	while (1) {
		string name,pass;
		char c;
		bool look=0;
		printf ("请输入您的用户名与密码。\n");
		printf ("用户名：");
		while (c=_getch ()) {
			if (c=='\r'||c==27) break;
			if (c==8) {
				printf ("\b \b");
				if (name.size ())
					name.pop_back ();
			} else if (check (c)) {
				printf ("%c",c);
				name+=c;
			}
		}
		if (c==27) {
			system ("cls");
			return ;
		}
		puts ("");
		bool flag=0;
		for (int i=0;i<usernum;i++) {
			if (name==User[i].username&&!f[i]&&User[i].isadmin>=isadmin) {
				flag=1;
				nowuser=i;
				break;
			}
		}
		if (flag) printf ("用户名合法。\n");
		else {
			printf ("该用户尚未注册。\n");
			Sleep (1000);
			system ("cls");
			continue;
		}
		printf ("密码：\n");
		while (c=_getch ()) {
			if (c=='\r'||c==27) break;
			if (c==9) {
				if (!look) {
					look=1;
					for (int i=0;i<pass.size ();i++)
						printf ("\b \b");
					printf ("%s",pass.c_str ());
				} else {
					look=0;
					for (int i=0;i<pass.size ();i++)
						printf ("\b \b");
					for (int i=0;i<pass.size ();i++)
						printf ("*");
				}
			}
			if (c==8) {
				printf ("\b \b");
				if (pass.size ())
					pass.pop_back ();
			} else if (check (c)) {
				if (!look) printf ("*");
				else printf ("%c",c);
				pass+=c;
			}
		}
		for (int i=0;i<pass.size ();i++)
			printf ("\b \b");
		for (int i=0;i<pass.size ();i++)
			printf ("*");
		if (c==27) {
			system ("cls");
			return ;
		}
		puts ("");
		if (pass==User[nowuser].password) {
			printf ("登录成功！\n");
			Sleep (1000);
			system ("cls");
			flg=isadmin+1;
			break;
		} else {
			printf ("密码错误！\n");
			Sleep (1000);
			system ("cls");
			continue;
		}
	}
}

void Users::SignUp (int isadmin) {
	while (1) {
		string name,passfi,passse;
		char c;
		bool look=0;
		printf ("请输入您的用户名与密码。\n");
		printf ("用户名（1 至 114514 个字符）：");
		while (c=_getch ()) {
			if (c=='\r'||c==27) break;
			if (c==8) {
				printf ("\b \b");
				if (name.size ())
					name.pop_back ();
			} else if (check (c)) {
				printf ("%c",c);
				name+=c;
			}
		}
		if (c==27) {
			system ("cls");
			return ;
		}
		puts ("");
		if (name.size ()>114514) {
			printf ("该用户名不合法。\n");
			Sleep (1000);
			system ("cls");
			continue;
		}
		bool flag=0;
		for (int i=0;i<usernum;i++) {
			if (name==User[i].username&&!f[i]) {
				flag=1;
				break;
			}
		}
		if (flag) {
			printf ("\n");
			Sleep (1000);
			system ("cls");
			continue;
		} else printf ("用户名合法\n");
		printf ("密码（1 至 1919810 个字符）：\n");
		while (c=_getch ()) {
			if (c=='\r'||c==27) break;
			if (c==9) {
				if (!look) {
					look=1;
					for (int i=0;i<passfi.size ();i++)
						printf ("\b \b");
					printf ("%s",passfi.c_str ());
				} else {
					look=0;
					for (int i=0;i<passfi.size ();i++)
						printf ("\b \b");
					for (int i=0;i<passfi.size ();i++)
						printf ("*");
				}
			}
			if (c==8) {
				printf ("\b \b");
				if (passfi.size ())
					passfi.pop_back ();
			} else if (check (c)) {
				if (!look) printf ("*");
				else printf ("%c",c);
				passfi+=c;
			}
		}
		for (int i=0;i<passfi.size ();i++)
			printf ("\b \b");
		for (int i=0;i<passfi.size ();i++)
			printf ("*");
		if (c==27) {
			system ("cls");
			return ;
		}
		puts ("");
		if (passfi.size ()>1919810) {
			printf ("该密码不合法！\n");
			Sleep (1000);
			system ("cls");
			continue;
		}
		look=0;
		printf ("请再次输入您的密码：");
		while (c=_getch ()) {
			if (c=='\r'||c==27) break;
			if (c==9) {
				if (!look) {
					look=1;
					for (int i=0;i<passse.size ();i++)
						printf ("\b \b");
					printf ("%s",passse.c_str ());
				} else {
					look=0;
					for (int i=0;i<passse.size ();i++)
						printf ("\b \b");
					for (int i=0;i<passse.size ();i++)
						printf ("*");
				}
			}
			if (c==8) {
				printf ("\b \b");
				if (passse.size ())
					passse.pop_back ();
			} else if (check (c)) {
				if (!look) printf ("*");
				else printf ("%c",c);
				passse+=c;
			}
		}
		for (int i=0;i<passse.size ();i++)
			printf ("\b \b");
		for (int i=0;i<passse.size ();i++)
			printf ("*");
		if (c==27) {
			system ("cls");
			return ;
		}
		puts ("");
		if (passfi==passse) {
			Us.MakeNew (name,passfi,isadmin);
			printf ("注册成功！\n");
			Sleep (1000);
			system ("cls");
			break;
		} else {
			printf ("两次输入的密码不一样！\n");
			Sleep (1000);
			system ("cls");
			continue;
		}
	}
}

int Users::GetReady () {
	flg=0;
	while (flg!=1) {
		printf ("1.登录\n2.注册\n3.游客登陆\n4.帮助\n5.关机（这可不是个玩笑！）\n6.管理员设置\n7.结束\n");
		char opt;
		while (opt=_getch ()) {
			system ("cls");
			switch (opt) {
				case '1': {
					Us.LogIn (0);
					break;
				}
				case '2': {
					Us.SignUp (0);
					break;
				}
				case '3': {
					MakeNew ("Guest","Guest",0);
					f[nowuser]=1;
					flg=1;
					break;
				}
				case '4': {
					MessageBox (0,"按 [w][a][s][d] 移动。\n按 [i][j][k][l] 发射子弹。\n按 [t][f][g][h] 放置板砖。\n按 [u] 换弹。\n按 [y] 换枪。\n按 [o] 使用炸弹。\n按 [p] 打开背包。\n按 [q] 进入商店。\n按 [r] 打开帮助。","帮助",MB_OK);
					break;
				}
				case '5': {
					if (MessageBox (0,"您确定吗？\n","提示",MB_ICONASTERISK|MB_YESNO)==6) {
						int sec=rnd ()%60+1;
						printf ("好的！您的电脑将将会在 %d 秒后关机。\n",sec);
						sprintf (cmd,"shutdown -s -t %d",sec);
						system (cmd);
						Sleep (1000);
						system ("cls");
					} else {
						printf ("好的！\n");
						Sleep (1000);
						system ("cls");
					}
					break;
				}
				case '6': {
					Us.LogIn (1);
					break;
				}
				case '7': {
					Us.Save ();
					printf ("感谢游玩，再见。\nFAQ:https://note.ms/cs2dfaq\n");
					return 0;
					break;
				}
				default: {
					printf ("输入不合法！\n");
					Sleep (1000);
					system ("cls");
					break;
				}
			}
			if (flg!=0) break;
			printf ("1.登录\n2.注册\n3.游客登陆\n4.帮助\n5.关机（这可不是个玩笑！）\n6.管理员设置\n7.结束\n");
		}
		if (flg==2) {
			printf ("1.清空用户\n2.注册用户\n3.退出管理员模式\n");
			while (opt=_getch ()) {
				system ("cls");
				switch (opt) {
					case '1': {
						printf ("好的！\n");
						Sleep (1000);
						system ("cls");
						Us.Clear ();
						break;
					}
					case '2': {
						Us.SignUp (1);
						break;
					}
					case '3': {
						printf ("好的！\n");
						Sleep (1000);
						system ("cls");
						flg=0;
						break;
					}
					default: {
						printf ("输入不合法！\n");
						Sleep (1000);
						system ("cls");
						break;
					}
				}
				if (flg==0) break;
				printf ("1.清空用户\n2.注册用户\n3.退出管理员模式\n");
			}
		}
	}
	printf ("您好，%s！\n这是 lh,lyht,ysh 开发的一款单机枪战游戏！\n",User[nowuser].username.c_str ());
	Sleep (1000);
	system ("cls");
	return 1;
}

void Users::AddEnemy (int px,int py,int gun,int bld,int guai) {
	ene.push_back ({px,py,gun,bld,guai});
	man[px][py]=ene.size ();
}

void Users::Shot (int px,int py,int dirx,int diry,int sp,int tim,int rd,int dmg,int cjd=0) {
	bul.push ({px,py,dirx,diry,sp,tim,rd,dmg,cjd});
}

void Users::AddBrick (int px,int py,int bld=1) {
	bm[px][py]=bld;
}

void Users::Init () {
	memset (man,0,sizeof (man));
	for (int i=1;i<=101;i++)
		for (int j=1;j<=101;j++)
			mp[i][j]="  ";
	srand(time(0)); 
	for (int i=ene.size ()+1;i<=4+User[nowuser].lv+rnd ()%6;i++)
		AddEnemy (rnd ()%101+1,rnd ()%101+1,rnd ()%User[nowuser].lv+1,20,rand()%3);
}

void Users::Update () {
	if (isrl) {
		User[nowuser].ca=(User[nowuser].ca+1)%cati[User[nowuser].gun];
		if (User[nowuser].ca==0) {
			User[nowuser].rb=min (bull[User[nowuser].gun],User[nowuser].num[2]);
			User[nowuser].num[2]=max (User[nowuser].num[2]-bull[User[nowuser].gun],0);
			isrl=0;
		}
	}
	if (usebomb) {
		trt=(trt+1)%1;
		if (trt==0) usebomb=0;
	}
	for (int i=1;i<=101;i++)
		for (int j=1;j<=101;j++)
			if (bm[i][j]==-1) mp[i][j]="¤";
			else if (!bm[i][j]) mp[i][j]="  ";
			else if (bm[i][j]==1) mp[i][j]="□";
			else if (bm[i][j]>1) mp[i][j]="■";
	srand(time(0));
	for (int i=0;i<ene.size ();i++) {
		int kx=abs (ene[i].px-User[nowuser].px),ky=abs (ene[i].py-User[nowuser].py);
		if(ene[i].guai==1)
		{
			if(rand()%50==9)
			{
				Shot (ene[i].px-1,ene[i].py-1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun],0);
				Shot (ene[i].px-1,ene[i].py,  -1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  -1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,-1,0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//上
				Shot (ene[i].px-1,ene[i].py-1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,1, 0, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//下
				Shot (ene[i].px-1,ene[i].py-1,0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py,  0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,0,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//左
				Shot (ene[i].px-1,ene[i].py-1,0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py,  0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,0, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//右
				Shot (ene[i].px-1,ene[i].py-1,-1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py,  -1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,-1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,-1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  -1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,-1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,-1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  -1,-1,speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//左上
				Shot (ene[i].px-1,ene[i].py-1,-1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py,  -1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,-1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,-1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  -1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,-1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  -1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,-1,1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//右上
				Shot (ene[i].px-1,ene[i].py-1,1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py,  1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,1,-1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				//左下
				Shot (ene[i].px-1,ene[i].py,  1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px-1,ene[i].py+1,1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py-1,1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py,  1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px,  ene[i].py+1,1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py-1,1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py,  1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
				Shot (ene[i].px+1,ene[i].py+1,1, 1, speed[ene[i].gun],0,0,dmg[ene[i].gun]);
			}
		} if(ene[i].guai==2)
		{
			if(rand()%10==3)
			{
				for(int e=0;e<8;++e)
				{
					Shot (ene[i].px+dx[e],ene[i].py+dy[e],dx[e],dy[e],speed[ene[i].gun]/3,0,0,dmg[ene[i].gun]);
				}
			}
		} 
		
		if (ene[i].bld>0)
		{
			if (rnd ()%100<(rnd ()%20+1)&&(kx+ky>15||(kx+ky<15&&rnd ()%100<(rnd ()%8+1))||(kx+ky<10&&rnd ()%100<(rnd ()%5+1))||(kx+ky<5&&rnd ()%100<(rnd ()%3+1)))) {
				if (kx>=ky) {
					if (ene[i].px<User[nowuser].px) {
						if (ene[i].px<101) {
							if (bm[ene[i].px+1][ene[i].py]) {
								bm[ene[i].px+1][ene[i].py]--;
							} else ene[i].px++;
						}
					} else {
						if (ene[i].px>1) {
							if (bm[ene[i].px-1][ene[i].py]) {
								bm[ene[i].px-1][ene[i].py]--;
							} else ene[i].px--;
						}
					}
				} else {
					if (ene[i].py<User[nowuser].py) {
						if (ene[i].py<101) {
							if (bm[ene[i].px][ene[i].py+1]) {
								bm[ene[i].px][ene[i].py+1]--;
							} else ene[i].py++;
						}
					} else {
						if (ene[i].py>1) {
							if (bm[ene[i].px][ene[i].py-1]) {
								bm[ene[i].px][ene[i].py-1]--;
							} else ene[i].py--;
						}
					}
				}
			} else if (rnd ()%100<(rnd ()%3+1)){
				if (kx==0) {
					if (ene[i].py<User[nowuser].py)
						Shot (ene[i].px,ene[i].py,0,1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
					else
						Shot (ene[i].px,ene[i].py,0,-1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
				} else if (ky==0) {
					if (ene[i].px<User[nowuser].px)
						Shot (ene[i].px,ene[i].py,1,0,rnd ()%40+180,0,0,dmg[ene[i].gun]);
					else
						Shot (ene[i].px,ene[i].py,-1,0,rnd ()%40+180,0,0,dmg[ene[i].gun]);
				} else {
					if (ene[i].px<User[nowuser].px&&ene[i].py<User[nowuser].py)
						Shot (ene[i].px,ene[i].py,1,1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
					else if (ene[i].px<User[nowuser].px&&ene[i].py>User[nowuser].py)
						Shot (ene[i].px,ene[i].py,1,-1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
					else if (ene[i].px>User[nowuser].px&&ene[i].py<User[nowuser].py)
						Shot (ene[i].px,ene[i].py,-1,1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
					else if (ene[i].px>User[nowuser].px&&ene[i].py>User[nowuser].py)
						Shot (ene[i].px,ene[i].py,-1,-1,rnd ()%40+180,0,0,dmg[ene[i].gun]);
				}
			}
		}
		man[ene[i].px][ene[i].py]=i+1;
	}
	stack<Bullet> bu;
	while (bul.size ()) {
		Bullet tot=bul.top ();
		bul.pop ();
		tot.tim+=tot.sp;
		bool pf=1;
		while (tot.tim>=(tot.rd+1)*125) {
			tot.rd++;
			if (tot.px+tot.dirx>0&&tot.px+tot.dirx<102&&tot.py+tot.diry>0&&tot.py+tot.diry<102) {
				tot.px+=tot.dirx;
				tot.py+=tot.diry;
				if (bm[tot.px][tot.py]>0) {
					bm[tot.px][tot.py]--;
					pf=tot.cjd;break;
				} else if (tot.px==User[nowuser].px&&tot.py==User[nowuser].py) {
					User[nowuser].bld-=tot.dmg;
					pf=tot.cjd;break;
				} else if (man[tot.px][tot.py]>0) {
					ene[man[tot.px][tot.py]-1].bld-=tot.dmg;
					if (ene[man[tot.px][tot.py]-1].bld<0) {
						User[nowuser].num[1]+=dmg[ene[man[tot.px][tot.py]-1].gun];
						ene.erase (ene.begin ()+man[tot.px][tot.py]-1);
						man[tot.px][tot.py]=0;
					}
					pf=tot.cjd;break;
				}
			} else pf=0;
		}
		if (pf) {
			if (!tot.dirx) {
				if (tot.diry>0) mp[tot.px][tot.py]="> ";
				else mp[tot.px][tot.py]="< ";
			} else if (!tot.diry) {
				if (tot.dirx>0) mp[tot.px][tot.py]="∨";
				else mp[tot.px][tot.py]="Λ";
			} else if (tot.dirx>0) {
				if (tot.diry>0) mp[tot.px][tot.py]="◢";
				else mp[tot.px][tot.py]="◣";
			} else {
				if (tot.diry>0) mp[tot.px][tot.py]="◥";
				else mp[tot.px][tot.py]="◤";
			}
			bu.push (tot);
		}
	}
	while (bu.size ()) {
		bul.push (bu.top ());
		bu.pop ();
	}
	for (int i=0;i<ene.size ();i++)
		mp[ene[i].px][ene[i].py]="○";
	mp[User[nowuser].px][User[nowuser].py]="●";
}

void Users::ShowMap () {
	int sx=max (User[nowuser].px-15,1),tx=min (sx+30,101);
	sx-=30-(tx-sx);
	int sy=max (User[nowuser].py-15,1),ty=min (sy+30,101);
	sy-=30-(ty-sy);
	for (int i=sx;i<=tx;i++,puts (""))
		for (int j=sy;j<=ty;j++)
			printf ("%s",mp[i][j].c_str ());
	gotoxy (62,0);
	printf ("X 坐标：%3d\n",User[nowuser].px);
	gotoxy (62,1);
	printf ("Y 坐标：%3d\n",User[nowuser].py);
	gotoxy (62,2);
	printf ("等级：%2d\n",User[nowuser].lv);
	gotoxy (62,3);
	printf ("血量：%4d\n",User[nowuser].bld);
	gotoxy (62,4);
	printf ("枪：%s\n",gn[User[nowuser].gun].c_str ());
	gotoxy (62,5);
	printf ("子弹速度：%3d\n",speed[User[nowuser].gun]);
	gotoxy (62,6);
	printf ("子弹伤害：%2d\n",dmg[User[nowuser].gun]);
	gotoxy (62,7);
	printf ("子弹数量：%3d\n",User[nowuser].rb);
	gotoxy (62,8);
	printf ("换弹时间：%3d\n",User[nowuser].ca);
}

void Users::ShowBag () {
	char opt;
	system ("cls");
	printf ("您的背包\n");
	int cur=0;
	for (int i=1;i<=4;i++)
		if (User[nowuser].num[i]!=0) {
			cur++;
			printf ("%s x %d\n",opti[i].c_str (),User[nowuser].num[i]);
		}
	if (cur==0) printf ("空空如也\n");
	while (opt=_getch ()) {
		switch (opt) {
			case 'g': {
				printf ("要喝几个？");
				int num;
				scanf ("%d",&num);
				if (User[nowuser].num[4]>=num) {
					if (User[nowuser].bld!=blood[User[nowuser].lv]) {
						User[nowuser].num[4]-=num;
						User[nowuser].bld=min (User[nowuser].bld+30*num,blood[User[nowuser].lv]);
						printf ("好的，您喝了 %d 个牢大，还剩 %d 个牢大，回血至 %d 点。",num,User[nowuser].num[4],User[nowuser].bld);
					} else printf ("血量已满，不要浪费！"); 
				} else printf ("您没有足够的牢大！"); 
				Sleep (1000);
				break;
			}
			case 27: {
				system ("cls");
				return ;
				break;
			}
		}
		system ("cls");
		printf ("您的背包\n");
		for (int i=1;i<=4;i++)
			if (User[nowuser].num[i]!=0) {
				cur++;
				printf ("%s x %d\n",opti[i].c_str (),User[nowuser].num[i]);
			}
		if (cur==0) printf ("空空如也");
		puts ("");
	}
}

void Users::ShowShop () {
	char opt;
	system ("cls");
	printf ("商店\n您还剩 %d $\n1.子弹（一份 1 $）\n2.板砖（一份 2 $）\n3.牢大（一份 30 $）\n一份十个\n",User[nowuser].num[1]);
	while (opt=_getch ()) {
		int typ=0;
		switch (opt) {
			case '1': typ=2;break;
			case '2': typ=3;break;
			case '3': typ=4;break;
			case 27: system ("cls");return ;break;
			default: printf ("没有这种商品！");break;
		}
		if (typ) {
			printf ("要多少份？（最多 1000 份）：");
			int num;
			scanf ("%d",&num);
			if (num < 0) printf("我并不觉得您可以卖东西。");
			else if (num<=1000) {
				if (User[nowuser].num[1]>=num*cst[typ-1]) {
					User[nowuser].num[1]-=num*cst[typ-1];
					User[nowuser].num[typ]+=num*10;
					printf ("商店\n您还剩 %d $\n1.子弹（一份 1 $）\n2.板砖（一份 2 $）\n3.牢大（一份 30 $）\n一份十个\n",User[nowuser].num[1]);
				} else printf ("您没有足够的 $！"); 
			} else printf ("单次购买最多 1000 份！");
		}
		Sleep (1000);
		system ("cls");
		printf ("商店\n您还剩 %d $\n1.子弹（一份 1 $）\n2.板砖（一份 2 $）\n3.牢大（一份 30 $）\n一份十个\n",User[nowuser].num[1]);
	}
}

void Users::Dead () {
	for (int i=1;i<=50;i++)
		for (int j=1;j<=100;j++)
			dead[i][j]=' ';
	dead[25][47]='Y';
	dead[25][48]='O';
	dead[25][49]='U';
	dead[25][51]='D';
	dead[25][52]='E';
	dead[25][53]='A';
	dead[25][54]='D';
	int go=rnd ()%11+45;
	for (int i=1;i<=go;i++) {
		if (_kbhit ())
			if (_getch ()==27)
				break;
		for (int j=1;j<=50;j++) {
			for (int k=1;k<=100;k++) {
				int rd=rnd ()%4;
				SetColorAndBackground (farr[rd],barr[rd]);
				printf ("%c",dead[j][k]);
			}
			if (j!=50) puts ("");
		}
		gotoxy (0,0);
	}
	system ("cls");
	User[nowuser].bld=blood[User[nowuser].lv];
	return ;
}

void Users::GameTime () {
	for(int i=1;i<=100;++i)
		for(int j=1;j<=100;++j)
		{
			if (rnd ()%8==1)
				AddBrick (i,j);
			else if(rnd ()%64==1)
			{
				for(int x=0;x<8;++x)
				for(int y=0;y<8;++y)
//				AddBrick (i+1,j,30);
//				AddBrick (i-1,j,30);
//				AddBrick (i,j-1,30);
//				AddBrick (i,j+1,30);
//				AddBrick (i+1,j+1,30);
//				AddBrick (i-1,j-1,30);
//				AddBrick (i+1,j-1,30);
//				AddBrick (i-1,j+1,30);
				AddBrick (i+dx[x],j+dy[y],30);
				AddBrick (i,j,-1);
			}
		}
	Init ();
	Update ();
	ShowMap ();
	usebomb=0;
	while (1) {
		gotoxy (0,0);
		Init ();
		auto tot=User[nowuser];
		if(bm[tot.px][tot.py]==-1)
		{
			system("cls");
			int k=rnd()%3;
			if(k==0)
			{
				cout<<"恭喜开到宝箱,无限子弹";
				User[nowuser].num[2]+=114514;
				bull[1]+=114514; 
			}
			if(k==1)
			{
				cout<<"恭喜开到宝箱,牢大 +6";
				User[nowuser].num[4]+=5;
			}
			if(k==2)
			{
				cout<<"恭喜开到宝箱,蛮牛冲撞 +3";
				User[nowuser].num[5]+=3;
			}
			Sleep(1000);
			bm[tot.px][tot.py]=0; 
            system("cls");
		}
		int x=User[nowuser].px,y=User[nowuser].py;
		if (_kbhit ()) {
			switch (_getch ()) {
				case 'w': {
					if(pp==1)
					{
						for (int i=max(x-20,1);i<=x;++i)
							for (int j=y-1;j<=y+1;++j)
								AddBrick (i,j,5);
						User[nowuser].px=max(x-20,1);
						pp=0;
						break;
					}
					if (User[nowuser].px>1&&bm[User[nowuser].px-1][User[nowuser].py]<=0)
						User[nowuser].px--;
					break;
				}
				case 'a':
				{
					if(pp==1)
					{
						for (int i=x-1;i<=x+1;++i)
							for (int j=max(y-20,1);j<=y;++j)
								AddBrick (i,j,5);
						User[nowuser].py=max(y-20,1);
						pp=0;
						break;
					}
					if (User[nowuser].py>1&&bm[User[nowuser].px][User[nowuser].py-1]<=0)
						User[nowuser].py--;	
					break;
				}
				case 's': {
					if(pp==1)
					{
						for (int i=x;i<=min(100,x+20);++i)
							for (int j=y-1;j<=y+1;++j)
								AddBrick (i,j,5);
						User[nowuser].px=min(100,x+20);
						pp=0;
						break;
					}
					if (User[nowuser].px<101&&bm[User[nowuser].px+1][User[nowuser].py]<=0)
						User[nowuser].px++;
					break;
				}
				case 'd': {
					if(pp==1)
					{
						for (int i=x-1;i<=x+1;++i)
							for (int j=y;j<=min(y+20,100);++j)
								AddBrick (i,j,5);
						User[nowuser].py=min(y+20,100);
						pp=0;
						break;
					}
					if (User[nowuser].py<101&&bm[User[nowuser].px][User[nowuser].py+1]<=0)
						User[nowuser].py++;
					break;
				}
				case 'i': {
					if (User[nowuser].px-1>0&&User[nowuser].rb!=0) {
						User[nowuser].rb--;
						Shot (User[nowuser].px,User[nowuser].py,-1,0,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]);
					}
					break;
				}
				case '0':
				{
//					if (User[nowuser].px+1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px+1][User[nowuser].py]) {
//						User[nowuser].num[3]--;
					int x=User[nowuser].px,y=User[nowuser].py;
					for(int i=x;i<=100;++i)
					for(int j=y-1;j<=y+1;++j)
					AddBrick (i,j,1);
					for(int i=1;i<=x;++i)
					for(int j=y-1;j<=y+1;++j)
					AddBrick (i,j,1);
					for(int i=x-1;i<=x+1;++i)
					for(int j=1;j<=100;++j)
					AddBrick (i,j,1);
					break;
				}
				case 'j': {
					if (User[nowuser].py-1>0&&User[nowuser].rb!=0) {
						User[nowuser].rb--;
						Shot (User[nowuser].px,User[nowuser].py,0,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]);
					}
					break;
				}
				case 'n': {
					pp=1;
//					system("cls");
//					cout<<"向哪边撞?";
//					char w;
//					cin>>w; 
//					int x=User[nowuser].px,y=User[nowuser].py;
//                    system("cls");
					break;
				}
				case 'k': {
					if (User[nowuser].px+1<102&&User[nowuser].rb!=0) {
						User[nowuser].rb--;
						Shot (User[nowuser].px,User[nowuser].py,1,0,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]);
					}
					break;
				}
				case 'l': {
					if (User[nowuser].py+1<102&&User[nowuser].rb!=0) {
						User[nowuser].rb--;
						Shot (User[nowuser].px,User[nowuser].py,0,1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]);
					}
					break;
				}
				case '1': {
					if (User[nowuser].px+1<101&&User[nowuser].py-1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px+1][User[nowuser].py-1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px+1,User[nowuser].py-1);
					}
					break;
				}
				case '2': {
					if (User[nowuser].px+1<101&&User[nowuser].num[3]&&!bm[User[nowuser].px+1][User[nowuser].py]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px+1,User[nowuser].py);
					}
					break;
				}
				case '3': {
					if (User[nowuser].px+1<101&&User[nowuser].py+1<101&&User[nowuser].num[3]&&!bm[User[nowuser].px+1][User[nowuser].py+1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px+1,User[nowuser].py+1);
					}
					break;
				}
				case '4': {
					if (User[nowuser].py-1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px][User[nowuser].py-1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px,User[nowuser].py-1);
					}
					break;
				}
				case '5': {
					if (User[nowuser].px+1<101&&User[nowuser].num[3]&&!bm[User[nowuser].px+1][User[nowuser].py]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px+1,User[nowuser].py);
					}
					break;
				}
				case '6': {
					if (User[nowuser].py+1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px][User[nowuser].py+1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px,User[nowuser].py+1);
					}
					break;
				}
				case '7': {
					if (User[nowuser].px-1>0&&User[nowuser].py-1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px-1][User[nowuser].py-1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px-1,User[nowuser].py-1);
					}
					break;
				}
				case '8': {
					if (User[nowuser].px-1>0&&User[nowuser].num[3]&&!bm[User[nowuser].px-1][User[nowuser].py]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px-1,User[nowuser].py);
					}
					break;
				}
				case '9': {
					if (User[nowuser].px-1>0&&User[nowuser].py+1<101&&User[nowuser].num[3]&&!bm[User[nowuser].px-1][User[nowuser].py+1]) {
						User[nowuser].num[3]--;
						AddBrick (User[nowuser].px-1,User[nowuser].py+1);
					}
					break;
				}
				case 'u': {
					isrl=1;
					break;
				}
				case 'y': {
					User[nowuser].gun=User[nowuser].gun+1>User[nowuser].lv? 1: User[nowuser].gun+1;
					User[nowuser].rb=0;
					break;
				}
				case 'o': {
					if (!usebomb&&User[nowuser].rb>=64) {
						usebomb=1;
						User[nowuser].rb-=64;
						Shot (User[nowuser].px-1,User[nowuser].py-1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  -1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  -1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,-1,0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//上
						Shot (User[nowuser].px-1,User[nowuser].py-1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,1, 0, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//下
						Shot (User[nowuser].px-1,User[nowuser].py-1,0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,0,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//左
						Shot (User[nowuser].px-1,User[nowuser].py-1,0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,0, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//右
						Shot (User[nowuser].px-1,User[nowuser].py-1,-1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  -1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,-1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,-1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  -1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,-1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,-1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  -1,-1,speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//左上
						Shot (User[nowuser].px-1,User[nowuser].py-1,-1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  -1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,-1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,-1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  -1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,-1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  -1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,-1,1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//右上
						Shot (User[nowuser].px-1,User[nowuser].py-1,1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py,  1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,1,-1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//左下
						Shot (User[nowuser].px-1,User[nowuser].py,  1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px-1,User[nowuser].py+1,1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py-1,1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py,  1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px,  User[nowuser].py+1,1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py-1,1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py,  1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						Shot (User[nowuser].px+1,User[nowuser].py+1,1, 1, speed[User[nowuser].gun],0,0,dmg[User[nowuser].gun]*10,1);
						//右下
					}
					break;
				}
				case 'p': {
					ShowBag ();
					break;
				}
				case 'q': {
					ShowShop ();
					break;
				}
				case 'r': {
					MessageBox (0,"按 [w][a][s][d] 移动。\n按 [i][j][k][l] 发射子弹。\n按 [t][f][g][h] 放置砖块。\n按 [u] 换弹。\n按 [y] 换枪。\n按 [o] 使用炸弹。\n按 [p] 打开背包。\n按 [q] 进入商店。\n按 [r] 打开帮助。","帮助",MB_OK);
					break;
				}
				case 27: {
					system ("cls");
					return ;
					break;
				}
			}
		}
		Update ();
		if (User[nowuser].bld<=0) {
			system ("cls");
			Dead ();
			return ;
		}
		ShowMap ();
	}
}

int main () {
	Ready ();
	while (Us.GetReady ())
		Us.GameTime ();
	Us.Save ();
	return 0;
}
