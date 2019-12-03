#include <list> //For list
#include <map> //For map
#include <cstdlib> //I honestly cant remember something with Malloc I'm pretty sure
#include <algorithm>    //For find
#include "UUIDGenerator.h"

#ifndef MEMORYPOOLSPECIFIC_h
#define MEMORYPOOLSPECIFIC_h

/*
	This memory pool is designed to be used with a predetermined number of objects
	All items are allocated at once then disabled, it is up to the user to enable objects when they are needed
*/

template <class T>
class MemoryPoolSpecific
{
public:
	//-----------------Functions

	~MemoryPoolSpecific()
	{
	};

	void  init(int inNumberOfEntries, UUIDGenerator *inUUIDGenerator)
	{
		numberOfEntries = inNumberOfEntries;
		uuidGenerator = inUUIDGenerator; //This would normaly be part of engine however it's like this for demo purposes
		allocateMemoryChunk(inNumberOfEntries); //Allocates the memory of the pool
		initData();
	}; //Sets up bolt the data map & the free index lsit

	void cleanup()
	{
		
		//for (std::map<int, DataHolder>::iterator it = dataMap.begin(); it != dataMap.end(); ++it)
		//{
		//	it->second->~theData();
		//}

		//for (auto pair : dataMap)
		//{
		//	delete pair.second.theData;
		//}

		freeMemory();

	}; //Cleans up the pool

	T * getEntry(int entryUUID)
	{
		return dataMap[entryUUID].theData; //Returns the data based on the UUID sent in
	}; //Find the entry with the desired UUID

	int setEntry()
	{
		int freeUUID = findFreeUUID(); //Gets an open UUID
		removeFreeUUID(freeUUID); //Removes from list
		int newUUID = uuidGenerator->getUUID(); //Gives the data a new uuid

		//Sets up a new feild with the correct UUID
		auto temp = dataMap[freeUUID]; 
		dataMap.erase(freeUUID);
		dataMap.insert(std::pair<int, DataHolder>(newUUID, temp));
		dataMap[newUUID] = temp;
		dataMap[newUUID].UUID = newUUID; //updates the uuid

		return newUUID; //Returns the data UUID of the now open spot
	};//Sets up a new entry in a free spot

	void removeEntry(int entryUUID)
	{
		addFreeUUID(entryUUID); //Adds the UUID to the free list
	}; //Finds a free UUID; //Removes an entry from the list

private:

	//-----------------Variables
	struct DataHolder //A struct to hold the data, keeps track of it's UUID, index, and the pointer to the data
	{
	public:
		T* theData = nullptr; 
		int index = 0;
		int UUID;
	private:
	};

	int numberOfEntries; //The number of entries in the pool
	std::map<int, DataHolder> dataMap; //A map of all of the data in the pool
	std::list<int> freeIndexs; //A list of all the free indexs in the pool
	std::list<int> freeUUIDs;
	void* poolData; //The data of the pool
	UUIDGenerator *uuidGenerator; //UUID generator for the pool

	//-----------------Functions
	void initData()
	{

		for (int i = 0; i < numberOfEntries; i++)
		{
			DataHolder dataHolderIn;
			dataHolderIn.index = i; //Sets up a new index
			//freeIndexs.push_back(i); //Puts the new index into the free index list
			dataHolderIn.UUID = uuidGenerator->getUUID(); //Generates an UUID from the generator
			freeUUIDs.push_back(dataHolderIn.UUID); //Adds the UUID to the free list
			//int dataIndex = findFreeIndex(); //Gets a free index
			//removeFreeIndex(dataIndex); //Removes the index from the free list
			dataHolderIn.theData = ((T*)poolData + i);//(i * sizeof(T))); //Allocates the memory to a spot in the memory
			dataMap.insert(std::pair<int, DataHolder>(dataHolderIn.UUID, dataHolderIn)); //Inserts the data into the map
		}
	}; //Inits the data needed

	void removeFreeIndex(int indexToRemove)
	{
		//Finds and removes an index from the list
		auto foundIndex = std::find(freeIndexs.begin(), freeIndexs.end(), indexToRemove);
		freeIndexs.erase(foundIndex);
	}; //Removes an index from the free list

	void addFreeIndex(int indexToAdd)
	{
		freeIndexs.push_back(indexToAdd);
	}; //Adds an index to the free list

	int findFreeIndex()
	{
		if (freeIndexs.size() != 0)
		{
			return freeIndexs.front();
		}

		return -1; //Returns an error
	}; //Finds a free index

	void removeFreeUUID(int UUIDToRemove)
	{
		//Finds and removes an UUID from the list
		auto foundIndex = std::find(freeUUIDs.begin(), freeUUIDs.end(), UUIDToRemove);
		freeUUIDs.erase(foundIndex);
	}; //Removes a UUID from the free list

	void addFreeUUID(int UUIDToAdd)
	{
		freeUUIDs.push_back(UUIDToAdd);

	};

	int findFreeUUID()
	{
		if (freeUUIDs.size() != 0)
		{
			return freeUUIDs.front();
		}

		return -1; //Returns an error
	};

	void allocateMemoryChunk(int inNumberOfEntries)
	{
		poolData = malloc(sizeof(T) * inNumberOfEntries); //Allocates the memory
	}; //Allocates the memory for the pool

	void freeMemory()
	{
		std::free(poolData);
	
	}; //Frees the allocated memory in the pool
};


#endif // MEMORYPOOLSPECIFIC_h

