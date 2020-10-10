#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace	std;

class Product
{
public:
	string name;
	int orderListNum;
};

struct Object
{
	string ob1;
	string ob2;
};

void loadJsonFile(ifstream& inFile, vector<Product>& productList, vector< vector<int> >& orderList);

void loadTxtFile(ifstream& inFile, vector<Object>& objectList);

int insertProductList(vector<Product>& productList, Product product);

void calculateResult(vector<Product>& productList, vector< vector<int> >& orderList, vector<Object>& objectList);

int main(int argc, char* argv[])
{
	vector<Product> productList;
	vector<Object> objectList;
	vector< vector<int> > orderList;

	ifstream readFileOrder;
	readFileOrder.open(argv[1]);
	ifstream readFileInfo;
	readFileInfo.open(argv[2]);

	loadJsonFile(readFileOrder, productList, orderList);
	loadTxtFile(readFileInfo, objectList);

	calculateResult(productList, orderList, objectList);
}

void loadJsonFile(ifstream& inFile, vector<Product>& productList, vector< vector<int> >& orderList)
{
	if (!inFile) {
		cout << "File could not be opened" << endl;
		return;
	}

	char buffer, previous = '\0', orderIdString[10];
	int status = 0, orderIdPos = 0, orderId, orderListNum;
	bool catchProductName = false, catchOrderId = false;
	vector<int> order;
	order.push_back(0);
	Product product;
	while (!inFile.eof()) {
		inFile >> buffer;
		if (catchProductName) {
			if (buffer == '"') {
				catchProductName = false;
				status++;
				product.orderListNum = orderList.size();
				orderListNum = insertProductList(productList, product);
				if (orderListNum == orderList.size())
					orderList.push_back(order);
				product.name.clear();
				continue;
			}
			product.name += buffer;
			continue;
		}
		if (catchOrderId) {
			if (buffer == ',') {
				catchOrderId = false;
				orderIdPos = 0;
				orderId = (int)atoi(orderIdString);
				status++;
				continue;
			}
			orderIdString[orderIdPos++] = buffer;
		}
		if (previous == ':') {
			if (status == 1) {
				orderIdString[orderIdPos++] = buffer;
				catchOrderId = true;
			}
			else if (status == 3)
				catchProductName = true;
			else if (status == 4) {
				if (buffer != '0' && *(--orderList[orderListNum].end()) != orderId)
					orderList[orderListNum].push_back(orderId);
				status--;
			}
		}
		if (buffer == '{')
			status++;
		else if (buffer == ']')
			status--;
		else if (buffer == '}')
			status--;
		previous = buffer;
	}
}

void loadTxtFile(ifstream& inFile, vector<Object>& objectList)
{
	if (!inFile) {
		cout << "File could not be opened" << endl;
		return;
	}

	Object object;
	char numericString[8], buffer[4];
	int pos, dataNum;
	inFile.getline(numericString, 8, '\n');
	dataNum = (int)atoi(numericString);
	for (int i = 0; i < dataNum; i++) {
		inFile.getline(numericString, 8, '\n');
		pos = 0;
		while (numericString[pos] != ',')
			object.ob1 += numericString[pos++];
		pos++;
		while (numericString[pos] != '\0')
			object.ob2 += numericString[pos++];
		objectList.push_back(object);
		object.ob1.clear();
		object.ob2.clear();
	}
}

int insertProductList(vector<Product>& productList, Product product)
{
	vector<Product>::iterator it;
	int left = 0, right = productList.size() - 1, middle = (right + left) / 2, pos;
	if (!productList.empty()) {
		if (productList[left].name.compare(product.name) == 1) {
			productList.insert(productList.begin(), product);
			return product.orderListNum;
		}
		else if (productList[right].name.compare(product.name) == -1) {
			productList.push_back(product);
			return product.orderListNum;
		}
		else if (productList[left].name.compare(product.name) == 0) {
			return productList[left].orderListNum;
		}
		else if (productList[right].name.compare(product.name) == 0) {
			return productList[right].orderListNum;
		}
		do {
			if (productList[middle].name.compare(product.name) == 0) {
				return productList[middle].orderListNum;

			}
			if (productList[middle].name.compare(product.name) == 1)
				right = middle;
			else
				left = middle;

			middle = (right + left) / 2;
			it = productList.begin() + middle + 1;
			pos = middle + 1;
		} while (middle != left && middle != right);

		if (productList[middle].name.compare(product.name) != 0)
			productList.insert(it, product);
	}
	else {
		productList.push_back(product);
		pos = productList.size() - 1;
	}
	return productList[pos].orderListNum;
}

void calculateResult(vector<Product>& productList, vector< vector<int> >& orderList, vector<Object>& objectList)
{
	int total, j, k, orderListNum1, orderListNum2;
	Product pro1, pro2;
	for (int i = 0; i < objectList.size(); i++) {
		total = -1;
		j = k = 0;
		pro1.name = objectList[i].ob1;
		pro2.name = objectList[i].ob2;
		orderListNum1 = insertProductList(productList, pro1);
		orderListNum2 = insertProductList(productList, pro2);
		while (j < orderList[orderListNum1].size() && k < orderList[orderListNum2].size()) {
			if (orderList[orderListNum1][j] == orderList[orderListNum2][k]) {
				total++;
				j++;
				k++;
			}
			else if (orderList[orderListNum1][j] < orderList[orderListNum2][k])
				j++;
			else
				k++;
		}
		cout << total << endl;
	}
}