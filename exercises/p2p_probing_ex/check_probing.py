import sys, os

print('Checking results')
f_in = open('res.txt', 'r')

ts_table = [(1, 0), (2, 1), (1, 1), (1, 0), (2, 0)]

for i, line in enumerate(f_in):
    line = line.strip()
    
    if i == 5:
        if line == 'TECHIO> success false':
            print('Error : The count is wrong !')
        else:
            print('Final count is OK !')
        print(line)
        exit(0)
            
    result = 'Received a message from process {0[0]} with tag {0[1]}'.format(ts_table[i])
    if line.strip() != result:
        print('Error !')
        print(' - Process wrote : {}'.format(line))
        print(' - Expected : {}'.format(result))
        exit(0)

    print(line)
            


        
    
