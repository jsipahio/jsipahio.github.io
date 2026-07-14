# import FastAPI class from fastapi package
from fastapi import FastAPI
# import the BaseModel class from pydantic
from pydantic import BaseModel


# example class that represents JSON data
# with an object at the top level
class ObjectExample(BaseModel):
    # specify the expected data types of each field
    # data1 is a string
    data1: str
    # data2 is an int
    data2: int
    # data 3 is an int with unknown contents
    # pydantic will interpret it as a list of strings
    data3: list


# example class that represents JSON data
# with an array at the top level
class ArrayExample(BaseModel):
    # here, we expect that the list contains ObjectExamples
    array: list[ObjectExample]


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


# put the url param in curly braces
# and add it as a funciton parameter
@app.get("url/{param}")
def get_url_param(param: str):
    return {"url_param": param}


# basic POST example
@app.post("/post-example")
def post_example():
    return { "key" : "value" }


# POST example that accepts JSON object
@app.post("/post-object")
def post_object(data: ObjectExample):
    print(f"data1: {data.data1}")
    print(f"data2: {data.data2}")
    print(f"data3: {data.data3}")
    return { "status" : "accpeted" }


# POST example that accepts JSON array
@app.post("/post-array")
def post_array(data: ArrayExample):
    for d in data.array:
        print(f"data1: {d.data1}")
        print(f"data2: {d.data2}")
        print(f"data3: {d.data3}")
    return { "status" : "accpeted" }
