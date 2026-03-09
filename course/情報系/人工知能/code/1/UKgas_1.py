import pandas as pd
UKgas = pd.read_csv("UKgas.csv")
nikkei = pd.read_csv("data_nikkei.csv")

import matplotlib.pyplot as plt

plt.figure(figsize=(30,14)) ##グラフサイズ
plt.plot(UKgas.x, linewidth=5, color='gray',label="UKgas",
        marker='P',markerfacecolor='blue',markersize=15,
         markeredgewidth=2, markeredgecolor='red')
plt.xlabel("Quatuor",fontsize=24)
plt.ylabel("Consumption of gas in England",fontsize=24)
plt.grid(linestyle = 'dashdot' )

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("UKgass.png")
