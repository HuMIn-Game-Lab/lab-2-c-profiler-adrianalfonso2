import pandas as pd
import matplotlib.pyplot as plt

pd.set_option('display.width', 1000)
pd.set_option('display.max_columns', 50)
pd.set_option('display.max_rows', 100)
pd.set_option('display.max_colwidth', 100)

file_path = 'Data/ProfilerStats.csv'
data = pd.read_csv(file_path)

data.plot(x='Section', y='Avg Time', kind='bar', color='orange')
plt.title('Avg Time per Section')
plt.xlabel('Section')
plt.ylabel('Avg Time (Sec)')
plt.xticks(rotation=45)
plt.show()

data.plot(x='Section', y='Total Time', kind='bar', color='blue')
plt.title('Total Time per Section')
plt.xlabel('Section')
plt.ylabel('Total Time')
plt.xticks(rotation=45)
plt.show()
