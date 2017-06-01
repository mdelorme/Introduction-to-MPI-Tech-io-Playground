import sys, os

files = sorted(os.listdir('out/'))
err = False

for f in files:
    fn = 'out/' + f

    f_in = open(fn, 'r')
    line = f_in.readline().strip()

    nid = int(f[-1])
    res = 'Hello world, from process #{}'.format(nid)

    print('TECHIO> message --channel "Process {}" "Output : \'{}\'"'.format(nid, line))
    if line != res:
        err = True
        print('TECHIO> message --channel "Process {}" "  -> ERROR, Expected : \'{}\'"'.format(nid, res))

if err:
    print('TECHIO> success false')
else:
    print('TECHIO> success true')
        
