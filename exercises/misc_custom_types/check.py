f_1 = open('ref', 'r')
f_2 = open('out', 'r')

for i, lines in enumerate(zip(f_1, f_2)):
    l1, l2 = lines
    print('TECHIO> message --channel "Your program" "{}"'.format(l2.strip()))
    print('TECHIO> message --channel "Solution" "{}"'.format(l1.strip()))

    if l1 != l2: 
        print('Error, line {}'.format(i))
        print('  - Your solution : {}'.format(l2))
        print('  - Expected : {}'.format(l1))
        print('TECHIO> success false')
        exit(0)

print('TECHIO> success true')


