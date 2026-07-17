import sqlite3
import tkinter as tk
from tkinter import messagebox, ttk

# path to database
DB_PATH = "pets.db"

# function to check if the database exists
# if it doesn't, it creates it
def initialize_database():
    # create connection and cursor
    connection = sqlite3.connect(DB_PATH)
    cursor = connection.cursor()

    # this will create the pets table if it does not already exist
    cursor.execute(
        """
        CREATE TABLE IF NOT EXISTS pets (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            pet_name TEXT NOT NULL,
            age INTEGER NOT NULL,
            type TEXT NOT NULL
        );
        """
    )

    # this will check if the database is empty
    cursor.execute("SELECT COUNT(*) FROM pets")
    if cursor.fetchone()[0] == 0:
        # if it is, it will insert data into it
        cursor.executemany(
            "INSERT INTO pets (pet_name, age, type) VALUES (?, ?, ?)",
            [
                ("Fido", 2, "Dog"),
                ("Mittens", 4, "Cat"),
                ("Bella", 1, "Dog"),
                ("Whiskers", 6, "Cat"),
                ("Shadow", 3, "Rabbit"),
            ],
        )

    # closing the database
    connection.commit()
    connection.close()


# class that inherits from the base Tkinter window
# this is more typical of how a Tkinter app is created
class PetApp(tk.Tk):
    # constructor handles setting up the window geometry and name
    def __init__(self):
        super().__init__()
        self.title("Pets Database")
        self.geometry("760x500")
        self.selected_pet_id = None

        # Tkinter variables to enable modification of the database through the app
        self.pet_name_var = tk.StringVar()
        self.age_var = tk.StringVar()
        self.pet_type_var = tk.StringVar()
        self.status_var = tk.StringVar(value="Select a pet or add a new one.")

        # call helper functions to construct the coponents on the window
        self.build_ui()
        # and load the database
        self.load_pets()


    # helper function to build the main UI of the app
    def build_ui(self):
        # create a frame to hold all the components
        main_frame = ttk.Frame(self, padding=12)
        main_frame.pack(fill="both", expand=True)

        # this frame is for the form that allows the fields to be modified
        # or for new pets to be added
        form_frame = ttk.LabelFrame(main_frame, text="Pet details", padding=10)
        form_frame.pack(fill="x", pady=(0, 12))

        # add the entry components to the form_frame
        ttk.Label(form_frame, text="Name:").grid(row=0, column=0, sticky="w", padx=5, pady=5)
        ttk.Entry(form_frame, textvariable=self.pet_name_var, width=30).grid(
            row=0, column=1, sticky="ew", padx=5, pady=5
        )

        ttk.Label(form_frame, text="Age:").grid(row=1, column=0, sticky="w", padx=5, pady=5)
        ttk.Entry(form_frame, textvariable=self.age_var, width=30).grid(
            row=1, column=1, sticky="ew", padx=5, pady=5
        )

        ttk.Label(form_frame, text="Type:").grid(row=2, column=0, sticky="w", padx=5, pady=5)
        ttk.Entry(form_frame, textvariable=self.pet_type_var, width=30).grid(
            row=2, column=1, sticky="ew", padx=5, pady=5
        )

        # create a sub-frame for the buttons
        button_frame = ttk.Frame(form_frame)
        button_frame.grid(row=3, column=0, columnspan=2, sticky="ew", pady=(8, 0))

        # create and add buttons for creating, updating, and deleting pets
        ttk.Button(button_frame, text="Add", command=self.add_pet).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Update", command=self.update_pet).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Delete", command=self.delete_pet).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Clear", command=self.clear_form).pack(side="left", padx=5)
        ttk.Button(button_frame, text="Refresh", command=self.load_pets).pack(side="left", padx=5)

        # create a frame for the pet table display
        table_frame = ttk.LabelFrame(main_frame, text="Pets", padding=10)
        table_frame.pack(fill="both", expand=True)

        # the tree view is like a Listbox, but better for displaying tabular data
        # it is added by ttk
        # first, specifiy the column names
        columns = ("id", "name", "age", "type")
        # then create the Treeview
        self.tree = ttk.Treeview(table_frame, columns=columns, show="headings", height=12)
        # bind "pretty" names to the internal column names
        self.tree.heading("id", text="ID")
        self.tree.heading("name", text="Name")
        self.tree.heading("age", text="Age")
        self.tree.heading("type", text="Type")
        # set dimensions of the columns
        self.tree.column("id", width=50, anchor="center")
        self.tree.column("name", width=180)
        self.tree.column("age", width=60, anchor="center")
        self.tree.column("type", width=120)
        self.tree.pack(fill="both", expand=True)
        self.tree.bind("<<TreeviewSelect>>", self.on_select)

        ttk.Label(main_frame, textvariable=self.status_var, foreground="blue").pack(anchor="w", pady=(8, 0))


    # function to initially load the pet database
    def load_pets(self):
        # create connection and cursor
        connection = sqlite3.connect(DB_PATH)
        cursor = connection.cursor()

        # select all data
        cursor.execute("SELECT id, pet_name, age, type FROM pets ORDER BY id")
        rows = cursor.fetchall()
        connection.close()

        # empty the Treeview
        for item in self.tree.get_children():
            self.tree.delete(item)

        # insert the data that was just loaded into the Treeview
        for row in rows:
            self.tree.insert("", "end", values=row)

        # clear values from the form and set the status message
        self.clear_form()
        self.status_var.set("Loaded pets from the database.")


    # sets form to initial state
    def clear_form(self):
        # deselect any selected pet in the Treeview
        self.selected_pet_id = None
        # set the form variables to null values
        self.pet_name_var.set("")
        self.age_var.set("")
        self.pet_type_var.set("")
        # update GUI so that no pet appears to be selected
        if self.tree.selection():
            self.tree.selection_remove(self.tree.selection()[0])


    # event handler for when a pet is selected in the Treeview
    def on_select(self, _event):
        selected_items = self.tree.selection()
        if not selected_items:
            return

        # read the selected item
        item = selected_items[0]
        # convert to individual variables
        pet_id, pet_name, age, pet_type = self.tree.item(item, "values")
        # update the id tracker
        self.selected_pet_id = pet_id
        # set the values of the form Entry widgets
        self.pet_name_var.set(pet_name)
        self.age_var.set(age)
        self.pet_type_var.set(pet_type)
        # update the status message
        self.status_var.set(f"Editing pet #{pet_id}.")


    # handler for the Add button
    def add_pet(self):
        # read data from the Entry widgets
        # removes extra whitespace with strip()
        pet_name = self.pet_name_var.get().strip()
        pet_type = self.pet_type_var.get().strip()

        # pet_name and pet_type cannot be None due to the NOT NULL constraint
        if not pet_name or not pet_type:
            messagebox.showwarning("Missing data", "Please enter a pet name and type.")
            return

        # try to parse the age as an integer
        try:
            age = int(self.age_var.get())
        except ValueError:
            messagebox.showwarning("Invalid age", "Age must be a whole number.")
            return

        # open the database
        connection = sqlite3.connect(DB_PATH)
        cursor = connection.cursor()
        # insert the new row
        cursor.execute(
            "INSERT INTO pets (pet_name, age, type) VALUES (?, ?, ?)",
            (pet_name, age, pet_type),
        )
        # commit the transaction and close
        connection.commit()
        connection.close()

        # refresh the view
        self.load_pets()
        self.status_var.set(f"Added {pet_name}.")


    # handler for Update button
    def update_pet(self):
        # check that a row is selected for updating
        if self.selected_pet_id is None:
            messagebox.showwarning("No selection", "Select a pet before updating it.")
            return

        # same is add_pet, read values of name and type and check if they are not None
        pet_name = self.pet_name_var.get().strip()
        pet_type = self.pet_type_var.get().strip()

        if not pet_name or not pet_type:
            messagebox.showwarning("Missing data", "Please enter a pet name and type.")
            return

        # verify the age
        try:
            age = int(self.age_var.get())
        except ValueError:
            messagebox.showwarning("Invalid age", "Age must be a whole number.")
            return

        # create connection and run UPDATE table query
        connection = sqlite3.connect(DB_PATH)
        cursor = connection.cursor()
        cursor.execute(
            "UPDATE pets SET pet_name = ?, age = ?, type = ? WHERE id = ?",
            (pet_name, age, pet_type, self.selected_pet_id),
        )
        connection.commit()
        connection.close()

        # refresh GUI
        self.load_pets()
        self.status_var.set(f"Updated pet #{self.selected_pet_id}.")


    # hanlder for Delete button
    def delete_pet(self):
        # verify that a row is selected
        if self.selected_pet_id is None:
            messagebox.showwarning("No selection", "Select a pet before deleting it.")
            return

        # display confirmation message box
        if not messagebox.askyesno("Confirm delete", "Delete this pet from the database?"):
            return

        # open database and run DELETE FROM query
        connection = sqlite3.connect(DB_PATH)
        cursor = connection.cursor()
        cursor.execute("DELETE FROM pets WHERE id = ?", (self.selected_pet_id,))
        connection.commit()
        connection.close()

        # refresh GUI
        self.load_pets()
        self.status_var.set(f"Deleted pet #{self.selected_pet_id}.")


# main function
def main():
    # create database if it does not exist
    initialize_database()
    # create the PetApp object
    app = PetApp()
    # since PetApp inherits from tk.Tk, it has access to the mainloop() function
    app.mainloop()


# run the main function
if __name__ == "__main__":
    main()
