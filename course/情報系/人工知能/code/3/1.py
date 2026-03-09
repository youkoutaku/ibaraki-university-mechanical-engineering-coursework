import numpy as np
from scipy.stats import t
x=[7.86, 7.89, 7.84, 7.90, 7.82]
x_bar = np.mean(x)
alpha = 0.01
s2 =np.var(x,ddof=1)
N = 5
m = N-1 # 自由度
t = t.ppf( 1-alpha/2, df=m ) # カウントの向きが逆なので
Left = x_bar - t*np.sqrt(s2/N)
Right = x_bar + t*np.sqrt(s2/N)
[Left, Right]