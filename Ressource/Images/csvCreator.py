import os
import csv
import random

# The output csv file is structured like this: minecraft:id,texture.png,name,quantity,price


# Set the folder path you want to scan
folder_path = './1.21.5'  # Change this to your actual folder

# Output CSV file
output_csv = 'output.csv'

# Open the CSV file for writing
with open(output_csv, mode='w', newline='') as file:
    writer = csv.writer(file)

    # Iterate through all files in the folder
    for filename in os.listdir(folder_path):
        if filename.lower().endswith('.png'):
            id =  os.path.splitext(filename)[0].replace('minecraft_','minecraft:')
            name = os.path.splitext(filename)[0].replace('_',' ')
            name = name.replace('minecraft ','')
            writer.writerow([id, filename, name, random.randint(0, 100), random.randint(0, 100)])

print(f"CSV file '{output_csv}' created successfully.")