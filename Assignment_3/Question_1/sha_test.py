import sha

with open('pwd1.txt') as f:
    line = f.read()
    hash_val = line.split(':')[1].rstrip()[2:]
    salt = line.split(':')[1].rstrip()[0:2]

assert(len(hash_val) == 40)
print "Hash: " + hash_val
print "Salt: " + salt

count = 0
while count < 10000:
    input_val = salt + "%04d" % count
    hex_val = sha.new(input_val).hexdigest().upper()
    assert(len(hex_val) == 40)
    if hex_val == hash_val:
        break
    count += 1

if count < 10000:
    print "Found matching SHA-1 input: " + input_val
else:
    print "Couldn't find anything that worked!"
