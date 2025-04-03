# RFID Attendance Management System

## 📌 Project Overview
The **RFID Attendance Management System** is an IoT-based solution for managing employee/student attendance using RFID cards. The system integrates:
- **RFID Module** for scanning unique RFID tags.
- **NodeMCU ESP8266** for processing and sending data to the server.
- **PHP-based Web Interface** for managing, recording, displaying, editing, and exporting attendance data.
- **MySQL Database** to store attendance records.
- **Excel Export Feature** to download attendance reports.

## 🛠️ Features
✅ RFID-based attendance marking  
✅ Real-time data transfer using NodeMCU-ESP8266  
✅ Web dashboard to manage employees/students  
✅ Add, edit, and remove devices  
✅ Generate and export attendance reports in Excel  
✅ Admin login system for security  
✅ Live attendance count on the dashboard  
✅ Email notifications on attendance updates  

## 📌 Technology Stack
- **Hardware:** RFID Module, NodeMCU ESP8266
- **Frontend:** HTML, CSS, JavaScript
- **Backend:** PHP, MySQL
- **Database:** MySQL
- **Communication:** HTTP API (between ESP8266 and PHP server)

## 🔧 Installation Guide
### 1️⃣ Setting Up the Hardware
1. Connect the RFID module to the NodeMCU ESP8266:
   - **SDA** → D2 (GPIO4)
   - **SCK** → D5 (GPIO14)
   - **MOSI** → D7 (GPIO13)
   - **MISO** → D6 (GPIO12)
   - **GND** → GND
   - **VCC** → 3.3V
2. Flash the NodeMCU with the provided firmware (`rfid_attendance.ino`).

### 2️⃣ Setting Up the Server
1. Install **XAMPP** (or any PHP & MySQL server).
2. Clone this repository:
   ```bash
   git clone https://github.com/Megatron-XCoder/rfid-attendance-system.git
   ```
3. Move the project folder to `htdocs` (if using XAMPP).
4. Import the `database.sql` file into MySQL.
5. Edit `config.php` to set up your database credentials.
6. Start Apache and MySQL services in XAMPP.

### 3️⃣ Configuring the NodeMCU
1. Edit the `config.h` file in the firmware.
2. Set up WiFi credentials:
   ```c
   #define WIFI_SSID "your-SSID"
   #define WIFI_PASSWORD "your-PASSWORD"
   ```
3. Upload the firmware using **Arduino IDE** or **PlatformIO**.
4. Restart the NodeMCU and check serial monitor logs.

## 🚀 Usage Guide
1. Register employees/students with their RFID tags on the web interface.
2. The RFID reader scans tags and updates the database.
3. View attendance records on the dashboard.
4. Export attendance reports as Excel files.
5. Manage devices, employees, and settings via the admin panel.

## 🏆 Future Improvements
- ✅ SMS/Email notifications for late arrivals.
- ✅ Integration with biometric attendance.
- ✅ Cloud-based database for multi-location access.
- ✅ Mobile app for attendance tracking.

## 📄 License
This project is licensed under the **MIT License**.

## 🤝 Contributing
Pull requests are welcome! Feel free to open an issue or suggest new features.

## 📞 Contact
For any queries, feel free to reach out:
- GitHub: [Megatron-XCoder](https://github.com/Megatron-XCoder)
- Email: your-email@example.com
