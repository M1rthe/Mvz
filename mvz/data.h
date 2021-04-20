#ifndef DATA_H
#define DATA_H

#include <vector>
#include <string>

struct Data {
	enum { TypeCode = 0 };
};

template<class T> 
std::vector<char> PackNetworkData(T Data) {

	std::vector<char> NetworkData;
	NetworkData.push_back(Data.TypeCode);
	NetworkData.push_back(sizeof(Data));
	NetworkData.insert(NetworkData.end(), (char const*)&Data, (char const*)(&Data + 1));

	return NetworkData;
}

template<class T>
T UnpackNetworkData(std::vector<char> NetworkData) {

	int DataType = NetworkData.at(0);
	int DataSize = NetworkData.at(1);

	T Data;
	std::memcpy(&Data, &NetworkData[2], DataSize);

	return Data;
}

#endif
