from flask import Flask, render_template, request, redirect, url_for
import subprocess
import os
from werkzeug.utils import secure_filename

UPLOAD_FOLDER = 'uploads'
ALLOWED_EXTENSIONS = {'csv'}

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Ensure the uploads directory exists
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/run', methods=['POST'])
def run_c_program():
    file = request.files['csvfile']
    chosen_parameter = request.form['chosenParameter']
    chosen_day = request.form.get('chosenDay', '')
    chosen_period = request.form.get('chosenPeriod', '0')

    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        filepath = os.path.join(app.config['UPLOAD_FOLDER'], filename)
        file.save(filepath)

        # Build the command
        command = ['./cprog', filepath, chosen_parameter]
        if chosen_parameter == '0':
            command.append(chosen_period)
        else:
            command.append(chosen_day)

        try:
            result = subprocess.run(command, capture_output=True, text=True, check=True)
            output = result.stdout
        except subprocess.CalledProcessError as e:
            output = f"An error occurred:\n{e.stderr}"

        return render_template('index.html', output=output)

    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)