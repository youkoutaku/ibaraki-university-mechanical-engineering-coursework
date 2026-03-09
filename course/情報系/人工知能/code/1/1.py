import pandas as pd
UKgas = pd.read_csv("UKgas.csv")
nikkei = pd.read_csv("data_nikkei.csv")

import matplotlib.pyplot as plt

plt.figure(figsize=(15,7)) ##グラフサイズ
plt.plot(UKgas.x, linewidth=4, color='gray',label="UKgas",
        marker='o',markerfacecolor='red',markersize=12,
         markeredgewidth=3, markeredgecolor='blue')
plt.xlabel("Quatuor",fontsize=18)
plt.ylabel("Consumption of gas in England",fontsize=18)
plt.grid(linestyle = 'dotted' )

plt.legend(fontsize=18)
plt.tick_params(labelsize=18)

plt.savefig("UKgass.png")

# matplotlib.linestlye
# 'solid'実線
# 'dashed'点線
# 'dashdot'一点鎖線
# 'dotted'点
