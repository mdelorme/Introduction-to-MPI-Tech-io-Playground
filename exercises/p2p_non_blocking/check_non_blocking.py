import sys, os

f = open('out.txt', 'r')
tmp = f.readline()
blocking = f.readline()
tmp = f.readline()
non_blocking = f.readline()
blocking = float(blocking.split(':')[1][:-2])
non_blocking = float(non_blocking.split(':')[1][:-2])

print('Checking results')

if int(blocking) != 11:
    print('Something is wrong with blocking time. It should be ~11s')
    print('TECHIO> success false')
    exit(0)
    
if int(non_blocking) != 8:
    print('Something is wrong with the non-blocking time. It should be ~8s')
    print('TECHIO> success false')
    exit(0)

f_out = open('res.txt', 'r')
l1 = f_out.readline().split()
l1 = list(int(x) for x in l1)
if len(l1) != 100000:
    print('Error : received buffer is smaller than supposed to !')
    print('TECHIO> success false')
    exit(0)
    
for i, x in enumerate(l1):
    if x != i*2:
        print('Error : On 1st buffer, Received element #{} should be {}. Received {}'.format(i, i*i, x))
        print('TECHIO> success false')
        exit(0)

l2 = f_out.readline().split()
l2 = list(int(x) for x in l2)
if len(l2) != 100000:
    print('Error : received buffer is smaller than supposed to !')
    print('TECHIO> success false')
    exit(0)
    
for i, x in enumerate(l2):
    if x != -i:
        print('Error : On 2nd buffer, Received element #{} should be {}. Received {}'.format(i, i*i, x))
        print('TECHIO> success false')
        exit(0)

print('All good !!!')
print('TECHIO> success true')
