# 🚀 Flight Information Display System (FIDS)

Simulating the working of airport FIDS using Data Structures.

---

## 📌 Project Overview

This repository contains the implementation of a **Flight Information Display System (FIDS)**, developed as part of the **Data Structures and Applications** course at Malnad College of Engineering. The project uses structured programming to efficiently manage and query flight data.

---

## 💡 Features

### User Account Management:
- Secure login and account creation.
- Password validation with retries for failed attempts.

### Flight Search Options:
- **Direct Flights:** Find flights directly connecting two cities.
- **Indirect Flights:** Search for 1-stop and 2-stop connecting flights.
- **Cheapest Routes:** Identify the most cost-effective flights.

### Comprehensive Data Handling:
- Load and manage flight, city, and user data from CSV files.

### Interactive User Interface:
- User-friendly prompts and menu navigation.

---

## ⚙️ How It Works

### Login/Signup
- Users can log in or create accounts securely.

### Flight Search Options
- Browse all flights.
- Filter flights based on source and destination cities.
- View route details (travel time and fare).

### Flight Suggestions
- Displays all direct and indirect routes with cost calculations.

---

## 🛠 Technologies Used

- **Programming Language:** C
- **Data Structures:** Structures, Arrays
- **File Handling:** CSV Parsing

---

## 📝 **How to Run**  

1. Clone the repository:  
   ```bash
   git clone https://github.com/Rakshak-D/Flightmanagement.git
   ```  
2. Change the directory:  
   ```bash
   cd Flightmanagement 
   ``` 
3. Compile the code:  
   ```bash
   gcc FLIGHT.c -o flight_system
   ```  

4. Run the program:  
   ```bash
   ./flight_system
   ```  

---

## 📂 File Overview

1. **FLIGHT.c**
   - Main program implementing the FIDS logic.
   - Includes user account management, flight search, and route optimization features.

2. **FLIGHTDETAILS.csv**
   - Stores flight information.
   - Format: `FlightID, Source, ArrivalTime, Destination, DepartureTime, FlightTime, Fare`

3. **PLACES.csv**
   - Contains the list of cities served by the system.

4. **Userdetails.csv**
   - Stores user account information: `Username, Email, Password`.

---

## 📈 Example Output

```plaintext
Welcome to Flight Finder
Do you have a travel account with us? [Y/N]: Y

Enter username: Rakshak
Enter password: *********

Welcome Back!! Rakshak

Select an option:
1. View all available flights.
2. View flights from a specific source.
3. View flights from one place to another.
4. Logout

DIRECT FLIGHTS:
Flight ID   Source    Arrival    Destination    Departure   Time   Fare
FL123       BLR       10:30      DEL            13:30       3.00   5000.00

INDIRECT FLIGHTS:
**FLIGHT 1**
Flight ID   Source    Arrival    Destination    Departure   Time   Fare
FL124       BLR       08:00      BOM            10:00       2.00   2000.00
**FLIGHT 2**
Flight ID   Source    Arrival    Destination    Departure   Time   Fare
FL125       BOM       12:00      DEL            14:00       2.00   2500.00

Cheapest Indirect Flight:
Checkpoints: BLR -> BOM -> DEL
Fare: Rs. 4500.00
```

---

## 🧑‍💻 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository.
2. Create a new branch (`feature/your-feature-name`).
3. Commit your changes.
4. Submit a pull request.

---

## 📧 Contact

For queries or suggestions, feel free to reach out:

- **Email:** rakshakmce@gmail.com
- **GitHub:** [@Rakshak-D](https://github.com/Rakshak-D)

---
## ✨ **Contributors**  
- **Rakshak D** - [@Rakshak-D](https://github.com/Rakshak-D)
- **Shesha Prasad H** - [@Shesha-Prasad-H](https://github.com/Shesha2705)
- **Max!!** - [@dizzedbliss](https://github.com/dizziedbliss)
---
Thank you for visiting! ✈️ Happy coding!
