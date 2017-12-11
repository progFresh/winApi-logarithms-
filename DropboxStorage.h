#pragma once

#include "CloudStorage.h"

class DropboxCloudStorage : public CloudStorage {

private:
	string photoUrl;
	int filesCount;

public:
	DropboxCloudStorage(string url, string name, string photoUrl) : CloudStorage(url, name) {
		this->photoUrl = photoUrl;
		this->filesCount = 0;
	}

	~DropboxCloudStorage() {}

	void uploadFile(string path) {
		cout << "Uploading file: " << path << " to Dropbox" << endl;
		_sleep(1000);
		this->filesCount = this->filesCount + 1;
		cout << "File uploaded" << endl;
	}

	void downloadFile(string path) {
		cout << "Download file: " << path << " from Dropbox" << endl;
		_sleep(1000);
		cout << "File downloaded" << endl;
	}

	void delereAllFiles() {
		this->filesCount = 0;
		cout << "all files were deleted" << endl;
	}

	int countOfFiles() {
		return this->filesCount;
	}
};