#ifndef HEAP_FILE_H_
#define HEAP_FILE_H_
#include "DBFile.h"
#include "BaseFile.h"



class HeapDBFile: public BaseFile {



public:
	HeapDBFile ();
	~HeapDBFile();

	int Create (char* fpath, void* startup);
	void Load (Schema &mySchema, char *loadMe);
	int GetNext (Record& fetchme);
	//int GetNext (Record &fetchMe, CNF &applyMe, Record &literal, Schema * p=NULL);
	int GetNext (Record &fetchMe, CNF &applyMe, Record &literal);

	void Add (Record& me);
	void MoveFirst();
};
#endif
