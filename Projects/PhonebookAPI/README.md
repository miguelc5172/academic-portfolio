# Secure Phonebook API

## 📘 Overview

The **Secure Phonebook API** is a REST API built with **FastAPI** that
provides a secure and validated interface for managing phonebook
contacts.
This project emphasizes **input validation**, **role-based access
control**, and **audit logging** for accountability.

For deeper discussion on design decisions, see the report:

📄 [*Cervantes Input Validation Report.pdf*](https://github.com/miguelc5172/academic-portfolio/blob/main/Projects/PhonebookAPI/Cervantes%20Input%20Validation%20Report.pdf)

------------------------------------------------------------------------

## 🚀 Features

-   🔑 **Role-based authentication** using API keys (`read` vs
    `readwrite`)
-   📱 CRUD-like operations for managing phonebook contacts
-   🛡️ Strong **input validation** using regular expressions for names
    and phone numbers
-   📜 **Audit logging** of every request for accountability
-   🐳 Dockerized for reproducible deployments
-   🧪 Integration tested with Postman

------------------------------------------------------------------------

## 🛠️ Tech Stack

-   **Backend:** FastAPI (Python)
-   **Database:** SQLite (via SQLAlchemy)
-   **Authentication:** API key tokens with roles (read / readwrite)
-   **Deployment:** Docker
-   **Testing:** Postman

------------------------------------------------------------------------

## 📂 Example Endpoints

``` http
GET    /PhoneBook/list           # List all phonebook entries (requires read/readwrite key)
POST   /PhoneBook/add            # Add a new entry (requires readwrite key)
PUT    /PhoneBook/deleteByName   # Delete an entry by full name (requires readwrite key)
PUT    /PhoneBook/deleteByNumber # Delete an entry by phone number (requires readwrite key)
```

### 🔑 Authorization

All requests must include a **Bearer token** in the header:

``` http
Authorization: Bearer <API_KEY>
```

-   `read` → can only list contacts
-   `readwrite` → can list, add, and delete contacts

------------------------------------------------------------------------

## 📖 Usage

### Run locally

``` bash
uvicorn app:app --reload
```

### Run with Docker

``` bash
docker build -t phonebook-api .
docker run -p 8000:8000 phonebook-api
```

------------------------------------------------------------------------

## 🎯 Learning Outcomes

-   Implemented a **secure REST API** using FastAPI.
-   Learned to **Dockerize applications** for portability and
    persistence.
-   Practiced **role-based authentication and authorization**.
-   Strengthened **input validation** skills with regex (see *Cervantes
    Input Validation Report.pdf*).
-   Integrated **logging and auditing** for monitoring API usage.
