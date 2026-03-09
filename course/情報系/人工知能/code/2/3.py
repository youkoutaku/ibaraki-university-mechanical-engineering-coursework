x=[131,131,133,140,145,149,155,156,157,186]
y=[204,370,46,223,497,189,123,327,601,199]

import matplotlib.pyplot as plt
plt.figure( figsize=(10,10) )
plt.plot(x,y,'.',linewidth=4,color='black',
    label="(3)",marker='X',markerfacecolor='red',markersize=15,
    markeredgewidth=4,markeredgecolor='blue',alpha=0.7)
plt.xlabel('Height[m]',fontsize=18)
plt.ylabel('Total water storage[100 million m^2]',fontsize=18)
plt.grid(linestyle='dashed')

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("Fig3.png")