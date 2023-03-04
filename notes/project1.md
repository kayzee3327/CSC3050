# usage of jal and jr

1. MIPS uses the jump-and-link instruction jal to call functions.

   - The jal saves the return address (the address of the next instruction) in the dedicated register `$ra`, before jumping to the function.

   - jal is the only MIPS instruction that can access the value of the program counter, so it can store the return address `PC+4` in `$ra`.

2. To transfer control back to the caller, the function just has to jump to the address that was stored in `$ra`.

   ```assembly
   jr $ra
   ```

   

# useful link

[how to solve "ld: symbol(s)  not found for architecture ..."](https://www.positioniseverything.net/ld-symbols-not-found-for-architecture-x86_64/)



# convert int to str (hex or bin)

1. convert `int` to be `unsigned int` before conversion
2. `<bitset>` header in cpp



# branch offset and jump target

calculate `(target - PC - 4) / 4`

```cpp
std::string get_offset_str_branch(unsigned int PC, unsigned int target){
    std::bitset<16> ofs((target - PC - 4)/4); // minus 4 is important
    return ofs.to_string();
}
```

but `bitset` has the problem of stack over flow

use `boost::dynamic_bitset` instead

https://stackoverflow.com/questions/6950230/how-to-calculate-jump-target-address-and-branch-target-address



# 配置新ubuntu

[安装cmake](https://blog.csdn.net/yuanzhoulvpi/article/details/122938078)



## Unordered_map fault

### Question

1. Why does `unordered_map` sometimes return a null value for a missing key and sometimes trigger segfault?
2. Why is there a `balabala.cc` not exist warning? Is it true that c++ transform unordered_map datastructure into files during compilation?
