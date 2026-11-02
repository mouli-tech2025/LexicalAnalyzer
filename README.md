# Lexical Analyzer

## Compiler Design Project

### Introduction

This project implements a web-based lexical analyzer for the C programming language. It demonstrates the first phase of the compilation process, where source code is scanned and divided into meaningful units called tokens.

The application identifies different types of tokens, such as keywords, identifiers, operators, constants, and special symbols, and displays them along with their corresponding lexemes.

The core lexical analysis is implemented in C, while Python Flask connects the analyzer to the web interface.

### Objectives

- To understand the role of lexical analysis in compiler design.
- To identify and classify tokens from C source code.
- To understand the concepts of tokens and lexemes.
- To implement token recognition using C.
- To demonstrate lexical analysis through a web-based interface.

### Features

- Identifies keywords and identifiers.
- Recognizes operators and constants.
- Detects special symbols.
- Handles comments and whitespace.
- Displays token types and their corresponding lexemes.
- Provides an interactive interface for analyzing C source code.

### Technologies Used

| Technology | Purpose |
|---|---|
| C | Core lexical analysis |
| Python | Backend integration |
| Flask | Backend framework |
| HTML | Webpage structure |
| CSS | Interface styling |
| JavaScript | User interaction and result display |

### Project Structure

```text
LexicalAnalyzer/
│
├── app.py
├── lexer.c
├── templates/
│   └── index.html
│
└── static/
    ├── style.css
    └── script.js
```

### Installation and Execution

**1. Clone the repository**

```bash
git clone https://github.com/YOUR_USERNAME/LexicalAnalyzer.git
cd LexicalAnalyzer
```

**2. Create and activate a virtual environment**

```bash
python3 -m venv venv
source venv/bin/activate
```

**3. Install Flask**

```bash
pip install flask
```

**4. Compile the C program**

```bash
gcc lexer.c -o lexer
```

**5. Run the application**

```bash
python3 app.py
```

**6. Open in your browser**

Visit:

`http://127.0.0.1:5000`

### Working Principle

1. The user enters C source code through the web interface.
2. Flask receives the source code.
3. The source code is passed to the C lexical analyzer.
4. The C program identifies and classifies the tokens.
5. Flask collects the results and sends them to the frontend.
6. The identified tokens are displayed in a structured table.

### Conclusion

This project demonstrates the implementation of lexical analysis using C and its integration with a web interface. It provides a practical understanding of token recognition and the role of lexical analysis as the first phase of a compiler.

### Developed By

**Mouli Biswas**
**Subject:** Compiler Design