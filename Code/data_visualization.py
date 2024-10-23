import pandas as pd
import matplotlib.pyplot as plt
#input = pd.read_csv('Code/ProfilerStats.csv')  # Read the CSV file into a DataFrame

# Set the maximum display width
pd.set_option('display.width', 1000)
# Set the maximum number of columns to display
pd.set_option('display.max_columns', 50)
# Set the maximum number of rows to display
pd.set_option('display.max_rows', 100)
# Set the maximum column width
pd.set_option('display.max_colwidth', 100)
file_path = 'Data/ProfilerStats.csv'
#file_path = '/Users/adrianalfonso2/Downloads/GitHub/lab-2-c-profiler-adrianalfonso2/Data/ProfilerStats.csv'  
data = pd.read_csv(file_path)
#print(data.columns)  # Display the column names of the DataFrame
data.plot(x='Section', y=' Avg Time', kind='bar', color='orange')

plt.title('Avg Time per Section')
plt.xlabel('Section')
plt.ylabel('Avg Time (Sec)')
plt.xticks(rotation=45)
plt.show()

# data.plot(x='Section', y=' Avg Time', kind='bar', color='blue')
# plt.title('Avg Time per Section (Sec)')
# plt.xlabel('Section')
# plt.ylabel('Avg Time')
# plt.show()
#print(data.columns)  # Display the column names of the DataFrame
# plt.plot(data['Section'], data[' Total Time'], marker='o', linestyle='-', color='b')
# plt.title('Total Time per Section')
# plt.xlabel('Section')
# plt.ylabel('Total Time')
# plt.xticks(rotation=45)
# plt.grid(True)
# plt.show()