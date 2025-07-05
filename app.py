from flask import Flask, render_template, request, redirect, url_for
import subprocess
import os
from werkzeug.utils import secure_filename
import glob

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'csv'}

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

@app.route('/')
def index(): 
    list_of_files = glob.glob(os.path.join(app.config['UPLOAD_FOLDER'], '*.csv'))
    if list_of_files:
        latest_file = max(list_of_files, key=os.path.getctime)
        if latest_file:
            fileUploaded = True 
    else:
        fileUploaded = False   
    return render_template(
        'index.html',
        fileUploaded=fileUploaded
    )

@app.route('/save_file', methods=['POST'])
def save_file():
    file = request.files['csvfile']
    if file:
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)
        return render_template(
            'index.html',
            fileUploaded=True
)
    return "Invalid file", 400

@app.route('/run', methods=['POST'])
def run_program():
    
    list_of_files = glob.glob(os.path.join(app.config['UPLOAD_FOLDER'], '*.csv'))
    if not list_of_files:
        return "No uploaded CSV file found", 400

    latest_file = max(list_of_files, key=os.path.getctime)
    if latest_file:
        fileUploaded = True

    chosen_parameter = request.form['chosenParameter']
    chosen_day = request.form.get('chosenDay', '')
    chosen_period = request.form.get('chosenPeriod', '0')

    command = ['./cprog', latest_file, chosen_parameter, chosen_day, chosen_period]

    try:
        result = subprocess.run(command, capture_output=True, text=True, check=True)
        output = result.stdout.strip()
        total_cost, cost_per_hour = output.split(":", 1)
    except subprocess.CalledProcessError as e:
        return f"""
        Error running C program:
        Return Code: {e.returncode}
        Command: {e.cmd}
        Stdout: {e.stdout}
        Stderr: {e.stderr}
        """, 500
    except Exception as e:
        return f"Unexpected error:\n{str(e)}", 500

    return render_template(
        'index.html',
        output=output,
        total_cost=total_cost.strip(),
        cost_per_hour=cost_per_hour.strip(),
        fileUploaded=fileUploaded
)

if __name__ == '__main__':
    app.run(debug=True)