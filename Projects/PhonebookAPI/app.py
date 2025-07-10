'''References
1) https://fastapi.tiangolo.com/
2) https://github.com/sumanentc/python-sample-FastAPI-application
3) https://dassum.medium.com/building-rest-apis-using-fastapi-sqlalchemy-uvicorn-8a163ccf3aa1

- Python Phonebook Starter by Siddhrajsinh Pradumansinh Solanki used as a base -
Miguel Cervantes
1002045172
'''
# Import the required modules
from fastapi import FastAPI, HTTPException, Depends
from fastapi.security import HTTPBearer, HTTPAuthorizationCredentials
from pydantic import BaseModel
from sqlalchemy import create_engine, Column, Integer, String
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker
import re
import logging
from logging.config import dictConfig
from config import DATABASE_URL, LOGGING_CONFIG, API_KEYS, NAME_PATTERN, PHONE_PATTERN

# Configures log file settings. Ensures that important logs are filed in audit_log.log
# while excluding SQLAlchemy engine logs from the file but not from the console
dictConfig(LOGGING_CONFIG)

# Intialize logger variable which will be used for logging API Calls
logger = logging.getLogger("__main__")

# Enables Swagger UI token-based authentication via authenticate button.
security = HTTPBearer()

# Authorize the user's role using their token. Also prints the attempt to the log file.
def authorize(credentials: HTTPAuthorizationCredentials = Depends(security)):
    token = credentials.credentials
    role = API_KEYS.get(token, "none")
    logger.info(f"Authorization attempt with token: {token} | role: {role}")
    return role

# Create the FastAPI app
app = FastAPI()

# Create the SQLite database engine
engine = create_engine(DATABASE_URL, echo=False)

# Create the base class for the database models
Base = declarative_base()

# Create the PhoneBook model class
class PhoneBook(Base):
    __tablename__ = "phonebook"

    id = Column(Integer, primary_key=True)
    full_name = Column(String)
    phone_number = Column(String)

# Create the database schema
Base.metadata.create_all(engine)

# Create the session class for database operations
Session = sessionmaker(bind=engine)

# Create the Pydantic model class for request and response data
class Person(BaseModel):
    full_name: str
    phone_number: str

# Set the name pattern that will be used for Regex name validation
name_pattern = NAME_PATTERN

# Set the phone pattern that will be used for regex phone number validation
phone_pattern = PHONE_PATTERN

# Define regex patterns for input validation
name_regex_pattern = re.compile(name_pattern, re.VERBOSE)
phone_regex_pattern = re.compile(phone_pattern, re.VERBOSE)



# Define the API endpoints
@app.get("/PhoneBook/list")
def list_phonebook(role: str = Depends(authorize)):
    if role not in ["read", "readwrite"]:
        logger.info('Unauthorized attempt to list phonebook.')
        raise HTTPException(status_code=403, detail="You are not authorized to access this call")
    # Log that the List Names API Call was issued
    logger.info('List Names API Call Issued')
    # Get a new session
    session = Session()
    # Query all the records in the phonebook table
    phonebook = session.query(PhoneBook).all()
    # Close the session
    session.close()
    # Return the list of records as JSON objects
    return phonebook

@app.post("/PhoneBook/add")
def add_person(person: Person, role: str = Depends(authorize)):
    if role != "readwrite":
        logger.info('Unauthorized attempt to access Add Person API call')
        raise HTTPException(status_code=403, detail="You are not authorized to access this call")
    # Log that the Add Person API call was issued along with the name of the person added.
    logger.info('Add Person API Call Issued | Name = %s', person.full_name)
    # Use name_regex pattern for input validation
    if not name_regex_pattern.match(person.full_name):
        logger.info('Input was invalid. No new addition to database')
        raise HTTPException(status_code=400, detail="Invalid name")
    # Use phone_regex pattern for input validation
    if not phone_regex_pattern.match(person.phone_number):
        logger.info('Input was invalid. No new addition to database')
        raise HTTPException(status_code=400, detail="Invalid phone number")
    # Get a new session
    session = Session()
    # Check if the person already exists in the database by phone number
    existing_person = session.query(PhoneBook).filter_by(phone_number=person.phone_number).first()
    # If the person exists, raise an exception
    if existing_person:
        session.close()
        logger.info('Person already exists in the database. No new addition to database')
        raise HTTPException(status_code=400, detail="Person already exists in the database")
    # Otherwise, create a new PhoneBook record and add it to the database
    new_person = PhoneBook(full_name=person.full_name, phone_number=person.phone_number)
    session.add(new_person)
    session.commit()
    # If the request was succesfull log the person that was added
    logger.info('User: %s was added to the database.', person.full_name)
    # Close the session
    session.close()
    # Return a success message
    return {"message": "Person added successfully"}

@app.put("/PhoneBook/deleteByName")
def delete_by_name(full_name: str, role: str = Depends(authorize)):
    if role != "readwrite":
        logger.info('Unauthorized attempt to access Delete By Name API call')
        raise HTTPException(status_code=403, detail="You are not authorized to access this call")
    # Log that the Delete By Name API call was issued along with the name of the person deleted.
    logger.info('Delete By Name API Call Issued | Name = %s', full_name)
    # Get a new session
    session = Session()
    # Query the person by name in the database
    person = session.query(PhoneBook).filter_by(full_name=full_name).first()
    # If the person does not exist, raise an exception
    if not person:
        session.close()
        logger.info('Person not found in database. No deletions made to database.')
        raise HTTPException(status_code=404, detail="Person not found in the database")
    # Otherwise, delete the person from the database
    session.delete(person)
    session.commit()
    # If the request was succesfull log the person that was deleted
    logger.info('User: %s deleted from database.', person.full_name)
    # Close the session
    session.close()
    # Return a success message
    return {"message": "Person deleted successfully"}

@app.put("/PhoneBook/deleteByNumber")
def delete_by_number(phone_number: str, role: str = Depends(authorize)):
    if role != "readwrite":
        logger.info('Unauthorized attempt to access Delete By Number API call')
        raise HTTPException(status_code=403, detail="You are not authorized to access this call.")
    # Log that the Delete Person API By Number call was issued
    logger.info('Delete By Number API Call Issued | Number = %s', phone_number)
    # Get a new session
    session = Session()
    # Query the person by phone number in the database
    person = session.query(PhoneBook).filter_by(phone_number=phone_number).first()
    # If the person does not exist, raise an exception
    if not person:
        session.close()
        logger.info('Person not found in database. No deletions made to database.')
        raise HTTPException(status_code=404, detail="Person not found in the database")
    # Otherwise, delete the person from the database
    session.delete(person)
    session.commit()
    # If the request was succesful log the person that was deleted
    logger.info('User: %s deleted from database.', person.full_name)
    # Close the session
    session.close()
    # Return a success message
    return {"message": "Person deleted successfully"}