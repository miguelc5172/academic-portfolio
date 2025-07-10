import os
from datetime import datetime

os.makedirs("logs", exist_ok=True)
os.makedirs("data", exist_ok=True)

log_filename = f"{datetime.now().strftime('%Y-%m-%d_%H-%M-%S')}_audit_log.log"
log_path = os.path.join("logs", log_filename)

# DO NOT CHANGE. Ensures phonebook.db is made in correct folder for Docker mounting
DATABASE_URL = "sqlite:///./data/phonebook.db"

LOGGING_CONFIG = {
    "version": 1,
    "disable_existing_loggers": False,
    "formatters": {
        "default": {
            "format": "%(asctime)s | %(levelname)s | %(message)s",
        },
    },
    "handlers": {
        "file": {
            "level": "INFO",
            "class": "logging.FileHandler",
            "filename": f"logs/{log_filename}",
            "formatter": "default",
            "mode": "a"
        },
        "console": {
            "level": "INFO",
            "class": "logging.StreamHandler",
            "formatter": "default",
        },
    },
    "root": {
        "level": "INFO",
        "handlers": ["file", "console"],
    },
}

# CAUTION. If these are changed then the tests in Postman won't work unless they are updated.
API_KEYS = {
    "read123": "read",
    "rw456": "readwrite"
}

NAME_PATTERN = r"""^
(?=.{1,100}$)                                   # Length constraint
(?!.*(['’])\1)                                  # No double apostrophes
(?!.*--+)                                       # No double hyphens
(?!.*<.*?>)                                     # No HTML tags
(?!.*\b(?:select|drop|insert)\b)                # SQL injection protection
(?!.*\d)                                        # No digits
(?:                                             
    # First Last OR First Middle Last
    ([A-Z][a-zA-Z'’]{1,30}(?:-[A-Z][a-zA-Z'’]{1,30})?)                # First name (optional hyphen)
    (?:\s+([A-Z][a-zA-Z'’]{1,30}(?:-[A-Z][a-zA-Z'’]{1,30})?))?        # Optional Middle
    (?:\s+([A-Z][a-zA-Z'’]{1,30}(?:-[A-Z][a-zA-Z'’]{1,30})?))?        # Optional Last
    (?!(?:-[A-Za-z'’]+){2,})                                          # No more than one hyphenated part
|
    # Last, First (Optional MI)
    ([A-Z][a-zA-Z'’\-]{1,30}),\s+
    ([A-Z][a-zA-Z'’\-]{1,30})                                         # Allow hyphen in first name
    (?:\s+([A-Z]\.?|[A-Z][a-zA-Z]{1,30}))?                            # Optional MI
|
    # Single name
    ([A-Z][a-zA-Z'’\-]{1,30})
)
$"""

PHONE_PATTERN = r"""^
(?!.*[\\/])                                 # No slashes
(?!.*<.*?>)                                 # No HTML tags
(?!.*ext\b)                                 # No 'ext' extensions
(?!.*\b001\b|\+01\b)                        # Disallow 001 or +01 as North America codes
(?!\b\d{10}\b)                              # Disallow plain 10-digit numbers

(
    \d{5}(\.\d{5})?                         # 5-digit or 5.5-digit internal extensions
    |
    (
        (\+?\d{1,3}|011(\s\d{1,3})?)\s*     # Country code, optional + or 011
    )?
    (\(?\d{2,4}\)?[\s\-\.]?)?               # Optional area code with optional formatting
    \d{3,4}[\s\-\.]?\d{4}                   # Subscriber number
)
$"""