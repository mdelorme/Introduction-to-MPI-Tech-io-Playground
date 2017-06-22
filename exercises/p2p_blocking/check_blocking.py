import sys, os

v1 = int(sys.argv[1])
v2 = int(sys.argv[2])

files = sorted(os.listdir('out/'))
err = False

print('The random values provided are : {} and {}'.format(v1, v2))

for rank, f in enumerate(files):
    fn = 'out/' + f

    f_in = open(fn, 'r')
    line = f_in.readline().strip()
    v = int(line)

    if rank == 0:
        res = v1 + v2
    else:
        res = v1 * v2

    print('TECHIO> message --channel "Process {}" "{}"'.format(rank, line))
    if v != res:
        err = True
        print('TECHIO> message --channel "Process {}" "  -> ERROR, Expected : {}"'.format(rank, res))

if err:
    print('TECHIO> success false')
else:
    print('TECHIO> success true')
        
