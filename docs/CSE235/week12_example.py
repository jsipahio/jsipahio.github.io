import tkinter as tk
import sqlite3


# database operations
# open database and create cursor
connection = sqlite3.connect("pets.db")
cursor = sqlite3.cursor(connection)

# create the table and add data, if it doesn't exist
cursor.execute(
"""CREATE TABLE IF NOT EXISTS pets(
    id INT PRIMARY KEY AUTOINCREMENT,
    pet_name TEXT NOT NULL,
    age INT NOT NULL,
    type TEXT NOT NULL
);
""")
cursor.execute(
"""INSERT INTO pets(pet_name, age, type)
VALUES ('',1,'')
WHERE NOT EXISTS (SELECT 1 FROM pets);
"""
)

main_window = tk.Tk()
main_window.title("Pets DB")
main_window.geometry("700x500")



main_window.mainloop()
