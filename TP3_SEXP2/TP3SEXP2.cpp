// TP3SEXP2.cpp : Définit le point d'entrée pour l'application console.
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
	string domainePossible[9]{ "com","ca","info","biz","jobs","net","org","mobi","travel" }; //.com .ca .info .biz .jobs .net .org .mobi .travel
	size_t positionPoint = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (adresse[i] != 'w')
		{
			false;
		}
	}
	if (adresse[3] != '.')
	{
		false;
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

bool AdresseVersIP(char* adresse)
{
	WSADATA wsaData;
	int iResult;

	DWORD dwError;

	struct hostent *remoteHost;
	char *host_name;
	struct in_addr addr;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}

	host_name = adresse;

	remoteHost = gethostbyname(host_name);
	addr.s_addr = *(u_long *)remoteHost->h_addr_list[0];
	printf("First IP Address: %s\n", inet_ntoa(addr));
	return true;
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
			thread first(validerAdresse, adresse);
			first.join();
			RunSocket(adresse);
			char *cAdresse = &adresse[0u];
			AdresseVersIP(cAdresse);
		}
	}
	return 0;
}