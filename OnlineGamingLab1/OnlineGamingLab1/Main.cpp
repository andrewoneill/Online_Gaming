#include <WinSock2.h>
#include "Net.h"
#include <string.h>

#include <iostream>
using namespace std;
void playerA(Net*);
void playerB(Net*);
int main(){
	Net* n = new Net();
	n->initialise();

	string input;
	cin >> input;

	if(input == "a"){
		playerA(n);
	}
	else if(input == "b"){
		playerB(n);
	}
	system("PAUSE");
}

void playerA(Net* n){
	n->setupUDP(28000, "149.153.102.51");//set to work with mine and my partners pc
	cout << n->getOurIP() << "    " << n->getOurPort() << endl;

	//input message and change it into char array
	string message;
	cin >> message;
	char* messageChar = &message[0];
	//send to other player
	n->sendData("149.153.102.54",28001,messageChar);//set to work with mine and my partners pc
	message="";
	while(true){
		n->receiveData(messageChar);
		if(message[0] != '\0'){
			cout<< messageChar << endl;
			break;
		}
		Sleep(100);
	}
}

void playerB(Net* n){
	n->setupUDP(28001, "149.153.102.54");//set to work with mine and my partners pc
	cout << n->getOurIP() << "    " << n->getOurPort() << endl;

	char message[200]="";
	while(true){
		n->receiveData(message);
		if(message[0] != '\0'){
			break;
		}
		Sleep(100);
	}
	//input rock, paper or scissors
	cout << "type rock paper or scissors"<<endl;

	string rps;
	cin >> rps;
	string message1(message);
	cout << message << endl;

	if(message1==rps){
		n->sendData("149.153.102.51",28000,"the result is a draw");
		cout << "the result is a draw" << endl;
	}
	else if(message1=="rock"&&rps=="paper"){
		n->sendData("149.153.102.51",28000,"you lose");
		cout << "you win!"<<endl;
	}
	else if(message1=="rock"&& rps=="scissors"){
		n->sendData("149.153.102.51",28000,"you win");
		cout << "you lose!"<<endl;
	}
	else if(message1=="paper"&&rps=="rock"){
		n->sendData("149.153.102.51",28000,"you win");
		cout << "you lose!"<<endl;
	}
	else if(message1=="paper"&&rps=="scissors"){
		n->sendData("149.153.102.51",28000,"you lose");
		cout << "you win!"<<endl;
	}
	else if(message1=="scissors"&&rps=="rock"){
		n->sendData("149.153.102.51",28000,"you lose");
		cout << "you win!"<<endl;
	}
	else if(message1=="scissors"&&rps=="paper"){
		n->sendData("149.153.102.51",28000,"you win");
		cout << "you lose!"<<endl;
	}
}