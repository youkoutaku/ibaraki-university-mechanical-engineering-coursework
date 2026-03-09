import matplotlib.pyplot as plt
import numpy as np

x1=[8,7,5,4,6,2,3,9]
x2=[8,7,9,3,8,3,6,7]
x3=[3,7,8,3,8,5,6,9]
y=[18,12,14,6,12,8,10,16]

x1_h=(x1-np.mean(x1))/np.std(x1,ddof=1)
x2_h = (x2-np.mean(x2))/np.std(x2,ddof=1)
x3_h=(x3-np.mean(x3))/np.std(x3,ddof=1)
y_h=(y-np.mean(y))/np.std(y,ddof=1)

plt.plot(x1_h,y_h,'o',color='red',label="x1_h")
plt.plot(x2_h,y_h,'o',color='blue',label="x2_h")
plt.plot(x3_h,y_h,'o',color='green',label="x3_h")
plt.xlabel("x_h")
plt.ylabel("y_h")

def jukaiki_bunseki(x1, x2, x3, y):
 N = np.size(x1) # 標本数
 Y = np.c_[y]
 X = np.c_[x1, x2, x3, np.ones(N)]
 
 tmp = np.dot(X.T, X) # XTX
 r1 = np.linalg.inv(tmp) # (XTX)^-1 逆行列
 r2 = np.dot(X.T, Y) # XTY
 A = np.dot(r1, r2) # 係数ベクトル
 
 a1 = A[0] # 傾き
 a2 = A[1] # 傾き
 a3 = A[2] #　傾き
 b = A[3] # 切片b
 
 # [追加機能]回帰直線の妥当性を評価する
 Y_hat = a1*x1+a2*x2+a3*x3+b # 予測値
 C = np.corrcoef(Y_hat, y)[0,1] # 相関係数
 # 決定係数
 R2 = np.sum( (Y_hat-np.mean(y))**2 ) / np.sum( (y-np.mean(y))**2 )
 
 return a1, a2, a3 ,b, C, R2

print("標準化済みの重回帰微分")
print(f'偏相関係数a1={jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[0]}')
print(f'偏相関係数a2="{jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[1]}')
print(f'偏相関係数a3="{jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[2]}')
print(f'b="{jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[3]}')
print(f'相関係数C={jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[4]}')
print(f'決定係数R2={jukaiki_bunseki(x1_h,x2_h,x3_h,y_h)[5]}')
