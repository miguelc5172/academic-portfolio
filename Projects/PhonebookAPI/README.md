# Secure Phonebook API

## 📘 Overview
The **Secure Phonebook API** is a REST API built with **FastAPI** that provides a secure and validated interface for managing phonebook contacts.  
This project emphasizes **input validation**, **authentication**, and **data persistence**.

For deeper discussion on design decisions, see the report:  
📄 *Cervantes Input Validation Report.pdf*

---

## 🚀 Features
- 🔐 Authentication with JWT tokens  
- 📱 CRUD operations on phonebook contacts  
- 🛡️ Input validation to prevent injection and malformed data  
- 🐳 Dockerized for reproducible deployments  
- 🧪 Integration tested with Postman  

---

## 🛠️ Tech Stack
- **Backend:** FastAPI (Python)  
- **Database:** SQLite / Supabase  
- **Authentication:** JWT  
- **Deployment:** Docker  
- **Testing:** Postman  

---

## 📂 Example Endpoints
```http
POST /auth/register   # Register a new user
POST /auth/login      # Login and receive JWT
GET  /contacts/       # Get all contacts (requires token)
POST /contacts/       # Add a new contact
PUT  /contacts/{id}   # Update a contact
DELETE /contacts/{id} # Delete a contact
```

---

## 📖 Usage
### Run locally
```bash
uvicorn app.main:app --reload
```

### Run with Docker
```bash
docker build -t phonebook-api .
docker run -p 8000:8000 phonebook-api
```

---

## 🎯 Learning Outcomes
- Implemented a **secure REST API** using FastAPI.  
- Learned to **Dockerize applications** for portability.  
- Practiced **authentication/authorization** best practices.  
- Developed strong **input validation skills** (see *Cervantes Input Validation Report.pdf* for details).  
