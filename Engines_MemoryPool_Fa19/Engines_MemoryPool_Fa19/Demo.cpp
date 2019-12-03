//Demo cpp for demonstraiting memory pools use
#include"MemoryPoolSpecific.h"
#include<iostream>
//#include "UUIDGenerator.h"

int main()
{
	UUIDGenerator *uuidGen = new UUIDGenerator();
	
	MemoryPoolSpecific<int> *pool = new MemoryPoolSpecific<int>();
	pool->init(3, uuidGen);

	int dataID = pool->setEntry();
	int* testData = pool->getEntry(dataID);
	*testData = 3333333;

	int dataID2 = pool->setEntry();
	int* testData2 = pool->getEntry(dataID2);
	*testData2 = 2;

	int dataID3 = pool->setEntry();
	int* testData3 = pool->getEntry(dataID3);
	*testData3 = 3;

	std::cout << *testData << std::endl;
	std::cout << *testData2 << std::endl;
	std::cout << *testData3 << std::endl;

	pool->cleanup();

	system("pause");
	delete pool;
	delete uuidGen;
}