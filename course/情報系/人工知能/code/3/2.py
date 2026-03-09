import numpy as np
from scipy.stats import chi2
x=[15.4, 16.1, 15.7, 16.6, 14.9, 15.5, 16.2]
x_bar = np.mean(x)
alpha = 0.01
s2 =np.var(x,ddof=1)
N = 8
m = N-1 # 自由度
chi2_L = chi2.ppf( 1-alpha/2, df=m ) # カウントの向きが逆なので
chi2_R = chi2.ppf( alpha/2, df=m )
Left = (N-1)*s2/chi2_L
Right = (N-1)*s2/chi2_R
[Left, Right]