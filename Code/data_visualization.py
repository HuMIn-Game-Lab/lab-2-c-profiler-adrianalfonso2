import pandas as pd
import matplotlib.pyplot as plt

pd.set_option('display.width', 1000)
pd.set_option('display.max_columns', 50)
pd.set_option('display.max_rows', 100)
pd.set_option('display.max_colwidth', 100)

file_path = ('ProfilerStats.csv')
data = pd.read_csv("ProfilerStats.csv")

if 'Avg Time' in data.columns:
    data = data[data['Avg Time'] > 0]  

    if not data.empty:
        data.plot(x='Section', y='Avg Time', kind='bar', color='orange')
        plt.title('Avg Time per Section')
        plt.xlabel('Section')
        plt.ylabel('Avg Time (Sec)')
        plt.xticks(rotation=45)
        plt.show()
    else:
        print("No valid data to plot for 'Avg Time'.")
else:
    print("Error: 'Avg Time' column not found in the CSV file.")

if 'Total Time' in data.columns:
    if not data.empty:
        data.plot(x='Section', y='Total Time', kind='bar', color='blue')
        plt.title('Total Time per Section')
        plt.xlabel('Section')
        plt.ylabel('Total Time (Sec)')
        plt.xticks(rotation=45)
        plt.show()
    else:
        print("No valid data to plot for 'Total Time'.")
else:
    print("Error: 'Total Time' column not found in the CSV file.")