// TP3SEXP2.cpp : Définit le point d'entrée pour l'application console.
//
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <thread>
#include <string>
#include <iostream>
#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;
void validerAdresse(string adresse)
{
	string table[4];
	int intTable[4];
	size_t position = 0;
	int count = 0;
	bool validIp = true;
	for (int i = 0; i < 4; i++)
	{
		position = adresse.find('.');
		table[i] = adresse.substr(0, position);
		intTable[i] = std::stoi(table[i]);
		adresse.erase(0, position + 1);
		if (intTable[i] > 255 || intTable < 0)
		{
			validIp = false;
		}
	}
}
int RunSocket(string adresse)
{
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");


	server.sin_addr.s_addr = inet_addr(adresse.c_str());
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	return 0;
}

int main()
{
	std::thread::id mainThreadId = std::this_thread::get_id();
	//while (true)
	{
		std::cout << "Voulez vous vous connecter à un site web? [y/n]" << endl;
		char value;
		cin >> value;
		if (value == 'y')
		{
			cout << "Veuillez entrer une adresse de connexion valide sous format ipv4" << endl;
			string adresse;
			cin >> adresse;
			thread first (validerAdresse,adresse);
			first.join();
			RunSocket(adresse);
		}
	}
    return 0;
}
