import pandas as pd # NOTE: PANDAS must be installed. Use 'pip install pandas'
import datetime
import pandas_datareader.data as web

# Company name to pull stock values from. TODO: input validation
companyName = 'AAPL'

# Dates we are pulling.
start = datetime.datetime(2015, 1, 1)
end = datetime.datetime.now()

# Pulling stock data for [companyName] from yahoo. 
df = web.DataReader(companyName, "yahoo", start, end)

# Records month to ensure monthly close data
lastMonth=str(df.index[0])
lastMonth=lastMonth[5:7] # Date is at the 5th and 6th index

for x in range(len(df)):
    currentMonth = str(df.index[x])
    if lastMonth != currentMonth[5:7]: # Compare previous month with current month
        print( (str(df.index[x]))[0:10] + "\t" + str(df.Close[x]))
        lastMonth = currentMonth[5:7] # Move on to next month

