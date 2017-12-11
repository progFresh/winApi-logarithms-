#include "DropboxStorage.h"
#include "CloudStorage.h"
#include "GoogleStorage.h"

#include <iostream>
#include <conio.h>
#include <string>

using namespace std;
int main(int argc, char **argv) {

	int check;
	CloudStorage *goodleStorage = NULL;
	CloudStorage *dropboxStorage = NULL;
	string path;

	goodleStorage = new GoogleCloudStorage("htttp://Googgle.com", "myGoogleStorage", "47983195182374182");
	dropboxStorage = new DropboxCloudStorage("htttps://Dropboxx.com", "myDropboxStorage", "htttps://Dropboxx.com/image.png");

	do {
		cout << "1. work with google storage" << endl;
		cout << "2. work with dropbox storage" << endl;
		cout << "0. Exit" << endl; 
		check = _getch() - '0';
		switch (check) {
		case 1:
			system("CLS");
			goodleStorage->connect();
			int googleCheckOut;
			do {
				cout << "1. upload file " << endl;
				cout << "2. download file " << endl;
				cout << "3. to know the name of Author" << endl;
				cout << "4. to know the file weight" << endl;
				cout << "0. Back" << endl; 
				googleCheckOut = _getch() - '0';
				switch(googleCheckOut) {
				case 1: 
					cout << "Please, enter the path of file: ";
					getline (std::cin,path);
					goodleStorage->uploadFile(path);
					break;
				case 2:
					cout << "Please, enter the path of file: ";
					getline (std::cin,path);
					goodleStorage->downloadFile(path);
					break;
				case 3:
					cout << ((GoogleCloudStorage*)goodleStorage)->getAuthorName() << endl;
					break;
				case 4:
					cout << "Please, enter the path of file: ";
					getline (std::cin,path);
					cout << "weight: " << ((GoogleCloudStorage*)goodleStorage)->getFileWeight(path) << endl;
					break;
				default:
					cout << "Please, Enter only 1,2,3 or 4." << endl;
				}
				// checking
				if (googleCheckOut != 0) {
					system("PAUSE");
					system("CLS");
				}
			} while (googleCheckOut != 0);
			break;
		case 2:
			system("CLS");
			dropboxStorage->connect();
			int dropboxCheckOut;
			do {
				cout << "1. upload file " << endl;
				cout << "2. download file " << endl;
				cout << "3. to delete all files" << endl;
				cout << "4. to know how much there are files" << endl;
				cout << "0. Back" << endl; 
				dropboxCheckOut = _getch() - '0';
				switch(dropboxCheckOut) {
				case 1: 
					cout << "Please, enter the path of file: ";
					getline (std::cin,path);
					dropboxStorage->uploadFile(path);
					break;
				case 2:
					cout << "Please, enter the path of file: ";
					getline (std::cin,path);
					dropboxStorage->downloadFile(path);
					break;
				case 3:
					((DropboxCloudStorage*)dropboxStorage)->delereAllFiles();
					break;
				case 4:
					cout << "count of files: " << ((DropboxCloudStorage*)dropboxStorage)->countOfFiles() << endl;
					break;
				default:
					cout << "Please, Enter only 1,2,3 or 4." << endl;
				}
				// checking
				if (dropboxCheckOut != 0) {
					system("PAUSE");
					system("CLS");
				}
			} while (dropboxCheckOut != 0);
			break;
		default:
			cout << "Please, Enter only 1,2 or 3." << endl;
		}
		if (check != 0) {
			system("CLS");
		}
	} while (check != 0);

	delete goodleStorage;
	goodleStorage = NULL;
	delete dropboxStorage;
	dropboxStorage = NULL;
	return 0;
}