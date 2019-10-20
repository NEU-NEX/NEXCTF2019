import random
import string


base64_table = ['t', 'd', 'p', 'q', 'w', 'G', 'U', 's', 'I', 'M', '6', 'o', 'a', 'b', '3', 'Q', '5', 'C', 'v', '2', 'g', 'J', 'O', '4', 'e', 'j', 'P', 'N', 'i', '9', 'E', 'f', 'z', 'u', 'K', 'y', 'F', 'B', 'D', 'T', 'r', 'h', 'n', 'A', '+', 'X', 'Z', 'W', 'Y', 'S', '7', 'V', 'l', 'L', '0', '/', 'c', '8', 'H', '1', 'R', 'k', 'm', 'x']

def base64_encode(s):
    l = len(s)
    i = 0
    result = ''
    while (i<l):
        s1 = s[i]
        b1 = bin(ord(s1))[2:].rjust(8,'0')
        i+=1

        if i >= l:
            b2 = '00000000'
        else:
            s2 = s[i]
            b2 = bin(ord(s2))[2:].rjust(8,'0')

        i+=1

        if i >= l:
            b3 = '00000000'
        else:
            s3 = s[i]
            b3= bin(ord(s3))[2:].rjust(8,'0')

        b = b1 + b2 + b3
        nb = [b[j:j+6] for j in [0,6,12,18]]

        result += base64_table[int(nb[0],2)]
        result += base64_table[int(nb[1],2)]
        
        if ((i - 1) >= l):
            result += '='
        else:
            result += base64_table[int(nb[2],2)]

        if i >= l:
            result += '='
        else:
            result += base64_table[int(nb[3],2)]

        i += 1

    return result

print base64_encode('flag{???????}')

#  output
#  jDSuj/Xy32bDaUMBaUa7eyF8bVJuaybuaygYj2z0bDgLb058e/l=
