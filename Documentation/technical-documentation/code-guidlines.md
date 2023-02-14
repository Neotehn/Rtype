# Code Guidlines

## General rules <a href="#general-rules" id="general-rules"></a>

* if using const values, write const dataType variableName
  * example: “const int count” instead of “int const count”
* never use “using namespace” in header file, always in .cpp
* always use Guards:

```
1 #ifndef PATH_FILENAME_HPP_
2 #define PATH_FILENAME_HPP_
3
4 code ...
5
6 #endif /* !PATH_FILENAME_HPP_ */
```

* always use namespace for non-class methods
* use C++ style “new” keyword instead of c style malloc
* for bool use TRUE and FALSE
* if checking on bool, always check FALSE = x of FALSE != x (false is mostly default value)

## Formatting <a href="#formatting" id="formatting"></a>

* use inline functions if they are up to 10 lines
* max line length = 80 character
* tab = 2 spaces
* always use // for comments (not /\* \*/)
* single quotes for chars, double quotes for strings
* block statement delimiters ({}) on next line

```
1 if (true)
2 {
3    return;
4 }
```

* indent function parameters from method name

```
1 void myMethod(int long_name_param_one,
2               char long_name_param_two,
3               MyType long_name_param_three);
```

* line folding: value on each line

```
1 enum color
2 {
3    red,
4    orange,
5    yellow,
6    green,
7    //...
8    violet
9 };
```

* each file ends with an empty line

## Naming <a href="#naming" id="naming"></a>

* c++ files end in .cpp
* header files end in .hpp
* functions in camelCase → myMethod
* types (class, struct, enum, …) in PascalCase → MyType
* variables in snake\_case → my\_variable
* private class data members are named m\_snake\_case (m = member) → m\_private\_class\_count
* function parameter t\_snake\_case → t\_my\_function\_parameter
* file name of class: PascalCase, otherwise camelCase
* macros are all upper case with underscore
* method to retrieve value → type getX();
* method to change value → void setX(type change\_param);
* method to check condition → bool isX();

## Imports <a href="#imports" id="imports"></a>

* each import group is sorted alphabetically
* use <> for system includes, ““ for local includes
* Include in the following order with blank line between each other:
  * C system headers → unistd.h / stdlib.h / …
  * C++ standard library headers → algorithm / …
  * other libraries' headers
  * your project's headers.
* example:

```
1 #include <sys/types.h>
2 #include <unistd.h>
3
4 #include <string>
5 #include <vector>
6
7 #include "base/basictypes.h"
8 #include "foo/server/bar.h"
9 #include "third_party/absl?flags/flag.h"
```

## Struct <a href="#struct" id="struct"></a>

* only use structs for passive objects - carrying data (all public fields)

## Classes <a href="#classes" id="classes"></a>

* only one class definition per file
* use “explicit” keyword for single parameter constructors
* make data members private - exception: constants
* section order
  * public:
  * protected:
  * private:
* default values for data members in header file with {}

```
1 private:
2    int m_value = {0};
```

* header: only function declaration, function definition / implementation in .cpp file

## Functions <a href="#functions" id="functions"></a>

* keep functions short → if they are not, think about breaking it into several functions

## Resources <a href="#resources" id="resources"></a>

* [![](https://www.google.com/favicon.ico)Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
* [https://lefticus.gitbooks.io/cpp-best-practices/content/03-Style.html](https://lefticus.gitbooks.io/cpp-best-practices/content/03-Style.html)
* [C++ Programming Guidelines](https://sceweb.uhcl.edu/helm/rationalunifiedprocess/manuals/cpp/cpp.htm)
* [C++ Coding Standard](https://users.ece.cmu.edu/\~eno/coding/CppCodingStandard.html)



[Back](../../README.md)
