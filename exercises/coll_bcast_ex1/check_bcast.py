import sys, os

f_in = open('input', 'r')
values = list(float(x) for x in f_in)

p0 = 0.0
p1 = 0.0
p2 = 0.0

for v in values[1:]:
    if v < 0.0:
        p2 += v
    else:
        p1 += v
    p0 += v

files = sorted(os.listdir('out/'))
err = False

for rank, f in enumerate(files):
    fn = 'out/' + f

    f_in = open(fn, 'r')
    line = f_in.readline().strip()
    v = float(line)

    if rank == 0:
        res = p0
    elif rank == 1:
        res = p1
    else:
        res = p2

    print('TECHIO> message --channel "Process {}" "{}"'.format(rank, line))
    if abs(v-res) > 1e-5:
        err = True
        print('TECHIO> message --channel "Process {}" "  -> ERROR, Expected : {}"'.format(rank, res))

if err:
    print('TECHIO> success false')
else:
    print('TECHIO> success true')
        
