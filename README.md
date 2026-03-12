# Log Parser

The current project presents a **Log Parser** written in C++ (C++17). My idea with this project was to implement as much as possible some modern features of the language. At the same time, I also try to apply clean architecture with reusable classes.

The implementation I chose for this parser was so the user can **filter out IPs** of a given log file which follows the Apache Log format (although you can use the interface to implement it on any log file you wish!). I also provide two logs inside the `/data` directory, so the user can test how it works.

My focus is specially in the following areas:

- Encapsulation
- Polymorphism
- Templates
- Smart pointers
- STL containers and algorithms
- IPC
- Clean Code
- SOLID principles (SRP in particular)

**Note**: Some of the topics listed have not been implemented yet. Stay tuned!

Of course, since this is a small project merely intended to practice programming in the language myself, do not expect it to have very advanced features (which might even fall into over-engineering).

After all, in order to judge the code you see first, you need to have clear the end of it! Even though computing is based on trade-offs by its nature, since if you pull the rope from one side the other edge might get weaker, it is always a conscious decision based on the end of the program.

## Installation

In order to compile and run the program following the best practices, you would need:
 
1. `cd` into the root directory of this repository
2. Create a directory called `build` and `cd` into it
3. Run the corresponding `cmake` commands
4. Run the program

The two steps from above can be achieved in the following way:

```bash
# Step 1
cd <repo-root-folder>

# Step 2
mkdir build
cd build

# Step 3
cmake ..
cmake --build .
```

## Usage

Once we have our program compiled, it will be ready to run! We do so with the following command

```bash
./log_analyzer <file_path> <top_n>

# Example
./log_analyzer apache.log 10

Processing logs...

--- Displaying Top 10 IPs ---
66.249.73.135 : 482 requests
46.105.14.53 : 364 requests
130.237.218.86 : 357 requests
75.97.9.59 : 273 requests
50.16.19.13 : 113 requests
209.85.238.199 : 102 requests
68.180.224.225 : 99 requests
100.43.83.137 : 84 requests
208.115.111.72 : 83 requests
198.46.149.143 : 82 requests
```

The first argument takes the file path of the log file, while the second argument takes a number which represents how many IPs the user wants to check. The IPs are sorted on decreasing order, so you will see the IP that sent more requests first.

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.