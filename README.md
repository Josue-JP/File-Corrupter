# File-Corrupter
This file corrupter was made to target a windows machine. 
It works by retrieving all of the bytes in a file, comparing each bit in each byte to change it's original bit value with another value, and later writes all of that information into the file.


### Visual Representation
At a certain point in this program it compares each bit in a select byte with value 0xFF, which in bits is 11111111.
When you use `^= 0xFF` on a byte, it flips all the bits. 

- `0xFF` is `11111111` in binary, which means **every bit** will be flipped.
- If the bit is `0`, it becomes `1`.
- If the bit is `1`, it becomes `0`.

For example:
- Original byte:   `01010101`
- After `^= 0xFF`: `10101010`

It simply **inverts** every bit of the byte.

### How to use
to use this file corrupter please download the FC.exe, and execute it, preferablly with administrator privileges in a virtual machine.
