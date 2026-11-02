
async function analyzeCode() {
    const code = document.getElementById("codeInput").value;
    const resultBody = document.getElementById("resultBody");

    if (!code.trim()) {
        alert("Please enter some C code!");
        return;
    }

    resultBody.innerHTML = "<tr><td colspan='2'>Analyzing...</td></tr>";

    try {
        const response = await fetch("/analyze", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({ code: code })
        });

        const data = await response.json();

        if (!response.ok) {
            throw new Error(data.error || "Analysis failed");
        }

        resultBody.innerHTML = "";

        data.tokens.forEach(token => {
            const row = document.createElement("tr");

            const typeCell = document.createElement("td");
            typeCell.textContent = token.type;

            const lexemeCell = document.createElement("td");
            lexemeCell.textContent = token.lexeme;

            row.appendChild(typeCell);
            row.appendChild(lexemeCell);

            resultBody.appendChild(row);
        });

        document.getElementById("totalTokens").textContent =
            data.tokens.length;

        if (data.tokens.length === 0) {
            resultBody.innerHTML =
                "<tr><td colspan='2'>No tokens found.</td></tr>";
        }

    } catch (error) {
        resultBody.innerHTML =
            `<tr><td colspan="2">${error.message}</td></tr>`;
    }
}

function clearCode() {
    document.getElementById("codeInput").value = "";
    document.getElementById("totalTokens").textContent = "0";

    document.getElementById("resultBody").innerHTML =
        "<tr><td colspan='2'>No analysis performed yet.</td></tr>";
}
