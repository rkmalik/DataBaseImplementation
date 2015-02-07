#ifndef  BASEFILE_H
#define  BASEFILE_H

#include <string>
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"

typedef enum { READ, WRITE } fMode;

class BaseFile {

protected:
	// This offset starts with zero index
	off_t 	currentPageIndex;
	// This is the page on which we are currently working
	Page 	currentPage;
	// Pages added to the file so far
	int 	totalPageCount;
	File 	file;

public:
	BaseFile();
	virtual ~BaseFile();
	virtual int Open (char* fpath);
	virtual int Close();

	virtual int GetNext (Record& fetchme) = 0;
	//virtual int GetNext (Record &fetchMe, CNF &applyMe, Record &literal, Schema * p = NULL)=0;
	virtual int GetNext (Record &fetchMe, CNF &applyMe, Record &literal)=0;

	virtual void Add (Record &addMe) = 0;
	virtual void MoveFirst() = 0;


	// Following functions are based on the type of files. So need to be
	// implemented seprately by the derived classes.
	virtual int Create (char* fpath, void* startup)=0;
	virtual void Load (Schema &mySchema, char *loadMe)=0;

};
#endif
