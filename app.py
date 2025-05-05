from flask import Flask, render_template, jsonify
import threading
import time
import requests

app = Flask(__name__)

ESP8266_IP = 'http://192.168.18.61/data'

sensor1_state = 0
sensor2_state = 0
current_signal = {'signal1': 'red', 'signal2': 'red'}

def fetch_sensor_data():
    global sensor1_state, sensor2_state
    while True:
        try:
            response = requests.get(ESP8266_IP)
            if response.status_code == 200:
                data = response.json()
                sensor1_state = data.get('sensor1', 0)
                sensor2_state = data.get('sensor2', 0)
        except Exception as e:
            print("Connection Error:", e)
        time.sleep(1)

def signal_control_loop():
    global current_signal
    while True:
        if sensor1_state and sensor2_state:
            current_signal = {'signal1': 'green', 'signal2': 'red'}
            time.sleep(3)
            current_signal = {'signal1': 'yellow', 'signal2': 'red'}
            time.sleep(0.5)
            current_signal = {'signal1': 'red', 'signal2': 'green'}
            time.sleep(3)
            current_signal = {'signal1': 'red', 'signal2': 'yellow'}
            time.sleep(0.5)
        elif sensor1_state:
            current_signal = {'signal1': 'green', 'signal2': 'red'}
            time.sleep(2)
            current_signal = {'signal1': 'yellow', 'signal2': 'red'}
            time.sleep(0.5)
            current_signal = {'signal1': 'red', 'signal2': 'red'}
        elif sensor2_state:
            current_signal = {'signal1': 'red', 'signal2': 'green'}
            time.sleep(2)
            current_signal = {'signal1': 'red', 'signal2': 'yellow'}
            time.sleep(0.5)
            current_signal = {'signal1': 'red', 'signal2': 'red'}
        else:
            current_signal = {'signal1': 'red', 'signal2': 'red'}
        time.sleep(1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get_signal_data')
def get_signal_data():
    return jsonify(current_signal)

if __name__ == '__main__':
    threading.Thread(target=fetch_sensor_data, daemon=True).start()
    threading.Thread(target=signal_control_loop, daemon=True).start()
    app.run(debug=True, host='0.0.0.0', port=5000)
