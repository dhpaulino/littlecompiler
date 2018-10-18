# littlecompiler
A really simple compiler for a really simple language


## Symbols

* identifiers: for the names of the variables
  * a string beginning with a letter, it may contein letters, digits and the caracter "_".
* intergers:
  * a string with only digits.
* let: word reserved to assignment
  * the string "let".
* print: word reserved to print
  * the string "print".
* add: word reserved to addition
  * string "add".
* assignment:
  * the caracter "=".
* addition:
  * o caracter "+".


## Exemple:

### Input
```
  let a = 2
  add b + 4
  print a
  print b
```
### Output
 ```
  2
  4
 ```

## Dependencies

* Flex
* Make
* GCC

## Running

```
make
./compiler < inputfile
``` 
