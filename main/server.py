

from flask import Flask, request, jsonify
from flask_cors import CORS
import subprocess
import os
import tempfile
import uuid

app = Flask(__name__)
CORS(app)  # Enable CORS for frontend communication

# Path to compiler executable
COMPILER_PATH = os.path.join(os.path.dirname(__file__), 'build', 'compiler.exe')

@app.route('/api/compile', methods=['POST'])
def compile_code():
 
    try:
        # Get code from request
        code = request.form.get('code', '')
        if not code:
            code = request.json.get('code', '') if request.is_json else ''
        
        if not code:
            return jsonify({
                'success': False,
                'assembly': '',
                'scope_tree': '',
                'errors': 'No code provided'
            }), 400
        
        # Create temporary directory for this compilation
        temp_dir = tempfile.mkdtemp()
        input_file = os.path.join(temp_dir, 'input.c')
        
        # Write code to temp file
        with open(input_file, 'w', encoding='utf-8') as f:
            f.write(code)
        
        # Run compiler
        try:
            result = subprocess.run(
                [COMPILER_PATH, input_file],
                capture_output=True,
                text=True,
                timeout=30,
                cwd=temp_dir
            )
        except subprocess.TimeoutExpired:
            return jsonify({
                'success': False,
                'assembly': '',
                'scope_tree': '',
                'errors': 'Compilation timed out'
            }), 500
        except FileNotFoundError:
            return jsonify({
                'success': False,
                'assembly': '',
                'scope_tree': '',
                'errors': f'Compiler not found at {COMPILER_PATH}'
            }), 500
        
        # Read output files
        assembly = ''
        scope_tree = ''
        errors = ''
        
        quadruples_file = os.path.join(temp_dir, 'quadruples.txt')
        output_file = os.path.join(temp_dir, 'output.txt')
        error_file = os.path.join(temp_dir, 'error.txt')
        
        if os.path.exists(quadruples_file):
            with open(quadruples_file, 'r', encoding='utf-8') as f:
                assembly = f.read()
        
        if os.path.exists(output_file):
            with open(output_file, 'r', encoding='utf-8') as f:
                scope_tree = f.read()
        
        if os.path.exists(error_file):
            with open(error_file, 'r', encoding='utf-8') as f:
                errors = f.read()
        
        # Add stderr to errors if present
        if result.stderr:
            errors = result.stderr + '\n' + errors if errors else result.stderr
        
        # Cleanup temp files
        try:
            for f in os.listdir(temp_dir):
                os.remove(os.path.join(temp_dir, f))
            os.rmdir(temp_dir)
        except:
            pass  # Ignore cleanup errors
        
        success = result.returncode == 0 and 'error' not in errors.lower()
        
        return jsonify({
            'success': success,
            'assembly': assembly,
            'scope_tree': scope_tree,
            'errors': errors if errors.strip() else ('No errors' if success else 'Compilation failed'),
            'stdout': result.stdout
        })
        
    except Exception as e:
        return jsonify({
            'success': False,
            'assembly': '',
            'scope_tree': '',
            'errors': f'Server error: {str(e)}'
        }), 500


@app.route('/api/health', methods=['GET'])
def health_check():
    """Health check endpoint"""
    compiler_exists = os.path.exists(COMPILER_PATH)
    return jsonify({
        'status': 'ok',
        'compiler_found': compiler_exists,
        'compiler_path': COMPILER_PATH
    })


if __name__ == '__main__':
    print(f"Starting Compiler API Server...")
    print(f"Compiler path: {COMPILER_PATH}")
    print(f"Compiler exists: {os.path.exists(COMPILER_PATH)}")
    app.run(host='0.0.0.0', port=5000, debug=True)
