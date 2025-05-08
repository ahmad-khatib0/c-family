Here’s a **quick-reference cheat sheet** for `printf()` in C, covering format specifiers,
escape sequences, modifiers, and common usage:

---

### **1. Basic Format Specifiers**
| Specifier | Output                          | Example (`printf`)       | Result               |
|-----------|---------------------------------|-------------------------|----------------------|
| `%d`      | Signed integer (decimal)        | `printf("%d", 42);`     | `42`                 |
| `%u`      | Unsigned integer (decimal)      | `printf("%u", 42);`     | `42`                 |
| `%o`      | Unsigned octal                  | `printf("%o", 42);`     | `52` (42 in octal)   |
| `%x`      | Unsigned hex (lowercase)        | `printf("%x", 255);`    | `ff`                 |
| `%X`      | Unsigned hex (uppercase)        | `printf("%X", 255);`    | `FF`                 |
| `%f`      | Floating-point (decimal)        | `printf("%f", 3.14);`   | `3.140000`           |
| `%e`      | Scientific notation (lowercase) | `printf("%e", 1000.0);` | `1.000000e+03`       |
| `%E`      | Scientific notation (uppercase) | `printf("%E", 1000.0);` | `1.000000E+03`       |
| `%g`      | Shortest of `%f` or `%e`        | `printf("%g", 0.0001);` | `0.0001` or `1e-04`  |
| `%c`      | Single character                | `printf("%c", 'A');`    | `A`                  |
| `%s`      | String                          | `printf("%s", "Hi");`   | `Hi`                 |
| `%p`      | Pointer address                 | `printf("%p", &x);`     | `0x7ffd3456`         |
| `%%`      | Literal `%`                     | `printf("%%");`         | `%`                  |

---

### **2. Format Modifiers**
| Modifier       | Effect                                    | Example (`printf`)        | Result               |
|----------------|-------------------------------------------|---------------------------|----------------------|
| `%5d`         | Min. width (right-aligned)               | `printf("%5d", 42);`      | `   42`              |
| `%-5d`        | Min. width (left-aligned)                | `printf("%-5d", 42);`     | `42   `              |
| `%05d`        | Pad with zeros                           | `printf("%05d", 42);`     | `00042`              |
| `%.2f`        | Precision (2 decimal places)             | `printf("%.2f", 3.1415);` | `3.14`               |
| `%10.2f`      | Width + precision                        | `printf("%10.2f", 3.14);` | `      3.14`         |
| `%+d`         | Force `+` sign                           | `printf("%+d", 42);`      | `+42`                |
| `%#x`         | Prefix (`0x` for hex, `0` for octal)      | `printf("%#x", 255);`     | `0xff`               |
| `%*d`         | Dynamic width (passed as argument)       | `printf("%*d", 5, 42);`   | `   42`              |

---

### **3. Escape Sequences**
| Sequence | Meaning          | Example (`printf`)         | Output       |
|----------|------------------|----------------------------|--------------|
| `\n`     | Newline          | `printf("Line1\nLine2");`  | `Line1`<br>`Line2` |
| `\t`     | Tab              | `printf("A\tB");`          | `A    B`     |
| `\\`     | Backslash        | `printf("\\");`            | `\`          |
| `\"`     | Double quote     | `printf("\"Hi\"");`        | `"Hi"`       |
| `\'`     | Single quote     | `printf("\'");`            | `'`          |
| `\b`     | Backspace        | `printf("A\bB");`          | `B` (overwrites `A`) |
| `\r`     | Carriage return  | `printf("123\rAB");`       | `AB3`        |

---

### **4. Advanced Usage**
#### **Printing Variables with Clarity**
```c
int apples = 5;
float price = 1.99;
printf("You bought %d apples for $%.2f each.\n", apples, price);
// Output: "You bought 5 apples for $1.99 each."
```

#### **Dynamic Formatting**
```c
int width = 8, precision = 3;
double num = 123.4567;
printf("%*.*f\n", width, precision, num);  // Equivalent to "%8.3f"
// Output: " 123.457" (padded to 8 chars, 3 decimal places)
```

#### **Printing Pointers**
```c
int x = 42;
printf("Address of x: %p\n", (void*)&x);
// Output: "Address of x: 0x7ffd3456"
```

---

### **5. Common Pitfalls**
1. **Mismatched Specifiers**  
   ```c
   printf("%d", 3.14);  // Undefined behavior (use `%f` for floats)
   ```
2. **Missing Arguments**  
   ```c
   printf("%d %d", 42);  // Undefined (too few args)
   ```
3. **Unsafe `%s` with NULL**  
   ```c
   printf("%s", NULL);  // Crashes (use `%.*s` with length checks)
   ```

---

### **6. Quick Reference Table**
| Need                  | Format Specifier      | Example               |
|-----------------------|-----------------------|-----------------------|
| Integer               | `%d`, `%i`            | `printf("%d", 42);`   |
| Float                 | `%f`                  | `printf("%.2f", 3.14);` |
| Hexadecimal           | `%x`, `%X`            | `printf("%X", 255);`  |
| String                | `%s`                  | `printf("%s", "Hi");` |
| Pointer               | `%p`                  | `printf("%p", &x);`   |
| Left-align            | `%-10s`               | `printf("%-10s", "Hi");` → `Hi        ` |
| Leading zeros         | `%05d`                | `printf("%05d", 42);` → `00042` |

---
---
---

For the **`long` data type** in C, you need to use specific format specifiers with
`printf()` to ensure correct printing. Here’s a cheat sheet tailored for `long` and 
related types:

---

### **1. Format Specifiers for `long`**
| Data Type          | Format Specifier | Example (`printf`)              | Output (Example) |
|--------------------|------------------|----------------------------------|------------------|
| **`long`**         | `%ld`            | `printf("%ld", 123456789L);`     | `123456789`      |
| **`unsigned long`**| `%lu`            | `printf("%lu", 4000000000UL);`   | `4000000000`     |
| **`long long`**    | `%lld`           | `printf("%lld", 123456789012LL);`| `123456789012`   |
| **`unsigned long long`** | `%llu`    | `printf("%llu", 18446744073709551615ULL);` | `18446744073709551615` |

---

### **2. Modifiers for `long`**
| Modifier           | Effect                                   | Example (`printf`)               | Output (Example)    |
|--------------------|------------------------------------------|-----------------------------------|---------------------|
| `%10ld`           | Min. width (right-aligned)              | `printf("%10ld", 12345L);`       | `     12345`        |
| `%-10ld`          | Min. width (left-aligned)               | `printf("%-10ld", 12345L);`      | `12345     `        |
| `%+ld`            | Force `+` sign                          | `printf("%+ld", 12345L);`        | `+12345`            |
| `%020ld`          | Pad with zeros                          | `printf("%020ld", 12345L);`      | `0000000000000012345` |

---

### **3. Hexadecimal/Octal for `long`**
| Specifier          | Output Format                  | Example (`printf`)               | Output (Example)    |
|--------------------|--------------------------------|-----------------------------------|---------------------|
| `%lx`             | Lowercase hex (`long`)         | `printf("%lx", 0xABCDEFL);`      | `abcdef`            |
| `%lX`             | Uppercase hex (`long`)         | `printf("%lX", 0xABCDEFL);`      | `ABCDEF`            |
| `%lo`             | Octal (`long`)                 | `printf("%lo", 123456L);`        | `361100` (octal)    |

---

### **4. Common Pitfalls**
1. **Mismatched Specifiers**  
   ```c
   long big_num = 123456789L;
   printf("%d", big_num);  // WRONG! Use `%ld` for `long`.
   ```
   → **Undefined behavior** (truncation or garbage values).

2. **Forgetting `L`/`LL` Suffixes**  
   ```c
   printf("%ld", 123456789);  // May work but risky. Always use `L` suffix.
   ```

3. **Portability Issues**  
   - On some systems, `long` and `int` are the same size (e.g., Windows 64-bit). 
     Use `long long` for 64-bit guarantees.

---

### **5. Examples**
#### **Printing `long` with Alignment**
```c
long population = 7800000000L;
printf("World population: %'20ld\n", population);
// Output: "World population:        7,800,000,000" (if locale supports commas)
```

#### **Hex/Octal for `long`**
```c
long flags = 0xDEADBEEFL;
printf("Flags: %#lx\n", flags);  // `#` adds "0x" prefix
// Output: "Flags: 0xdeadbeef"
```

#### **Unsigned `long`**
```c
unsigned long big = 18446744073709551615UL;
printf("Max unsigned long: %lu\n", big);
// Output: "Max unsigned long: 18446744073709551615"
```

---

### **6. Quick Reference Table**
| Need                  | Format Specifier | Example (`printf`)              |
|-----------------------|------------------|----------------------------------|
| Base-10 `long`        | `%ld`            | `printf("%ld", 123456789L);`     |
| Unsigned `long`       | `%lu`            | `printf("%lu", 4000000000UL);`   |
| `long long`           | `%lld`           | `printf("%lld", 123456789012LL);`|
| Hex (`long`)          | `%lx` or `%lX`   | `printf("%lX", 0xABCDEFL);`      |
| Octal (`long`)        | `%lo`            | `printf("%lo", 123456L);`        |
| Force `+` sign        | `%+ld`           | `printf("%+ld", 12345L);`        |

---

### **Key Notes**
- Always use `L` or `UL` suffixes for `long` literals to avoid compiler warnings.
- For **64-bit integers**, prefer `long long` and `%lld`/`%llu` for portability.
- Use `%zu` for `size_t` (though not `long`-specific, it’s common in system code).


