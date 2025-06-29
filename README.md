# Akers Array Implementation in C++

This project provides a clean and efficient implementation of the Akers Array in C++. The Akers Array is a parallel computing model used in digital logic design to evaluate Boolean expressions using a grid of logic cells.

## What is an Akers Array?

An Akers Array is a 2D matrix of identical logic cells. Each cell performs basic Boolean operations and passes values to its neighboring cells. The model is useful in combinational circuit design and for implementing Boolean functions in hardware.

## Features

- Modular, object-oriented C++ implementation
- Evaluates simple Boolean logic operations using a logic grid
- Easy to extend for more complex logic
- Beginner-friendly structure
- Command-line interaction

## File Structure

```
akers-array/
├── akerscode.cpp      # Main C++ source code
├── README.md          # Project description
├── .gitignore         # Git ignore file
├── LICENSE            # MIT License
```

## How to Compile and Run

### Requirements

- A C++ compiler (such as g++ or clang)

### Compile

```
g++ akerscode.cpp -o akers
```

### Run

```
./akers
```

## Example Input and Output

```
Enter two Boolean inputs:
A = 1
B = 0
Operation: AND

Output = 0
```

## Educational Use

This project is well-suited for:

- Students studying digital logic and computer architecture
- Engineers learning about logic synthesis and grid-based computing
- Academic demonstrations of parallel logic computation

## Concepts Covered

- Boolean algebra
- Logic gate simulation
- Grid-based logic processing
- Modular programming in C++

## References

- Akers, S. B., "Binary Decision Diagrams", IEEE Transactions on Computers
- Digital Logic Design textbooks (e.g., Morris Mano)
- Wikipedia: Akers Array

## License

This project is open-source and distributed under the MIT License. You are free to use, modify, and distribute this code for academic and personal use.
