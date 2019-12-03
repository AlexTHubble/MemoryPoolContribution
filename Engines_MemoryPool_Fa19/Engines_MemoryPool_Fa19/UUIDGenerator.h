#ifndef UUIDGENERATOR_h
#define UUIDGENERATOR_h

//Super quick UUID generator, not proper but works for now
//Basicly holds an itterator that increments every time a new uuid is made
//This ensures that no 2 functions have the same UUID
class UUIDGenerator
{
public:
	UUIDGenerator();
	~UUIDGenerator();

	int getUUID();
private:
	
	int currentItterator = 0;
};

#endif // !UUIDGENERATOR_h
