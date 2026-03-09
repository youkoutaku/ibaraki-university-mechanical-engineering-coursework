x=[1.54,2.18,9.59,5.16,7.39,2.08,4.64,3.18,2.38,9.07,3.74,1.28]
y=[4.26,5.35,3.68,4.72,3.46,3.91,3.85,5.02,4.36,4.15,5.79,5.63]


import matplotlib.pyplot as plt
plt.figure( figsize=(10,10) )
plt.plot(x,y,'.',linewidth=4,color='black',
    label="(2)",marker='X',markerfacecolor='red',markersize=15,
    markeredgewidth=4,markeredgecolor='blue',alpha=0.7)
plt.xlabel('Consultation rate',fontsize=18)
plt.ylabel('Death rate',fontsize=18)
plt.grid(linestyle='dashed')

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("Fig2.png")