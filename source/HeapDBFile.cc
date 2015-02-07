#include <iostream> // only for debugging
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "Defs.h"
#include "HeapDBFile.h"
//#define verbose


HeapDBFile::HeapDBFile () {

}
HeapDBFile::~HeapDBFile() {

}

void HeapDBFile::MoveFirst(){
	// Setting the currentPage to first record.
	currentPageIndex = (off_t)0;
	//currentPage.EmptyItOut ();
	cout << "File Length = " << file.GetLength () << endl;

	if (file.GetLength () != 0) {
		#ifdef verbose
			cout << "Getting the Page " << currentPageIndex << endl;
		#endif
		file.GetPage(&currentPage, currentPageIndex);
	} else {
		currentPage.EmptyItOut ();
	}
}

void HeapDBFile::Add (Record &addMe)
{
	// Keep on adding the record to the page and empty once it is full
	//cout << "Page is added to the file" << endl;

	if (currentPage.Append (&addMe) ==0) {
		cout << "Page is full needs to be added to the file" << endl;
		file.AddPage (&currentPage, ++currentPageIndex);
		totalPageCount++;
		currentPage.EmptyItOut ();
		cout << "Page is added to the file" << endl;
	}
}

void HeapDBFile::Load (Schema &mySchema, char *loadMe)
{
	// Create the file which needs to be loaded.
	FILE * fload = fopen (loadMe, "rw");

	if (fload == NULL){
		cout << "File could not be opened." << endl;
	}

	int rcount = 0;
	Record record;
	while (record.SuckNextRecord(&mySchema, fload)) {
		Add (record);
		rcount++;
	}

	file.AddPage (&currentPage, ++currentPageIndex);
	totalPageCount++;

	cout << "Total Records loaded to the File = " << rcount << endl \
	<< " Current Page Index  = " << currentPageIndex << endl \
	<< " Total Pages  = " << totalPageCount << endl;
	rcount = 0;
}

int HeapDBFile::Create(char* fpath, void* startup) {
	file.Open(0, fpath);
	return 1;
}

int HeapDBFile::GetNext (Record& fetchme) {

	// currentPage is now having the first page in the file with MoveFirst
    //
	while (!currentPage.GetFirst(&fetchme)) {
		if(++currentPageIndex > totalPageCount)
			return 0;
		file.GetPage(&currentPage, currentPageIndex);
	}
	return 1;
}


// int HeapDBFile::GetNext (Record &fetchMe, CNF &applyMe, Record &literal, Schema * p)
int HeapDBFile::GetNext (Record &fetchMe, CNF &applyMe, Record &literal)
{

    ComparisonEngine e;
     //cout << "Parsing CNF" << endl;

     // Loop till I dont get any of the comparing element

    while (GetNext(fetchMe) == 1) {
        //fetchMe.Print(p);
        if (e.Compare(&fetchMe, &literal, &applyMe) == 1){

            return 1;
        }
    }

    // (n_nationkey >0) AND (n_nationkey<25)
     //cout << "Parsing CNF 0 " << endl;

	return 0;
}

