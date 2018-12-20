# ft_ls (42 School Project)

**ft_ls** is a program that lists directory contents just like the Unix 'ls'.
To recollect what does it exactly do, you can read the BSD [man page](https://www.freebsd.org/cgi/man.cgi?query=ls&sektion=1&apropos=0&manpath=FreeBSD+4.3-RELEASE).

This program handles a lot of standard options: **[1AFRSTUacdfgloprtu]**

The main difference of the output is that ft_ls doesn't provide a multicolumn layout without the option -l.

### How to run
* git clone https://github.com/itiievskyi/42-ft_ls.git ~/ft_ls
* cd ~/ft_ls
* make
* ./ft_ls [-1AFRSTUacdfgloprtu][file ...]

### Sort
To sort a large number of files when recursive view is enabled I use the **merge sort**. Take a look at this [article](https://en.wikipedia.org/wiki/Merge_sort) to read about algorithm.

Look at some examples of ft_ls work:
![Example 1](/images/1.png)
![Example 2](/images/2.png)

### Enjoy!
