# Progress

A neat (mostly) progress bar for c++.

It's a single header file.

(There's also a CMakeLists.txt if you want it.)

Note that I'm not an expert C++ guy. I just wanted some progress printing, and wanted
something similar to tqdm in python.

There's not much in the way of actual pretty printing,
but with C++ 20 and init statements, at least the code can be very clean.

Feel free to suggest changes.

## Usage

The idea is that you can pretty easily replace any code like this:

```cpp
for (int i = 0; i < limit; i++) {
    // whatever you do with i here
}
```

with:

```cpp
#include "progress/progress.h"
for (progress::Progress bar(limit); int i : bar) {
    // still do the same thing with i here
}
```

and you get on your console

```plain
  progress [##############     ] 123 / limit  69%
```

```cpp
#include "progress/progress.h"

int main() {
    for (progress::Progress bar(100); int counter : bar.name("such wow")) {
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
