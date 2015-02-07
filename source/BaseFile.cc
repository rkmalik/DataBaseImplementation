#include <fstream>
#include <iostream>
#include "DBFile.h"
#include "HeapDBFile.h"
#include "BaseFile.h"


using namespace std;

BaseFile::BaseFile()
{
	currentPageIndex = -1;
	totalPageCount = 0;

}
BaseFile::~BaseFile()
{


}
int BaseFile::Open (char* fpath) {
	cout << "Opening the file  " <<  fpath << endl;
	file.Open(1, fpath);
	return 1;
}

int BaseFile::Close ()
{
	file.Close ();
	return 0;
}

