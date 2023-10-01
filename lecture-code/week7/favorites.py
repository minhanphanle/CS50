# import csv

# # Open a CSV file
# with open("favorites.csv", "r") as file:
#     # Create reader
#     reader = csv.DictReader(file)

#     # Iterate over CSV file, printing each favorite
#     counts = {}
#     for row in reader:
#         favorite = row["problem"]
#         if favorite in counts:
#             counts[favorite] += 1
#         else:
#             counts[favorite] = 1

#     favorite = input("Favorite: ")
#     if favorite in counts:
#         print(f"{favorite}: {counts[favorite]}")

#     # for favorite in sorted(counts, key = lambda problem: counts[problem], reverse=True):
#     #     print(f"{favorite}: {counts[favorite]}")

# ------------------ SQL ------------------ #

from cs50 import SQL

db = SQL("sqlite:///favorites.db")

favorite = input("Favorite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite) # Return a list of dictionaries
# In the world of SQL usually use ? 

row = rows[0]

print(row["n"])

