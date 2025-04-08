
# File-Corruptor
This file corruptor was made to target a Windows machine.  
It works by retrieving all of the bytes in a file, comparing each bit in each byte to change its original bit value with another value, and later writes all of that information into the file.

### Visual Representation
At a certain point in this program, it compares each bit in a selected byte with the value `0xFF`, which in bits is `11111111`.  
When you use `^= 0xFF` on a byte, it flips all the bits.

- `0xFF` is `11111111` in binary, which means **every bit** will be flipped.
- If the bit is `0`, it becomes `1`.
- If the bit is `1`, it becomes `0`.

For example:
- Original byte:   `01010101`
- After `^= 0xFF`: `10101010`

It simply **inverts** every bit of the byte.


### How to use
To use this file corruptor, please download the `FC.exe` and execute it, preferably with administrator privileges in a virtual machine.

Please ignore the other directories like "test," as those are just the history of how this program was made.

### Who can use it?
Anyone can use it, but I encourage you not to use it with malicious intent.

