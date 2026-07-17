from fastapi import FastAPI
from models import PetModel
from database import PetDatabase

database = PetDatabase()
app = FastAPI()

# endpoint to get a list of all pets
@app.get("/all-pets")
def get_all_pets():
    return database.select_all_pets()


# endpoint to get a single pet based on ID
@app.get("/pet/{id}")
def get_pet_by_id(id: int):
    pet = database.select_pet_by_id(id)
    if pet == 0:
        return { "status": "not found" }
    return pet


# endpoint to delete a pet based on ID
@app.get("/delete/{id}")
def delete_pet(id: int):
    database.delete_pet(id)
    return { "status": "deleted" }


# endpoint to update a pet
@app.post("/update")
def update_pet(pet: PetModel):
    database.update_pet(pet)
    return { "status": "updated" }


# endpoint to add a pet
@app.post("/add")
def add_pet(pet: PetModel):
    database.add_pet(pet)
    return { "status": "updated"}
