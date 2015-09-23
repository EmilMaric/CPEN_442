cipher = { 
            'a' : 'k',
            'b' : 'g',
            'c' : '_',
            'd' : 'c',
            'e' : 't',
            'f' : 'i',
            'g' : 'f',
            'h' : 'y',
            'i' : 'n',
            'j' : 'b',
            'k' : 'e',
            'l' : 'o',
            'm' : 'a',
            'n' : 'q',
            'o' : 'r',
            'p' : 'm',
            'q' : 'p',
            'r' : 's',
            's' : '_',
            't' : 'l',
            'u' : 'v',
            'v' : 'u',
            'w' : 'w',
            'x' : 'd',
            'y' : 'h',
            'z' : '_',
}

alphabet = [    
                'a',
                'b',
                'c',
                'd',
                'e',
                'f',
                'g',
                'h',
                'i',
                'j',
                'k',
                'l',
                'm',
                'n',
                'o',
                'p',
                'q',
                'r',
                's',
                't',
                'u',
                'v',
                'w',
                'x',
                'y',
                'z',
]

letter_freq = {}
for letter in alphabet:
    letter_freq[ letter ] = 0

with open("cipher.txt") as f:
    content = f.readlines()

content = content[0].split("\n")[0].lower()

for c in content:
    letter_freq[c] += 1

sorted_alphabet = reversed(sorted( letter_freq, key=letter_freq.get))

# Frequency Analysis
for letter in sorted_alphabet:
    print "[" + letter + "] {" + str(letter_freq[letter]) + "} = " + ("#" * letter_freq[letter])

# Caesar Cipher
#for num in range(0, 26):
#    decipher = []
#    for letter in content:
#        idx = alphabet.index(letter.lower())
#        decipher.append(alphabet[(idx + num)%26])
#    print ''.join(decipher)

# Find the most repeated sequences in the ciphertext
#rep_seq = {}
#for start_idx in range(0, len(content) - 1):
#    for end_idx in range(start_idx + 2, len(content) + 1):
#        string = content[start_idx:end_idx]
#        if string in rep_seq:
#            rep_seq[string] += 1
#        else:
#            rep_seq[string] = 1
#
#rep_seq_opt = {}
#for seq in rep_seq:
#    if rep_seq[seq] > 1:
#        rep_seq_opt[seq] = rep_seq[seq]
#
#sorted_rep_seq = reversed(sorted( rep_seq_opt, key=rep_seq_opt.get))
#for seq in sorted_rep_seq:
#    print "\"" + seq + "\" : " + str(rep_seq[ seq ])

# Substitutions
substitute = []
for letter in content:
    substitute.append(cipher[letter])

substitute = ''.join(substitute)
print substitute
