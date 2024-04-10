import yfinance as yf
import pandas as pd
import matplotlib.pyplot as plt
import japanize_matplotlib

# 株価データの取得
ticker_symbol = 'AAPL'
start_date = '2022-01-01'
end_date = '2023-12-31'
stock_date = yf.download(ticker_symbol, start=start_date, end=end_date)

# 折れ線グラフを描画
plt.figure(figsize=(12, 6))
plt.plot(stock_date['Adj Close'], label=f'(ticker_symbol) Adj Close', color='blue')
plt.title(f'(ticker_symbol) 株価')
plt.xlabel('日付')
plt.ylabel('終値')
plt.legend(loc='upper left')
plt.grid(True)
plt.show()
