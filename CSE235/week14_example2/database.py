import sqlite3
from models import PetModel


class PetDatabase:
    def __init__(self):
        # create single connection for each class object
        # the check_same_thread is a hack for this example because of the way
        # SQLite3 works. there are more elegant solutions for production apps,
        # which are beyond the scope of this course
        self.connection = sqlite3.connect("pets.db", check_same_thread=False)
        cursor = self.connection.cursor()
            
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

        self.connection.commit()


    # defining __del__ to close database connection 
    # when object is no longer being used
    def __del__(self):
        self.connection.commit()
        self.connection.close()


    def add_pet(self, pet: PetModel):
        cursor = self.connection.cursor()
        cursor.execute("INSERT INTO pets(pet_name, age, type) VALUES(?,?,?)", 
                       (pet.name, pet.age, pet.type))
        self.connection.commit()
        

    def update_pet(self, pet: PetModel):
        cursor = self.connection.cursor()
        cursor.execute("""UPDATE pets
                       set pet_name = ?,
                       age = ?,
                       type = ?
                       WHERE id = ?""",
                       (pet.name, pet.age, pet.type, pet.id))
        self.connection.commit()


    def delete_pet(self, pet_id):
        cursor = self.connection.cursor()
        cursor.execute("DELETE FROM pets WHERE id = ?", (pet_id,))
        self.connection.commit()


    def select_all_pets(self):
        cursor = self.connection.cursor()
        cursor.execute("SELECT id, pet_name, age, type FROM pets")
        pets = list(cursor.fetchall())
        pet_objects = []
        for pet in pets:
            pet_dict = {
                "id": pet[0],
                "name": pet[1],
                "age": pet[2],
                "type": pet[3]
            }
            pet_object = PetModel(**pet_dict)
            pet_objects.append(pet_object)
        return pet_objects
    

    def select_pet_by_id(self, pet_id):
        cursor = self.connection.cursor()
        cursor.execute("SELECT id, pet_name, age, type FROM pets WHERE id = ?", (pet_id,))
        if cursor.fetchone() == 0:
            return 0
        pet = cursor.fetchone()
        pet_dict = {
            "id": pet[0],
            "name": pet[1],
            "age": pet[2],
            "type": pet[3]
        }
        pet_object = PetModel(**pet_dict)
        return pet_object
