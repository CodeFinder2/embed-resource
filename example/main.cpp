#include <iostream>
using namespace std;

#include <embed_resource/loader.h>

// Demonstrate the use within a namespace (a bit tricky due to name mangling):
namespace test {

string myFunction()
{
  Resource text = LOAD_RESOURCE(example_data_txt);
  return string(text.data(), text.size());
}

} // end of namespace: test

int main()
{
  // Use without namespace:
  Resource text = LOAD_RESOURCE(example_data_txt);
  cout << text.toString() << endl;
  // ... and again with a namespace:
  cout << test::myFunction() << endl;

  return text.toString() == "Hello World!" ? EXIT_SUCCESS : EXIT_FAILURE;
}
