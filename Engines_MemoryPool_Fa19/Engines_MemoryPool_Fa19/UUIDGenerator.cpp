#include "UUIDGenerator.h"

UUIDGenerator::UUIDGenerator()
{
}

UUIDGenerator::~UUIDGenerator()
{
}

int UUIDGenerator::getUUID()
{
	currentItterator++;
	return currentItterator;
}
