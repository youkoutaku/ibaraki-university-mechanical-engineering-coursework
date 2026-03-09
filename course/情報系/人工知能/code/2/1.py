x=[140,101,149,82,118,98,143,69,137]
y=[120,113,160,76,105,93,140,73,140]

import matplotlib.pyplot as plt
plt.figure( figsize=(10,10) )
plt.plot(x,y,'.',linewidth=4,color='black',
    label="(1)",marker='X',markerfacecolor='red',markersize=15,
    markeredgewidth=4,markeredgecolor='blue',alpha=0.7)
plt.xlabel('Price',fontsize=18)
plt.ylabel('Max_output',fontsize=18)
plt.grid(linestyle='dashed')

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("Fig1.png")