import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import shapiro

norm  = np.loadtxt('norm')

print('Generating a random uniform law')
uni   = np.random.rand(5000)

print('Generating plots')
plt.figure(figsize=(8, 8), edgecolor='black', linewidth=1)
plt.subplot(211)
plt.hist(uni, bins=50)
plt.title('Uniform distribution')
plt.subplot(212)
plt.hist(norm, bins=50)
plt.title('Summed distribution')
plt.savefig('histograms.png')
print('TECHIO> open --static-dir /project/target/coll_red_ex1 index.html')

print('Computing Shapiro test')
print(' H0 : The distribution follows a Normal distribution')
s1 = shapiro(uni)
s2 = shapiro(norm)
print('')
print(' p-value for the uniform distribution : {:.5}'.format(s1[1]))
if (s1[1] > 0.05):
    print('  -> p > 5%; H0 is not rejected : the distribution does not diverges from a normal distribution')
else:
    print('  -> p <= 5%; H0 is rejected : the distribution diverges from a normal distribution')

print(' p-value for the summed distribution : {:.5}'.format(s2[1]))
if (s2[1] > 0.05):
    print('  -> p > 5%; H0 is not rejected : the distribution does not diverges from a normal distribution')
    print('  => OK')
    print('TECHIO> success true')
else:
    print('  -> p <= 5%; H0 is rejected : the distribution diverges from a normal distribution')
    print('  => ERROR !')
    print('TECHIO> success false')
