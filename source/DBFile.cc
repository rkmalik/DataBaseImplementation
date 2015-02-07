#include <iostream>
#include "TwoWayList.h"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"

using namespace std;
// stub file .. replace it with your own DBFile.cc

DBFile::DBFile () {
	mode = heap;
	mydbfile = NULL;
}

DBFile::~DBFile () {
	delete mydbfile;
}

int DBFile::Create (char *f_path, fType f_type, void *startup) {

	switch (f_type)
	{
		case heap:

			mydbfile = new HeapDBFile ();
			if (mydbfile== NULL){
				cout << "Failed to Create a Heap File" << endl;
			}
			cout<< "Heap File Created" << endl;
			return mydbfile->Create (f_path, startup);

			break;

		case sorted:
			break;

		case tree:
			break;

		default:
			break;
	}


	return 0;
}

void DBFile::Load (Schema &f_schema, char *loadpath) {
	mydbfile->Load (f_schema, loadpath);

}

int DBFile::Open (char *f_path) {
	int ret = 0;
	cout << "Opening the file " << f_path<< endl;
	if (mydbfile==NULL)
		mydbfile = new HeapDBFile ();

	ret = mydbfile->Open (f_path);
	if (ret == 1)
		cout << "Heap File is Opened" << endl;

	return ret;

}

void DBFile::MoveFirst () {
	mydbfile->MoveFirst ();
}

int DBFile::Close () {
	// Calling the Base class Close method to close the file
	mydbfile->Close();
}

void DBFile::Add (Record &rec) {
}

int DBFile::GetNext (Record &fetchme) {
	mydbfile->GetNext (fetchme);
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
    return mydbfile->GetNext(fetchme, cnf, literal);
}
