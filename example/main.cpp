#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

#include <embed_resource/loader.h>

// Demonstrate the use within a namespace (a bit tricky due to name mangling):
namespace test {

void myFunction()
{
  // Here, we embed this source code itself as the resource:
  Resource text = LOAD_RESOURCE(example_main_cpp);
  // File-like processing: iterate through file line-by-line:
  istringstream buf(text.data());
  string line;
  int lc = 1;
  while (getline(buf, line)) {
    cout << setfill('0') << setw(2) << lc++ << ": " << line << endl;
  }
}

} // end of namespace: test

int main()
{
  // Use without namespace:
  Resource text = LOAD_RESOURCE(example_data_txt);
  cout << text.toString() << endl << endl;
  // ... and again with a namespace:
  test::myFunction();

  return text.toString() == "Hello World!" ? EXIT_SUCCESS : EXIT_FAILURE;
}
