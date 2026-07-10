from fastapi import FastAPI

# create fastapi object
app = FastAPI()


# handles get request for root of API
@app.get("/")
def get_root():
    return "Hello World"


# handles get request for '/dict'
@app.get('/dict')
def get_dict():
    return { "key1": "value1", "key2": "value2" }


# handles get request for '/list'
@app.get('/list')
def get_list():
    return [
        { "object1" : { "key1": "value1", "key2": "value2" } },
        { "object2" : { "key1": "value1", "key2": "value2" } },
        { "object3" : { "key1": "value1", "key2": "value2" } }
    ]


# this expects query parameters called key1 and key2
# and returns them as JSON
@app.get('/params')
def get_params(key1 = None, key2 = None):
    return { "key1" : key1, "key2" : key2 }
