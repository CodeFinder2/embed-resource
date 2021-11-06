# Overview

Embed binary files and resources (such as GLSL shader source files) into C++ projects. Uses C++11 features but no other library.

# Usage

Use [CPM](https://github.com/cpm-cmake/CPM.cmake) to add this to your `CMakeLists.txt`:
```cmake
include(cmake/CPM.cmake)
CPMAddPackage("gh:CodeFinder2/embed-resource#master")
```

Now you can add your resources, by calling the provided `embed_resources()` function in your
CMakeLists.txt file:
```cmake
embed_resources(MyResources shaders/vertex.glsl shaders/frag.glsl)
```
Then link to your binary by adding the created variable to your `add_executable()` statement:
```cmake
add_executable(your_target_name ${SOURCE_FILES} ${MyResources})
target_link_libraries(your_target_name embed_resource)
```
In your C++ project you can access your embed resources using the `Resource` class provided in `embed_resource/loader.h`. Here's an example:
```c++
#include <iostream>
using namespace std;

#include <embed_resource/loader.h>

int main()
{
  Resource text = LOAD_RESOURCE(frag_glsl);
  cout << text.toString() << endl;

  return EXIT_SUCCESS;
}
```

Note: to reference the file, replace the `.` in `frag.glsl` with an underscore `_`. So, in this example, the symbol name is `frag_glsl`.

# Credits
Forked and improved from [here](https://github.com/cyrilcode/embed-resource).

# License
Public Domain / [WTFPL](http://www.wtfpl.net/)
