# Simple Library Management System (C Project)

This is a modular C-based book tracking system that supports:

- Adding books  
- Listing all books  
- Searching by ID or text  
- Issuing books  
- Returning books  
- Removing books  
- Persistent storage using `library.dat`

---

## 📌 File Structure

library.c → Core book operations
library.h → Function declarations & struct definitions
utils.c → Helper functions (string utilities)
utils.h → Utility function prototypes
main.c → Program entry point
library.dat → Auto-generated binary database file
README.md → Project documentation

yaml
Copy code

---

## 📌 How to Compile

Use GCC:

```bash
gcc main.c library.c utils.c -o library
📌 How to Run
bash
Copy code
./library
📌 Data Persistence
The program automatically saves book data to library.dat
using binary file read/write.

📌 Notes
Supports up to 1000 books

Case-insensitive searching

Self-generating incremental IDs

Fully modular project structure

yaml
Copy code

---

If you want, I can also:

✅ Create a **Makefile**  
✅ Add **error handling improvements**  
✅ Add **colorful UI**  
✅ Add **student login system**  
Just tell me!
