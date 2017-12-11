#pragma once

#include <string>
#include <iostream>

using namespace std;

class CloudStorage {
	
protected:
	string url;
	string name;

public:
	CloudStorage(string url, string name) {
		this->url = url;
		this->name = name;
	}

	~CloudStorage() {}

	void setUrl(string url) {
		this->url = url;
	}
	
	string getUrl() {
		return url;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() {
		return name;
	}

	void connect() {
		cout << "Connecting..." << endl;
		_sleep(1000);
		cout << "Connected" << endl;
	}

	void desconnect() {
		cout << "Disconnected" << endl;
	}

	virtual void uploadFile(string path) = 0;
	virtual void downloadFile(string path) = 0;
};