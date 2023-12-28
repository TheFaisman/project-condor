# project-condor
A basic arithmetic calculator written in C++. 

## Learning Outcomes
This mini-project introduces the idea of tokenization, grammars, and parsing. The calculator tokenizes the input then parses it according to the grammar defined for the standard order of operations.

## Condor's Grammar for Order of Operations
Expression:
- Term
- Expression + Term
- Expression - Term

Term:
- Primary
- Term * Primary
- Term / Primary

Primary:
- Number
- Number "!"
- "(" Expression ")"
- "(" Expression ")" "!"
