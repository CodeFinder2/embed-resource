#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 3) {
    cerr << "USAGE: " << argv[0] << " {sym} {rsrc}" << endl << endl
         << "  Creates {sym}.c from the contents of {rsrc}"  << endl;
    return EXIT_FAILURE;
  }

  string sym(argv[2]);
  replace(sym.begin(), sym.end(), '.', '_');
  replace(sym.begin(), sym.end(), '-', '_');
  replace(sym.begin(), sym.end(), '/', '_');
  replace(sym.begin(), sym.end(), '\\', '_');

  ifstream ifs;
  ifs.open(argv[2]);
  if (!ifs.is_open()) {
    cerr << "error: unable to read " << argv[2] << endl;
    return EXIT_FAILURE;
  }

  ofstream ofs;
  ofs.open(argv[1]);
  if (!ofs.is_open()) {
    cerr << "error: unable to create " << argv[1] << endl;
    return EXIT_FAILURE;
  }

  ofs << "#include <stdlib.h>" << endl;
  ofs << "const char _resource_" << sym << "[] = {" << endl;

  size_t lineCount = 0;
  char c;
  while (ifs >> std::noskipws >> c) {
    ofs << "0x" << hex << (c & 0xff) << ", ";
    if (++lineCount == 10) {
      ofs << endl;
      lineCount = 0;
    }
  }

  ofs << "};" << endl;
  ofs << "const size_t _resource_" << sym << "_len = sizeof(_resource_" << sym << ");";
  return EXIT_SUCCESS;
}
