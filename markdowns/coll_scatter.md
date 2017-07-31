# Scattering and Gathering

**Scattering** and **Gathering** are two very useful collective operations. They are used to distribute and regroup data from one process to many, or from many process to one. As an example is worth a thousand words, let's see one :

Consider a system with four processes. Process 0 is reading data and stores a 4x4 matrix. Now, as for the broadcast example, you want to dispatch the data to the other processes, but this time you don't want each process to have all the data, but only a piece. That's when scatter comes into play. The scattering operation divides the send buffer into equal parts of `count` elements and distribute them over every process. See the figure below for a clearer comprehension.

![Scattering operation](/img/scatter.png)
*The scattering operation distributes evenly a set of data over all the processes of a communicator.*

The gathering operation does the exact opposite. If you consider four processes with a buffer of four values each, the gathering operation will regroup everything on one single process. The order follows the rank in the communicator.

![Gathering operation](/img/gather.png)
*The gathering operation regroups every buffer into a single one on a specific process.*

This seems pretty straightforward so let's apply this to an example.


