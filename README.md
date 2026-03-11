# Log Parser

The current project presents a **Log Parser** written in C++. My idea with this project was to implement as much as possible some modern features of the language. At the same time, I also try to apply clean architecture with reusable classes.

The implementation I chose for this parser was so the user can **filter out the IPs** of a given log file which follows the Apache Log format in this case (although you can use the interface to implement it on any log file you wish!). I also provide two logs inside the `/data` directory, so the user can test how it works.

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

I made sure to code an interface that is dynamic, and you have the possibility to implement it on any log file you are trying to parse! Of course, since this is a small project merely intended to practice programming in the language myself, do not expect it to have very advanced features (which might even fall into over-engineering).

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
./log_analyzer
```

**Note**: On this moment, I have the path of the log file hardcoded in the program! Nonetheless, I'll fix it soon so it is interactive for you (the user). In addition, you would also choose how many lines of the final filter you want to see!

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.