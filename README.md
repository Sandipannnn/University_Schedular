```md
# 🎓 University Timetable Generator (DAA Project)

## 📌 Overview
This project is an **Automated University Timetable Generator** developed using **C (Backtracking Algorithm)** with a simple **HTML frontend**.

It generates a valid timetable by satisfying constraints such as:
- Faculty availability
- Room allocation
- Course scheduling conflicts

The system demonstrates the use of **Design and Analysis of Algorithms (DAA)** concepts, especially **Backtracking and Constraint Satisfaction**.

---

## ⚙️ Tech Stack

- **Backend:** C (Scheduling Engine)
- **Server:** Mongoose HTTP Server (C-based)
- **Frontend:** HTML
- **Algorithm:** Backtracking

---

## 🧠 Key Features

- ✅ Automated timetable generation  
- ✅ Constraint handling (faculty, room conflicts)  
- ✅ Backtracking-based scheduling  
- ✅ Lightweight HTTP server using Mongoose  
- ✅ Simple web interface to view timetable  

---

## 📁 Project Structure

```

project_daa
│
├── backend/
│   ├── timetable_engine.c      # Core scheduling logic (Backtracking)
│   ├── server.c                # HTTP server using Mongoose
│   ├── mongoose.c              # Mongoose source
│   └── mongoose.h              # Mongoose header
│
├── frontend/
│   └── index.html              # UI for timetable display
│
├── data/
│   └── courses.txt             # Input course data
│
├── README.md
└── .gitignore

````

---

## 🚀 How to Run the Project

### Step 1: Compile the Backend

Open terminal in the `backend` folder:

```bash
gcc server.c mongoose.c timetable_engine.c -o server
````

---

### Step 2: Run the Server

```bash
./server
```

On Windows:

```bash
server.exe
```

---

### Step 3: Open the Frontend

Open the file:

```
frontend/index.html
```

Or visit in browser:

```
http://localhost:8000
```

---

## 🔄 How It Works

```
User (HTML Page)
       ↓
HTTP Request
       ↓
Mongoose Server (C)
       ↓
Timetable Engine (Backtracking)
       ↓
Generated Timetable
       ↓
Displayed in Browser
```

---

## 📊 Algorithm Used

### Backtracking Algorithm

The timetable is generated using:

* Recursive assignment of courses
* Checking constraints at each step
* Backtracking when conflicts occur

### Time Complexity (Worst Case)

```
O(C × H × D × S × R)
```

Where:

* C = Courses
* H = Hours per course
* D = Days
* S = Slots
* R = Rooms

---

## 📷 Sample Output

```
MONDAY
Slot 1: DataStructures (Room R1)
Slot 2: OperatingSystems (Room R2)

TUESDAY
Slot 1: ComputerNetworks (Room R1)
```

---

## 🎯 Learning Outcomes

* Understanding of **Backtracking algorithms**
* Practical implementation of **Constraint Satisfaction Problems**
* Integration of **C backend with web frontend**
* Use of **embedded web server (Mongoose)**

---

## 🔧 Future Improvements

* Add database (MySQL / MongoDB)
* Better UI with CSS & JavaScript
* Faculty login system
* Export timetable to PDF
* Dynamic input instead of static file

---

## 👨‍💻 Author

**Sandipan**
B.Tech CSE (DAA Project)

---

## 📜 License

```
This project is for academic purposes.

```


