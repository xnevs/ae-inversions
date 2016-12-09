#!/usr/bin/python3

import sys
import numpy as np
import pandas as pd 
import matplotlib.pyplot as plt

tr = pd.read_csv(sys.argv[1], sep=',', names=['alg','n','seq','rep','result','time'], index_col=[2,0,1])
tr.sort_index(inplace=True)
tr['time_one'] = tr['time'] / tr['rep']

pd.set_option('display.max_rows', len(tr))
print(tr)
pd.reset_option('display.max_rows')

def prepare(name, minn, maxn, mint, maxt):
    # figure
    fig = plt.figure(figsize=(14,8), facecolor='#FFFFAA')
    plt.suptitle(name, size=16, color='blue')

    # axes
    plt.axes(frameon=True, axisbg='0.9')
    #plt.title('Plot - time vs size')

    plt.xlabel('n')
    xadd = (maxn - minn) * 0.05
    plt.xlim(minn - xadd, maxn + xadd)
    #plt.xticks(np.arange(minn,maxn+1,maxn//10))
    plt.xticks()

    plt.ylabel('time [s]')
    yadd = (maxt - mint) * 0.05
    plt.ylim(mint - yadd, maxt + yadd)
    plt.yticks()
    plt.grid(which='both', axis='both')

    return fig


def plot(name, seq, algs, ns):
    df = tr.loc[seq,algs,ns]
    
    fig = prepare(name, min(ns),max(ns), min(df['time_one']), max(df['time_one']))
    for alg in algs:
        plt.plot(ns, df.loc[seq,alg]['time_one'], ('' if alg in fast_algs+fast_idx_algs else '--'), label=alg)
    plt.legend(loc='best', shadow=True)
    plt.tight_layout(rect=(0,0,1,.95))
    #plt.show()
    fig.savefig(name+'.pdf', dpi=96) # png, eps, pdf
    plt.close('all')

slow_algs     = ['bf','is1','is2','is2a']
slow_idx_algs = ['bf_idx','is1_idx','is2_idx']
fast_algs     = ['ms1','ms2','ms2_is2','ms2_is2a','ms3','ms3_is2']
fast_idx_algs = ['ms1_idx','ms2_idx','ms3_idx']

all_algs = slow_algs + fast_algs

tiny_ns = list(range(10, 201, 10))
small_ns = list(range(1000, 9001, 1000))
med_ns=list(range(10000, 90001, 10000))
large_ns = list(range(100000, 900001, 100000)) + list(range(1000000, 10000001, 1000000))


plot('tiny-inc', 'inc', all_algs, tiny_ns)
plot('tiny-dec', 'dec', all_algs, tiny_ns)
plot('tiny-rnd', 'rnd', all_algs, tiny_ns)

plot('tiny-inc-slow', 'inc', slow_algs, tiny_ns)
plot('tiny-dec-slow', 'dec', slow_algs, tiny_ns)
plot('tiny-rnd-slow', 'rnd', slow_algs, tiny_ns)

plot('small-inc', 'inc', all_algs, small_ns)
plot('small-dec', 'dec', all_algs, small_ns)
plot('small-rnd', 'rnd', all_algs, small_ns)

plot('medium-inc', 'inc', all_algs, med_ns)
plot('medium-dec', 'dec', all_algs, med_ns)
plot('medium-rnd', 'rnd', all_algs, med_ns)

plot('medium-inc-fast', 'inc', fast_algs, med_ns)
plot('medium-dec-fast', 'dec', fast_algs, med_ns)
plot('medium-rnd-fast', 'rnd', fast_algs, med_ns)

plot('large-inc-fast', 'inc', fast_algs, large_ns)
plot('large-dec-fast', 'dec', fast_algs, large_ns)
plot('large-rnd-fast', 'rnd', fast_algs, large_ns)

plot('bf', 'rnd', ['bf','bf_idx'], small_ns+med_ns)
plot('is1', 'rnd', ['is1','is1_idx'], small_ns+med_ns)
plot('is2', 'rnd', ['is2','is2_idx'], small_ns+med_ns)

plot('ms1', 'rnd', ['ms1','ms1_idx'], small_ns+med_ns+large_ns)
plot('ms2', 'rnd', ['ms2','ms2_idx'], small_ns+med_ns+large_ns)
plot('ms3', 'rnd', ['ms3','ms3_idx'], small_ns+med_ns+large_ns)
