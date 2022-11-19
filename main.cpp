#include <iostream>
#include <bits/stdc++.h>
#include <mysql.h>
#include <mysqld_error.h>

using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

char HOST[]="localhost";
char USER[]="root";
char PASS[]="root";

string generatePassword(int length) {
	string capitalLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string smallLetters = "abcdefghijklmnopqrstuvwxyz";
	string numbers = "1234567890";
	string special = "!@#$%^&*_=+-/.?<>)";

	//All the characters at our disposal for password generation.
	string values = capitalLetters + smallLetters + numbers + special;

	//Resultant password string.
	string password = "";

	// srand() sets the seed which is used by rand to generate “random” numbers.
	// If we don’t call srand before our first call to rand, it’s as if you had called srand(1) to set the seed to one.
	// In short, srand() — Set Seed for rand() Function.
	srand(time(0));

	//Taking out characters at random index to form the password.
	for (int i = 0; i < length; i++) {
		password.push_back(values[0 + rand() % values.size()]);
	}

	//Finally returning the generated password.
	return password;
}

int main() {
//	cout<<"hello";

//	cout<<pwd;
	
	MYSQL *obj;
	char Website[20];
	char Password[40];
	
	bool ProgramIsOpened=true;
	int answer; //to keep program opened
	
	char* consult;
	char* sentence;
	string QUERY;
	
	//CONNECTION
	
	if(!(obj=mysql_init(0))) {
		cout<<"ERROR: MYSQL OBJECT COULD NOT BE CREATED."<<endl;
	}
	else {
		if(!mysql_real_connect(obj,HOST,USER,PASS,"password",3306,NULL,0)) {
			cout<<"ERROR: SOME DATABASE INFORMATION IS WRONG OR DOES NOT EXIST."<<endl;
			cout<<mysql_error(obj)<<endl;
		}
		else {
			cout<<"SUCCESSFULLY LOGGED IN."<<endl;
			cout<<"----WELCOME TO PASSWORD MANAGER----"<<endl;
		}

		while(ProgramIsOpened) {
			
			char option;
			cout<<"[A] ADD PASSWORD"<<endl;
			cout<<"[B] FETCH PASSWORD"<<endl;
			cout<<"[C] DELETE PASSWORD"<<endl;
			cin>>option;
				
			if(option=='a' || option=='A') {
				
				cout<<"Enter Website Name: ";
//				cin.getline(Website,20,'\n');
				cin>>Website;
				
				cout<<"Enter Required Length of the Password (Less than 32): ";
				int len;
				cin>>len;
				cin.ignore(100,'\n'); //Clean buffer after using cin for int,float and double.
				
				char* pwd1;
				int notHappy=1;
				while(notHappy) {
					string pwd=generatePassword(len);
					pwd1=new char[pwd.length()+1];
					strcpy(pwd1,pwd.c_str());
					
					cout<<"Your Password: "<<pwd<<endl;
					cout<<"Are you Happy with your Password? Press Y for YES and N for NO ";
					
					char choice;
					cin>>choice;
					
					if(choice=='Y' || choice == 'y') {
						notHappy=0;
					}
				}
				 //copy string pwd to char*
	//			sprintf()
				
					
				cout<<endl;
				
				//SETTING UPDATE
				QUERY="INSERT INTO password(Website,Password) VALUES('%s','%s')";
				sentence=new char[QUERY.length()+1];
				strcpy(sentence,QUERY.c_str()); //copy string stmt to char*
				consult=new char[strlen(sentence)+strlen(Website)+strlen(pwd1)];
				sprintf(consult,sentence,Website,pwd1); //substitutes %d %s etc.....
				
				if(mysql_ping(obj)) {
					cout<<"ERROR: IMPOSSIBLE TO CONNECT"<<endl;
					cout<<mysql_error(obj)<<endl;
				}
				
				if(mysql_query(obj,consult)) {
					cout<<"ERROR: "<<mysql_error(obj)<<endl;
					rewind(stdin);
					getchar();
				}
				else {
					cout<<"WEBSITE AND PASSWORD ADDED CORRECTLY."<<endl;
				}
				mysql_store_result(obj);
//				cout<<endl<<"Add Another Password? "<<endl;
//				cout<<"[1]: YES"<<endl;
//				cout<<"[0]: NO"<<endl;
//				cout<<"ANSWER: "<<endl;
//				cin>>answer;
//				cin.ignore(100,'\n');
//				if(answer==0) {
//					ProgramIsOpened=false;
//				}
				cout<<endl;
			}
			
			else if(option=='b'|| option=='B') {
				cout<<"Fetch"<<endl;
			}
			
			else if(option=='c'|| option=='C') {
				cout<<"Delete"<<endl;
			}
			
			
		}
	}
	cout<<"Thank you for using our app."<<endl;
	
	return 0;
}
