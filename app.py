
from flask import Flask, render_template, request, jsonify
import subprocess

app = Flask(__name__)

@app.route("/")
def home():
    return render_template("index.html")


@app.route("/analyze", methods=["POST"])
def analyze():

    data = request.get_json()
    source_code = data.get("code", "")

    if not source_code.strip():
        return jsonify({"error": "Please enter some C code."}), 400

    try:
        result = subprocess.run(
            ["./lexer"],
            input=source_code,
            capture_output=True,
            text=True,
            timeout=5
        )

        if result.returncode != 0:
            return jsonify({"error": "Lexical analysis failed."}), 500

        tokens = []

        for line in result.stdout.splitlines():
            parts = line.split("\t", 1)

            if len(parts) == 2:
                tokens.append({
                    "type": parts[0],
                    "lexeme": parts[1]
                })

        return jsonify({"tokens": tokens})

    except subprocess.TimeoutExpired:
        return jsonify({"error": "Analysis timed out."}), 408

    except FileNotFoundError:
        return jsonify({"error": "C analyzer not compiled. Run gcc lexer.c -o lexer."}), 500

    except Exception:
        return jsonify({"error": "Something went wrong during analysis."}), 500


if __name__ == "__main__":
    app.run(debug=True)
