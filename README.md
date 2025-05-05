# 🚦 Smart Traffic Signal System using ESP8266 and Ultrasonic Sensors

This project simulates a smart traffic signal system using an ESP8266 microcontroller and two ultrasonic sensors. It detects vehicles and controls signal lights accordingly, displaying real-time signal status via a Flask web interface.

---

## 📦 Project Features

* Detects vehicles using two HC-SR04 ultrasonic sensors
* ESP8266 serves JSON sensor data over Wi-Fi
* Flask-based frontend displays traffic light status
* Only one signal turns green at a time — the other remains red
* Two ESP8266 operation modes:

  * **Wi-Fi Mode**: Sends real-time JSON data to Python frontend
  * **Local Mode**: Outputs sensor detection to Serial Monitor

---

## 🛠 Hardware Requirements

* 1 × ESP8266 (NodeMCU)
* 2 × HC-SR04 Ultrasonic Sensors
* Jumper wires & Breadboard
* Smartphone or router for hotspot/Wi-Fi

---

## 🧰 Software Requirements

* Python 3.8+
* [`uv`](https://github.com/astral-sh/uv) – A fast Python package manager

To install `uv`:

```bash
curl -Ls https://astral.sh/uv/install.sh | sh
```

---

## 📁 Project Structure

```
traffic-signal-project/
├── .venv/                        # Virtual environment directory (auto-created by uv)
│
├── esp8266_code/                # Folder containing both Arduino sketches
│   ├── esp8266_local_mode.ino   # Local mode: serial print sensor data
│   └── esp8266_wifi_mode.ino    # Wi-Fi mode: sends sensor data via HTTP
│
├── templates/
│   └── index.html               # Web interface with traffic lights
│
├── .gitignore                   # (Optional) Git ignore file
├── .python-version              # (Optional) Python version pinning
├── app.py                       # Flask backend server
├── LICENSE                      # Project license (e.g., MIT)
├── pyproject.toml               # uv-compatible dependency file
├── README.md                    # Project documentation
├── uv.lock                      # uv-generated lock file
---

## 🚀 Getting Started

1. **Flash ESP8266 with Wi-Fi Mode sketch**
   Upload `esp8266_wifi_mode.ino` to your NodeMCU and connect to Wi-Fi.
   Check Serial Monitor for IP address (e.g., `192.168.18.61`).

2. **Install Python dependencies using `uv`**

   ```bash
   uv pip install -r requirements.txt
   ```

3. **Update `app.py` with ESP8266 IP**

   ```python
   ESP8266_IP = "http://192.168.18.61/data"
   ```

4. **Run the Flask App**

   ```bash
   uv install
   uv run app.py
   ```

5. **Open the web interface**
   On your browser, visit:

   ```
   http://<your-laptop-ip>:5000
   ```

---

## ✅ Behavior

* When a vehicle is detected by either sensor, the associated signal turns green.
* The other signal remains red — avoiding both signals turning green at once.
* Yellow is shown for 1 second during transitions.
* Signals alternate priority when both detect vehicles.

---

## 🔍 Troubleshooting

* **404 errors**: Ensure frontend JavaScript is calling `/get_sensor_data`, not `/fetch_sensor_data`.
* **Cannot access from phone**: Replace `127.0.0.1` with your laptop’s IP (e.g., `192.168.18.93`).
* **ESP8266 unreachable**: Make sure it's on the same Wi-Fi/hotspot as your PC.

---

## 📜 License

MIT License. Open for educational and personal use.
