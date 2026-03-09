import pandas as pd
UKgas = pd.read_csv("UKgas.csv")
nikkei = pd.read_csv("data_nikkei.csv")

import matplotlib.pyplot as plt

plt.figure(figsize=(30,14)) ##グラフサイズ
plt.plot(nikkei.end, linewidth=6, color='red',label="nikkei",
        marker='o',markerfacecolor='blue',markersize=10,
         markeredgewidth=2, markeredgecolor='black')
plt.xlabel("Time",fontsize=24)
plt.ylabel("JPY",fontsize=24)
plt.grid(linestyle = 'solid' )

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("nikkei.png")