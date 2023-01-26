# Progress

A neat (mostly) progress bar for c++.

It's a single header file.

(There's also a CMakeLists.txt if you want it.)

Note that I'm not an expert C++ guy. I just wanted some progress printing, and wanted
something similar to tqdm in python.

There's not much in the way of actual pretty printing,
but with C++ 20 and init statements, at least the code can be very clean.

Contributions welcome :)

## Usage

```cpp
// assuming you linked against the `progress` target in CMake
#include "progress/progress.h"

int main() {
    for (progress::Progress bar(100); int counter : bar.name("such wow")) {
        // do something with the counter which goes from 0 to 99 like a normal for loop
        // but dont print anything else though (maybe std::err might work...)
    }
    for (progress::Progress bar(1000); int counter : bar.name("much amaze")) {
        // another one
    }
    return 0;
}
```

result

```plain
  such wow [###################] 100 / 100  100%
  much amaze [######              ] 301 / 1000  31%
```

You can check `examples/example.cpp` for more usage. There's some documentation too. But it shouldn't be that hard to figure out how to use this. Maybe I'll add more/do it properly later or something.
