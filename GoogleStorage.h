#pragma once

#include "CloudStorage.h"
#include <random>
#include <string>

class GoogleCloudStorage : public CloudStorage {

private:
	string googleToken;

	int getRandomWeight() {
		std::random_device rd;     // only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
		std::uniform_int_distribution<int> uni(0,1024); // guaranteed unbiased
		int random_integer = uni(rng);
		return random_integer;
	}

public:
	GoogleCloudStorage(string url, string name, string boobleToken) : CloudStorage(url, name) {
		this->googleToken = boobleToken;
	}

	~GoogleCloudStorage() {}

	void uploadFile(string path) {
		cout << "Uploading file: " << path << " to Google" << endl;
		_sleep(500);
		cout << "File uploaded" << endl;
	}

	void downloadFile(string path) {
		cout << "Download file: " << path << " from Gooble" << endl;
		_sleep(500);
		cout << "File downloaded" << endl;
	}

	string getAuthorName() {
		return "name: Sergey";
	}

	string getFileWeight(string path) {
		int weight = getRandomWeight();
		std::string string = std::to_string(weight);
		return string;
	}
};