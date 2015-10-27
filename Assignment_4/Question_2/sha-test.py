import sha

char_set = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+-='

with open('pwd2.txt') as f:
    line = f.read()
    hash_val = line.split(':')[1].rstrip()[2:]
    salt = line.split(':')[1].rstrip()[0:2]

assert(len(hash_val) == 40)
assert(len(salt) == 2)
print "Hash: " + hash_val
print "Salt: " + salt

count = 0
plaintext = ['a', 'a', 'a', 'a', 'a', 'a']
while count < pow(len(char_set), 6):
    plaintext[0] = char_set[(count / pow(len(char_set), 5)) % len(char_set)]
    plaintext[1] = char_set[(count / pow(len(char_set), 4)) % len(char_set)]
    plaintext[2] = char_set[(count / pow(len(char_set), 3)) % len(char_set)]
    plaintext[3] = char_set[(count / pow(len(char_set), 2)) % len(char_set)]
    plaintext[4] = char_set[(count / pow(len(char_set), 1)) % len(char_set)]
    plaintext[5] = char_set[count % len(char_set)]
    input_val = salt + ''.join(plaintext)
    hex_val = sha.new(input_val).hexdigest().upper()
    assert(len(hex_val) == 40)
    if hex_val == hash_val:
        break
    if (count % 100000000) == 0:
        print ''
        print "Count: " + str(count)
        print "Plaintext: " + input_val
    count += 1

if count < pow(len(char_set), 6):
    print "Found matching SHA-1 input: " + input_val
else:
    print "Couldn't find anything that worked!"
